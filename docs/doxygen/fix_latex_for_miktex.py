#!/usr/bin/env python3
"""
Post-process doxygen-generated LaTeX files for MiKTeX/LuaLaTeX compatibility.

Three problems are fixed:
1. doxygen.sty: replace unmaintained tabu/longtabu packages with ltablex+longtable.
2. Generated .tex files: convert bare longtabu environments to longtable (with
   p{} columns) and remove blank lines inside tabular environments.
3. refman.tex: force loading current array.sty instead of the 2016 rollback.
   Modern LuaHBTeX defines \\requestedLaTeXdate=0, which triggers the else branch
   in doxygen 1.9.8's refman.tex, loading array.sty rolled back to 2016-10-06.
   The old v2.4d array.sty is incompatible with ltablex+longtable on modern TeX.

Usage:
    python3 fix_latex_for_miktex.py <latex_output_dir>

Example:
    python3 fix_latex_for_miktex.py build/hdf5lib_docs/latex
"""

import os
import re
import sys

# ---------------------------------------------------------------------------
# The replacement block for doxygen.sty's tabu_doxygen section
# ---------------------------------------------------------------------------

# Original 3 lines in doxygen 1.9.8's generated doxygen.sty:
_TABU_ORIG = (
    r'\RequirePackage{longtable_doxygen}' + '\n'
    r'\RequirePackage{tabu_doxygen}' + '\n'
    r'\RequirePackage{fancyvrb}' + '\n'
    r'\RequirePackage{tabularx}'
)

# Replacement: longtable + ltablex (ltablex globally redefines \begin{tabularx} to
# use longtable internally).  doxygen.sty environments (DoxyParams, DoxyFields,
# DoxyEnumFields) use \begin{tabularx} together with longtable header commands
# (\endfirsthead, \endhead) — these only work correctly when tabularx IS longtable,
# i.e. with ltablex.  Standard tabularx ignores those header commands and corrupts
# alignment state ("Missing # in alignment preamble").
#
# Nested tabularx inside table cells (emitted by doxygen 1.9.8) is handled by
# fix_nested_tabularx, which converts them to plain \begin{tabular} before ltablex
# can turn them into nested longtable (unsupported by LaTeX).
#
# \insert@pcolumn compatibility shim.
#
# array.sty >= 2.6a (2023-10-02) moved the p-column cell-content placeholder
# (\@sharp) out of the preamble template and into a hook called \insert@pcolumn.
# array.sty >= ~2.6b (2024+) defines \insert@pcolumn itself.
# longtable >= 4.20 (2023-12-22) also defines \insert@pcolumn (for footnote
# collection in longtable p-columns).
#
# MiKTeX on Ubuntu noble can ship the transitional array.sty 2.6a that CALLS
# \insert@pcolumn but does NOT define it, while longtable is still < 4.20.
# In that window the command is undefined -> "Undefined control sequence" error.
#
# Making it a no-op (\providecommand\insert@pcolumn{}) is WRONG: the hook is
# supposed to supply \@sharp (the alignment # placeholder), so an empty
# definition causes "Missing # inserted in alignment preamble".
#
# The correct minimal definition mirrors what newer array.sty provides:
#   \the@toks \the \@tempcnta \relax   -- before-column hook tokens (>{ } spec)
#   \ignorespaces \@sharp \unskip       -- the cell-content placeholder
#   \the@toks \the \count@ \relax       -- after-column hook tokens
# \the@toks and the \@tempcnta/\count@ registers are set up by array.sty's own
# preamble builder, so they are available whenever \insert@pcolumn is called.
# \UseTaggingSocket calls (PDF accessibility) are omitted here for compatibility.
#
# \providecommand is used so that if array.sty >= 2.6b or longtable >= 4.20
# has already defined \insert@pcolumn, this shim is silently skipped.
_LTABLEX_BLOCK = (
    r'\RequirePackage{longtable}' + '\n'
    r'\RequirePackage{fancyvrb}' + '\n'
    r'\newdimen\tabulinesep \tabulinesep=1mm' + '\n'
    r'% Compatibility shim for transitional array.sty 2.6a (calls \insert@pcolumn' + '\n'
    r'% but does not define it) paired with longtable < 4.20 (also does not define it).' + '\n'
    r'% The shim supplies the \@sharp placeholder plus column-hook tokens.' + '\n'
    r'\providecommand\insert@pcolumn{%' + '\n'
    r'   \the@toks \the \@tempcnta \relax' + '\n'
    r'   \ignorespaces \@sharp \unskip' + '\n'
    r'   \the@toks \the \count@ \relax' + '\n'
    r'}'
)

