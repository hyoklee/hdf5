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

# Replacement: ltablex (loads longtable + tabularx) + TX@endtabularx patch
_LTABLEX_BLOCK = (
    r'\RequirePackage{ltablex}' + '\n'
    r'\keepXColumns' + '\n'
    r'% Use ltablex with keepXColumns. Nested tabularx environments have been' + '\n'
    r'% converted to plain tabular in the generated .tex files (see build script).' + '\n'
    r'%' + '\n'
    r"% Patch ltablex's \TX@endtabularx to use \end{\TX@} (dynamic env name) instead" + '\n'
    r'% of the hardcoded \end{tabularx}. This is required when \tabularx is called' + '\n'
    r'% directly (without \begin{tabularx}) inside \newenvironment BEGIN code: in that' + '\n'
    r'% case \TX@ equals the outer environment name, not "tabularx".' + '\n'
    r'\renewcommand\TX@endtabularx{%' + '\n'
    r'  \expandafter\TX@newcol\expandafter{\tabularxcolumn{\TX@col@width}}%' + '\n'
    r'  \let\verb\TX@verb' + '\n'
    r'  \def\@elt##1{\global\value{##1}\the\value{##1}\relax}%' + '\n'
    r'  \edef\TX@ckpt{\cl@@ckpt}%' + '\n'
    r'  \let\@elt\relax' + '\n'
    r'  \TX@old@table=\maxdimen' + '\n'
    r'  \TX@col@width=\TX@target' + '\n'
    r'  \global\TX@cols=\@ne' + '\n'
    r'  \TX@typeout@' + '\n'
    r'    {\@spaces Table Width\@spaces Column Width\@spaces X Columns}%' + '\n'
    r'  \let\savecaption\caption' + '\n'
    r'  \def\caption{%' + '\n'
    r'    \@ifstar\TX@cap@gobble\TX@cap@gobble' + '\n'
    r'  }%' + '\n'
    r'  \let\saveendhead\endhead' + '\n'
    r'  \def\endhead{\\}%' + '\n'
    r'  \let\saveendfirsthead\endfirsthead' + '\n'
    r'  \def\endfirsthead{\\}%' + '\n'
    r'  \let\saveendfoot\endfoot' + '\n'
    r'  \def\endfoot{\\}%' + '\n'
    r'  \let\saveendlastfoot\endlastfoot' + '\n'
    r'  \def\endlastfoot{\\}%' + '\n'
    r'  \ifTX@convertX@' + '\n'
    r'    \TX@trial{\def\NC@rewrite@X{\NC@find l}}%' + '\n'
    r'    \ifdim\wd\@tempboxa<\TX@target' + '\n'
    r'      \TX@newcol{l}%' + '\n'
    r'    \else' + '\n'
    r'      \TX@convertX@false' + '\n'
    r'    \fi' + '\n'
    r'  \fi' + '\n'
    r'  \ifTX@convertX@' + '\n'
    r'    \relax' + '\n'
    r'  \else' + '\n'
    r'    \TX@trial{\def\NC@rewrite@X{%' + '\n'
    r'        \global\advance\TX@cols\@ne\NC@find p{\TX@col@width}}}%' + '\n'
    r'    \loop' + '\n'
    r'      \TX@arith' + '\n'
    r'      \ifTX@' + '\n'
    r'      \TX@trial{}%' + '\n'
    r'    \repeat' + '\n'
    r'  \fi' + '\n'
    r'  {\let\@footnotetext\TX@ftntext\let\@xfootnotenext\TX@xftntext' + '\n'
    r'    \LTchunksize\maxdimen' + '\n'
    r'    \let\caption\savecaption' + '\n'
    r'    \let\endhead\saveendhead' + '\n'
    r'    \let\endfirsthead\saveendfirsthead' + '\n'
    r'    \let\endfoot\saveendfoot' + '\n'
    r'    \let\endlastfoot\saveendlastfoot' + '\n'
    r'    \expandafter\longtable' + '\n'
    r'      \the\toks@' + '\n'
    r'    \endlongtable' + '\n'
    r'    }%' + '\n'
    r'  \global\TX@ftn\expandafter{\expandafter}\the\TX@ftn' + '\n'
    r'  \ifnum0=`{\fi}%' + '\n'
    r'   \expandafter\end\expandafter{\TX@}%' + '\n'
    r'}' + '\n'
    r'\newcolumntype{R}{>{\raggedleft\arraybackslash}X}' + '\n'
    r'\newdimen\tabulinesep \tabulinesep=1mm' + '\n'
    r'\RequirePackage{fancyvrb}'
)


