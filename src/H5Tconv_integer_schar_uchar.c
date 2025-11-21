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
 * Function:    H5T__conv_schar_uchar
 *
 * Purpose:     Converts `signed char' to `unsigned char'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_schar_uchar(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_su(SCHAR, UCHAR, signed char, unsigned char, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_schar_short
 *
 * Purpose:     Converts `signed char' to `short'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_schar_short(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sS(SCHAR, SHORT, signed char, short, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_schar_ushort
 *
 * Purpose:     Converts `signed char' to `unsigned short'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_schar_ushort(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sU(SCHAR, USHORT, signed char, unsigned short, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_schar_int
 *
 * Purpose:     Converts `signed char' to `int'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_schar_int(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                    size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                    void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sS(SCHAR, INT, signed char, int, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_schar_uint
 *
 * Purpose:     Converts `signed char' to `unsigned int'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_schar_uint(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sU(SCHAR, UINT, signed char, unsigned, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_schar_long
 *
 * Purpose:     Converts `signed char' to `long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_schar_long(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sS(SCHAR, LONG, signed char, long, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_schar_ulong
 *
 * Purpose:     Converts `signed char' to `unsigned long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_schar_ulong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sU(SCHAR, ULONG, signed char, unsigned long, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_schar_llong
 *
 * Purpose:     Converts `signed char' to `long long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_schar_llong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sS(SCHAR, LLONG, signed char, long long, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_schar_ullong
 *
 * Purpose:     Converts `signed char' to `unsigned long long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_schar_ullong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sU(SCHAR, ULLONG, signed char, unsigned long long, -, -);
}

#ifdef H5_HAVE__FLOAT16
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_schar__Float16
 *
 * Purpose:     Converts `signed char` to `_Float16`
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_schar__Float16(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(SCHAR, FLOAT16, signed char, H5__Float16, -, -);
}
#endif

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_schar_float
 *
 * Purpose:     Convert native signed char to native float using hardware.
 *              This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_schar_float(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(SCHAR, FLOAT, signed char, float, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_schar_double
 *
 * Purpose:     Convert native signed char to native double using hardware.
 *              This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_schar_double(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(SCHAR, DOUBLE, signed char, double, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_schar_ldouble
 *
 * Purpose:     Convert native signed char to native long double using
 *              hardware. This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_schar_ldouble(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                        size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                        void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(SCHAR, LDOUBLE, signed char, long double, -, -);
}

#ifdef H5_HAVE_COMPLEX_NUMBERS
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_schar_fcomplex
 *
 * Purpose:     Convert native signed char to native
 *              float _Complex / _Fcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_schar_fcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(SCHAR, FLOAT_COMPLEX, signed char, H5_float_complex, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_schar_dcomplex
 *
 * Purpose:     Convert native signed char to native
 *              double _Complex / _Dcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_schar_dcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(SCHAR, DOUBLE_COMPLEX, signed char, H5_double_complex, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_schar_lcomplex
 *
 * Purpose:     Convert native signed char to native
 *              long double _Complex / _Lcomplex using hardware. This is a
 *              fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_schar_lcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(SCHAR, LDOUBLE_COMPLEX, signed char, H5_ldouble_complex, -, -);
}
#endif

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uchar_schar
 *
 * Purpose:     Converts `unsigned char' to `signed char'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uchar_schar(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_us(UCHAR, SCHAR, unsigned char, signed char, -, SCHAR_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uchar_short
 *
 * Purpose:     Converts `unsigned char' to `short'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uchar_short(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uS(UCHAR, SHORT, unsigned char, short, -, SHRT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uchar_ushort
 *
 * Purpose:     Converts `unsigned char' to `unsigned short'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uchar_ushort(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uU(UCHAR, USHORT, unsigned char, unsigned short, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uchar_int
 *
 * Purpose:     Converts `unsigned char' to `int'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uchar_int(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                    size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                    void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uS(UCHAR, INT, unsigned char, int, -, INT_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uchar_uint
 *
 * Purpose:     Converts `unsigned char' to `unsigned int'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uchar_uint(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uU(UCHAR, UINT, unsigned char, unsigned, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uchar_long
 *
 * Purpose:     Converts `unsigned char' to `long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uchar_long(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uS(UCHAR, LONG, unsigned char, long, -, LONG_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uchar_ulong
 *
 * Purpose:     Converts `unsigned char' to `unsigned long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uchar_ulong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uU(UCHAR, ULONG, unsigned char, unsigned long, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uchar_llong
 *
 * Purpose:     Converts `unsigned char' to `long long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uchar_llong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uS(UCHAR, LLONG, unsigned char, long long, -, LLONG_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uchar_ullong
 *
 * Purpose:     Converts `unsigned char' to `unsigned long long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uchar_ullong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_uU(UCHAR, ULLONG, unsigned char, unsigned long long, -, -);
}

#ifdef H5_HAVE__FLOAT16
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uchar__Float16
 *
 * Purpose:     Converts `unsigned char` to `_Float16`
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uchar__Float16(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(UCHAR, FLOAT16, unsigned char, H5__Float16, -, -);
}
#endif

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uchar_float
 *
 * Purpose:     Convert native unsigned char to native float using
 *              hardware. This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uchar_float(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(UCHAR, FLOAT, unsigned char, float, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uchar_double
 *
 * Purpose:     Convert native unsigned char to native double using
 *              hardware. This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uchar_double(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(UCHAR, DOUBLE, unsigned char, double, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uchar_ldouble
 *
 * Purpose:     Convert native unsigned char to native long double using
 *              hardware. This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uchar_ldouble(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                        size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                        void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(UCHAR, LDOUBLE, unsigned char, long double, -, -);
}

#ifdef H5_HAVE_COMPLEX_NUMBERS
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uchar_fcomplex
 *
 * Purpose:     Convert native unsigned char to native
 *              float _Complex / _Fcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uchar_fcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(UCHAR, FLOAT_COMPLEX, unsigned char, H5_float_complex, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uchar_dcomplex
 *
 * Purpose:     Convert native unsigned char to native
 *              double _Complex / _Dcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uchar_dcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(UCHAR, DOUBLE_COMPLEX, unsigned char, H5_double_complex, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_uchar_lcomplex
 *
 * Purpose:     Convert native unsigned char to native
 *              long double _Complex / _Lcomplex using hardware. This is a
 *              fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_uchar_lcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(UCHAR, LDOUBLE_COMPLEX, unsigned char, H5_ldouble_complex, -, -);
}
#endif

