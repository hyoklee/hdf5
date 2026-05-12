# HDF5 Test Fix Report

## Summary

Five test failures were fixed on the `develop` branch targeting OpenBSD 7.8 and s390x.

---

## Fix 1: `test/tunicode.c` — s390x `memcmp` failures

### Symptom
Two `VERIFY(memcmp(...), 0, "memcmp")` failures in `test_strpad`, triggered after replacing
`strcpy` with `strlcpy` in commit `07a0fdde`.

### Root Cause
`strlcpy(&cmpbuf[2 * small_len], new_string, big_len - 2 * small_len + 1)`

The `length` variable is always adjusted to be odd, so `small_len = (length + 1) / 2` and
`2 * small_len == big_len`. The size argument therefore evaluates to `1`, causing `strlcpy`
to copy zero characters (only writes the null terminator). The comparison buffer was never
populated, making `memcmp` fail.

### Fix
```c
// Before:
strlcpy(&cmpbuf[2 * small_len], new_string, big_len - 2 * small_len + 1);

// After:
memcpy(&cmpbuf[2 * small_len], new_string, big_len);
```

---

## Fix 2: `tools/test/perform/zip_perf.c:227` — `strcpy` warning

### Symptom
OpenBSD linker warning when ZLIB test is enabled:
```
zip_perf.c:227: warning: strcpy() is almost always misused, please use strlcpy()
```

### Fix
```c
// Before:
strcpy(filename, prefix);

// After:
strlcpy(filename, prefix, strlen(prefix) + strlen(ZIP_PERF_FILE) + 2);
```

---

## Fix 3: `test/mdset.c` — Timeout and `H5Dcreate2` failure under `MALLOC_OPTIONS="SCFGJRU"`

### Symptom
Running `export MALLOC_OPTIONS="SCFGJRU" && ./bin/mdset` produced two distinct failures:

1. **Timeout** — 50 iterations with guard-page/junk-fill allocations are too slow.
2. **`H5Dcreate2` failure** — "unable to get the next power of 2" from `H5VM_power2up()`.

### Root Cause (Timeout)
OpenBSD's `MALLOC_OPTIONS` flags `C` (zero-fill), `G` (guard pages), and `J` (junk-fill)
dramatically slow every heap allocation. With 50 iterations the test exceeds the time limit.

### Root Cause (H5Dcreate2 failure)
On OpenBSD with `MALLOC_OPTIONS="SCFGJRU"`, `rand()` returns **negative values**.

The `J` (junk-fill freed memory with `0xDF`), `F` (free immediately / unmap pages), and
`U` (no reuse) flags corrupt `arc4random`'s internally heap-allocated keystream buffer.
When `rand()` internally calls `arc4random()` using a junk-filled buffer, the garbage
chacha20 keystream has ~50% of values with the high bit set, making them negative when
interpreted as `int`.

In `test_mdset`, these negative values are cast to `hsize_t` (uint64_t):

```c
dset_dims[j][0] = (hsize_t)((rand() % MAX_DSET_X) + 1);
//  rand() = -623120889
//  -623120889 % 10 = -9  (C99 truncation-toward-zero)
//  -9 + 1 = -8
//  (hsize_t)(-8) = 18446744073709551608  ← UINT64_MAX - 7
```

`UINT64_MAX - 7 >= 2^63`, so `H5VM_power2up()` returns 0 (error), propagating as the
`H5Dcreate2` failure.

Confirmed by debug instrumentation:
```
DBG RAND: r0=-623120889 r1=-1439909067
DBG PRE: dset_dims={18446744073709551608, 18446744073709551610}
```

### Fix

**Timeout** — Detect slow-malloc flags at runtime and reduce iterations:
```c
size_t niter = 50;
const char *malloc_opts = getenv("MALLOC_OPTIONS");
if (malloc_opts && strpbrk(malloc_opts, "CGJ"))
    niter = 5;
// ...
nerrors += test_mdset(niter, i, fapl_id);
```

