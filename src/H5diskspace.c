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
 * Purpose: Disk space utilities for HDF5 library to prevent hanging
 *          when insufficient disk space is available.
 */

/****************/
/* Module Setup */
/****************/

#include "H5diskspace.h"
#include "H5Eprivate.h" /* Error handling */

/***********/
/* Headers */
/***********/
#include "H5private.h" /* Generic Functions */

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#include <sys/statvfs.h>
#define H5_HAVE_STATVFS 1
#endif

#ifdef H5_HAVE_WINDOWS
#include <windows.h>
#define H5_HAVE_GETDISKFREESPACE 1
#endif

/****************/
/* Local Macros */
/****************/

/******************/
/* Local Typedefs */
/******************/

/********************/
/* Local Prototypes */
/********************/

/*********************/
/* Package Variables */
/*********************/

/*****************************/
/* Library Private Variables */
/*****************************/

/*******************/
/* Local Variables */
/*******************/

/*-------------------------------------------------------------------------
 * Function:    H5_get_available_disk_space
 *
 * Purpose:     Get available disk space in bytes for the given path
 *
 * Return:      Success: Number of bytes available
 *              Failure: -1
 *
 *-------------------------------------------------------------------------
 */
long long
H5_get_available_disk_space(const char *path)
{
    long long ret_value;

    FUNC_ENTER_NOAPI_NOINIT_NOERR

#ifdef H5_HAVE_STATVFS
    struct statvfs stat;
    if (statvfs(path ? path : ".", &stat) == 0) {
        ret_value = (long long)stat.f_bavail * stat.f_frsize;
        HGOTO_DONE(ret_value)
    }
#elif defined(H5_HAVE_GETDISKFREESPACE)
    ULARGE_INTEGER free_bytes_available;
    if (GetDiskFreeSpaceExA(path ? path : ".", &free_bytes_available, NULL, NULL)) {
        ret_value = (long long)free_bytes_available.QuadPart;
        HGOTO_DONE(ret_value)
    }
#endif

    ret_value = -1; /* Unable to determine disk space */

done:
    FUNC_LEAVE_NOAPI(ret_value)
} /* end H5_get_available_disk_space() */

/*-------------------------------------------------------------------------
 * Function:    H5_check_disk_space
 *
 * Purpose:     Check if there's enough disk space available for the operation
 *
 * Return:      Success: SUCCEED
 *              Failure: FAIL (insufficient disk space)
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5_check_disk_space(const char *path, long long required_bytes)
{
    long long available;
    herr_t    ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT

    /* Get available disk space */
    available = H5_get_available_disk_space(path);

    if (available == -1) {
        /* Unable to determine disk space - issue warning but continue */
        /* Note: Could add debug tracing here if needed */
        HGOTO_DONE(SUCCEED)
    }

    /* Check if we have enough space (with some buffer) */
    if (available < (required_bytes + H5_DISKSPACE_MIN_FREE_BYTES)) {
        HGOTO_ERROR(H5E_DATASET, H5E_NOSPACE, FAIL,
                    "insufficient disk space: available=%lld bytes, required=%lld bytes", available,
                    required_bytes)
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
} /* end H5_check_disk_space() */

/*-------------------------------------------------------------------------
 * Function:    H5_check_disk_space_before_write
 *
 * Purpose:     Check disk space before a write operation with size estimation
 *
 * Return:      Success: SUCCEED
 *              Failure: FAIL (insufficient disk space)
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5_check_disk_space_before_write(const char *path, size_t data_size)
{
    long long required_bytes;
    herr_t    ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT

    /* Estimate required space with overhead for metadata, compression, chunking, etc. */
    required_bytes = (long long)data_size;

    /* Add 50% overhead for worst-case metadata, indexing, and fragmentation */
    required_bytes += (required_bytes / 2);

    /* Check if we have enough space */
    if (H5_check_disk_space(path, required_bytes) < 0)
        HGOTO_ERROR(H5E_DATASET, H5E_NOSPACE, FAIL, "insufficient disk space for write operation")

done:
    FUNC_LEAVE_NOAPI(ret_value)
} /* end H5_check_disk_space_before_write() */