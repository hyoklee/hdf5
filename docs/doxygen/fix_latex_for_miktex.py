#!/usr/bin/env python3
"""
Post-process doxygen-generated LaTeX files for MiKTeX/LuaLaTeX compatibility.

Two problems are fixed:
1. doxygen.sty: replace unmaintained tabu/longtabu packages with ltablex.
2. Generated .tex files: remove blank lines inside tabular environments
   (blank lines in tabularx/longtabu/tabu bodies cause TeX errors).

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

# Replacement: standard longtable + tabularx (no ltablex).
# Using standard tabularx avoids ltablex's global redefinition of \begin{tabularx}
# to longtable internals.  doxygen.sty environments (DoxyItemize, DoxyEnumerate,
# ...) use \begin{tabularx} which produces a single-page table — acceptable for
# list items. Top-level longtabu tables in .tex files are converted to
# \begin{tabularx}{\linewidth}{X cols} (see fix_longtabu_in_tex below).
#
# \insert@pcolumn compatibility shim: newer array.sty generates \insert@pcolumn
# in the p-column preamble (called from \@endpbox).  This macro is defined by
# longtable >=4.20 (2023-12-22) but may be absent in MiKTeX installations that
# ship an earlier longtable.  \providecommand defines it as a no-op only when
# absent, so newer installations use the real definition unchanged.
_STD_TABULARX_BLOCK = (
    r'\RequirePackage{longtable}' + '\n'
    r'\RequirePackage{tabularx}' + '\n'
    r'\RequirePackage{fancyvrb}' + '\n'
    r'\newcolumntype{R}{>{\raggedleft\arraybackslash}X}' + '\n'
    r'\newdimen\tabulinesep \tabulinesep=1mm' + '\n'
    r'% Compatibility shim: defined by longtable >=4.20; no-op for older installs.' + '\n'
    r'\providecommand\insert@pcolumn{}'
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
    """Replace tabu_doxygen/longtable_doxygen with standard tabularx+longtable in doxygen.sty."""
    with open(path, encoding='utf-8') as f:
        content = f.read()

    if r'\RequirePackage{longtable}' in content and r'\RequirePackage{tabu_doxygen}' not in content:
        print(f"  {path}: already patched, skipping")
        return

    if r'\RequirePackage{tabu_doxygen}' not in content:
        print(f"  WARNING: {path}: expected tabu_doxygen pattern not found; skipping")
        return

    # 1. Replace the tabu_doxygen packages with standard tabularx + longtable
    content = content.replace(_TABU_ORIG, _STD_TABULARX_BLOCK)
    if r'\RequirePackage{tabu_doxygen}' in content:
        print(f"  WARNING: {path}: replacement did not match exactly; trying fallback")
        # Fallback: replace line by line
        content = content.replace(
            r'\RequirePackage{longtable_doxygen}', r'\RequirePackage{longtable}')
        content = content.replace(
            r'\RequirePackage{tabu_doxygen}',
            r'\newcolumntype{R}{>{\raggedleft\arraybackslash}X}' + '\n'
            r'\newdimen\tabulinesep \tabulinesep=1mm')

    # 2. Fix environments that use longtabu* / tabu.
    #    Replace internal \tabulinesep assignment and convert longtabu* to standard
    #    \begin{tabularx}{\linewidth}{COLS}...\end{tabularx} form.
    content = content.replace(
        r'    \tabulinesep=1mm%',
        r'    \setlength{\extrarowheight}{\tabulinesep}%')

    # Replace \begin{longtabu*}spread 0pt [l|c]{...} → \begin{tabularx}{\linewidth}{...}
    def longtabu_repl(m):
        cols = _convert_tabu_cols(m.group(1))
        return r'\begin{tabularx}{\linewidth}{' + cols + r'}'

    content = re.sub(
        r'\\begin\{longtabu\*\}spread 0pt \[[lc]\]\{([^}]+)\}',
        longtabu_repl,
        content)
    content = content.replace(r'\end{longtabu*}%', r'\end{tabularx}%')
    content = content.replace(r'\end{longtabu*}', r'\end{tabularx}')

    # Fix TabularC: {\tabulinesep=1mm  (no trailing %)
    content = content.replace(
        '{\n\\tabulinesep=1mm\n',
        '{\n\\setlength{\\extrarowheight}{\\tabulinesep}%\n')
    content = content.replace(
        '{\\tabulinesep=1mm\n',
        '{\\setlength{\\extrarowheight}{\\tabulinesep}%\n')

    # Fix TabularNC: {\begin{tabu}spread 0pt [l]{*#1{|X[-1]}|}}%
    content = content.replace(
        '{\\begin{tabu}spread 0pt [l]{*#1{|X[-1]}|}}%',
        '{\\begin{tabularx}{\\linewidth}{*#1{|X}|}}%')
    content = content.replace(
        '{\\end{longtabu*}\\par}%',
        '{\\end{tabularx}\\par}%')
    content = content.replace(
        '{\\end{tabu}\\par}%',
        '{\\end{tabularx}\\par}%')

    with open(path, 'w', encoding='utf-8') as f:
        f.write(content)
    print(f"  {path}: patched (tabu_doxygen -> standard tabularx+longtable)")


# ---------------------------------------------------------------------------
# Replace longtabu (without asterisk) in generated .tex files
# ---------------------------------------------------------------------------
# doxygen can emit \begin{longtabu}spread 0pt [c]{COLS} directly in individual
# .tex files (not only via doxygen.sty macros).  After fix_doxygen_sty removes
# the tabu_doxygen package, those bare longtabu calls become undefined.
# Column specs may contain nested braces (e.g. *{2}{|X[-1]|}), so we need a
# regex that handles one level of nesting.
# Standard tabularx is used (not longtable with p{} columns) to avoid a
# MiKTeX longtable/array package version mismatch (\insert@pcolumn undefined).

_BEGIN_LONGTABU_PLAIN_RE = re.compile(
    r'\\begin\{longtabu\}spread 0pt \[[lcrb]\]\{((?:[^{}]|\{[^{}]*\})*)\}'
)


def fix_longtabu_in_tex(path):
    """Replace longtabu (without asterisk) with tabularx in a .tex file.

    Uses standard \\begin{tabularx}{\\linewidth}{COLS}...\\end{tabularx}, keeping
    X column types so tabularx computes column widths automatically.

    Standard tabularx (not longtable) avoids the MiKTeX longtable/array package
    version mismatch that causes '\\insert@pcolumn undefined' when using p{}
    columns in longtable with certain MiKTeX installations.  Standard tabularx
    is also safe to nest inside table cells (unlike longtable).
    """
    with open(path, encoding='utf-8', errors='replace') as f:
        content = f.read()

    if r'\begin{longtabu}' not in content:
        return

    def _longtabu_plain_repl(m):
        cols = _convert_tabu_cols(m.group(1))
        return r'\begin{tabularx}{\linewidth}{' + cols + r'}'

    new_content = _BEGIN_LONGTABU_PLAIN_RE.sub(_longtabu_plain_repl, content)
    new_content = new_content.replace(r'\end{longtabu}%', r'\end{tabularx}%')
    new_content = new_content.replace(r'\end{longtabu}', r'\end{tabularx}')

    if new_content != content:
        with open(path, 'w', encoding='utf-8') as f:
            f.write(new_content)
        print(f"  {os.path.basename(path)}: replaced longtabu with tabularx")


# ---------------------------------------------------------------------------
# Convert tabularx nested inside table cells to plain tabular
# ---------------------------------------------------------------------------
# doxygen 1.9.8 emits {\begin{tabularx}{\linewidth}{COLS} inside longtabu
# table cells (after &{ or similar).  After fix_longtabu_in_tex converts the
# outer longtabu → tabularx, the inner {\begin{tabularx} would be nested
# tabularx.  Standard tabularx supports nesting (it re-measures from scratch),
# but converting to plain tabular with X→l is safer and simpler.
# The matching \end{tabularx}} (extra } closes the cell group) is the reliable
# distinguisher from outer \end{tabularx} patterns.

_NESTED_TABULARX_RE = re.compile(
    r'\{\\begin\{tabularx\}\{[^}]+\}\{((?:[^{}]|\{(?:[^{}]|\{[^{}]*\})*\})*)\}'
)


def _convert_x_cols_to_l(cols):
    """Convert X column types (tabularx) to l (plain tabular)."""
    # >{\raggedright\arraybackslash}X  → l
    cols = re.sub(r'>\{[^{}]+\}X', 'l', cols)
    # bare X  → l
    cols = re.sub(r'\bX\b', 'l', cols)
    return cols


def fix_nested_tabularx(path):
    """Convert tabularx nested inside table cells to plain tabular.

    doxygen 1.9.8 emits {\\begin{tabularx}{W}{COLS} inside table cells.
    After fix_longtabu_in_tex converts the outer longtabu to longtable with
    p{} columns, the inner \\begin{tabularx} would have \\linewidth equal to
    the p-column width.  Converting to plain tabular with X columns mapped
    to l is simpler and avoids any potential issues with tabularx inside a
    parbox.

    The nested closing \\end{tabularx}} (with extra } closing the cell group)
    reliably distinguishes inner from outer \\end{tabularx}.
    """
    with open(path, encoding='utf-8', errors='replace') as f:
        content = f.read()

    if r'{\begin{tabularx}' not in content:
        return

    def _replace(m):
        cols = _convert_x_cols_to_l(m.group(1))
        return r'{\begin{tabular}{' + cols + r'}'

    new_content = _NESTED_TABULARX_RE.sub(_replace, content)
    new_content = new_content.replace(r'\end{tabularx}}', r'\end{tabular}}')

    if new_content != content:
        with open(path, 'w', encoding='utf-8') as f:
            f.write(new_content)
        print(f"  {os.path.basename(path)}: converted nested tabularx to tabular")


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

    # 2. Fix longtabu (without asterisk) in .tex files, then remove blank lines
    tex_files = sorted(f for f in os.listdir(latex_dir) if f.endswith('.tex'))
    print(f"Checking {len(tex_files)} .tex files for longtabu and blank lines...")
    for fname in tex_files:
        fpath = os.path.join(latex_dir, fname)
        fix_longtabu_in_tex(fpath)
        fix_nested_tabularx(fpath)
        fix_blank_lines(fpath)

    print("Done.")


if __name__ == '__main__':
    main()
