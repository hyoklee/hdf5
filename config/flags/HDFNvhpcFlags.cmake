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

###############################################################################
# This file included from HDFCompilerFlags.cmake with
#  if (CMAKE_C_COMPILER_ID MATCHES "NVHPC" )
###############################################################################

#-----------------------------------------------------------------------------
# Compiler specific flags
#-----------------------------------------------------------------------------
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Minform=warn")

# Add flags to improve long double precision handling for dt_arith tests
# This addresses known NVHPC issues with long double arithmetic
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Kieee")

# Force -O1 optimization to prevent segmentation faults in dt_arith tests
# NVHPC has known bugs with -O2 and higher that cause segfaults in long double conversions
# Reference: RELEASE.txt - "work-around is to set the optimization level to -O1"
set (CMAKE_C_FLAGS_RELEASE "-O1")
set (CMAKE_C_FLAGS_RELWITHDEBINFO "-O1 -g")

# Disable problematic long double conversions that cause segmentation faults
# Similar to IBM ppc64le systems, NVHPC has issues with certain long double conversions
set (H5_DISABLE_SOME_LDOUBLE_CONV 1 CACHE BOOL "Disable some long double conversions for NVHPC" FORCE)

if (NOT ${HDF_CFG_NAME} MATCHES "Debug" AND NOT ${HDF_CFG_NAME} MATCHES "Developer")
  if (NOT ${HDF_CFG_NAME} MATCHES "RelWithDebInfo")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s")
  endif ()
else ()
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Mbounds -gopt")
endif ()