# ---------------------------------------------------------------------------
# Replacement definitions for doxygen.sty environments that used tabularx.
#
# tabularx's \TX@get@body scans for the LITERAL token \end{tabularx} in the
# input stream.  When tabularx is embedded inside another LaTeX environment
# (e.g. DoxyParams), \TX@get@body never finds \end{tabularx} because it only
# appears in the environment's END CODE, not in user source — causing "File
# ended while scanning use of \TX@get@body" for every such environment.
#
# Fix: replace tabularx with longtable directly, using explicit p{} column
# widths computed from \linewidth.  longtable processes rows token-by-token
# without pre-scanning, so there is no body-collection issue.
# ---------------------------------------------------------------------------

# Width for N equal columns in a full-width table with N+1 vertical rules:
#   W_N = (\linewidth - (N+1)\arrayrulewidth) / N - 2\tabcolsep
def _longtable_width(n):
    return (r'\dimexpr(\linewidth-' + str(n + 1)
            + r'\arrayrulewidth)/' + str(n) + r'-2\tabcolsep\relax')


def _longtable_col_spec(n, first_raggedleft=False):
    """Return a longtable column spec with n equal p{} columns.

    If first_raggedleft is True the first column gets
    >{\raggedleft\arraybackslash}p{W} (the R-column replacement).
    """
    w = _longtable_width(n)
    pcol = r'p{' + w + r'}'
    rcol = r'>{\raggedleft\arraybackslash}p{' + w + r'}'
    cols = [rcol if (first_raggedleft and i == 0) else pcol for i in range(n)]
    return '|' + '|'.join(cols) + '|'


# Environment definitions that replace the tabularx-based versions.
# Each entry: (env_name, orig_block, new_block)
# The orig_block is matched literally in doxygen.sty; new_block is the replacement.

def _doxy_tabular_env(name, col_spec_orig, col_spec_new, ncols, comment=''):
    """Build (orig, new) pair for a 2-part doxygen environment.

    Environments of this form:
        \\newenvironment{name}[1]{%
            \\setlength{\\extrarowheight}{\\tabulinesep}%
            \\par%
            \\begin{tabularx}{\\linewidth}{col_spec_orig}%
            \\multicolumn{ncols}{l}{...#1...}\\\\[1ex]%
            \\hline%
            \\endfirsthead%
            \\multicolumn{ncols}{l}{...#1...}\\\\[1ex]%
            \\hline%
            \\endhead%
        }{%
            \\end{tabularx}%
            \\vspace{6pt}%
        }
    """
    head = (
        r'\multicolumn{' + str(ncols) + r'}{l}'
        r'{\hspace{-6pt}\bfseries\fontseries{bc}\selectfont\color{darkgray} #1}\\[1ex]%'
        + '\n'
        r'    \hline%' + '\n'
    )
    orig_env = (
        r'\newenvironment{' + name + r'}[1]{%' + '\n'
        + r'    \setlength{\extrarowheight}{\tabulinesep}%' + '\n'
        + r'    \par%' + '\n'
        + r'    \begin{tabularx}{\linewidth}{' + col_spec_orig + r'}%' + '\n'
        + r'    ' + head
        + r'    \endfirsthead%' + '\n'
        + r'    ' + head
        + r'    \endhead%' + '\n'
        + r'}{%' + '\n'
        + r'    \end{tabularx}%' + '\n'
        + r'    \vspace{6pt}%' + '\n'
        + r'}'
    )
    new_env = (
        (('% ' + comment + '\n') if comment else '')
        + r'\newenvironment{' + name + r'}[1]{%' + '\n'
        + r'    \setlength{\extrarowheight}{\tabulinesep}%' + '\n'
        + r'    \par%' + '\n'
        + r'    \begin{longtable}{' + col_spec_new + r'}%' + '\n'
        + r'    ' + head
        + r'    \endfirsthead%' + '\n'
        + r'    ' + head
        + r'    \endhead%' + '\n'
        + r'}{%' + '\n'
        + r'    \end{longtable}%' + '\n'
        + r'    \vspace{6pt}%' + '\n'
        + r'}'
    )
    return orig_env, new_env


# Pre-build the replacement table for the simple fixed-column environments.
_TWO_COL_RX_SPEC = _longtable_col_spec(2, first_raggedleft=True)  # |R|X| equiv
_THREE_COL_RXX_SPEC = _longtable_col_spec(3, first_raggedleft=True)  # |R|X|X| equiv
_TWO_COL_RX_SPEC_ENUM = _longtable_col_spec(2, first_raggedleft=True)

_DOXY_ENV_REPLACEMENTS = [
    _doxy_tabular_env('DoxyFields',     '|R|X|X|', _THREE_COL_RXX_SPEC, 3),
    _doxy_tabular_env('DoxyEnumFields', '|R|X|',   _TWO_COL_RX_SPEC,    2),
    _doxy_tabular_env('DoxyRetVals',    '|R|X|',   _TWO_COL_RX_SPEC,    2),
    _doxy_tabular_env('DoxyExceptions', '|R|X|',   _TWO_COL_RX_SPEC,    2),
    _doxy_tabular_env('DoxyTemplParams','|R|X|',   _TWO_COL_RX_SPEC,    2),
]

