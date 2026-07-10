# CI Fix Summary — 2026-04-12

Fixes for CI build failures in https://github.com/hyoklee/hdf5/actions/runs/24321273000,
committed as `5e325758cde fix: resolve CI build failures across multiple compilers and platforms`.

## Fixes Applied

### 1. `docs/doxygen/hdf5doxy_layout.xml` — Doxygen 1.16.1 fatal error
Removed the hidden `<tab>` entries for `modules`, `annotated`, and `files` that were added in the "docs: make pdf" commit. Doxygen 1.16.1 treats `annotated` as an invalid navindex type and exits with a fatal error. These tabs were invisible (`visible="no"`) and weren't in upstream.

### 2. `docs/doxygen/Doxyfile.in` + `docs/doxygen/CMakeLists.txt` — Two Doxygen errors
- **`@ref h5tools` unresolved**: Added `h5tools.h` to `FILE_PATTERNS` so Doxygen processes the `\defgroup h5tools` definition in `tools/lib/h5tools.h`.
- **`epstopdf` fatal error**: In Doxygen 1.16.1, missing `epstopdf` causes a fatal error when `GENERATE_LATEX = YES`. Changed to `@DOXYGEN_GENERATE_LATEX@` and added CMake detection via `find_program(EPSTOPDF_FOUND epstopdf)` — LaTeX is only enabled when epstopdf is actually available.

### 3. `test/dt_arith.c` — Clang/AOCC/MSYS2 build errors
Removed the invalid `#pragma omp simd collapse(1)` and `#pragma clang loop vectorize(disable)` pragmas. Both directives must immediately precede a loop statement, not an assignment. Clang treated the misuse as a hard error.

### 4. `test/CMakeLists.txt` — NVHPC 26.3 compiler crash
Added `-O0` for NVHPC/PGI when compiling `dt_arith.c`. NVHPC 26.3's LLC (LLVM backend) crashes with signal 6 during instruction selection at `-O1`. This was a pre-existing compiler bug that the removed pragmas were trying (incorrectly) to fix.

### 5. `src/H5win32defs.h` — Intel oneAPI Windows build error
Reverted `|| defined(_MSC_VER)` from the complex-number typedef guard to match upstream. Intel ICX on Windows defines `_MSC_VER` for compatibility but supports C99 `_Complex`, so the extra condition incorrectly enabled MSVC-specific `_Fcomplex`/`_Dcomplex`/`_Lcomplex` types that ICX doesn't provide.

## Root Cause Analysis

| Job(s) failing | Root cause | Introduced by |
|---|---|---|
| All Linux/macOS/Windows cmake CI builds | `annotated` navindex type removed in Doxygen 1.16.1 | `6bbfb63d440 docs: make pdf` |
| All Linux/macOS/Windows cmake CI builds | `@ref h5tools` unresolvable (h5tools.h not in FILE_PATTERNS) | `31e02943e7a sync upstream/develop` |
| All Linux/macOS/Windows cmake CI builds | `epstopdf` not installed in cmake CI environment | `6bbfb63d440 docs: make pdf` |
| macOS Clang, AOCC, MSYS2-clangarm64 | `#pragma clang loop` before non-loop statement | `728fb45ff25 test(nvhpc): disable vectorization` |
| nvhpc Release | NVHPC 26.3 LLC crash (signal 6) on `dt_arith.c` at -O1 | Pre-existing NVHPC 26.3 compiler bug |
| Intel windows-oneapi | `_Fcomplex` unknown type on ICX | Pre-existing divergence from upstream |

## Key Insight: Doxygen Version Mismatch

The doxygen-specific workflow (`doxygen gh-pages pdf`) installs Doxygen 1.9.8 from Ubuntu apt, where these issues are **warnings**. The main cmake CI workflow downloads Doxygen **1.16.1** from GitHub releases, where they are **fatal errors**. This masked the problems until the main cmake CI was examined.
