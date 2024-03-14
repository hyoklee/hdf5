# HDF5 for testing OpenBSD, ARM, RISC-V, aocc+clang+icc/x+nvhpc, and Spack+h5py

## Arch

| Test | Status |
| -----| ------ |
| ARM | [![armv7 CMake](https://github.com/hyoklee/hdf5/actions/workflows/armv7.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/armv7.yml) [![arm64 CMake](https://github.com/hyoklee/hdf5/actions/workflows/arm64.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/arm64.yml) [![linux CMake gcc_arm64](https://github.com/hyoklee/hdf5/actions/workflows/linux-gcc_arm64.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/linux-gcc_arm64.yml) [![linux CMake gcc_arm64 cpp](https://github.com/hyoklee/hdf5/actions/workflows/linux-gcc_arm64-cpp.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/linux-gcc_arm64-cpp.yml)|
| RISC-V | [![riscv64 lin](https://github.com/hyoklee/hdf5/actions/workflows/riscv64-lin.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/riscv64-lin.yml) |
| s390x | [![s390x](https://github.com/hyoklee/hdf5/actions/workflows/s390x.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/s390x.yml) |

## OS

| Test | Status |
| -----| ------ |
| OpenBSD | [![auto](https://github.com/hyoklee/hdf5/actions/workflows/auto.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/auto.yml) [![d](https://github.com/hyoklee/hdf5/actions/workflows/d.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/d.yml) [![r](https://github.com/hyoklee/hdf5/actions/workflows/r.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/r.yml) |
| MSYS2 | [![msys2](https://github.com/hyoklee/hdf5/actions/workflows/msys2.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/msys2.yml) |
| Cygwin |  [![auto](https://github.com/hyoklee/hdf5/actions/workflows/cyg-auto.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/cyg-auto.yml) [![cmake](https://github.com/hyoklee/hdf5/actions/workflows/cyg.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/cyg.yml) |
| iOS |  [![mac13 ios](https://github.com/hyoklee/hdf5/actions/workflows/ios.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/ios.yml) |

## Compilers

| Test | Status |
| -----| ------ |
| aocc | [![linux autotools aocc ompi](https://github.com/hyoklee/hdf5/actions/workflows/lin-auto-aocc-ompi.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin-auto-aocc-ompi.yml) [![linux autotools aocc f ompi](https://github.com/hyoklee/hdf5/actions/workflows/linux-auto-aocc-f-ompi.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/linux-auto-aocc-f-ompi.yml) [![linux autotools aocc d f ompi](https://github.com/hyoklee/hdf5/actions/workflows/linux-auto-aocc-d-f-ompi.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/linux-auto-aocc-d-f-ompi.yml)|
| icx | [![linux CMake icx](https://github.com/hyoklee/hdf5/actions/workflows/linux-icx.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/linux-icx.yml) [![lin auto icx](https://github.com/hyoklee/hdf5/actions/workflows/lin-auto-icx.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin-auto-icx.yml) [![linux autotools icx debug](https://github.com/hyoklee/hdf5/actions/workflows/linux-icx-auto-debug.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/linux-icx-auto-debug.yml) [![linux CMake icx sf](https://github.com/hyoklee/hdf5/actions/workflows/linux-icx-sf.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/linux-icx-sf.yml) [![linux autotools icx sf debug](https://github.com/hyoklee/hdf5/actions/workflows/linux-icx-auto-sf-debug.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/linux-icx-auto-sf-debug.yml) [![windows ninja icx](https://github.com/hyoklee/hdf5/actions/workflows/win-ninja-icx.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/win-ninja-icx.yml) [![windows ninja icx p](https://github.com/hyoklee/hdf5/actions/workflows/win-ninja-icx-p.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/win-ninja-icx-p.yml) |
| ifx | [![windows ninja icx ifx](https://github.com/hyoklee/hdf5/actions/workflows/win-ninja-icx-f.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/win-ninja-icx-f.yml) [![win ninja icx ifx sh](https://github.com/hyoklee/hdf5/actions/workflows/win-ninja-icx-f-sh.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/win-ninja-icx-f-sh.yml) [![windows ninja icx ifx p](https://github.com/hyoklee/hdf5/actions/workflows/win-ninja-icx-f-p.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/win-ninja-icx-f-p.yml) [![windows ninja icx ifx p sf](https://github.com/hyoklee/hdf5/actions/workflows/win-ninja-icx-f-p-sf.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/win-ninja-icx-f-p-sf.yml)  |
| clang |  [![mac-13 CMake clang15 debug gfortran mpich sf](https://github.com/hyoklee/hdf5/actions/workflows/mac-clang15-cmake.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac-clang15-cmake.yml) [![mac13 clang15 r f mpich sf](https://github.com/hyoklee/hdf5/actions/workflows/mac13-clang15-r-f-mpich-sf.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac13-clang15-r-f-mpich-sf.yml) [![mac-13 CMake Xcode clang15 debug mpich sf](https://github.com/hyoklee/hdf5/actions/workflows/mac-clang15-xcode.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac-clang15-xcode.yml)  [![mac CMake java parallel](https://github.com/hyoklee/hdf5/actions/workflows/mac-cmake.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac-cmake.yml) [![mac CMake java parallel threadsafe](https://github.com/hyoklee/hdf5/actions/workflows/mac-cmake-ts.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac-cmake-ts.yml) |
| flang |  [![mac CMake flang java parallel mpich](https://github.com/hyoklee/hdf5/actions/workflows/mac-cmake-flang-mpich.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac-cmake-flang-mpich.yml) |
| nvhpc | [![lin nvhpc](https://github.com/hyoklee/hdf5/actions/workflows/lin-nvhpc.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin-nvhpc.yml) [![lin nvhpc f p](https://github.com/hyoklee/hdf5/actions/workflows/lin-nvhpc-f-p.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin-nvhpc-f-p.yml)   [![linux autotools nvhpc](https://github.com/hyoklee/hdf5/actions/workflows/linux-nvhpc-auto.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/linux-nvhpc-auto.yml) [![linux CMake nvhpc sf](https://github.com/hyoklee/hdf5/actions/workflows/linux-nvhpc-sf.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/linux-nvhpc-sf.yml)  [![linux autotools nvhpc sf](https://github.com/hyoklee/hdf5/actions/workflows/linux-nvhpc-auto-sf.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/linux-nvhpc-auto-sf.yml) |
| MPICH | [![mac CMake fortran java parallel mpich](https://github.com/hyoklee/hdf5/actions/workflows/mac-cmake-mpich.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac-cmake-mpich.yml) |

## Build

| Test | Status |
| -----| ------ |
| Spack+h5py | [![lin spack f ompi](https://github.com/hyoklee/hdf5/actions/workflows/lin-spack-f-ompi.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin-spack-f-ompi.yml) [![lin spack h5py](https://github.com/hyoklee/hdf5/actions/workflows/lin-spack-h5py.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin-spack-h5py.yml) [![mac spack h5py](https://github.com/hyoklee/hdf5/actions/workflows/mac-spack-h5py.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac-spack-h5py.yml) |
| Xcode |  [![mac Xcode](https://github.com/hyoklee/hdf5/actions/workflows/mac-xcode.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac-xcode.yml) |

## Feature

| Test | Status |
| -----| ------ |
| Off | [![mac13 off](https://github.com/hyoklee/hdf5/actions/workflows/mac13-off.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac13-off.yml) |
| Extra | [![linux atutools parallel threadsafe vfds](https://github.com/hyoklee/hdf5/actions/workflows/linux-auto-ts.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/linux-auto-ts.yml) [![linux autotools parallel vfds](https://github.com/hyoklee/hdf5/actions/workflows/linux-auto.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/linux-auto.yml) [![mac autotools parallel](https://github.com/hyoklee/hdf5/actions/workflows/mac-auto.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac-auto.yml) |
| Julia | [![lin jl](https://github.com/hyoklee/hdf5/actions/workflows/lin-jl.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin-jl.yml) [![lin auto jl](https://github.com/hyoklee/hdf5/actions/workflows/lin-auto-jl.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/lin-auto-jl.yml) |
| Interop. | [![HDF-EOS5](https://img.shields.io/github/actions/workflow/status/HDFGroup/hdf5/hdfeos5.yml?branch=develop&label=HDF-EOS5)](https://github.com/HDFGroup/hdf5/actions?query=branch%3Adevelop) [![netCDF](https://github.com/hyoklee/hdf5/actions/workflows/netcdf.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/netcdf.yml) |
| S3 |  [![mac-13 CMake ROS3](https://github.com/hyoklee/hdf5/actions/workflows/mac-cmake-ros3.yml/badge.svg)](https://github.com/hyoklee/hdf5/actions/workflows/mac-cmake-ros3.yml) |

[![Average time to resolve an issue](http://isitmaintained.com/badge/resolution/HDFGroup/hdf5.svg)](http://isitmaintained.com/project/HDFGroup/hdf5 "Average time to resolve an issue")
[![Percentage of issues still open](http://isitmaintained.com/badge/open/HDFGroup/hdf5.svg)](http://isitmaintained.com/project/HDFGroup/hdf5 "Percentage of issues still open")

![reology](https://repology.org/badge/vertical-allrepos/hdf5.svg?header=hdf5)