# DoxyParams is special: variable column count selected by optional arg.
_DOXYPARAMS_TABULARX_ORIG = (
    r'% Used by parameter lists' + '\n'
    r'\newenvironment{DoxyParams}[2][]{%' + '\n'
    r'    \setlength{\extrarowheight}{\tabulinesep}%' + '\n'
    r'    \par%' + '\n'
    r'    \ifthenelse{\equal{#1}{}}%' + '\n'
    r'      {\def\DoxyParamColSpec{|X|X|}}%' + '\n'
    r'    {\ifthenelse{\equal{#1}{1}}%' + '\n'
    r'      {\def\DoxyParamColSpec{|X|X|X|}}%' + '\n'
    r'      {\def\DoxyParamColSpec{|X|X|X|X|}}%' + '\n'
    r'    }%' + '\n'
    r'    \begin{tabularx}{\linewidth}{\DoxyParamColSpec}' + '\n'
    r'    \multicolumn{2}{l}{\hspace{-6pt}\bfseries\fontseries{bc}\selectfont\color{darkgray} #2}\\[1ex]%' + '\n'
    r'    \hline%' + '\n'
    r'    \endfirsthead%' + '\n'
    r'    \multicolumn{2}{l}{\hspace{-6pt}\bfseries\fontseries{bc}\selectfont\color{darkgray} #2}\\[1ex]%' + '\n'
    r'    \hline%' + '\n'
    r'    \endhead%' + '\n'
    r'}{%' + '\n'
    r'    \end{tabularx}%' + '\n'
    r'    \vspace{6pt}%' + '\n'
    r'}'
)

_W2 = _longtable_width(2)
_W3 = _longtable_width(3)
_W4 = _longtable_width(4)

# longtable is used directly inside \ifthenelse branches (safe: longtable does
# not pre-scan its body with TX@get@body, unlike tabularx/ltablex).
# The \begin{longtable}{SPEC} is placed inside the ifthenelse branch so the
# column spec is a literal string — array.sty cannot expand a \def-ed macro
# in the preamble position (it sees the unexpanded token as an illegal column
# type and emits "Illegal pream-token" errors).
_DOXYPARAMS_LONGTABLE_NEW = (
    r'% Used by parameter lists' + '\n'
    r'\newenvironment{DoxyParams}[2][]{%' + '\n'
    r'    \setlength{\extrarowheight}{\tabulinesep}%' + '\n'
    r'    \par%' + '\n'
    r'    \ifthenelse{\equal{#1}{}}%' + '\n'
    r'      {\def\DoxyParamNCols{2}%' + '\n'
    r'       \begin{longtable}{|p{' + _W2 + r'}|p{' + _W2 + r'}|}}%' + '\n'
    r'    {\ifthenelse{\equal{#1}{1}}%' + '\n'
    r'      {\def\DoxyParamNCols{3}%' + '\n'
    r'       \begin{longtable}{|p{' + _W3 + r'}|p{' + _W3 + r'}|p{' + _W3 + r'}|}}%' + '\n'
    r'      {\def\DoxyParamNCols{4}%' + '\n'
    r'       \begin{longtable}{|p{' + _W4 + r'}|p{' + _W4 + r'}|p{' + _W4 + r'}|p{' + _W4 + r'}|}}%' + '\n'
    r'    }%' + '\n'
    r'    \multicolumn{\DoxyParamNCols}{l}{\hspace{-6pt}\bfseries\fontseries{bc}\selectfont\color{darkgray} #2}\\[1ex]%' + '\n'
    r'    \hline%' + '\n'
    r'    \endfirsthead%' + '\n'
    r'    \multicolumn{\DoxyParamNCols}{l}{\hspace{-6pt}\bfseries\fontseries{bc}\selectfont\color{darkgray} #2}\\[1ex]%' + '\n'
    r'    \hline%' + '\n'
    r'    \endhead%' + '\n'
    r'}{%' + '\n'
    r'    \end{longtable}%' + '\n'
    r'    \vspace{6pt}%' + '\n'
    r'}'
)

# TabularC and TabularNC: N equal X columns → longtable with p{W_N} columns
_TABULARC_ORIG = (
    r'\newenvironment{TabularC}[1]%' + '\n'
    r'{\setlength{\extrarowheight}{\tabulinesep}%' + '\n'
    r'\begin{tabularx}{\linewidth}{*#1{|X}|}}%' + '\n'
    r'{\end{tabularx}\par}%'
)
_TABULARC_NEW = (
    r'\newenvironment{TabularC}[1]%' + '\n'
    r'{\setlength{\extrarowheight}{\tabulinesep}%' + '\n'
    r'\begin{longtable}{*{#1}{|p{\dimexpr(\linewidth-(#1+1)\arrayrulewidth)/#1-2\tabcolsep\relax}}|}}%' + '\n'
    r'{\end{longtable}\par}%'
)

