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
 * Function:    H5T__conv_ushort_schar
 *
 * Purpose:     Converts `unsigned short' to `signed char'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ushort_schar(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Us(USHORT, SCHAR, unsigned short, signed char, -, SCHAR_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ushort_uchar
 *
 * Purpose:     Converts `unsigned short' to `unsigned char'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ushort_uchar(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Uu(USHORT, UCHAR, unsigned short, unsigned char, -, UCHAR_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ushort_short
 *
 * Purpose:     Converts `unsigned short' to `short'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ushort_short(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_us(USHORT, SHORT, unsigned short, short, -, SHRT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ushort_int
 *
 * Purpose:     Converts `unsigned short' to `int'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ushort_int(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uS(USHORT, INT, unsigned short, int, -, INT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ushort_uint
 *
 * Purpose:     Converts `unsigned short' to `unsigned int'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ushort_uint(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uU(USHORT, UINT, unsigned short, unsigned, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ushort_long
 *
 * Purpose:     Converts `unsigned short' to `long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ushort_long(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uS(USHORT, LONG, unsigned short, long, -, LONG_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ushort_ulong
 *
 * Purpose:     Converts `unsigned short' to `unsigned long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ushort_ulong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uU(USHORT, ULONG, unsigned short, unsigned long, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ushort_llong
 *
 * Purpose:     Converts `unsigned short' to `long long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ushort_llong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uS(USHORT, LLONG, unsigned short, long long, -, LLONG_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ushort_ullong
 *
 * Purpose:     Converts `unsigned short' to `unsigned long long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ushort_ullong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                        size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                        void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uU(USHORT, ULLONG, unsigned short, unsigned long long, -, -);
}

#ifdef H5_HAVE__FLOAT16
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ushort__Float16
 *
 * Purpose:     Converts `unsigned short' to `_Float16'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ushort__Float16(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata,
                          const H5T_conv_ctx_t *conv_ctx, size_t nelmts, size_t buf_stride,
                          size_t H5_ATTR_UNUSED bkg_stride, void *buf, void H5_ATTR_UNUSED *bkg)
{
    /* Suppress warning about non-standard floating-point literal suffix */
    H5_WARN_NONSTD_SUFFIX_OFF
    H5T_CONV_Xf(USHORT, FLOAT16, unsigned short, H5__Float16, -FLT16_MAX, FLT16_MAX);
    H5_WARN_NONSTD_SUFFIX_ON
}
#endif

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ushort_float
 *
 * Purpose:     Convert native unsigned short to native float using
 *              hardware. This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ushort_float(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(USHORT, FLOAT, unsigned short, float, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ushort_double
 *
 * Purpose:     Convert native unsigned short to native double using
 *              hardware. This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ushort_double(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                        size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                        void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(USHORT, DOUBLE, unsigned short, double, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ushort_ldouble
 *
 * Purpose:     Convert native unsigned short to native long double using
 *              hardware. This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ushort_ldouble(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(USHORT, LDOUBLE, unsigned short, long double, -, -);
}

#ifdef H5_HAVE_COMPLEX_NUMBERS
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ushort_fcomplex
 *
 * Purpose:     Convert native unsigned short to native
 *              float _Complex / _Fcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ushort_fcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata,
                          const H5T_conv_ctx_t *conv_ctx, size_t nelmts, size_t buf_stride,
                          size_t H5_ATTR_UNUSED bkg_stride, void *buf, void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(USHORT, FLOAT_COMPLEX, unsigned short, H5_float_complex, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ushort_dcomplex
 *
 * Purpose:     Convert native unsigned short to native
 *              double _Complex / _Dcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ushort_dcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata,
                          const H5T_conv_ctx_t *conv_ctx, size_t nelmts, size_t buf_stride,
                          size_t H5_ATTR_UNUSED bkg_stride, void *buf, void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(USHORT, DOUBLE_COMPLEX, unsigned short, H5_double_complex, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ushort_lcomplex
 *
 * Purpose:     Convert native unsigned short to native
 *              long double _Complex / _Lcomplex using hardware. This is a
 *              fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ushort_lcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata,
                          const H5T_conv_ctx_t *conv_ctx, size_t nelmts, size_t buf_stride,
                          size_t H5_ATTR_UNUSED bkg_stride, void *buf, void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(USHORT, LDOUBLE_COMPLEX, unsigned short, H5_ldouble_complex, -, -);
}
#endif

