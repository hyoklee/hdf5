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
 * Function:    H5T__conv_uint_schar
 *
 * Purpose:     Converts `unsigned int' to `signed char'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uint_schar(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Us(UINT, SCHAR, unsigned, signed char, -, SCHAR_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uint_uchar
 *
 * Purpose:     Converts `unsigned int' to `unsigned char'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uint_uchar(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Uu(UINT, UCHAR, unsigned, unsigned char, -, UCHAR_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uint_short
 *
 * Purpose:     Converts `unsigned int' to `short'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uint_short(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Us(UINT, SHORT, unsigned, short, -, SHRT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uint_ushort
 *
 * Purpose:     Converts `unsigned int' to `unsigned short'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uint_ushort(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Uu(UINT, USHORT, unsigned, unsigned short, -, USHRT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uint_int
 *
 * Purpose:     Converts `unsigned int' to `int'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uint_int(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                   size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                   void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_us(UINT, INT, unsigned, int, -, INT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uint_long
 *
 * Purpose:     Converts `unsigned int' to `long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uint_long(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                    size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                    void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uS(UINT, LONG, unsigned, long, -, LONG_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uint_ulong
 *
 * Purpose:     Converts `unsigned int' to `unsigned long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uint_ulong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uU(UINT, ULONG, unsigned, unsigned long, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uint_llong
 *
 * Purpose:     Converts `unsigned int' to `long long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uint_llong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uS(UINT, LLONG, unsigned, long long, -, LLONG_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uint_ullong
 *
 * Purpose:     Converts `unsigned int' to `unsigned long long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uint_ullong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uU(UINT, ULLONG, unsigned, unsigned long long, -, -);
}

#ifdef H5_HAVE__FLOAT16
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uint__Float16
 *
 * Purpose:     Converts `unsigned int' to `_Float16'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uint__Float16(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                        size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                        void H5_ATTR_UNUSED *bkg)
{
    /* Suppress warning about non-standard floating-point literal suffix */
    H5_WARN_NONSTD_SUFFIX_OFF
    H5T_CONV_Xf(UINT, FLOAT16, unsigned int, H5__Float16, -FLT16_MAX, FLT16_MAX);
    H5_WARN_NONSTD_SUFFIX_ON
}
#endif

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uint_float
 *
 * Purpose:     Convert native unsigned integer to native float using
 *              hardware.  This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uint_float(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(UINT, FLOAT, unsigned int, float, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uint_double
 *
 * Purpose:     Convert native unsigned integer to native double using
 *              hardware.  This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uint_double(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(UINT, DOUBLE, unsigned int, double, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uint_ldouble
 *
 * Purpose:     Convert native unsigned integer to native long double using
 *              hardware.  This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uint_ldouble(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(UINT, LDOUBLE, unsigned int, long double, -, -);
}

#ifdef H5_HAVE_COMPLEX_NUMBERS
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uint_fcomplex
 *
 * Purpose:     Convert native unsigned integer to native
 *              float _Complex / _Fcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uint_fcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                        size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                        void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(UINT, FLOAT_COMPLEX, unsigned int, H5_float_complex, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uint_dcomplex
 *
 * Purpose:     Convert native unsigned integer to native
 *              double _Complex / _Dcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uint_dcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                        size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                        void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(UINT, DOUBLE_COMPLEX, unsigned int, H5_double_complex, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uint_lcomplex
 *
 * Purpose:     Convert native unsigned integer to native
 *              long double _Complex / _Lcomplex using hardware. This is a
 *              fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uint_lcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                        size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                        void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(UINT, LDOUBLE_COMPLEX, unsigned int, H5_ldouble_complex, -, -);
}
#endif

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_long_schar
 *
 * Purpose:     Converts `long' to `signed char'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_long_schar(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Ss(LONG, SCHAR, long, signed char, SCHAR_MIN, SCHAR_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_long_uchar
 *
 * Purpose:     Converts `long' to `unsigned char'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_long_uchar(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Su(LONG, UCHAR, long, unsigned char, -, UCHAR_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_long_short
 *
 * Purpose:     Converts `long' to `short'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_long_short(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Ss(LONG, SHORT, long, short, SHRT_MIN, SHRT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_long_ushort
 *
 * Purpose:     Converts `long' to `unsigned short'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_long_ushort(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Su(LONG, USHORT, long, unsigned short, -, USHRT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_long_int
 *
 * Purpose:     Converts `long' to `int'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_long_int(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                   size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                   void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Ss(LONG, INT, long, int, INT_MIN, INT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_long_uint
 *
 * Purpose:     Converts `long' to `unsigned int'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_long_uint(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                    size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                    void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Su(LONG, UINT, long, unsigned, -, UINT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_long_ulong
 *
 * Purpose:     Converts `long' to `unsigned long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_long_ulong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_su(LONG, ULONG, long, unsigned long, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_long_llong
 *
 * Purpose:     Converts `long' to `long long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_long_llong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sS(LONG, LLONG, long, long long, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_long_ullong
 *
 * Purpose:     Converts `long' to `unsigned long long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_long_ullong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sU(LONG, ULLONG, long, unsigned long long, -, -);
}

#ifdef H5_HAVE__FLOAT16
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_long__Float16
 *
 * Purpose:     Converts `long' to `_Float16'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_long__Float16(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                        size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                        void H5_ATTR_UNUSED *bkg)
{
    /* Suppress warning about non-standard floating-point literal suffix */
    H5_WARN_NONSTD_SUFFIX_OFF
    H5T_CONV_Xf(LONG, FLOAT16, long, H5__Float16, -FLT16_MAX, FLT16_MAX);
    H5_WARN_NONSTD_SUFFIX_ON
}
#endif

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_long_float
 *
 * Purpose:     Convert native long to native float using hardware.
 *              This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_long_float(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(LONG, FLOAT, long, float, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_long_double
 *
 * Purpose:     Convert native long to native double using hardware.
 *              This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_long_double(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(LONG, DOUBLE, long, double, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_long_ldouble
 *
 * Purpose:     Convert native long to native long double using hardware.
 *              This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_long_ldouble(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(LONG, LDOUBLE, long, long double, -, -);
}

#ifdef H5_HAVE_COMPLEX_NUMBERS
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_long_fcomplex
 *
 * Purpose:     Convert native long to native
 *              float _Complex / _Fcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_long_fcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                        size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                        void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(LONG, FLOAT_COMPLEX, long, H5_float_complex, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_long_dcomplex
 *
 * Purpose:     Convert native long to native
 *              double _Complex / _Dcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_long_dcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                        size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                        void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(LONG, DOUBLE_COMPLEX, long, H5_double_complex, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_long_lcomplex
 *
 * Purpose:     Convert native long to native
 *              long double _Complex / _Lcomplex using hardware. This is a
 *              fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_long_lcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                        size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                        void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(LONG, LDOUBLE_COMPLEX, long, H5_ldouble_complex, -, -);
}
#endif

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ulong_schar
 *
 * Purpose:     Converts `unsigned long' to `signed char'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ulong_schar(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Us(ULONG, SCHAR, unsigned long, signed char, -, SCHAR_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ulong_uchar
 *
 * Purpose:     Converts `unsigned long' to `unsigned char'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ulong_uchar(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Uu(ULONG, UCHAR, unsigned long, unsigned char, -, UCHAR_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ulong_short
 *
 * Purpose:     Converts `unsigned long' to `short'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ulong_short(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Us(ULONG, SHORT, unsigned long, short, -, SHRT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ulong_ushort
 *
 * Purpose:     Converts `unsigned long' to `unsigned short'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ulong_ushort(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Uu(ULONG, USHORT, unsigned long, unsigned short, -, USHRT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ulong_int
 *
 * Purpose:     Converts `unsigned long' to `int'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ulong_int(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                    size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                    void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Us(ULONG, INT, unsigned long, int, -, INT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ulong_uint
 *
 * Purpose:     Converts `unsigned long' to `unsigned int'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ulong_uint(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Uu(ULONG, UINT, unsigned long, unsigned, -, UINT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ulong_long
 *
 * Purpose:     Converts `unsigned long' to `long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ulong_long(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_us(ULONG, LONG, unsigned long, long, -, LONG_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ulong_llong
 *
 * Purpose:     Converts `unsigned long' to `long long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ulong_llong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uS(ULONG, LLONG, unsigned long, long long, -, LLONG_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ulong_ullong
 *
 * Purpose:     Converts `unsigned long' to `unsigned long long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ulong_ullong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uU(ULONG, ULLONG, unsigned long, unsigned long long, -, -);
}

#ifdef H5_HAVE__FLOAT16
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ulong__Float16
 *
 * Purpose:     Converts `unsigned long' to `_Float16'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ulong__Float16(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    /* Suppress warning about non-standard floating-point literal suffix */
    H5_WARN_NONSTD_SUFFIX_OFF
    H5T_CONV_Xf(ULONG, FLOAT16, unsigned long, H5__Float16, -FLT16_MAX, FLT16_MAX);
    H5_WARN_NONSTD_SUFFIX_ON
}
#endif

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ulong_float
 *
 * Purpose:     Convert native unsigned long to native float using
 *              hardware. This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ulong_float(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(ULONG, FLOAT, unsigned long, float, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ulong_double
 *
 * Purpose:     Convert native unsigned long to native double using
 *              hardware. This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ulong_double(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(ULONG, DOUBLE, unsigned long, double, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ulong_ldouble
 *
 * Purpose:     Convert native unsigned long to native long double using
 *              hardware.  This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ulong_ldouble(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                        size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                        void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(ULONG, LDOUBLE, unsigned long, long double, -, -);
}

#ifdef H5_HAVE_COMPLEX_NUMBERS
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ulong_fcomplex
 *
 * Purpose:     Convert native unsigned long to native
 *              float _Complex / _Fcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ulong_fcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(ULONG, FLOAT_COMPLEX, unsigned long, H5_float_complex, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ulong_dcomplex
 *
 * Purpose:     Convert native unsigned long to native
 *              double _Complex / _Dcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ulong_dcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(ULONG, DOUBLE_COMPLEX, unsigned long, H5_double_complex, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ulong_lcomplex
 *
 * Purpose:     Convert native unsigned long to native
 *              long double _Complex / _Lcomplex using hardware. This is a
 *              fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ulong_lcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(ULONG, LDOUBLE_COMPLEX, unsigned long, H5_ldouble_complex, -, -);
}
#endif

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_llong_schar
 *
 * Purpose:     Converts `long long' to `signed char'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_llong_schar(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Ss(LLONG, SCHAR, long long, signed char, SCHAR_MIN, SCHAR_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_llong_uchar
 *
 * Purpose:     Converts `long long' to `unsigned char'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_llong_uchar(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Su(LLONG, UCHAR, long long, unsigned char, -, UCHAR_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_llong_short
 *
 * Purpose:     Converts `long long' to `short'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_llong_short(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Ss(LLONG, SHORT, long long, short, SHRT_MIN, SHRT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_llong_ushort
 *
 * Purpose:     Converts `long long' to `unsigned short'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_llong_ushort(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Su(LLONG, USHORT, long long, unsigned short, -, USHRT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_llong_int
 *
 * Purpose:     Converts `long long' to `int'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_llong_int(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                    size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                    void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Ss(LLONG, INT, long long, int, INT_MIN, INT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_llong_uint
 *
 * Purpose:     Converts `long long' to `unsigned int'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_llong_uint(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Su(LLONG, UINT, long long, unsigned, -, UINT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_llong_long
 *
 * Purpose:     Converts `long long' to `long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_llong_long(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Ss(LLONG, LONG, long long, long, LONG_MIN, LONG_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_llong_ulong
 *
 * Purpose:     Converts `long long' to `unsigned long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_llong_ulong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Su(LLONG, ULONG, long long, unsigned long, -, ULONG_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_llong_ullong
 *
 * Purpose:     Converts `long long' to `unsigned long long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_llong_ullong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_su(LLONG, ULLONG, long long, unsigned long long, -, -);
}

#ifdef H5_HAVE__FLOAT16
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_llong__Float16
 *
 * Purpose:     Converts `long long' to `_Float16'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_llong__Float16(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    /* Suppress warning about non-standard floating-point literal suffix */
    H5_WARN_NONSTD_SUFFIX_OFF
    H5T_CONV_Xf(LLONG, FLOAT16, long long, H5__Float16, -FLT16_MAX, FLT16_MAX);
    H5_WARN_NONSTD_SUFFIX_ON
}
#endif

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_llong_float
 *
 * Purpose:     Convert native long long to native float using hardware.
 *              This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_llong_float(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(LLONG, FLOAT, long long, float, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_llong_double
 *
 * Purpose:     Convert native long long to native double using hardware.
 *              This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_llong_double(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(LLONG, DOUBLE, long long, double, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_llong_ldouble
 *
 * Purpose:     Convert native long long to native long double using
 *              hardware.  This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
#ifdef H5T_CONV_INTERNAL_LLONG_LDOUBLE
herr_t
H5T__conv_llong_ldouble(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                        size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                        void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(LLONG, LDOUBLE, long long, long double, -, -);
}
#endif /* H5T_CONV_INTERNAL_LLONG_LDOUBLE */

#ifdef H5_HAVE_COMPLEX_NUMBERS
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_llong_fcomplex
 *
 * Purpose:     Convert native long long to native
 *              float _Complex / _Fcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_llong_fcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(LLONG, FLOAT_COMPLEX, long long, H5_float_complex, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_llong_dcomplex
 *
 * Purpose:     Convert native long long to native
 *              double _Complex / _Dcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_llong_dcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(LLONG, DOUBLE_COMPLEX, long long, H5_double_complex, -, -);
}

#ifdef H5T_CONV_INTERNAL_LLONG_LDOUBLE
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_llong_lcomplex
 *
 * Purpose:     Convert native long long to native
 *              long double _Complex / _Lcomplex using hardware. This is a
 *              fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_llong_lcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(LLONG, LDOUBLE_COMPLEX, long long, H5_ldouble_complex, -, -);
}
#endif /* H5T_CONV_INTERNAL_LLONG_LDOUBLE */
#endif /* H5_HAVE_COMPLEX_NUMBERS */

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ullong_schar
 *
 * Purpose:     Converts `unsigned long long' to `signed char'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ullong_schar(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Us(ULLONG, SCHAR, unsigned long long, signed char, -, SCHAR_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ullong_uchar
 *
 * Purpose:     Converts `unsigned long long' to `unsigned char'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ullong_uchar(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Uu(ULLONG, UCHAR, unsigned long long, unsigned char, -, UCHAR_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ullong_short
 *
 * Purpose:     Converts `unsigned long long' to `short'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ullong_short(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Us(ULLONG, SHORT, unsigned long long, short, -, SHRT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ullong_ushort
 *
 * Purpose:     Converts `unsigned long long' to `unsigned short'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ullong_ushort(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                        size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                        void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Uu(ULLONG, USHORT, unsigned long long, unsigned short, -, USHRT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ullong_int
 *
 * Purpose:     Converts `unsigned long long' to `int'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ullong_int(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Us(ULLONG, INT, unsigned long long, int, -, INT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ullong_uint
 *
 * Purpose:     Converts `unsigned long long' to `unsigned int'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ullong_uint(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Uu(ULLONG, UINT, unsigned long long, unsigned, -, UINT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ullong_long
 *
 * Purpose:     Converts `unsigned long long' to `long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ullong_long(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Us(ULLONG, LONG, unsigned long long, long, -, LONG_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ullong_ulong
 *
 * Purpose:     Converts `unsigned long long' to `unsigned long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ullong_ulong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Uu(ULLONG, ULONG, unsigned long long, unsigned long, -, ULONG_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ullong_llong
 *
 * Purpose:     Converts `unsigned long long' to `long long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ullong_llong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_us(ULLONG, LLONG, unsigned long long, long long, -, LLONG_MAX);
}

#ifdef H5_HAVE__FLOAT16
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ullong__Float16
 *
 * Purpose:     Converts `unsigned long long' to `_Float16'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ullong__Float16(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata,
                          const H5T_conv_ctx_t *conv_ctx, size_t nelmts, size_t buf_stride,
                          size_t H5_ATTR_UNUSED bkg_stride, void *buf, void H5_ATTR_UNUSED *bkg)
{
    /* Suppress warning about non-standard floating-point literal suffix */
    H5_WARN_NONSTD_SUFFIX_OFF
    H5T_CONV_Xf(ULLONG, FLOAT16, unsigned long long, H5__Float16, -FLT16_MAX, FLT16_MAX);
    H5_WARN_NONSTD_SUFFIX_ON
}
#endif

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ullong_float
 *
 * Purpose:     Convert native unsigned long long to native float using
 *              hardware.  This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ullong_float(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(ULLONG, FLOAT, unsigned long long, float, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ullong_double
 *
 * Purpose:     Convert native unsigned long long to native double using
 *              hardware.  This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ullong_double(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                        size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                        void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(ULLONG, DOUBLE, unsigned long long, double, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ullong_ldouble
 *
 * Purpose:     Convert native unsigned long long to native long double using
 *              hardware.  This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
#ifdef H5T_CONV_INTERNAL_ULLONG_LDOUBLE
herr_t
H5T__conv_ullong_ldouble(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(ULLONG, LDOUBLE, unsigned long long, long double, -, -);
}
#endif /*H5T_CONV_INTERNAL_ULLONG_LDOUBLE*/

#ifdef H5_HAVE_COMPLEX_NUMBERS
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ullong_fcomplex
 *
 * Purpose:     Convert native unsigned long long to native
 *              float _Complex / _Fcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ullong_fcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata,
                          const H5T_conv_ctx_t *conv_ctx, size_t nelmts, size_t buf_stride,
                          size_t H5_ATTR_UNUSED bkg_stride, void *buf, void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(ULLONG, FLOAT_COMPLEX, unsigned long long, H5_float_complex, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ullong_dcomplex
 *
 * Purpose:     Convert native unsigned long long to native
 *              double _Complex / _Dcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ullong_dcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata,
                          const H5T_conv_ctx_t *conv_ctx, size_t nelmts, size_t buf_stride,
                          size_t H5_ATTR_UNUSED bkg_stride, void *buf, void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(ULLONG, DOUBLE_COMPLEX, unsigned long long, H5_double_complex, -, -);
}

#ifdef H5T_CONV_INTERNAL_ULLONG_LDOUBLE
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_ullong_lcomplex
 *
 * Purpose:     Convert native unsigned long long to native
 *              long double _Complex / _Lcomplex using hardware. This is a
 *              fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_ullong_lcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata,
                          const H5T_conv_ctx_t *conv_ctx, size_t nelmts, size_t buf_stride,
                          size_t H5_ATTR_UNUSED bkg_stride, void *buf, void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(ULLONG, LDOUBLE_COMPLEX, unsigned long long, H5_ldouble_complex, -, -);
}
#endif /* H5T_CONV_INTERNAL_ULLONG_LDOUBLE */
#endif /* H5_HAVE_COMPLEX_NUMBERS */