def _convert_tabu_cols(cols):
    """Convert tabu X[-1,...] column spec to tabularx X/R column spec."""
    result = cols.replace('X[-1,r]', 'R')
    result = re.sub(r'X\[-1(?:,[lc])?\]', 'X', result)
    return result


def fix_doxygen_sty(path):
    """Replace tabu_doxygen/longtable_doxygen with ltablex in doxygen.sty."""
    with open(path, encoding='utf-8') as f:
        content = f.read()

    if r'\RequirePackage{ltablex}' in content:
        print(f"  {path}: already patched, skipping")
        return

    if r'\RequirePackage{tabu_doxygen}' not in content:
        print(f"  WARNING: {path}: expected tabu_doxygen pattern not found; skipping")
        return

    # 1. Replace the tabu_doxygen packages with ltablex block
    content = content.replace(_TABU_ORIG, _LTABLEX_BLOCK)
    if r'\RequirePackage{tabu_doxygen}' in content:
        print(f"  WARNING: {path}: replacement did not match exactly; trying fallback")
        # Fallback: replace line by line
        content = content.replace(
            r'\RequirePackage{longtable_doxygen}', r'\RequirePackage{ltablex}')
        content = content.replace(
            r'\RequirePackage{tabu_doxygen}', r'\keepXColumns')
        content = content.replace(
            r'\RequirePackage{tabularx}', '')

    # 2. Fix environments that use longtabu* / tabu
    #    These have the form:  \tabulinesep=1mm%
    #                          \begin{longtabu*}spread 0pt [l]{COLS}%
    #    Replace with:         \setlength{\extrarowheight}{\tabulinesep}%
    #                          \tabularx{\linewidth}{COLS}%
    content = content.replace(
        r'    \tabulinesep=1mm%',
        r'    \setlength{\extrarowheight}{\tabulinesep}%')

    # Replace \begin{longtabu*}spread 0pt [l]{...} → \tabularx{\linewidth}{...}
    def longtabu_repl(m):
        cols = _convert_tabu_cols(m.group(1))
        return r'\tabularx{\linewidth}{' + cols + r'}'

    content = re.sub(
        r'\\begin\{longtabu\*\}spread 0pt \[[lc]\]\{([^}]+)\}',
        longtabu_repl,
        content)
    content = content.replace(r'\end{longtabu*}%', r'\endtabularx%')
    content = content.replace(r'\end{longtabu*}', r'\endtabularx')

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
        '{\\tabularx{\\linewidth}{*#1{|X}|}}%')
    content = content.replace(
        '{\\end{longtabu*}\\par}%',
        '{\\endtabularx\\par}%')
    content = content.replace(
        '{\\end{tabu}\\par}%',
        '{\\endtabularx\\par}%')

    # Note: the original doxygen 1.9.8's doxygen.sty does NOT use \begin{tabularx}
    # in environment definitions - it uses \begin{longtabu*} which we've already
    # replaced above. No further \begin{tabularx} → \tabularx conversion needed.

    with open(path, 'w', encoding='utf-8') as f:
        f.write(content)
    print(f"  {path}: patched (tabu_doxygen -> ltablex)")


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

    # 2. Remove blank lines from all .tex files
    tex_files = sorted(f for f in os.listdir(latex_dir) if f.endswith('.tex'))
    print(f"Checking {len(tex_files)} .tex files for blank lines in tabular envs...")
    for fname in tex_files:
        fix_blank_lines(os.path.join(latex_dir, fname))

    print("Done.")


if __name__ == '__main__':
    main()