_TABULARNCNC_ORIG = (
    r'\newenvironment{TabularNC}[1]%' + '\n'
    r'{\begin{tabularx}{\linewidth}{*#1{|X}|}}%' + '\n'
    r'{\end{tabularx}\par}%'
)
_TABULARNCNC_NEW = (
    r'\newenvironment{TabularNC}[1]%' + '\n'
    r'{\begin{longtable}{*{#1}{|p{\dimexpr(\linewidth-(#1+1)\arrayrulewidth)/#1-2\tabcolsep\relax}}|}}%' + '\n'
    r'{\end{longtable}\par}%'
)


def _convert_tabu_cols(cols):
    """Convert tabu X[-1,...] column spec to tabularx X/R column spec."""
    result = cols.replace('X[-1,r]', 'R')
    result = re.sub(r'X\[-1(?:,[lc])?\]', 'X', result)
    return result


def _convert_tabu_cols_for_longtable(cols):
    """Convert tabu X column spec to longtable p{} column spec.

    Counts the number of X columns (expanding *{N}{...} repetitions) and
    replaces each X with p{W} where W divides \\linewidth equally among
    all X columns, minus space for vertical rules and column separators.
    """
    # Expand *{N}{inner} repetitions (one level deep) to count X columns
    expanded = re.sub(
        r'\*\{(\d+)\}\{([^{}]*)\}',
        lambda m: m.group(2) * int(m.group(1)),
        cols)
    n_x = len(re.findall(r'X(?:\[-1(?:,[lrc])?\])?|\bX\b', expanded))
    if n_x == 0:
        return _convert_tabu_cols(cols)

    # Width = (\linewidth - (n_x+1)*\arrayrulewidth) / n_x - 2*\tabcolsep
    width = (r'\dimexpr(\linewidth - ' + str(n_x + 1) +
             r'\arrayrulewidth)/' + str(n_x) + r' - 2\tabcolsep\relax')

    r_col = '>{\\raggedleft\\arraybackslash}p{' + width + '}'
    p_col = 'p{' + width + '}'
    result = re.sub(r'X\[-1,r\]', lambda m: r_col, cols)
    result = re.sub(r'X\[-1(?:,[lc])?\]', lambda m: p_col, result)
    result = re.sub(r'\bX\b', lambda m: p_col, result)
    return result


