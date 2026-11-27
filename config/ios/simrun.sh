#!/bin/sh
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
# Run an iOS Simulator program in a booted simulator from the caller's
# working directory. Usable as CMAKE_CROSSCOMPILING_EMULATOR.
#
#     simrun.sh <program> [args...]
#
# Environment:
#   SIMLAUNCH       path to the simlaunch helper built for the simulator
#                   (default: simlaunch next to this script)
#   SIMRUN_DEVICE   simulator UDID or name (default: booted)
#
# HDF5_*, H5_*, and srcdir variables are forwarded to the program.

if [ $# -lt 1 ]; then
  echo "usage: simrun.sh program [args...]" >&2
  exit 125
fi

launcher=${SIMLAUNCH:-$(dirname "$0")/simlaunch}

# simctl only passes variables prefixed with SIMCTL_CHILD_ to the program
for v in $(env | sed -En 's/^((HDF5|H5)_[A-Za-z0-9_]*|srcdir)=.*/\1/p'); do
  eval "export SIMCTL_CHILD_$v=\"\$$v\""
done

prog=$1
shift
case $prog in
  /*) ;;
  *) prog=$PWD/$prog ;;
esac

exec xcrun simctl spawn "${SIMRUN_DEVICE:-booted}" "$launcher" "$PWD" "$prog" "$@"
