# HDF5 Wasted Space Analysis

**Key metric**: `Unaccounted space` in `h5stat -S` output — dead/fragmented bytes that `h5repack` can reclaim.

## Top Offenders in `test/testfiles/`

| File | Wasted (bytes) | Original (bytes) | % Wasted | Repacked (bytes) | Saved (bytes) | % Saved |
|---|---|---|---|---|---|---|
| `paged_persist.h5` | 14,480 | 16,384 | 88.3% | 2,448 | 13,936 | **85.0%** |
| `charsets.h5` | 6,856 | 8,288 | 82.7% | 6,176 | 2,112 | 25.4% |
| `paged_nopersist.h5` | 6,384 | 8,192 | 77.9% | 2,448 | 5,744 | **70.1%** |
| `le_extlink1.h5` | 664 | 896 | 74.1% | 896 | 0 | 0% |
| `be_extlink1.h5` | 664 | 896 | 74.1% | 896 | 0 | 0% |
| `tnullspace.h5` | 1,976 | 3,624 | 54.5% | 1,320 | 2,304 | **63.5%** |
| `test_filters_le.h5` | 2,036 | 5,720 | 35.5% | 5,440 | 280 | 4.8% |
| `test_filters_be.h5` | 2,036 | 5,720 | 35.5% | 5,440 | 280 | 4.8% |
| `filespace_1_8.h5` | 744 | 2,544 | 29.2% | 2,448 | 96 | 3.7% |
| `h5fc_ext_none.h5` | 1,843 | 6,474 | 28.4% | 6,676 | -202 | -3.1% ¹ |
| `h5fc_ext1_i.h5` | 1,846 | 6,526 | 28.2% | 6,676 | -150 | -2.2% ¹ |
| `h5fc_ext2_if.h5` | 1,843 | 6,526 | 28.2% | 6,676 | -150 | -2.2% ¹ |
| `fsm_aggr_nopersist.h5` | 648 | 2,448 | 26.4% | 2,448 | 0 | 0% |
| `fsm_aggr_persist.h5` | 661 | 2,565 | 25.7% | 2,448 | 117 | 4.5% |
| `deflate.h5` | 1,576 | 6,240 | 25.2% | 5,984 | 256 | 4.1% |
| `aggr.h5` | 616 | 2,448 | 25.1% | 2,448 | 0 | 0% |
| `noencoder.h5` | 2,012 | 8,088 | 24.8% | 7,832 | 256 | 3.1% |
| `tmtimeo.h5` | 472 | 2,052 | 23.0% | 2,052 | 0 | 0% |
| `filespace_1_6.h5` | 472 | 2,448 | 19.2% | 2,448 | 0 | 0% |
| `fill_old.h5` | 200 | 2,560 | 7.8% | 2,560 | 0 | 0% |

¹ Repacked files are slightly larger because h5repack rewrites external link metadata with a different layout.

Repacked files are saved as `*_repack.h5` alongside the originals in `test/testfiles/`.

## Findings

- `paged_persist.h5` is the worst at **88%** unaccounted space. It uses
  `H5F_FSPACE_STRATEGY_FSM_AGGR` but was likely created with a page strategy,
  leaving large empty page padding that is now dead space. Repacking recovered
  **85%** of the file size (13,936 bytes).
- `paged_nopersist.h5` similarly shrank by **70%** after repacking.
- `tnullspace.h5` shrank by **63.5%** — null-space datasets accumulated
  significant dead metadata.
- Files with external links (`le/be_extlink1.h5`, `h5fc_ext*.h5`) saw **no
  benefit or grew slightly** — h5repack rewrites external link metadata with
  more overhead than the original fragmented layout.
- Files with no repack savings had unaccounted space consisting of superblock
  padding or alignment bytes that h5repack reproduces identically.
- All files show **0 bytes of tracked free space**, meaning the FSM has no
  reusable blocks queued — all wasted space is dead/fragmented and unrecoverable
  at runtime without repacking.

## How to Inspect Any File

```bash
# Summary: raw data, metadata, unaccounted space
h5stat -S file.h5

# Free space section details
h5stat -F file.h5
```

## How to Reclaim Space

```bash
# Compact only
h5repack input.h5 output.h5

# Compact + recompress
h5repack -f SHUF -f GZIP=3 bloated.h5 compact.h5

# Change file space strategy while repacking
h5repack --fs_strategy=PAGE --fs_page_size=65536 old.h5 new.h5
```

> **Note**: `h5repack` requires approximately the same free disk space as the
> input file size. Do not run it while other processes have the file open.

## Reference

Generated using the `hdf5-file-space` skill from the
[agentic-hdf5](https://github.com/mattjala/agentic-hdf5) plugin.
