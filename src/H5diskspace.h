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
 * Purpose: Disk space utilities for HDF5 library
 */

#ifndef H5diskspace_H
#define H5diskspace_H

/* Include package's "private" header */
#include "H5private.h"

/* Local constants */
#define H5_DISKSPACE_MIN_FREE_BYTES 104857600 /* 100MB minimum free space */

/* Function prototypes */
H5_DLL long long H5_get_available_disk_space(const char *path);
H5_DLL herr_t    H5_check_disk_space(const char *path, long long required_bytes);
H5_DLL herr_t    H5_check_disk_space_before_write(const char *path, size_t data_size);

#endif /* H5diskspace_H */