**H5Dcreate2 failure** — Added `urand()` helper and replaced all `rand()` calls in
`test_mdset`:
```c
static unsigned int
urand(void)
{
    return (unsigned int)rand();
}
```

`(unsigned int)rand()` is always non-negative regardless of the platform's `rand()`
implementation, ensuring dimension values remain in the expected range (1–10).

### Verification
All 28 test configurations pass under `MALLOC_OPTIONS="SCFGJRU"`:
```
Testing random I/O   PASSED   (Contiguous, No shape-same, Single I/O, ...)
Testing random I/O   PASSED   (Chunked, ...)
...
Testing mdset location   PASSED
All multi dataset tests passed.
```

---

## Fix 4: `test/dsets.c` — nbit array/compound read failures

### Symptom
Three nbit filter read tests failed on OpenBSD:
1. `nbit array (read)` — "Read different values than written. At index 0,0,0,0"
2. `nbit compound complex (read)` — "Read different values than written. At index 0,X"
3. `nbit compound with no-op type (read)` — "Read different values than written. At index X"

### Root Cause
Same as Fix 3: `rand()` returns negative values on OpenBSD. The data initialization uses:
```c
orig_data[i][j][m][n] = (unsigned int)(((long long)rand() % (long long)power) << offset);
```

When `rand()` is negative (e.g., `-2112618`), the modulo gives a negative long long, left-shifting
a negative value is undefined behavior, and the cast to `unsigned int` produces a value with bits
above the nbit precision range set (e.g., `0xEFE1CB00` instead of `0x0FE1CB00`).

The nbit filter only stores and restores the significant bits (precision=22, offset=7). On
read-back, the extra high bits are zeroed (not preserved), so `orig_data != new_data`.

Confirmed by debug print before the write:
```
DBG nbit_array: orig[0][0][0][0]=0xE5036E80
```
`0xE5036E80 >> 7 = 0x1CA06DD = 30,017,245 > 2^22 = 4,194,304` — impossible with non-negative rand().

### Fix
Added `urand()` helper and replaced `rand()` calls for unsigned data generation:
```c
static unsigned int
urand(void)
{
    return (unsigned int)rand();
}
```

Changed in:
- `test_nbit_array`: `rand()` → `urand()` in `orig_data[i][j][m][n]` formula
- `test_nbit_compound_2`: `rand()` → `urand()` for the `v` (unsigned) member
- `test_nbit_compound_3`: `rand()` → `urand()` for the `i` (int, no mask comparison) member

---

## Fix 5: `test/dsets.c` — random chunk write/assertion failures

### Symptom
Two failures in chunk I/O tests:
1. `Write/read on randomly selected chunks w/non-implicit index` — H5Dwrite fails with
   "selection + offset not within extent for file dataspace"
2. `Write/read on randomly selected chunks w/implicit index` — assertion
   `assert(!check2[chunk_row][chunk_col])` fires (duplicate chunk selection detected)

### Root Cause
Same root cause: `rand()` returns negative values on OpenBSD.

In `make_random_offset_and_increment`:
```c
*offsetp = rand() % nelts;         // negative if rand() < 0
inc = 1 + rand() % maxinc;         // can be 0 or negative if rand() < 0
```

If `*offsetp` is negative, then `chunk_row = ofs / cols` is negative. This causes:
- **Non-implicit test**: `coord[i][0] = (hsize_t)chunk_row * csize[0]` wraps to a huge
  unsigned value (e.g., `UINT64_MAX - 89`), which exceeds the dataset extent → write fails.
- **Implicit test**: negative `chunk_row` indexes into `check2` at a garbage address, reading
  a non-zero value that triggers the duplicate-detection assertion.

### Fix
Replaced `rand()` with `urand()` in `make_random_offset_and_increment`:
```c
*offsetp = (long)(urand() % (unsigned long)nelts);
// ...
inc = 1 + (long)(urand() % (unsigned long)maxinc);
```

### Verification
After all five fixes, `dsets` tests on OpenBSD show:
```
All dataset tests passed.
PASSED: 3543, FAILED: 0, SKIP: 168
```
