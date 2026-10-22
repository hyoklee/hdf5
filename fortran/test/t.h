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

#include "hdf5.h"
#include "H5private.h"
#include "../src/H5f90i.h"
#include "../src/H5f90proto.h"

char *h5_fixname(const char *base_name, hid_t fapl, char *fullname, size_t size);

/*
 *  Functions from t.c
 */

H5FC_TEST_DLL int_f h5_fixname_c(_fcd base_name, size_t_f *base_namelen, hid_t_f *fapl, _fcd full_name,
                                 size_t_f *full_namelen);

H5FC_TEST_DLL int_f h5_cleanup_c(_fcd base_name, size_t_f *base_namelen, hid_t_f *fapl);

H5FC_TEST_DLL H5_ATTR_NORETURN void h5_exit_c(int_f *status);

H5FC_TEST_DLL void h5_env_nocleanup_c(int_f *status);