def fix_doxygen_sty(path):
    """Replace tabu_doxygen/longtable_doxygen with longtable in doxygen.sty.

    Converts all tabularx-based Doxy environments to longtable with explicit
    p{} column widths.  tabularx is NOT used: its TX@get@body pre-scanner
    cannot locate \\end{tabularx} when it is hidden inside another environment's
    end code, causing "File ended while scanning use of \\TX@get@body" on every
    DoxyParams / DoxyFields / etc. use.
    """
    with open(path, encoding='utf-8') as f:
        content = f.read()

    # Already fully patched: tabu_doxygen gone, longtable present, inline
    # longtable specs in DoxyParams (i.e. no \DoxyParamColSpec macro dereference),
    # and no residual tabularx.
    _fully_patched = (
        r'\RequirePackage{tabu_doxygen}' not in content
        and r'\RequirePackage{longtable}' in content
        and r'\begin{longtable}{\DoxyParamColSpec}' not in content
        and r'\DoxyParamNCols' in content
        and r'\begin{tabularx}' not in content
    )
    if _fully_patched:
        print(f"  {path}: already patched, skipping")
        return

    if r'\RequirePackage{tabu_doxygen}' not in content:
        # Partially patched or unrecognised format - fall through to patch what we can.
        if r'\RequirePackage{longtable}' not in content:
            print(f"  WARNING: {path}: expected tabu_doxygen pattern not found; skipping")
            return

    # ------------------------------------------------------------------
    # Step 1: Replace the tabu_doxygen package block with longtable only.
    # ------------------------------------------------------------------
    if r'\RequirePackage{tabu_doxygen}' in content:
        content = content.replace(_TABU_ORIG, _LTABLEX_BLOCK)
        if r'\RequirePackage{tabu_doxygen}' in content:
            print(f"  WARNING: {path}: tabu_doxygen block did not match exactly; trying line fallback")
            content = content.replace(r'\RequirePackage{longtable_doxygen}',
                                      r'\RequirePackage{longtable}')
            content = content.replace(r'\RequirePackage{tabu_doxygen}',
                                      r'\newdimen\tabulinesep \tabulinesep=1mm')
        # Remove ltablex if it slipped in from a prior partial run
        content = content.replace(r'\RequirePackage{ltablex}' + '\n', '')
        content = content.replace(r'\newcolumntype{R}{>{\raggedleft\arraybackslash}X}' + '\n', '')

    # ------------------------------------------------------------------
    # Step 2: Fix environments that used longtabu* / tabu in doxygen.sty.
    #   \tabulinesep=1mm%  →  \setlength{\extrarowheight}{\tabulinesep}%
    #   longtabu* → longtable (not tabularx — longtable is what we use now)
    # ------------------------------------------------------------------
    content = content.replace(
        r'    \tabulinesep=1mm%',
        r'    \setlength{\extrarowheight}{\tabulinesep}%')

    def longtabu_star_repl(m):
        cols = _convert_tabu_cols_for_longtable(m.group(1))
        return r'\begin{longtable}{' + cols + r'}'

    content = re.sub(
        r'\\begin\{longtabu\*\}spread 0pt \[[lc]\]\{([^}]+)\}',
        longtabu_star_repl,
        content)
    content = content.replace(r'\end{longtabu*}%', r'\end{longtable}%')
    content = content.replace(r'\end{longtabu*}', r'\end{longtable}')

    # Fix TabularC / TabularNC tabu patterns (legacy partial-patch residues)
    content = content.replace(
        '{\n\\tabulinesep=1mm\n',
        '{\n\\setlength{\\extrarowheight}{\\tabulinesep}%\n')
    content = content.replace(
        '{\\tabulinesep=1mm\n',
        '{\\setlength{\\extrarowheight}{\\tabulinesep}%\n')
    content = content.replace(
        '{\\begin{tabu}spread 0pt [l]{*#1{|X[-1]}|}}%',
        '{\\begin{longtable}{*{#1}{|p{\\dimexpr(\\linewidth-(#1+1)\\arrayrulewidth)/#1-2\\tabcolsep\\relax}}|}}%')
    content = content.replace(r'{\end{longtabu*}\par}%', r'{\end{longtable}\par}%')
    content = content.replace(r'{\end{tabu}\par}%', r'{\end{longtable}\par}%')
    # Also fix tabularx residues from prior partial runs
    content = content.replace(r'{\end{tabularx}\par}%', r'{\end{longtable}\par}%')

    # ------------------------------------------------------------------
    # Step 3: Replace all tabularx-based Doxy environments with longtable.
    # ------------------------------------------------------------------
    if _DOXYPARAMS_TABULARX_ORIG in content:
        content = content.replace(_DOXYPARAMS_TABULARX_ORIG, _DOXYPARAMS_LONGTABLE_NEW)
    elif r'\begin{longtable}{\DoxyParamColSpec}' in content:
        # Intermediate state: a prior run of this script already replaced tabularx
        # with longtable but kept the \def\DoxyParamColSpec macro and then called
        # \begin{longtable}{\DoxyParamColSpec}.  array.sty cannot expand the \def-ed
        # macro in the column-spec position → "Illegal pream-token" errors.
        # Fix: match the entire DoxyParams definition and replace it with the new
        # inline-longtable version that puts \begin{longtable}{LITERAL_SPEC} directly
        # inside each \ifthenelse branch.
        _doxyparams_intermediate_re = re.compile(
            r'% Used by parameter lists\n'
            r'\\newenvironment\{DoxyParams\}\[2\]\[\]\{%\n'
            r'.*?'                    # body (any lines)
            r'\\begin\{longtable\}\{\\DoxyParamColSpec\}%\n'
            r'.*?'                    # header rows
            r'\}\{%\n'
            r'    \\end\{longtable\}%\n'
            r'    \\vspace\{6pt\}%\n'
            r'\}',
            re.DOTALL,
        )
        content, n = _doxyparams_intermediate_re.subn(
            lambda _: _DOXYPARAMS_LONGTABLE_NEW, content, count=1)
        if n:
            print(f"  {path}: fixed intermediate DoxyParams (inline longtable specs)")
        else:
            print(f"  WARNING: {path}: DoxyParamColSpec marker found but regex didn't match")

    for orig, new in _DOXY_ENV_REPLACEMENTS:
        if orig in content:
            content = content.replace(orig, new)

    if _TABULARC_ORIG in content:
        content = content.replace(_TABULARC_ORIG, _TABULARC_NEW)

    if _TABULARNCNC_ORIG in content:
        content = content.replace(_TABULARNCNC_ORIG, _TABULARNCNC_NEW)

    # Clean up any remaining tabularx references from partial prior patches
    content = content.replace(r'\RequirePackage{tabularx}' + '\n', '')
    content = content.replace(r'\RequirePackage{ltablex}' + '\n', '')

    with open(path, 'w', encoding='utf-8') as f:
        f.write(content)
    print(f"  {path}: patched (tabu_doxygen -> longtable)")


