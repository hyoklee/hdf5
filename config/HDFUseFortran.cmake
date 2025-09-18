#
# Copyright by The HDF Group.
# All rights reserved.
#
# This file is part of HDF5.  The full HDF5 copyright notice, including
# terms governing use, modification, and redistribution, is contained in
# the LICENSE file, which can be found at the root of the source code
# distribution tree, or in https://www.hdfgroup.org/licenses.
# If you do not have access to either file, you may request a copy from
# help@hdfgroup.org.
#
# -----------------------------------------------------------------------------
# HDFUseFortran.cmake
#
# This CMake module provides functions and macros for general Fortran support
# in HDF5 builds. It detects Fortran/C name mangling conventions, verifies
# Fortran and C/C++ compiler compatibility, and sets up macros for calling
# C from Fortran and vice versa. It also provides a macro for extracting
# Fortran source code blocks from a file for use in feature checks.
#
# -----------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# Enables Fortran language for the project
enable_language (Fortran)
set (HDF_PREFIX "H5")

include (CheckFortranSourceRuns)
include (CheckFortranSourceCompiles)

#-----------------------------------------------------------------------------
# Detects Fortran/C name mangling convention used between Fortran and C using FortranCInterface
#-----------------------------------------------------------------------------
include (FortranCInterface)

#-----------------------------------------------------------------------------
# Verifies Fortran and C/C++ compiler interoperability
#-----------------------------------------------------------------------------

# Special handling for flang-21 on ARM64 macOS before verification
if (CMAKE_Fortran_COMPILER_ID STREQUAL "LLVMFlang" AND CMAKE_SYSTEM_NAME MATCHES "Darwin" AND CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|aarch64")
  message (STATUS "Configuring flang-21 ARM64 macOS workarounds before Fortran verification")

  # Set required libraries for flang linking
  if (EXISTS "/opt/homebrew/lib")
    set (CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -L/opt/homebrew/lib")
  endif ()

  # Add runtime libraries needed for flang on ARM64 macOS
  set (CMAKE_REQUIRED_LIBRARIES "${CMAKE_REQUIRED_LIBRARIES} -lFortranRuntime -lFortranDecimal")
endif ()

FortranCInterface_VERIFY()

# Sets macros for Fortran name mangling (H5_FC_FUNC, H5_FC_FUNC_)
FortranCInterface_HEADER (
    ${CMAKE_BINARY_DIR}/FCMangle.h
    MACRO_NAMESPACE "H5_FC_"
    SYMBOL_NAMESPACE "H5_FC_"
)

file (STRINGS ${CMAKE_BINARY_DIR}/FCMangle.h CONTENTS REGEX "H5_FC_GLOBAL\\(.*,.*\\) +(.*)")
string (REGEX MATCH "H5_FC_GLOBAL\\(.*,.*\\) +(.*)" RESULT  ${CONTENTS})
set (H5_FC_FUNC "H5_FC_FUNC(name,NAME) ${CMAKE_MATCH_1}" CACHE INTERNAL "Fortran name mangling macro for C identifiers without underscores")

file (STRINGS ${CMAKE_BINARY_DIR}/FCMangle.h CONTENTS REGEX "H5_FC_GLOBAL_\\(.*,.*\\) +(.*)")
string (REGEX MATCH "H5_FC_GLOBAL_\\(.*,.*\\) +(.*)" RESULT  ${CONTENTS})
set (H5_FC_FUNC_ "H5_FC_FUNC_(name,NAME) ${CMAKE_MATCH_1}" CACHE INTERNAL "Fortran name mangling macro for C identifiers with underscores")

# READ_SOURCE macro to extract Fortran code blocks for tests
# Read source line beginning at the line matching Input:"START" and ending at the line matching Input:"END"
# Then use the source to check for required libraries for Fortran builds
macro (READ_SOURCE SOURCE_START SOURCE_END RETURN_VAR)
  if (EXISTS "${HDF_CONFIG_DIR}/aclocal_fc.f90")
    file (READ "${HDF_CONFIG_DIR}/aclocal_fc.f90" SOURCE_MASTER)
    string (REGEX MATCH "${SOURCE_START}[\\\t\\\n\\\r[].+]*${SOURCE_END}" SOURCE_CODE ${SOURCE_MASTER})
    set (RETURN_VAR "${SOURCE_CODE}")
  else ()
    message (FATAL_ERROR "${HDF_CONFIG_DIR}/aclocal_fc.f90 does not exist.\n")
  endif ()
endmacro ()

if (HDF5_REQUIRED_LIBRARIES)
  set (CMAKE_REQUIRED_LIBRARIES "${HDF5_REQUIRED_LIBRARIES}")
endif ()

# Additional libraries for flang-21 on ARM64 macOS
if (CMAKE_Fortran_COMPILER_ID STREQUAL "LLVMFlang" AND CMAKE_SYSTEM_NAME MATCHES "Darwin" AND CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|aarch64")
  if (EXISTS "/opt/homebrew/lib")
    set (CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -L/opt/homebrew/lib")
  endif ()
  set (CMAKE_REQUIRED_LIBRARIES "${CMAKE_REQUIRED_LIBRARIES} -lFortranRuntime -lFortranDecimal")
endif ()

READ_SOURCE("PROGRAM PROG_FC_SIZEOF" "END PROGRAM PROG_FC_SIZEOF" SOURCE_CODE)
check_fortran_source_compiles (${SOURCE_CODE} ${HDF_PREFIX}_FORTRAN_HAVE_SIZEOF SRC_EXT f90)

READ_SOURCE("PROGRAM PROG_FC_C_SIZEOF" "END PROGRAM PROG_FC_C_SIZEOF" SOURCE_CODE)
check_fortran_source_compiles (${SOURCE_CODE} ${HDF_PREFIX}_FORTRAN_HAVE_C_SIZEOF SRC_EXT f90)

READ_SOURCE("PROGRAM PROG_FC_STORAGE_SIZE" "END PROGRAM PROG_FC_STORAGE_SIZE" SOURCE_CODE)
check_fortran_source_compiles (${SOURCE_CODE} ${HDF_PREFIX}_FORTRAN_HAVE_STORAGE_SIZE SRC_EXT f90)

set (ISO_C_BINDING_CODE
  "
       PROGRAM main
            USE iso_c_binding
            IMPLICIT NONE
            TYPE(C_PTR) :: ptr
            TYPE(C_FUNPTR) :: funptr
            INTEGER(C_INT64_T) :: c_int64_type
            CHARACTER(LEN=80, KIND=c_char), TARGET :: ichr
            ptr = C_LOC(ichr(1:1))
       END PROGRAM
  "
)
check_fortran_source_compiles (${ISO_C_BINDING_CODE} ${HDF_PREFIX}_FORTRAN_HAVE_ISO_C_BINDING SRC_EXT f90)

#-----------------------------------------------------------------------------
# Adds debug flags for Intel Fortran on Windows
#-----------------------------------------------------------------------------
if (CMAKE_Fortran_COMPILER MATCHES ifx)
    if (WIN32 AND NOT MINGW)
        set (CMAKE_Fortran_FLAGS_DEBUG "/debug:full /dbglibs " CACHE STRING "flags" FORCE)
        set (CMAKE_EXE_LINKER_FLAGS_DEBUG "/DEBUG" CACHE STRING "flags" FORCE)
    endif ()
endif ()
