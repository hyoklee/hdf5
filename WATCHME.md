# HDF5 for All

## Quality

| Test   | Status |
|--------|--------|
| Google | [![OSS-Fuzz Status](https://oss-fuzz-build-logs.storage.googleapis.com/badges/hdf5.svg)](https://oss-fuzz-build-logs.storage.googleapis.com/index.html#hdf5) |
| Local | [![oss-fuzz](https://github.com/hyoklee/hdf5/actions/workflows/fuzz.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/fuzz.yml)|

# Documentation

| Test   | Status |
|--------|--------|
| Markdown | [![Check Markdown links](https://github.com/hyoklee/hdf5/actions/workflows/markdown-link-check.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/markdown-link-check.yml)|
| Linkchecker |[![linkchecker](https://github.com/hyoklee/hdf5/actions/workflows/linkchecker.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/linkchecker.yml)|

## Installation

| Test | Status |
| -----| ------ |
| RPM | [![alien](https://github.com/hyoklee/hdf5/actions/workflows/alien.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/alien.yml) |
| DEB | [![dpkg](https://github.com/hyoklee/hdf5/actions/workflows/dpkg.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/dpkg.yml) |


## Arch

| Test | Status |
| -----| ------ |
| amd64 | [![amd64](https://github.com/hyoklee/hdf5/actions/workflows/r.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/r.yml) |
| arm64 | [![arm64](https://github.com/hyoklee/hdf5/actions/workflows/arm64.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/arm64.yml) |
| armv7 | [![armv7 lin](https://github.com/hyoklee/hdf5/actions/workflows/armv7_lin.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/armv7_lin.yml) |
| riscv64 | [![riscv64 lin](https://github.com/hyoklee/hdf5/actions/workflows/riscv64_lin.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/riscv64_lin.yml) |
| powerpc64 | [![ppc64le lin](https://github.com/hyoklee/hdf5/actions/workflows/ppc64le_lin.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/ppc64le_lin.yml) |
| s390x | [![s390x lin](https://github.com/hyoklee/hdf5/actions/workflows/s390x_lin.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/s390x_lin.yml) |


## OS

### BSD

| Test    | Status |
| --------| ------ |
| FreeBSD |  [![fbsd](https://github.com/hyoklee/hdf5/actions/workflows/fbsd.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/fbsd.yml) [![fbsd d](https://github.com/hyoklee/hdf5/actions/workflows/fbsd_d.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/fbsd_d.yml) |
| NetBSD |  [![nbsd](https://github.com/hyoklee/hdf5/actions/workflows/nbsd.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/nbsd.yml)|

### Mac

| Test    | Status |
| --------| ------ |
| xcode |  [![mac xcode](https://github.com/hyoklee/hdf5/actions/workflows/mac_xcode.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac_xcode.yml) |
| off | [![mac off](https://github.com/hyoklee/hdf5/actions/workflows/mac_off.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac_off.yml) |
| iOS |  [![mac13 ios](https://github.com/hyoklee/hdf5/actions/workflows/ios.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/ios.yml) |

### Linux

| Test    | Status |
| --------| ------ |
| OpenSuse  | [![suse f cpp hl](https://github.com/hyoklee/hdf5/actions/workflows/suse.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/suse.yml) |
| Ubuntu  | [![arm64 lin](https://github.com/hyoklee/hdf5/actions/workflows/arm64_lin.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/arm64_lin.yml) |

### Solaris

| Test    | Status |
| --------| ------ |
| Solaris | [![sol](https://github.com/hyoklee/hdf5/actions/workflows/sol.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/sol.yml) |

### Windows

| Test    | Status |
| --------| ------ |
| Windows | [![win ninja icx](https://github.com/hyoklee/hdf5/actions/workflows/win_ninja_icx.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/win_ninja_icx.yml)  [![win ninja icx ifx p sf](https://github.com/hyoklee/hdf5/actions/workflows/win_ninja_icx_f_p_sf.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/win_ninja_icx_f_p_sf.yml) |


## Build

| Test  | Status |
| ------| ------ |
| Ninja | [![lin ninja nvhpc f p](https://github.com/hyoklee/hdf5/actions/workflows/lin_ninja_nvhpc_f_p.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_ninja_nvhpc_f_p.yml) [![win ninja icx](https://github.com/hyoklee/hdf5/actions/workflows/win_ninja_icx.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/win_ninja_icx.yml) [![win ninja icx ifx p sf](https://github.com/hyoklee/hdf5/actions/workflows/win_ninja_icx_f_p_sf.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/win_ninja_icx_f_p_sf.yml) |
| Spack | [![lin spack f ompi](https://github.com/hyoklee/hdf5/actions/workflows/lin_spack_f_ompi.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_spack_f_ompi.yml) [![lin spack h5py](https://github.com/hyoklee/hdf5/actions/workflows/lin_spack_h5py.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_spack_h5py.yml) [![mac spack h5py](https://github.com/hyoklee/hdf5/actions/workflows/mac_spack_h5py.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac_spack_h5py.yml) |
| vcpkg |  [![win25 vcpkg](https://github.com/hyoklee/hdf5/actions/workflows/win_25_vcpkg.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/win_25_vcpkg.yml) |
| Xcode |  [![mac Xcode](https://github.com/hyoklee/hdf5/actions/workflows/mac_xcode.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac_xcode.yml) |

## Compilers

| Test | Status |
| -----| ------ |
| clang |  [![mac13 ninja clang15 d h f mpich sf](https://github.com/hyoklee/hdf5/actions/workflows/mac_13_ninja_clang15_d_h_f_mpich_sf.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac_13_ninja_clang15_d_h_f_mpich_sf.yml) [![mac13 clang15 r f mpich sf](https://github.com/hyoklee/hdf5/actions/workflows/mac_13_clang15_r_f_mpich_sf.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac_13_clang15_r_f_mpich_sf.yml) [![mac13 xcode clang15 d mpich s3 sf](https://github.com/hyoklee/hdf5/actions/workflows/mac_13_xcode_clang15_d_mpich_s3_sf.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac_13_xcode_clang15_d_mpich_s3_sf.yml)  [![mac ninja clang j ompi](https://github.com/hyoklee/hdf5/actions/workflows/mac_ninja_clang_j_ompi.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac_ninja_clang_j_ompi.yml)  |
| flang |  [![mac14 ninja clang19 fl d f mpich sf](https://github.com/hyoklee/hdf5/actions/workflows/mac_14_ninja_clang19_fl_d_f_mpich_sf.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac_14_ninja_clang19_fl_d_f_mpich_sf.yml) |
| gcc_min | [![lin gcc_min](https://github.com/hyoklee/hdf5/actions/workflows/lin_gcc_min.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_gcc_min.yml) |
| ifx | [![windows ninja icx ifx](https://github.com/hyoklee/hdf5/actions/workflows/win_ninja_icx_f.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/win_ninja_icx_f.yml) [![win ninja icx ifx sh](https://github.com/hyoklee/hdf5/actions/workflows/win_ninja_icx_f_sh.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/win_ninja_icx_f_sh.yml) [![windows ninja icx ifx p](https://github.com/hyoklee/hdf5/actions/workflows/win_ninja_icx_f_p.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/win_ninja_icx_f_p.yml) [![win ninja icx ifx p sf](https://github.com/hyoklee/hdf5/actions/workflows/win_ninja_icx_f_p_sf.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/win_ninja_icx_f_p_sf.yml)  |
| lfortran | [![fbsd lf j](https://github.com/hyoklee/hdf5/actions/workflows/fbsd_lf_j.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/fbsd_lf_j.yml) |
| nvhpc | [![lin nvhpc](https://github.com/hyoklee/hdf5/actions/workflows/lin_nvhpc.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_nvhpc.yml) [![lin nvhpc d](https://github.com/hyoklee/hdf5/actions/workflows/lin_nvhpc_d.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_nvhpc_d.yml) |

## Options

### Configuration

| Test  | Status |
| ------| ------ |
| Debug |  [![fbsd d](https://github.com/hyoklee/hdf5/actions/workflows/fbsd_d.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/fbsd_d.yml) |
| Off   | [![mac13 off](https://github.com/hyoklee/hdf5/actions/workflows/mac_13_off.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac_13_off.yml) |
| Shared | [![nbsd f -sh](https://github.com/hyoklee/hdf5/actions/workflows/nbsd_f_sh.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/nbsd_f_sh.yml) |


### Languages

| Test  | Status |
| ------| ------ |
| Fortran | [![nbsd f](https://github.com/hyoklee/hdf5/actions/workflows/nbsd_f.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/nbsd_f.yml) [![s390x lin f](https://github.com/hyoklee/hdf5/actions/workflows/s390x_lin_f.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/s390x_lin_f.yml) |
| Java  | [![fbsd f j](https://github.com/hyoklee/hdf5/actions/workflows/fbsd_f_j.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/fbsd_f_j.yml) [![arm64 fbsd f j](https://github.com/hyoklee/hdf5/actions/workflows/arm64_fbsd_f_j.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/arm64_fbsd_f_j.yml) [![nbsd f j](https://github.com/hyoklee/hdf5/actions/workflows/nbsd_f_j.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/nbsd_f_j.yml) [![arm64 fbsd f j](https://github.com/hyoklee/hdf5/actions/workflows/arm64_fbsd_f_j.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/arm64_fbsd_f_j.yml) [![fbsd lf j](https://github.com/hyoklee/hdf5/actions/workflows/fbsd_lf_j.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/fbsd_lf_j.yml) [![mac ninja clang j ompi](https://github.com/hyoklee/hdf5/actions/workflows/mac_ninja_clang_j_ompi.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac_ninja_clang_j_ompi.yml) [![mac14 ninja h j ompi](https://github.com/hyoklee/hdf5/actions/workflows/mac_14_ninja_h_j_ompi_cd.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac_14_ninja_h_j_ompi_cd.yml) |
| Python | [![lin spack h5py](https://github.com/hyoklee/hdf5/actions/workflows/lin_spack_h5py.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_spack_h5py.yml) [![mac spack h5py](https://github.com/hyoklee/hdf5/actions/workflows/mac_spack_h5py.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac_spack_h5py.yml) |

### Parallel

| Test    | Status |
| --------| ------ |

### Thread-Safety

| Test | Status |
| -----| ------ |
|  ts  | [![mac ninja clang j ompi ts](https://github.com/hyoklee/hdf5/actions/workflows/mac_ninja_clang_j_ompi_ts.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac_ninja_clang_j_ompi_ts.yml) |

### VFDs

| Test | Status |
| -----| ------ |


## Previously Untested CMake Options

### Static-Only Builds

| Test | Status |
| -----| ------ |
| Linux Static-Only | [![Linux Static-Only Build](https://github.com/hyoklee/hdf5/actions/workflows/lin_sta_onl.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_sta_onl.yml) |
| Windows Static-Only | [![Windows Static-Only Build](https://github.com/hyoklee/hdf5/actions/workflows/win_sta_onl.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/win_sta_onl.yml) |
| macOS Static-Only | [![macOS Static-Only Build](https://github.com/hyoklee/hdf5/actions/workflows/mac_sta_onl.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac_sta_onl.yml) |

### macOS Frameworks

| Test | Status |
| -----| ------ |
| Frameworks | [![macOS Frameworks Build](https://github.com/hyoklee/hdf5/actions/workflows/mac_frm.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac_frm.yml) |

### API Version Compatibility

| Test | Status |
| -----| ------ |
| API v1.6 | [![Linux API v1.6 Compatibility](https://github.com/hyoklee/hdf5/actions/workflows/lin_api_v16.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_api_v16.yml) |
| API v1.8 | [![Linux API v1.8 Compatibility](https://github.com/hyoklee/hdf5/actions/workflows/lin_api_v18.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_api_v18.yml) [![Windows API v1.8](https://github.com/hyoklee/hdf5/actions/workflows/win_api_dep.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/win_api_dep.yml) [![macOS API v1.8](https://github.com/hyoklee/hdf5/actions/workflows/mac_api_map.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac_api_map.yml) |
| API v1.10 | [![Linux API v1.10 Compatibility](https://github.com/hyoklee/hdf5/actions/workflows/lin_api_v110.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_api_v110.yml) |
| API v1.12 | [![Linux API v1.12 Compatibility](https://github.com/hyoklee/hdf5/actions/workflows/lin_api_v112.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_api_v112.yml) |
| API v1.14 | [![Linux API v1.14 Compatibility](https://github.com/hyoklee/hdf5/actions/workflows/lin_api_v114.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_api_v114.yml) |

### Feature Options

| Test | Status |
| -----| ------ |
| Deprecated OFF | [![Linux Deprecated Symbols OFF](https://github.com/hyoklee/hdf5/actions/workflows/lin_dep_off.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_dep_off.yml) |
| Map API | [![Linux Map API Build](https://github.com/hyoklee/hdf5/actions/workflows/lin_map_api.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_map_api.yml) |
| Trace & Instrument | [![Linux Trace & Instrument](https://github.com/hyoklee/hdf5/actions/workflows/lin_trc_ins.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_trc_ins.yml) |
| pread/pwrite OFF | [![Linux pread/pwrite OFF](https://github.com/hyoklee/hdf5/actions/workflows/lin_prw_off.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_prw_off.yml) |
| Custom Naming | [![Linux Custom Library Naming](https://github.com/hyoklee/hdf5/actions/workflows/lin_nam_cus.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_nam_cus.yml) |
| Memory Checker | [![Linux Memory Checker Mode](https://github.com/hyoklee/hdf5/actions/workflows/lin_mem_chk.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_mem_chk.yml) |
| Embedded Libinfo OFF | [![Linux Embedded Libinfo OFF](https://github.com/hyoklee/hdf5/actions/workflows/lin_emb_off.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_emb_off.yml) |

### Development Tools

| Test | Status |
| -----| ------ |
| Analyzer & Formatter | [![Linux Analyzer & Formatter Tools](https://github.com/hyoklee/hdf5/actions/workflows/lin_anl_fmt.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_anl_fmt.yml) |

### Platform-Specific

| Test | Status |
| -----| ------ |
| MinGW Static GCC | [![Windows MinGW Static GCC Libs](https://github.com/hyoklee/hdf5/actions/workflows/win_mgw_sta.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/win_mgw_sta.yml) |

### Advanced Tests

| Test | Status |
| -----| ------ |
| Unsupported Combinations | [![Linux Unsupported Combinations](https://github.com/hyoklee/hdf5/actions/workflows/lin_uns_cbo.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin_uns_cbo.yml) |
## Extra

| Test     | Status |
| ---------| ------ |
| Interop. | [![HDF-EOS5](https://img.shields.io/github/actions/workflow/status/hyoklee/hdf5/hdfeos5.yml?branch=develop&label=HDF-EOS5)](https://github.com/hyoklee/hdf5/actions?query=branch%3Adevelop) [![netCDF](https://github.com/hyoklee/hdf5/actions/workflows/netcdf.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/netcdf.yml) |

[![Average time to resolve an issue](http://isitmaintained.com/badge/resolution/HDFGroup/hdf5.svg)](http://isitmaintained.com/project/HDFGroup/hdf5 "Average time to resolve an issue")
[![Percentage of issues still open](http://isitmaintained.com/badge/open/HDFGroup/hdf5.svg)](http://isitmaintained.com/project/HDFGroup/hdf5 "Percentage of issues still open")

![repology](https://repology.org/badge/vertical-allrepos/hdf5.svg?header=hdf5)

[![OpenSSF Best Practices](https://www.bestpractices.dev/projects/7802/badge)](https://www.bestpractices.dev/projects/7802)

[![Star History Chart](https://api.star-history.com/svg?repos=HDFGroup/hdf5&type=Date)](https://www.star-history.com/#HDFGroup/hdf5&Date)