# ---------------------------------------------------------------------------
# Replace longtabu (without asterisk) in generated .tex files
# ---------------------------------------------------------------------------
# doxygen can emit \begin{longtabu}spread 0pt [c]{COLS} directly in individual
# .tex files (not only via doxygen.sty macros).  After fix_doxygen_sty removes
# the tabu_doxygen package, those bare longtabu calls become undefined.
# Column specs may contain nested braces (e.g. *{2}{|X[-1]|}), so we need a
# regex that handles one level of nesting.
#
# longtable (not tabularx) is used because:
# 1. longtable handles \endfirsthead, \endhead, \endfoot natively — some
#    doxygen-generated tables use these longtable-specific commands.
# 2. ltablex's trial-typesetting phase (used when tabularx is the outer env)
#    can fail with "! Missing } inserted" on complex cell content such as
#    multi-paragraph cells or cells beginning with a scoped group (&{...}).
# 3. The \insert@pcolumn compatibility shim in doxygen.sty (loaded globally)
#    handles older MiKTeX installations that ship transitional array.sty 2.6a
#    (which calls \insert@pcolumn but does not define it).

_BEGIN_LONGTABU_PLAIN_RE = re.compile(
    r'\\begin\{longtabu\}spread 0pt \[[lcrb]\]\{((?:[^{}]|\{[^{}]*\})*)\}'
)

# Match \begin{tabularx}{W}{COLS} where COLS may contain one level of braces.
# Group 1 captures the column specification.
_NESTED_TABULARX_RE = re.compile(
    r'\\begin\{tabularx\}\{[^{}]*\}\{((?:[^{}]|\{[^{}]*\}|\{[^{}]*\{[^{}]*\}[^{}]*\})*)\}'
)

# Track outer longtable depth (longtable is what longtabu becomes after our fix;
# longtabu and tabu are included so the function is correct on un-patched content).
_LONGTABLE_BEGIN = re.compile(r'\\begin\{(?:longtable|longtabu(?:\*)?|tabu)\}')
_LONGTABLE_END = re.compile(r'\\end\{(?:longtable|longtabu(?:\*)?|tabu)\}')

_END_TABULARX_TAG = r'\end{tabularx}'
_END_TABULAR_TAG = r'\end{tabular}'


def _convert_tabularx_cols_to_tabular(cols):
    """Replace tabularx X columns with p{\\linewidth} for use in \\begin{tabular}.

    Inside a longtable p{W} cell, \\linewidth equals W (the column width), so
    p{\\linewidth} fills the available space and wraps text correctly.
    """
    result = re.sub(r'>\{\\raggedleft\\arraybackslash\}X',
                    r'>{\\raggedleft\\arraybackslash}p{\\linewidth}', cols)
    result = re.sub(r'>\{\\raggedright\\arraybackslash\}X',
                    r'>{\\raggedright\\arraybackslash}p{\\linewidth}', result)
    result = re.sub(r'\bX\b', r'p{\\linewidth}', result)
    return result


def _fix_nested_tabularx_in_content(content):
    """Convert \\begin{tabularx} inside longtable cells to plain \\begin{tabular}.

    ltablex globally redefines \\begin{tabularx} to use longtable internally.
    When a tabularx appears inside a longtable cell it creates a nested longtable,
    which is unsupported by LaTeX and causes "Extra alignment tab" compile errors.

    Tracks the depth of longtable environments (which result from our longtabu
    → longtable conversion).  At depth > 0 (inside a longtable), any
    \\begin{tabularx}{W}{COLS} is rewritten to \\begin{tabular}{FIXED_COLS} and
    the corresponding \\end{tabularx} is rewritten to \\end{tabular}.

    X columns in COLS are replaced with p{\\linewidth} so that the inner tabular
    fills the available cell width and wraps text correctly.
    """
    result = []
    depth = 0
    i = 0
    n = len(content)
    end_tabularx_len = len(_END_TABULARX_TAG)

    while i < n:
        if depth > 0:
            # Inside a longtable: convert nested tabularx → tabular.
            # Check this BEFORE the longtable-end check so \begin{tabularx}
            # at depth > 0 is converted rather than treated as a new outer env.
            m_tab = _NESTED_TABULARX_RE.match(content, i)
            if m_tab:
                fixed_cols = _convert_tabularx_cols_to_tabular(m_tab.group(1))
                result.append(r'\begin{tabular}{' + fixed_cols + r'}')
                i = m_tab.end()
                continue
            # Convert matching \end{tabularx} → \end{tabular} (depth unchanged).
            if content[i:i + end_tabularx_len] == _END_TABULARX_TAG:
                result.append(_END_TABULAR_TAG)
                i += end_tabularx_len
                continue
            # Exit longtable → decrement depth.
            m_end = _LONGTABLE_END.match(content, i)
            if m_end:
                result.append(m_end.group())
                i = m_end.end()
                depth -= 1
                continue
        else:
            # Outside longtable: look for longtable begin → increment depth.
            m_begin = _LONGTABLE_BEGIN.match(content, i)
            if m_begin:
                result.append(m_begin.group())
                i = m_begin.end()
                depth += 1
                continue

        result.append(content[i])
        i += 1
    return ''.join(result)


