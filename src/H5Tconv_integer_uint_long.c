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
 * Purpose: Datatype conversion functions for integer datatypes
 */

/****************/
/* Module Setup */
/****************/
#include "H5Tmodule.h" /* This source code file is part of the H5T module */

/***********/
/* Headers */
/***********/
#include "H5private.h" /* Generic Functions                    */
#include "H5Tconv.h"   /* Datatype conversions                 */
#include "H5Tconv_macros.h"
#include "H5Tconv_integer.h"

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_int_schar
 *
 * Purpose:     Converts `int' to `signed char'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_int_schar(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                    size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                    void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Ss(INT, SCHAR, int, signed char, SCHAR_MIN, SCHAR_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_int_uchar
 *
 * Purpose:     Converts `int' to `unsigned char'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_int_uchar(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                    size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                    void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Su(INT, UCHAR, int, unsigned char, -, UCHAR_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_int_short
 *
 * Purpose:     Converts `int' to `short'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_int_short(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                    size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                    void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Ss(INT, SHORT, int, short, SHRT_MIN, SHRT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_int_ushort
 *
 * Purpose:     Converts `int' to `unsigned short'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_int_ushort(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Su(INT, USHORT, int, unsigned short, -, USHRT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_int_uint
 *
 * Purpose:     Converts `int' to `unsigned int'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_int_uint(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                   size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                   void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_su(INT, UINT, int, unsigned, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_int_long
 *
 * Purpose:     Converts `int' to `long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_int_long(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                   size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                   void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sS(INT, LONG, int, long, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_int_ulong
 *
 * Purpose:     Converts `int' to `unsigned long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_int_ulong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                    size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                    void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sU(INT, LONG, int, unsigned long, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_int_llong
 *
 * Purpose:     Converts `int' to `long long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_int_llong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                    size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                    void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sS(INT, LLONG, int, long long, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_int_ullong
 *
 * Purpose:     Converts `int' to `unsigned long long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_int_ullong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sU(INT, ULLONG, int, unsigned long long, -, -);
}

#ifdef H5_HAVE__FLOAT16
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_int__Float16
 *
 * Purpose:     Converts `int' to `_Float16'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_int__Float16(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    /* Suppress warning about non-standard floating-point literal suffix */
    H5_WARN_NONSTD_SUFFIX_OFF
    H5T_CONV_Xf(INT, FLOAT16, int, H5__Float16, -FLT16_MAX, FLT16_MAX);
    H5_WARN_NONSTD_SUFFIX_ON
}
#endif

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_int_float
 *
 * Purpose:     Convert native integer to native float using hardware.
 *              This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_int_float(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                    size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                    void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(INT, FLOAT, int, float, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_int_double
 *
 * Purpose:     Convert native integer to native double using hardware.
 *              This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_int_double(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(INT, DOUBLE, int, double, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_int_ldouble
 *
 * Purpose:     Convert native integer to native long double using hardware.
 *              This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_int_ldouble(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(INT, LDOUBLE, int, long double, -, -);
}

#ifdef H5_HAVE_COMPLEX_NUMBERS
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_int_fcomplex
 *
 * Purpose:     Convert native integer to native
 *              float _Complex / _Fcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_int_fcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(INT, FLOAT_COMPLEX, int, H5_float_complex, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_int_dcomplex
 *
 * Purpose:     Convert native integer to native
 *              double _Complex / _Dcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_int_dcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(INT, DOUBLE_COMPLEX, int, H5_double_complex, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_int_lcomplex
 *
 * Purpose:     Convert native integer to native
 *              long double _Complex / _Lcomplex using hardware. This is a
 *              fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_int_lcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(INT, LDOUBLE_COMPLEX, int, H5_ldouble_complex, -, -);
}
#endif
