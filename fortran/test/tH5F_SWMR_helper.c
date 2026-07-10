/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.                                               *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF5. The full HDF5 copyright notice, including     *
 * terms governing use, modification, and redistribution, is contained in   *
 * the LICENSE file, which can be found at the root of the source code      *
 * distribution tree, or in https://www.hdfgroup.org/licenses.              *
 * If you do not have access to either file, you may request a copy from    *
 * help@hdfgroup.org.                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 * tH5F_SWMR_helper.c — C helper for the Fortran SWMR test.
 *
 * WHY THIS FILE EXISTS
 * --------------------
 * gfortran on s390x generates an R_390_64 (absolute 64-bit) relocation in
 * .rodata whenever it evaluates C_FUNLOC(). In a PIE-linked binary the
 * dynamic linker must make the read-only/execute segment temporarily writable
 * to apply the relocation (the ELF "TEXTREL" mechanism). QEMU s390x
 * user-mode emulation does not support TEXTREL, so the binary segfaults at
 * startup before reaching any test code.
 *
 * The fix is to avoid C_FUNLOC() in Fortran entirely. This file implements
 * the append-flush callback in C and exposes a small helper,
 * h5f_swmr_get_append_callback(), that writes the C function pointer into
 * a Fortran TYPE(C_FUNPTR) output variable. Fortran then passes that value
 * to h5pset_append_flush_f without ever calling C_FUNLOC.
 */

#include "hdf5.h" /* hid_t, hsize_t, herr_t, H5D_append_cb_t */

/*
 * Fortran module variable TH5F_SWMR::last_cur_dim, given a C binding via
 * BIND(C, NAME="th5f_swmr_last_cur_dim").  The callback updates it so the
 * test can verify the dimension value received.
 */
extern hsize_t th5f_swmr_last_cur_dim;

/*
 * The append-flush callback.  Matches H5D_append_cb_t:
 *   herr_t (*)(hid_t dataset_id, hsize_t *cur_dims, void *op_data)
 */
static herr_t
test_swmr_append_flush_cb(hid_t dataset_id, hsize_t *cur_dims, void *op_data)
{
    (void)dataset_id;

    if (cur_dims)
        th5f_swmr_last_cur_dim = cur_dims[0];

    /* op_data is C_LOC(callback_counter) — a pointer to a Fortran INTEGER(C_INT) */
    if (op_data)
        (*(int *)op_data)++;

    return 0;
}

/*
 * h5f_swmr_get_append_callback — store the callback address into *out.
 *
 * Fortran prototype (called as a BIND(C) subroutine):
 *   SUBROUTINE h5f_swmr_get_append_callback(fp) BIND(C)
 *     USE ISO_C_BINDING
 *     TYPE(C_FUNPTR), INTENT(OUT) :: fp
 *   END SUBROUTINE
 *
 * The Fortran compiler passes fp by reference (a pointer to a C_FUNPTR,
 * which is pointer-sized). Cast to H5D_append_cb_t* and write through it.
 */
void
h5f_swmr_get_append_callback(H5D_append_cb_t *out)
{
    *out = test_swmr_append_flush_cb;
}