def fix_longtabu_in_tex(path):
    """Replace longtabu (without asterisk) with longtable in a .tex file.

    Converts X columns to p{W} columns with width W computed to distribute
    \\linewidth equally among all X columns, accounting for vertical rules and
    column separators.  \\end{longtabu} is replaced with \\end{longtable}.

    longtable is used instead of tabularx so that:
    - \\endfirsthead / \\endhead / \\endfoot / \\endlastfoot work natively.
    - Multi-paragraph cell content and cells starting with a scoped group
      (&{...}) compile without errors (no ltablex trial-typesetting phase).

    After the longtabu → longtable conversion, any \\begin{tabularx} that
    appears inside a longtable cell is converted to plain \\begin{tabular}
    so that ltablex's global tabularx → longtable rewrite does not create
    nested longtable environments (unsupported by LaTeX).
    """
    with open(path, encoding='utf-8', errors='replace') as f:
        content = f.read()

    if r'\begin{longtabu}' not in content:
        return

    def _longtabu_plain_repl(m):
        cols = _convert_tabu_cols_for_longtable(m.group(1))
        return r'\begin{longtable}{' + cols + r'}'

    new_content = _BEGIN_LONGTABU_PLAIN_RE.sub(_longtabu_plain_repl, content)
    new_content = new_content.replace(r'\end{longtabu}%', r'\end{longtable}%')
    new_content = new_content.replace(r'\end{longtabu}', r'\end{longtable}')

    # Fix nested tabularx inside the newly-created longtable cells
    if r'\begin{tabularx}' in new_content:
        new_content = _fix_nested_tabularx_in_content(new_content)

    if new_content != content:
        with open(path, 'w', encoding='utf-8') as f:
            f.write(new_content)
        print(f"  {os.path.basename(path)}: replaced longtabu with longtable")


# ---------------------------------------------------------------------------
# Remove blank lines inside tabular environments in .tex files
# ---------------------------------------------------------------------------

# Environments that cannot contain blank lines (a blank line ends a paragraph)
_TABULAR_ENVS = [
    'tabularx', 'longtabu', r'longtabu\*', 'tabu', 'longtable',
    'tabular', r'tabular\*',
]

_BEGIN_TABULAR = re.compile(
    r'\\begin\{(?:' + '|'.join(_TABULAR_ENVS) + r')\}'
)
_END_TABULAR = re.compile(
    r'\\end\{(?:' + '|'.join(_TABULAR_ENVS) + r')\}'
)


def fix_blank_lines(path):
    """Remove blank lines inside tabular environments in a .tex file."""
    with open(path, encoding='utf-8', errors='replace') as f:
        lines = f.readlines()

    depth = 0
    removed = 0
    result = []

    for line in lines:
        if _BEGIN_TABULAR.search(line):
            depth += 1
        if depth > 0 and line.strip() == '':
            removed += 1
            continue  # drop blank line inside a tabular env
        result.append(line)
        if _END_TABULAR.search(line):
            depth = max(0, depth - 1)

    if removed:
        with open(path, 'w', encoding='utf-8') as f:
            f.writelines(result)
        print(f"  {os.path.basename(path)}: removed {removed} blank lines in tabular envs")


# ---------------------------------------------------------------------------
# Fix refman.tex: force current array.sty (not the 2016 rollback)
# ---------------------------------------------------------------------------
#
# doxygen 1.9.8 generates refman.tex with this conditional:
#
#   \ifx\requestedLaTeXdate\undefined
#     \usepackage{array}
#   \else
#     \usepackage{array}[=2016-10-06]
#   \fi
#
# The intent was: use old array.sty only when an explicit date rollback has
# been requested.  However, modern LuaHBTeX (MiKTeX 26.x) defines
# \requestedLaTeXdate to 0 (not \undefined), so the \else branch fires and
# loads the ancient array.sty v2.4d from 2016.  That old version is
# incompatible with ltablex + longtable on current LaTeX:
# - The p{W} column internals differ, causing "! Missing } inserted" errors
#   when longtable rows are processed inside an ltablex-rewritten environment.
#
# Fix: unconditionally load the current array.sty.  Since we replace tabu
# (the original motivation for the rollback workaround) with ltablex, the
# old array.sty compatibility shim is no longer needed.

_ARRAY_ROLLBACK_ORIG = (
    r'  \ifx\requestedLaTeXdate\undefined' + '\n'
    r'    \usepackage{array}' + '\n'
    r'  \else' + '\n'
    r'    \usepackage{array}[=2016-10-06]' + '\n'
    r'  \fi'
)

