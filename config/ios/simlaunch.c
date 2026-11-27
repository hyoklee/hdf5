/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.                                               *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF5.  The full HDF5 copyright notice, including     *
 * terms governing use, modification, and redistribution, is contained in    *
 * the LICENSE file, which can be found at the root of the source code       *
 * distribution tree, or in https://www.hdfgroup.org/licenses.               *
 * If you do not have access to either file, you may request a copy from     *
 * help@hdfgroup.org.                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 * simlaunch: helper that runs inside the iOS Simulator.
 *
 *     simlaunch <dir> <program> [args...]
 *
 * `xcrun simctl spawn` always starts programs in the simulated device's data
 * directory and the simulator has no shell, so this changes to <dir> and then
 * execs <program>. Used by simrun.sh.
 */
#include <stdio.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "usage: simlaunch dir program [args...]\n");
        return 125;
    }
    if (chdir(argv[1]) != 0) {
        perror(argv[1]);
        return 125;
    }
    execv(argv[2], &argv[2]);
    perror(argv[2]);
    return 127;
}
