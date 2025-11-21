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
 * Function:    H5T__conv_short_schar
 *
 * Purpose:     Converts `short' to `signed char'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_short_schar(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Ss(SHORT, SCHAR, short, signed char, SCHAR_MIN, SCHAR_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_short_uchar
 *
 * Purpose:     Converts `short' to `unsigned char'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_short_uchar(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_Su(SHORT, UCHAR, short, unsigned char, -, UCHAR_MAX);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_short_ushort
 *
 * Purpose:     Converts `short' to `unsigned short'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_short_ushort(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_su(SHORT, USHORT, short, unsigned short, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_short_int
 *
 * Purpose:     Converts `short' to `int'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_short_int(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                    size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                    void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sS(SHORT, INT, short, int, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_short_uint
 *
 * Purpose:     Converts `short' to `unsigned int'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_short_uint(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sU(SHORT, UINT, short, unsigned, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_short_long
 *
 * Purpose:     Converts `short' to `long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_short_long(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                     size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                     void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sS(SHORT, LONG, short, long, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_short_ulong
 *
 * Purpose:     Converts `short' to `unsigned long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_short_ulong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sU(SHORT, ULONG, short, unsigned long, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_short_llong
 *
 * Purpose:     Converts `short' to `long long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_short_llong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sS(SHORT, LLONG, short, long long, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_short_ullong
 *
 * Purpose:     Converts `short' to `unsigned long long'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_short_ullong(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_sU(SHORT, ULLONG, short, unsigned long long, -, -);
}

#ifdef H5_HAVE__FLOAT16
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_short__Float16
 *
 * Purpose:     Converts `short' to `_Float16'
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_short__Float16(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(SHORT, FLOAT16, short, H5__Float16, -, -);
}
#endif

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_short_float
 *
 * Purpose:     Convert native short to native float using hardware.
 *              This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_short_float(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                      size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                      void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(SHORT, FLOAT, short, float, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_short_double
 *
 * Purpose:     Convert native short to native double using hardware.
 *              This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_short_double(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                       size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                       void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(SHORT, DOUBLE, short, double, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_short_ldouble
 *
 * Purpose:     Convert native short to native long double using hardware.
 *              This is a fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_short_ldouble(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                        size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                        void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xF(SHORT, LDOUBLE, short, long double, -, -);
}

#ifdef H5_HAVE_COMPLEX_NUMBERS
/*-------------------------------------------------------------------------
 * Function:    H5T__conv_short_fcomplex
 *
 * Purpose:     Convert native short to native
 *              float _Complex / _Fcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_short_fcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(SHORT, FLOAT_COMPLEX, short, H5_float_complex, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_short_dcomplex
 *
 * Purpose:     Convert native short to native
 *              double _Complex / _Dcomplex using hardware. This is a fast
 *              special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_short_dcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(SHORT, DOUBLE_COMPLEX, short, H5_double_complex, -, -);
}

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_short_lcomplex
 *
 * Purpose:     Convert native short to native
 *              long double _Complex / _Lcomplex using hardware. This is a
 *              fast special case.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_short_lcomplex(const H5T_t *st, const H5T_t *dt, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
                         size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
                         void H5_ATTR_UNUSED *bkg)
{
    H5T_CONV_xZ(SHORT, LDOUBLE_COMPLEX, short, H5_ldouble_complex, -, -);
}
#endif