_ARRAY_ROLLBACK_FIXED = r'  \usepackage{array}'


# Doxygen 1.9.8 emits \chapter{...}\n\input{NAME} for index sections even when
# the corresponding NAME.tex is not generated (e.g. for C projects with no
# classes, no namespaces, no concepts).  We replace each such pair with a
# conditional include so that lualatex doesn't abort on a missing file.
#
# Format: (chapter_title, input_basename)
_OPTIONAL_INDEX_CHAPTERS = [
    ('Topic Index', 'topics'),
    ('Data Type Index', 'annotated'),
    ('File Index', 'files'),
    ('Namespace Index', 'namespaces'),
    ('Module Index', 'modules'),
    ('Class Hierarchy', 'hierarchy'),
    ('Page Index', 'pages'),
    ('Directory Index', 'dirs'),
]

# Regex that matches \chapter{TITLE}\n\input{BASENAME} for any of the above
_INDEX_CHAPTER_RE = re.compile(
    r'(\\chapter\{(' + '|'.join(re.escape(t) for t, _ in _OPTIONAL_INDEX_CHAPTERS) +
    r')\}\s*\n\s*\\input\{(\w+)\})',
    re.MULTILINE,
)

# Build lookup: chapter title -> expected basename
_CHAPTER_TO_BASENAME = {t: b for t, b in _OPTIONAL_INDEX_CHAPTERS}


def _make_index_chapters_conditional(content, latex_dir):
    """Wrap \\chapter{...}\\input{NAME} pairs in \\IfFileExists when NAME.tex is absent."""

    def _repl(m):
        title = m.group(2)
        basename = m.group(3)
        tex_path = os.path.join(latex_dir, basename + '.tex')
        if os.path.exists(tex_path):
            return m.group(0)  # file present – leave unchanged
        expected = _CHAPTER_TO_BASENAME.get(title)
        if expected and expected != basename:
            return m.group(0)  # unexpected basename mismatch – leave unchanged
        return (r'\IfFileExists{' + basename + r'.tex}{\chapter{' + title +
                r'}\input{' + basename + r'}}{}')

    new_content, n = _INDEX_CHAPTER_RE.subn(_repl, content)
    return new_content, n


def fix_refman_tex(path, latex_dir=None):
    """Fix refman.tex:
    1. Force current array.sty (remove the 2016 rollback).
    2. Make \\chapter{...}\\input{NAME} pairs conditional for absent index files.
    """
    if latex_dir is None:
        latex_dir = os.path.dirname(path)

    with open(path, encoding='utf-8') as f:
        content = f.read()

    changed = False

    if _ARRAY_ROLLBACK_ORIG in content:
        content = content.replace(_ARRAY_ROLLBACK_ORIG, _ARRAY_ROLLBACK_FIXED)
        changed = True
        print(f"  {path}: patched (array rollback removed)")
    elif r'array}[=2016-10-06]' in content:
        print(f"  WARNING: {path}: array rollback pattern not matched exactly; skipping")

    new_content, n_replaced = _make_index_chapters_conditional(content, latex_dir)
    if n_replaced:
        content = new_content
        changed = True
        print(f"  {path}: patched ({n_replaced} optional index chapter(s) made conditional)")

    if changed:
        with open(path, 'w', encoding='utf-8') as f:
            f.write(content)


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main():
    if len(sys.argv) != 2:
        print(__doc__)
        sys.exit(1)

    latex_dir = sys.argv[1]
    if not os.path.isdir(latex_dir):
        print(f"ERROR: not a directory: {latex_dir}")
        sys.exit(1)

    print(f"Processing LaTeX directory: {latex_dir}")

    # 1. Fix doxygen.sty
    sty_path = os.path.join(latex_dir, 'doxygen.sty')
    if os.path.exists(sty_path):
        fix_doxygen_sty(sty_path)
    else:
        print(f"  WARNING: doxygen.sty not found in {latex_dir}")

    # 2. Fix refman.tex: remove the old array.sty rollback workaround
    refman_path = os.path.join(latex_dir, 'refman.tex')
    if os.path.exists(refman_path):
        fix_refman_tex(refman_path, latex_dir)
    else:
        print(f"  WARNING: refman.tex not found in {latex_dir}")

    # 3. Fix longtabu (without asterisk) in .tex files, then remove blank lines
    tex_files = sorted(f for f in os.listdir(latex_dir) if f.endswith('.tex'))
    print(f"Checking {len(tex_files)} .tex files for longtabu and blank lines...")
    for fname in tex_files:
        fpath = os.path.join(latex_dir, fname)
        fix_longtabu_in_tex(fpath)
        fix_blank_lines(fpath)

    print("Done.")


if __name__ == '__main__':
    main()
