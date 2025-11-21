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
 * Function:    H5T__conv_i_i
 *
 * Purpose:     Convert one integer type to another. This is the catch-all
 *              function for integer conversions and is probably not
 *              particularly fast.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_i_i(const H5T_t *src, const H5T_t *dst, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
              size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
              void H5_ATTR_UNUSED *bkg)
{
    ssize_t        src_delta, dst_delta; /*source & destination stride    */
    int            direction;            /*direction of traversal    */
    size_t         elmtno;               /*element number        */
    size_t         half_size;            /*half the type size        */
    size_t         olap;                 /*num overlapping elements    */
    uint8_t       *s, *sp, *d, *dp;      /*source and dest traversal ptrs*/
    uint8_t       *src_rev  = NULL;      /*order-reversed source buffer  */
    uint8_t        dbuf[64] = {0};       /*temp destination buffer    */
    size_t         first;
    ssize_t        sfirst;              /*a signed version of `first'    */
    size_t         i;                   /*Local index variables         */
    H5T_conv_ret_t except_ret;          /*return of callback function   */
    bool           reverse;             /*if reverse the order of destination        */
    herr_t         ret_value = SUCCEED; /* Return value */

    FUNC_ENTER_PACKAGE

    switch (cdata->command) {
        case H5T_CONV_INIT:
            if (NULL == src || NULL == dst)
                HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a datatype");
            if (H5T_ORDER_LE != src->shared->u.atomic.order && H5T_ORDER_BE != src->shared->u.atomic.order)
                HGOTO_ERROR(H5E_DATATYPE, H5E_UNSUPPORTED, FAIL, "unsupported byte order");
            if (H5T_ORDER_LE != dst->shared->u.atomic.order && H5T_ORDER_BE != dst->shared->u.atomic.order)
                HGOTO_ERROR(H5E_DATATYPE, H5E_UNSUPPORTED, FAIL, "unsupported byte order");
            if (dst->shared->size > sizeof dbuf)
                HGOTO_ERROR(H5E_DATATYPE, H5E_UNSUPPORTED, FAIL, "destination size is too large");
            cdata->need_bkg = H5T_BKG_NO;
            break;

        case H5T_CONV_FREE:
            break;

        case H5T_CONV_CONV:
            if (NULL == src || NULL == dst)
                HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a datatype");
            if (NULL == conv_ctx)
                HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "invalid datatype conversion context pointer");

            /*
             * Do we process the values from beginning to end or vice versa? Also,
             * how many of the elements have the source and destination areas
             * overlapping?
             */
            if (src->shared->size == dst->shared->size || buf_stride) {
                sp = dp   = (uint8_t *)buf;
                direction = 1;
                olap      = nelmts;
            }
            else if (src->shared->size >= dst->shared->size) {
                double olap_d =
                    ceil((double)(dst->shared->size) / (double)(src->shared->size - dst->shared->size));

                olap = (size_t)olap_d;
                sp = dp   = (uint8_t *)buf;
                direction = 1;
            }
            else {
                double olap_d =
                    ceil((double)(src->shared->size) / (double)(dst->shared->size - src->shared->size));
                olap      = (size_t)olap_d;
                sp        = (uint8_t *)buf + (nelmts - 1) * src->shared->size;
                dp        = (uint8_t *)buf + (nelmts - 1) * dst->shared->size;
                direction = -1;
            }

            /*
             * Direction & size of buffer traversal.
             */
            H5_CHECK_OVERFLOW(buf_stride, size_t, ssize_t);
            H5_CHECK_OVERFLOW(src->shared->size, size_t, ssize_t);
            H5_CHECK_OVERFLOW(dst->shared->size, size_t, ssize_t);
            src_delta = (ssize_t)direction * (ssize_t)(buf_stride ? buf_stride : src->shared->size);
            dst_delta = (ssize_t)direction * (ssize_t)(buf_stride ? buf_stride : dst->shared->size);

            /* Allocate space for order-reversed source buffer */
            if (conv_ctx->u.conv.cb_struct.func)
                if (NULL == (src_rev = H5MM_calloc(src->shared->size)))
                    HGOTO_ERROR(H5E_DATATYPE, H5E_CANTALLOC, FAIL, "unable to allocate temporary buffer");

            /* The conversion loop */
            for (elmtno = 0; elmtno < nelmts; elmtno++) {

                /*
                 * If the source and destination buffers overlap then use a
                 * temporary buffer for the destination.
                 */
                if (direction > 0) {
                    s = sp;
                    d = elmtno < olap ? dbuf : dp;
                }
                else {
                    s = sp;
                    d = elmtno + olap >= nelmts ? dbuf : dp;
                }
#ifndef NDEBUG
                /* I don't quite trust the overlap calculations yet  */
                if (d == dbuf) {
                    assert((dp >= sp && dp < sp + src->shared->size) ||
                           (sp >= dp && sp < dp + dst->shared->size));
                }
                else {
                    assert((dp < sp && dp + dst->shared->size <= sp) ||
                           (sp < dp && sp + src->shared->size <= dp));
                }
#endif

                /*
                 * Put the data in little endian order so our loops aren't so
                 * complicated.  We'll do all the conversion stuff assuming
                 * little endian and then we'll fix the order at the end.
                 */
                if (H5T_ORDER_BE == src->shared->u.atomic.order) {
                    half_size = src->shared->size / 2;
                    for (i = 0; i < half_size; i++) {
                        uint8_t tmp                    = s[src->shared->size - (i + 1)];
                        s[src->shared->size - (i + 1)] = s[i];
                        s[i]                           = tmp;
                    }
                }

                /*
                 * What is the bit number for the msb bit of S which is set? The
                 * bit number is relative to the significant part of the number.
                 */
                sfirst = H5T__bit_find(s, src->shared->u.atomic.offset, src->shared->u.atomic.prec,
                                       H5T_BIT_MSB, true);
                first  = (size_t)sfirst;

                /* Set these variables to default */
                except_ret = H5T_CONV_UNHANDLED;
                reverse    = true;

                if (sfirst < 0) {
                    /*
                     * The source has no bits set and must therefore be zero.
                     * Set the destination to zero.
                     */
                    H5T__bit_set(d, dst->shared->u.atomic.offset, dst->shared->u.atomic.prec, false);
                }
                else if (H5T_SGN_NONE == src->shared->u.atomic.u.i.sign &&
                         H5T_SGN_NONE == dst->shared->u.atomic.u.i.sign) {
                    /*
                     * Source and destination are both unsigned, but if the
                     * source has more precision bits than the destination then
                     * it's possible to overflow.  When overflow occurs the
                     * destination will be set to the maximum possible value.
                     */
                    if (src->shared->u.atomic.prec <= dst->shared->u.atomic.prec) {
                        H5T__bit_copy(d, dst->shared->u.atomic.offset, s, src->shared->u.atomic.offset,
                                      src->shared->u.atomic.prec);
                        H5T__bit_set(d, dst->shared->u.atomic.offset + src->shared->u.atomic.prec,
                                     dst->shared->u.atomic.prec - src->shared->u.atomic.prec, false);
                    }
                    else if (first >= dst->shared->u.atomic.prec) {
                        /*overflow*/
                        if (conv_ctx->u.conv.cb_struct
                                .func) { /*If user's exception handler is present, use it*/
                            /* Reverse source buffer order first */
                            H5T__reverse_order(src_rev, s, src);

                            /* Prepare & restore library for user callback */
                            H5_BEFORE_USER_CB(FAIL)
                                {
                                    except_ret = (conv_ctx->u.conv.cb_struct.func)(
                                        H5T_CONV_EXCEPT_RANGE_HI, conv_ctx->u.conv.src_type_id,
                                        conv_ctx->u.conv.dst_type_id, src_rev, d,
                                        conv_ctx->u.conv.cb_struct.user_data);
                                }
                            H5_AFTER_USER_CB(FAIL)
                        }

                        if (except_ret == H5T_CONV_UNHANDLED) {
                            H5T__bit_set(d, dst->shared->u.atomic.offset, dst->shared->u.atomic.prec, true);
                        }
                        else if (except_ret == H5T_CONV_ABORT)
                            HGOTO_ERROR(H5E_DATATYPE, H5E_CANTCONVERT, FAIL,
                                        "can't handle conversion exception");
                        else if (except_ret == H5T_CONV_HANDLED)
                            /*Don't reverse because user handles it already*/
                            reverse = false;
                    }
                    else {
                        H5T__bit_copy(d, dst->shared->u.atomic.offset, s, src->shared->u.atomic.offset,
                                      dst->shared->u.atomic.prec);
                    }
                }
                else if (H5T_SGN_2 == src->shared->u.atomic.u.i.sign &&
                         H5T_SGN_NONE == dst->shared->u.atomic.u.i.sign) {
                    /*
                     * If the source is signed and the destination isn't then we
                     * can have overflow if the source contains more bits than
                     * the destination (destination is set to the maximum
                     * possible value) or overflow if the source is negative
                     * (destination is set to zero).
                     */
                    if (first + 1 == src->shared->u.atomic.prec) {
                        /*overflow - source is negative*/
                        if (conv_ctx->u.conv.cb_struct
                                .func) { /*If user's exception handler is present, use it*/
                            /* Reverse source buffer order first */
                            H5T__reverse_order(src_rev, s, src);

                            /* Prepare & restore library for user callback */
                            H5_BEFORE_USER_CB(FAIL)
                                {
                                    except_ret = (conv_ctx->u.conv.cb_struct.func)(
                                        H5T_CONV_EXCEPT_RANGE_LOW, conv_ctx->u.conv.src_type_id,
                                        conv_ctx->u.conv.dst_type_id, src_rev, d,
                                        conv_ctx->u.conv.cb_struct.user_data);
                                }
                            H5_AFTER_USER_CB(FAIL)
                        }

                        if (except_ret == H5T_CONV_UNHANDLED) {
                            H5T__bit_set(d, dst->shared->u.atomic.offset, dst->shared->u.atomic.prec, false);
                        }
                        else if (except_ret == H5T_CONV_ABORT)
                            HGOTO_ERROR(H5E_DATATYPE, H5E_CANTCONVERT, FAIL,
                                        "can't handle conversion exception");
                        else if (except_ret == H5T_CONV_HANDLED)
                            /*Don't reverse because user handles it already*/
                            reverse = false;
                    }
                    else if (src->shared->u.atomic.prec < dst->shared->u.atomic.prec) {
                        H5T__bit_copy(d, dst->shared->u.atomic.offset, s, src->shared->u.atomic.offset,
                                      src->shared->u.atomic.prec - 1);
                        H5T__bit_set(d, dst->shared->u.atomic.offset + src->shared->u.atomic.prec - 1,
                                     (dst->shared->u.atomic.prec - src->shared->u.atomic.prec) + 1, false);
                    }
                    else if (first >= dst->shared->u.atomic.prec) {
                        /*overflow - source is positive*/
                        if (conv_ctx->u.conv.cb_struct
                                .func) { /*If user's exception handler is present, use it*/
                            /* Reverse source buffer order first */
                            H5T__reverse_order(src_rev, s, src);

                            /* Prepare & restore library for user callback */
                            H5_BEFORE_USER_CB(FAIL)
                                {
                                    except_ret = (conv_ctx->u.conv.cb_struct.func)(
                                        H5T_CONV_EXCEPT_RANGE_HI, conv_ctx->u.conv.src_type_id,
                                        conv_ctx->u.conv.dst_type_id, src_rev, d,
                                        conv_ctx->u.conv.cb_struct.user_data);
                                }
                            H5_AFTER_USER_CB(FAIL)
                        }

                        if (except_ret == H5T_CONV_UNHANDLED)
                            H5T__bit_set(d, dst->shared->u.atomic.offset, dst->shared->u.atomic.prec, true);
                        else if (except_ret == H5T_CONV_ABORT)
                            HGOTO_ERROR(H5E_DATATYPE, H5E_CANTCONVERT, FAIL,
                                        "can't handle conversion exception");
                        else if (except_ret == H5T_CONV_HANDLED)
                            /*Don't reverse because user handles it already*/
                            reverse = false;
                    }
                    else {
                        H5T__bit_copy(d, dst->shared->u.atomic.offset, s, src->shared->u.atomic.offset,
                                      dst->shared->u.atomic.prec);
                    }
                }
                else if (H5T_SGN_NONE == src->shared->u.atomic.u.i.sign &&
                         H5T_SGN_2 == dst->shared->u.atomic.u.i.sign) {
                    /*
                     * If the source is not signed but the destination is then
                     * overflow can occur in which case the destination is set to
                     * the largest possible value (all bits set except the msb).
                     */
                    if (first + 1 >= dst->shared->u.atomic.prec) {
                        /*overflow*/
                        if (conv_ctx->u.conv.cb_struct
                                .func) { /*If user's exception handler is present, use it*/
                            /* Reverse source buffer order first */
                            H5T__reverse_order(src_rev, s, src);

                            /* Prepare & restore library for user callback */
                            H5_BEFORE_USER_CB(FAIL)
                                {
                                    except_ret = (conv_ctx->u.conv.cb_struct.func)(
                                        H5T_CONV_EXCEPT_RANGE_HI, conv_ctx->u.conv.src_type_id,
                                        conv_ctx->u.conv.dst_type_id, src_rev, d,
                                        conv_ctx->u.conv.cb_struct.user_data);
                                }
                            H5_AFTER_USER_CB(FAIL)
                        }

                        if (except_ret == H5T_CONV_UNHANDLED) {
                            H5T__bit_set(d, dst->shared->u.atomic.offset, dst->shared->u.atomic.prec - 1,
                                         true);
                            H5T__bit_set(d, (dst->shared->u.atomic.offset + dst->shared->u.atomic.prec - 1),
                                         (size_t)1, false);
                        }
                        else if (except_ret == H5T_CONV_ABORT)
                            HGOTO_ERROR(H5E_DATATYPE, H5E_CANTCONVERT, FAIL,
                                        "can't handle conversion exception");
                        else if (except_ret == H5T_CONV_HANDLED)
                            /*Don't reverse because user handles it already*/
                            reverse = false;
                    }
                    else if (src->shared->u.atomic.prec < dst->shared->u.atomic.prec) {
                        H5T__bit_copy(d, dst->shared->u.atomic.offset, s, src->shared->u.atomic.offset,
                                      src->shared->u.atomic.prec);
                        H5T__bit_set(d, dst->shared->u.atomic.offset + src->shared->u.atomic.prec,
                                     dst->shared->u.atomic.prec - src->shared->u.atomic.prec, false);
                    }
                    else {
                        H5T__bit_copy(d, dst->shared->u.atomic.offset, s, src->shared->u.atomic.offset,
                                      dst->shared->u.atomic.prec);
                    }
                }
                else if (first + 1 == src->shared->u.atomic.prec) {
                    /*
                     * Both the source and the destination are signed and the
                     * source value is negative.  We could experience overflow
                     * if the destination isn't wide enough in which case the
                     * destination is set to a negative number with the largest
                     * possible magnitude.
                     */
                    ssize_t sfz = H5T__bit_find(s, src->shared->u.atomic.offset,
                                                src->shared->u.atomic.prec - 1, H5T_BIT_MSB, false);
                    size_t  fz  = (size_t)sfz;

                    if (sfz >= 0 && fz + 1 >= dst->shared->u.atomic.prec) {
                        /*overflow*/
                        if (conv_ctx->u.conv.cb_struct
                                .func) { /*If user's exception handler is present, use it*/
                            /* Reverse source buffer order first */
                            H5T__reverse_order(src_rev, s, src);

                            /* Prepare & restore library for user callback */
                            H5_BEFORE_USER_CB(FAIL)
                                {
                                    except_ret = (conv_ctx->u.conv.cb_struct.func)(
                                        H5T_CONV_EXCEPT_RANGE_LOW, conv_ctx->u.conv.src_type_id,
                                        conv_ctx->u.conv.dst_type_id, src_rev, d,
                                        conv_ctx->u.conv.cb_struct.user_data);
                                }
                            H5_AFTER_USER_CB(FAIL)
                        }

                        if (except_ret == H5T_CONV_UNHANDLED) {
                            H5T__bit_set(d, dst->shared->u.atomic.offset, dst->shared->u.atomic.prec - 1,
                                         false);
                            H5T__bit_set(d, (dst->shared->u.atomic.offset + dst->shared->u.atomic.prec - 1),
                                         (size_t)1, true);
                        }
                        else if (except_ret == H5T_CONV_ABORT)
                            HGOTO_ERROR(H5E_DATATYPE, H5E_CANTCONVERT, FAIL,
                                        "can't handle conversion exception");
                        else if (except_ret == H5T_CONV_HANDLED)
                            /*Don't reverse because user handles it already*/
                            reverse = false;
                    }
                    else if (src->shared->u.atomic.prec < dst->shared->u.atomic.prec) {
                        H5T__bit_copy(d, dst->shared->u.atomic.offset, s, src->shared->u.atomic.offset,
                                      src->shared->u.atomic.prec);
                        H5T__bit_set(d, dst->shared->u.atomic.offset + src->shared->u.atomic.prec,
                                     dst->shared->u.atomic.prec - src->shared->u.atomic.prec, true);
                    }
                    else {
                        H5T__bit_copy(d, dst->shared->u.atomic.offset, s, src->shared->u.atomic.offset,
                                      dst->shared->u.atomic.prec);
                    }
                }
                else {
                    /*
                     * Source and destination are both signed but the source
                     * value is positive.  We could have an overflow in which
                     * case the destination is set to the largest possible
                     * positive value.
                     */
                    if (first + 1 >= dst->shared->u.atomic.prec) {
                        /*overflow*/
                        if (conv_ctx->u.conv.cb_struct
                                .func) { /*If user's exception handler is present, use it*/
                            /* Reverse source buffer order first */
                            H5T__reverse_order(src_rev, s, src);

                            /* Prepare & restore library for user callback */
                            H5_BEFORE_USER_CB(FAIL)
                                {
                                    except_ret = (conv_ctx->u.conv.cb_struct.func)(
                                        H5T_CONV_EXCEPT_RANGE_HI, conv_ctx->u.conv.src_type_id,
                                        conv_ctx->u.conv.dst_type_id, src_rev, d,
                                        conv_ctx->u.conv.cb_struct.user_data);
                                }
                            H5_AFTER_USER_CB(FAIL)
                        }

                        if (except_ret == H5T_CONV_UNHANDLED) {
                            H5T__bit_set(d, dst->shared->u.atomic.offset, dst->shared->u.atomic.prec - 1,
                                         true);
                            H5T__bit_set(d, (dst->shared->u.atomic.offset + dst->shared->u.atomic.prec - 1),
                                         (size_t)1, false);
                        }
                        else if (except_ret == H5T_CONV_ABORT)
                            HGOTO_ERROR(H5E_DATATYPE, H5E_CANTCONVERT, FAIL,
                                        "can't handle conversion exception");
                        else if (except_ret == H5T_CONV_HANDLED)
                            /*Don't reverse because user handles it already*/
                            reverse = false;
                    }
                    else if (src->shared->u.atomic.prec < dst->shared->u.atomic.prec) {
                        H5T__bit_copy(d, dst->shared->u.atomic.offset, s, src->shared->u.atomic.offset,
                                      src->shared->u.atomic.prec);
                        H5T__bit_set(d, dst->shared->u.atomic.offset + src->shared->u.atomic.prec,
                                     dst->shared->u.atomic.prec - src->shared->u.atomic.prec, false);
                    }
                    else {
                        H5T__bit_copy(d, dst->shared->u.atomic.offset, s, src->shared->u.atomic.offset,
                                      dst->shared->u.atomic.prec);
                    }
                }

                /*
                 * Set padding areas in destination.
                 */
                if (dst->shared->u.atomic.offset > 0) {
                    assert(H5T_PAD_ZERO == dst->shared->u.atomic.lsb_pad ||
                           H5T_PAD_ONE == dst->shared->u.atomic.lsb_pad);
                    H5T__bit_set(d, (size_t)0, dst->shared->u.atomic.offset,
                                 (bool)(H5T_PAD_ONE == dst->shared->u.atomic.lsb_pad));
                }
                if (dst->shared->u.atomic.offset + dst->shared->u.atomic.prec != 8 * dst->shared->size) {
                    assert(H5T_PAD_ZERO == dst->shared->u.atomic.msb_pad ||
                           H5T_PAD_ONE == dst->shared->u.atomic.msb_pad);
                    H5T__bit_set(d, dst->shared->u.atomic.offset + dst->shared->u.atomic.prec,
                                 8 * dst->shared->size -
                                     (dst->shared->u.atomic.offset + dst->shared->u.atomic.prec),
                                 (bool)(H5T_PAD_ONE == dst->shared->u.atomic.msb_pad));
                }

                /*
                 * Put the destination in the correct byte order.  See note at
                 * beginning of loop.
                 */
                if (H5T_ORDER_BE == dst->shared->u.atomic.order && reverse) {
                    half_size = dst->shared->size / 2;
                    for (i = 0; i < half_size; i++) {
                        uint8_t tmp                    = d[dst->shared->size - (i + 1)];
                        d[dst->shared->size - (i + 1)] = d[i];
                        d[i]                           = tmp;
                    }
                }

                /*
                 * If we had used a temporary buffer for the destination then we
                 * should copy the value to the true destination buffer.
                 */
                if (d == dbuf)
                    H5MM_memcpy(dp, d, dst->shared->size);

                /* Advance source & destination pointers by delta amounts */
                sp += src_delta;
                dp += dst_delta;
            } /* end for */

            break;

        default:
            HGOTO_ERROR(H5E_DATATYPE, H5E_UNSUPPORTED, FAIL, "unknown conversion command");
    } /* end switch */

done:
    if (src_rev)
        H5MM_free(src_rev);
    FUNC_LEAVE_NOAPI(ret_value)
} /* end H5T__conv_i_i() */

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_i_f_loop
 *
 * Purpose:     Implements the body of the conversion loop when converting
 *              integer values to floating-point values (including complex
 *              number values). Encapsulates common code that is shared
 *              between the H5T__conv_i_f conversion function and other
 *              functions where the logic is nearly identical, such as
 *              H5T__conv_i_complex.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_i_f_loop(const H5T_t *src_p, const H5T_t *dst_p, const H5T_conv_ctx_t *conv_ctx, size_t nelmts,
                   size_t buf_stride, void *buf)
{
    H5T_atomic_t src_atomic;           /* source datatype atomic info      */
    H5T_atomic_t dst_atomic;           /* destination datatype atomic info */
    hsize_t      expo_max;             /* maximal possible exponent value  */
    ssize_t      src_delta, dst_delta; /* source & destination stride      */
    uint8_t     *s, *sp, *d, *dp;      /* source and dest traversal ptrs   */
    uint8_t     *int_buf = NULL;       /* buffer for temporary value       */
    uint8_t     *src_rev = NULL;       /* order-reversed source buffer     */
    size_t       int_buf_size;         /* buffer size for temporary value  */
    size_t       olap;                 /* num overlapping elements         */
    int          direction;            /* forward or backward traversal    */
    herr_t       ret_value = SUCCEED;

    FUNC_ENTER_PACKAGE

    assert(src_p);
    assert(src_p->shared->type == H5T_INTEGER);
    assert(dst_p);
    assert(dst_p->shared->type == H5T_FLOAT || dst_p->shared->type == H5T_COMPLEX);
    assert(conv_ctx);
    assert(buf);

    src_atomic = src_p->shared->u.atomic;
    if (dst_p->shared->type == H5T_COMPLEX)
        dst_atomic = dst_p->shared->parent->shared->u.atomic;
    else
        dst_atomic = dst_p->shared->u.atomic;

    /*
     * Do we process the values from beginning to end or vice versa? Also,
     * how many of the elements have the source and destination areas
     * overlapping?
     */
    if (src_p->shared->size == dst_p->shared->size || buf_stride) {
        sp = dp   = (uint8_t *)buf;
        direction = 1;
        olap      = nelmts;
    }
    else if (src_p->shared->size >= dst_p->shared->size) {
        double olap_d =
            ceil((double)(dst_p->shared->size) / (double)(src_p->shared->size - dst_p->shared->size));
        olap = (size_t)olap_d;
        sp = dp   = (uint8_t *)buf;
        direction = 1;
    }
    else {
        double olap_d =
            ceil((double)(src_p->shared->size) / (double)(dst_p->shared->size - src_p->shared->size));
        olap      = (size_t)olap_d;
        sp        = (uint8_t *)buf + (nelmts - 1) * src_p->shared->size;
        dp        = (uint8_t *)buf + (nelmts - 1) * dst_p->shared->size;
        direction = -1;
    }

    /* Direction & size of buffer traversal */
    H5_CHECK_OVERFLOW(buf_stride, size_t, ssize_t);
    H5_CHECK_OVERFLOW(src_p->shared->size, size_t, ssize_t);
    H5_CHECK_OVERFLOW(dst_p->shared->size, size_t, ssize_t);
    src_delta = (ssize_t)direction * (ssize_t)(buf_stride ? buf_stride : src_p->shared->size);
    dst_delta = (ssize_t)direction * (ssize_t)(buf_stride ? buf_stride : dst_p->shared->size);

    /* Allocate enough space for the buffer holding temporary converted value */
    int_buf_size =
        ((src_atomic.prec > dst_atomic.u.f.msize ? src_atomic.prec : dst_atomic.u.f.msize) + 7) / 8;
    if (NULL == (int_buf = H5MM_calloc(int_buf_size)))
        HGOTO_ERROR(H5E_DATATYPE, H5E_CANTALLOC, FAIL, "couldn't allocate temporary buffer");

    /* Allocate space for order-reversed source buffer */
    if (conv_ctx->u.conv.cb_struct.func)
        if (NULL == (src_rev = H5MM_calloc(src_p->shared->size)))
            HGOTO_ERROR(H5E_DATATYPE, H5E_CANTALLOC, FAIL, "couldn't allocate temporary buffer");

    /* The conversion loop */
    for (size_t elmtno = 0; elmtno < nelmts; elmtno++) {
        H5T_conv_ret_t except_ret = H5T_CONV_UNHANDLED; /* return of conversion exception callback function */
        hsize_t        expo;                            /* destination exponent                             */
        uint8_t dbuf[TEMP_INT_CONV_BUFFER_SIZE] = {0};  /* temp destination buffer                          */
        ssize_t sfirst                          = 0;    /* a signed version of `first'                      */
        size_t  first;                                  /* first bit(MSB) in an integer                     */
        size_t  sign       = 0;                         /* source sign bit value                            */
        bool    reverse    = true;                      /* if reversed the order of destination             */
        bool    is_max_neg = false;                     /* source is maximal negative value?                */
        bool    do_round   = false;                     /* whether there is roundup                         */

        /*
         * If the source and destination buffers overlap then use a
         * temporary buffer for the destination.
         */
        if (direction > 0) {
            s = sp;
            d = elmtno < olap ? dbuf : dp;
        }
        else {
            s = sp;
            d = elmtno + olap >= nelmts ? dbuf : dp;
        }
#ifndef NDEBUG
        if (d == dbuf) {
            assert((dp >= sp && dp < sp + src_p->shared->size) ||
                   (sp >= dp && sp < dp + dst_p->shared->size));
        }
        else {
            assert((dp < sp && dp + dst_p->shared->size <= sp) ||
                   (sp < dp && sp + src_p->shared->size <= dp));
        }
#endif

        /* Put the data in little endian order so our loops aren't so
         * complicated. We'll do all the conversion stuff assuming
         * little endian and then we'll fix the order at the end.
         */
        if (H5T_ORDER_BE == src_atomic.order)
            for (size_t i = 0; i < src_p->shared->size / 2; i++)
                H5_SWAP_BYTES(s, i, src_p->shared->size - (i + 1));

        /* Zero-set all destination bits */
        H5T__bit_set(d, dst_atomic.offset, dst_atomic.prec, false);

        /* Copy source into a temporary buffer */
        H5T__bit_copy(int_buf, (size_t)0, s, src_atomic.offset, src_atomic.prec);

        /* Find the sign bit value of the source */
        if (H5T_SGN_2 == src_atomic.u.i.sign)
            sign = (size_t)H5T__bit_get_d(int_buf, src_atomic.prec - 1, (size_t)1);

        /* What is the bit position(starting from 0 as first one) for the most significant
         * bit(MSB) of S which is set?
         */
        if (H5T_SGN_2 == src_atomic.u.i.sign) {
            sfirst = H5T__bit_find(int_buf, (size_t)0, src_atomic.prec - 1, H5T_BIT_MSB, true);
            if (sign && sfirst < 0)
                /* The case 0x80...00, which is negative with maximal value */
                is_max_neg = 1;
        }
        else if (H5T_SGN_NONE == src_atomic.u.i.sign)
            sfirst = H5T__bit_find(int_buf, (size_t)0, src_atomic.prec, H5T_BIT_MSB, true);

        /* Handle special cases here. Integer is zero */
        if (!sign && sfirst < 0)
            goto padding;

        /* Convert source integer if it's negative */
        if (H5T_SGN_2 == src_atomic.u.i.sign && sign) {
            if (!is_max_neg) {
                /* Equivalent to ~(i - 1) */
                H5T__bit_dec(int_buf, (size_t)0, int_buf_size * 8);
                H5T__bit_neg(int_buf, (size_t)0, int_buf_size * 8);
                sfirst = H5T__bit_find(int_buf, (size_t)0, src_atomic.prec - 1, H5T_BIT_MSB, true);
            }
            else {
                /* If it's maximal negative number 0x80...000, treat it as if it overflowed
                 * (create a carry) to help conversion.  i.e. a character type number 0x80
                 * is treated as 0x100.
                 */
                sfirst     = (ssize_t)(src_atomic.prec - 1);
                is_max_neg = 0;
            }
            if (sfirst < 0)
                HGOTO_ERROR(H5E_DATATYPE, H5E_CANTCONVERT, FAIL, "zero bit not found");

            /* Sign bit has been negated if bit vector isn't 0x80...00.  Set all bits in front of
             * sign bit to 0 in the temporary buffer because they're all negated from the previous
             * step.
             */
            H5T__bit_set(int_buf, src_atomic.prec, (int_buf_size * 8) - src_atomic.prec, 0);

            /* Set sign bit in destination */
            H5T__bit_set_d(d, dst_atomic.u.f.sign, (size_t)1, (hsize_t)sign);
        }

        first = (size_t)sfirst;

        /* Calculate the true destination exponent by adjusting according to
         * the destination exponent bias. Implied and non-implied normalization
         * should be the same.
         */
        if (H5T_NORM_NONE == dst_atomic.u.f.norm || H5T_NORM_IMPLIED == dst_atomic.u.f.norm)
            expo = first + dst_atomic.u.f.ebias;
        else
            HGOTO_ERROR(H5E_DATATYPE, H5E_CANTCONVERT, FAIL, "normalization method not implemented yet");

        /* Handle mantissa part here */
        if (H5T_NORM_IMPLIED == dst_atomic.u.f.norm)
            H5T__bit_set(int_buf, first, (size_t)1, 0); /* Imply first bit */
        else if (H5T_NORM_NONE == dst_atomic.u.f.norm)
            first++;

        /* Roundup for mantissa */
        if (first > dst_atomic.u.f.msize) {
            /* If the bit sequence is bigger than the mantissa part, there'll be some
             * precision loss. Let user's handler deal with the case if it's present
             */
            if (conv_ctx->u.conv.cb_struct.func) {
                /* Reverse source buffer order first */
                H5T__reverse_order(src_rev, s, src_p);

                /* Prepare & restore library for user callback */
                H5_BEFORE_USER_CB(FAIL)
                    {
                        except_ret = (conv_ctx->u.conv.cb_struct.func)(
                            H5T_CONV_EXCEPT_PRECISION, conv_ctx->u.conv.src_type_id,
                            conv_ctx->u.conv.dst_type_id, src_rev, d, conv_ctx->u.conv.cb_struct.user_data);
                    }
                H5_AFTER_USER_CB(FAIL)
            }

            if (except_ret == H5T_CONV_HANDLED) {
                reverse = false;
                goto padding;
            }
            else if (except_ret == H5T_CONV_ABORT)
                HGOTO_ERROR(H5E_DATATYPE, H5E_CANTCONVERT, FAIL, "can't handle conversion exception");

            /* If user's exception handler does deal with it, we do it by dropping off the
             * extra bits at the end and do rounding.  If we have .50...0(decimal) after radix
             * point, we do roundup when the least significant digit before radix is odd, we do
             * rounddown if it's even.
             */

            /* Check 1st dropoff bit, see if it's set. */
            if (H5T__bit_get_d(int_buf, ((first - dst_atomic.u.f.msize) - 1), (size_t)1)) {
                /* Check all bits after 1st dropoff bit, see if any of them is set. */
                if (((first - dst_atomic.u.f.msize) - 1) > 0 &&
                    H5T__bit_get_d(int_buf, (size_t)0, ((first - dst_atomic.u.f.msize) - 1)))
                    do_round = 1;
                else { /* The .50...0 case */
                    /* Check if the least significant bit is odd. */
                    if (H5T__bit_get_d(int_buf, (first - dst_atomic.u.f.msize), (size_t)1))
                        do_round = 1;
                }
            }

            /* Right shift to drop off extra bits */
            H5T__bit_shift(int_buf, (ssize_t)(dst_atomic.u.f.msize - first), (size_t)0, int_buf_size * 8);

            if (do_round) {
                H5T__bit_inc(int_buf, (size_t)0, int_buf_size * 8);
                do_round = 0;

                /* If integer is like 0x0ff...fff and we need to round up the
                 * last f, we get 0x100...000.  Treat this special case here.
                 */
                if (H5T__bit_get_d(int_buf, dst_atomic.u.f.msize, (size_t)1)) {
                    if (H5T_NORM_IMPLIED == dst_atomic.u.f.norm) {
                        /* The bit at this 1's position was impled already, so this
                         * number should be 0x200...000.  We need to increment the
                         * exponent in this case.
                         */
                        expo++;
                    }
                    else if (H5T_NORM_NONE == dst_atomic.u.f.norm) {
                        /* Right shift 1 bit to let the carried 1 fit in the mantissa,
                         * and increment exponent by 1.
                         */
                        H5T__bit_shift(int_buf, (ssize_t)-1, (size_t)0, int_buf_size * 8);
                        expo++;
                    }
                }
            }
        }
        else {
            /* The bit sequence can fit mantissa part. Left shift to fit in from high-order of
             * bit position. */
            H5T__bit_shift(int_buf, (ssize_t)(dst_atomic.u.f.msize - first), (size_t)0, dst_atomic.u.f.msize);
        }

        /* Check if the exponent is too big */
        expo_max = (hsize_t)(pow(2.0, (double)dst_atomic.u.f.esize) - 1);

        if (expo > expo_max) {                     /* overflows */
            if (conv_ctx->u.conv.cb_struct.func) { /* user's exception handler */
                /* Reverse back source order */
                H5T__reverse_order(src_rev, s, src_p);

                /* Prepare & restore library for user callback */
                H5_BEFORE_USER_CB(FAIL)
                    {
                        except_ret = (conv_ctx->u.conv.cb_struct.func)(
                            H5T_CONV_EXCEPT_RANGE_HI, conv_ctx->u.conv.src_type_id,
                            conv_ctx->u.conv.dst_type_id, src_rev, d, conv_ctx->u.conv.cb_struct.user_data);
                    }
                H5_AFTER_USER_CB(FAIL)

                if (except_ret == H5T_CONV_ABORT)
                    HGOTO_ERROR(H5E_DATATYPE, H5E_CANTCONVERT, FAIL, "can't handle conversion exception");
                else if (except_ret == H5T_CONV_HANDLED) {
                    reverse = false;
                    goto padding;
                }
            }

            if (!conv_ctx->u.conv.cb_struct.func || (except_ret == H5T_CONV_UNHANDLED)) {
                /* Make destination infinity by setting exponent to maximal number and mantissa to zero. */
                expo = expo_max;
                memset(int_buf, 0, int_buf_size);
            }
        }

        if (except_ret == H5T_CONV_UNHANDLED) {
            /* Set exponent in destination */
            H5T__bit_set_d(d, dst_atomic.u.f.epos, dst_atomic.u.f.esize, expo);

            /* Copy mantissa into destination */
            H5T__bit_copy(d, dst_atomic.u.f.mpos, int_buf, (size_t)0,
                          (int_buf_size * 8) > dst_atomic.u.f.msize ? dst_atomic.u.f.msize
                                                                    : int_buf_size * 8);
        }

padding:
        /* Set padding areas in destination. */
        if (dst_atomic.offset > 0) {
            assert(H5T_PAD_ZERO == dst_atomic.lsb_pad || H5T_PAD_ONE == dst_atomic.lsb_pad);
            H5T__bit_set(d, (size_t)0, dst_atomic.offset, (bool)(H5T_PAD_ONE == dst_atomic.lsb_pad));
        }
        {
            size_t type_size;

            if (dst_p->shared->type == H5T_FLOAT)
                type_size = dst_p->shared->size;
            else
                type_size = dst_p->shared->parent->shared->size;

            if (dst_atomic.offset + dst_atomic.prec != 8 * type_size) {
                assert(H5T_PAD_ZERO == dst_atomic.msb_pad || H5T_PAD_ONE == dst_atomic.msb_pad);
                H5T__bit_set(d, dst_atomic.offset + dst_atomic.prec,
                             8 * type_size - (dst_atomic.offset + dst_atomic.prec),
                             (bool)(H5T_PAD_ONE == dst_atomic.msb_pad));
            }
        }

        /*
         * Put the destination in the correct byte order. See note at
         * beginning of loop. Only the "real" part of a complex number
         * element is swapped. By the C standard, the "imaginary" part
         * should just be zeroed when converting a real value to a
         * complex value.
         */
        if (H5T_ORDER_BE == dst_atomic.order && reverse) {
            size_t half_size = dst_p->shared->size / 2;

            if (H5T_FLOAT == dst_p->shared->type) {
                for (size_t i = 0; i < half_size; i++)
                    H5_SWAP_BYTES(d, i, dst_p->shared->size - (i + 1));
            }
            else {
                for (size_t i = 0; i < half_size / 2; i++)
                    H5_SWAP_BYTES(d, i, half_size - (i + 1));
            }
        }
        else if (H5T_ORDER_VAX == dst_atomic.order && reverse) {
            if (H5T_FLOAT == dst_p->shared->type) {
                uint8_t tmp1, tmp2;
                size_t  tsize = dst_p->shared->size;
                assert(0 == tsize % 2);

                for (size_t i = 0; i < tsize; i += 4) {
                    tmp1 = d[i];
                    tmp2 = d[i + 1];

                    d[i]     = d[(tsize - 2) - i];
                    d[i + 1] = d[(tsize - 1) - i];

                    d[(tsize - 2) - i] = tmp1;
                    d[(tsize - 1) - i] = tmp2;
                }
            }
            else
                HGOTO_ERROR(H5E_DATATYPE, H5E_UNSUPPORTED, FAIL,
                            "VAX byte ordering is unsupported for complex number type conversions");
        }

        /*
         * If we had used a temporary buffer for the destination then we
         * should copy the value to the true destination buffer.
         */
        if (d == dbuf) /* For complex number values, assume that dbuf was initialized to 0s */
            H5MM_memcpy(dp, d, dst_p->shared->size);
        else if (dst_p->shared->type == H5T_COMPLEX)
            /* Ensure imaginary part of complex number is zeroed */
            memset(dp + (dst_p->shared->size / 2), 0, dst_p->shared->size / 2);

        /* Advance source & destination pointers by delta amounts */
        sp += src_delta;
        dp += dst_delta;

        memset(int_buf, 0, int_buf_size);
    } /* end conversion loop */

done:
    H5MM_free(src_rev);
    H5MM_free(int_buf);

    FUNC_LEAVE_NOAPI(ret_value)
} /* end H5T__conv_i_f_loop() */

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_i_f
 *
 * Purpose:     Convert one integer type to a floating-point type. This is
 *              the catch-all function for integer-float conversions and
 *              is probably not particularly fast.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_i_f(const H5T_t *src_p, const H5T_t *dst_p, H5T_cdata_t *cdata, const H5T_conv_ctx_t *conv_ctx,
              size_t nelmts, size_t buf_stride, size_t H5_ATTR_UNUSED bkg_stride, void *buf,
              void H5_ATTR_UNUSED *bkg)
{
    herr_t ret_value = SUCCEED; /* Return value */

    FUNC_ENTER_PACKAGE

    switch (cdata->command) {
        case H5T_CONV_INIT: {
            H5T_atomic_t src_atomic; /* source datatype atomic info      */
            H5T_atomic_t dst_atomic; /* destination datatype atomic info */

            if (NULL == src_p || NULL == dst_p)
                HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a datatype");
            src_atomic = src_p->shared->u.atomic;
            dst_atomic = dst_p->shared->u.atomic;
            if (H5T_ORDER_LE != src_atomic.order && H5T_ORDER_BE != src_atomic.order)
                HGOTO_ERROR(H5E_DATATYPE, H5E_UNSUPPORTED, FAIL, "unsupported byte order");
            if (H5T_ORDER_LE != dst_atomic.order && H5T_ORDER_BE != dst_atomic.order &&
                H5T_ORDER_VAX != dst_atomic.order)
                HGOTO_ERROR(H5E_DATATYPE, H5E_UNSUPPORTED, FAIL, "unsupported byte order");
            if (dst_p->shared->size > TEMP_INT_CONV_BUFFER_SIZE)
                HGOTO_ERROR(H5E_DATATYPE, H5E_UNSUPPORTED, FAIL, "destination size is too large");
            if (8 * sizeof(hsize_t) - 1 < dst_atomic.u.f.esize)
                HGOTO_ERROR(H5E_DATATYPE, H5E_UNSUPPORTED, FAIL, "exponent field is too large");
            cdata->need_bkg = H5T_BKG_NO;

            break;
        }

        case H5T_CONV_FREE:
            break;

        case H5T_CONV_CONV:
            if (NULL == src_p || NULL == dst_p)
                HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a datatype");
            if (NULL == conv_ctx)
                HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "invalid datatype conversion context pointer");

            if (H5T__conv_i_f_loop(src_p, dst_p, conv_ctx, nelmts, buf_stride, buf) < 0)
                HGOTO_ERROR(H5E_DATATYPE, H5E_CANTCONVERT, FAIL, "unable to convert data values");

            break;

        default:
            HGOTO_ERROR(H5E_DATATYPE, H5E_UNSUPPORTED, FAIL, "unknown conversion command");
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
} /* end H5T__conv_i_f() */

/*-------------------------------------------------------------------------
 * Function:    H5T__conv_i_complex
 *
 * Purpose:     Convert integer values to complex number values. This is
 *              the catch-all function for integer -> complex number
 *              conversions and is probably not particularly fast.
 *
 * Return:      Non-negative on success/Negative on failure
 *
 *-------------------------------------------------------------------------
 */
herr_t
H5T__conv_i_complex(const H5T_t *src_p, const H5T_t *dst_p, H5T_cdata_t *cdata,
                    const H5T_conv_ctx_t *conv_ctx, size_t nelmts, size_t buf_stride,
                    size_t H5_ATTR_UNUSED bkg_stride, void *buf, void H5_ATTR_UNUSED *bkg)
{
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_PACKAGE

    switch (cdata->command) {
        case H5T_CONV_INIT: {
            H5T_atomic_t src_atomic; /* source datatype atomic info      */
            H5T_atomic_t dst_atomic; /* destination datatype atomic info */

            if (!src_p || !dst_p)
                HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a datatype");
            if (!H5T_IS_ATOMIC(dst_p->shared->parent->shared))
                HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "invalid complex number datatype");
            src_atomic = src_p->shared->u.atomic;
            dst_atomic = dst_p->shared->parent->shared->u.atomic;
            if (H5T_ORDER_LE != src_atomic.order && H5T_ORDER_BE != src_atomic.order)
                HGOTO_ERROR(H5E_DATATYPE, H5E_UNSUPPORTED, FAIL,
                            "unsupported byte order for source datatype");
            if (H5T_ORDER_LE != dst_atomic.order && H5T_ORDER_BE != dst_atomic.order)
                HGOTO_ERROR(H5E_DATATYPE, H5E_UNSUPPORTED, FAIL,
                            "unsupported byte order for destination datatype");
            if (dst_p->shared->size > TEMP_INT_CONV_BUFFER_SIZE)
                HGOTO_ERROR(H5E_DATATYPE, H5E_UNSUPPORTED, FAIL, "destination datatype size is too large");
            if (8 * sizeof(hsize_t) - 1 < dst_atomic.u.f.esize)
                HGOTO_ERROR(H5E_DATATYPE, H5E_UNSUPPORTED, FAIL, "exponent field is too large");
            cdata->need_bkg = H5T_BKG_NO;

            break;
        }

        case H5T_CONV_FREE:
            break;

        case H5T_CONV_CONV:
            if (!src_p || !dst_p)
                HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a datatype");
            if (NULL == conv_ctx)
                HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "invalid datatype conversion context pointer");

            if (H5T__conv_i_f_loop(src_p, dst_p, conv_ctx, nelmts, buf_stride, buf) < 0)
                HGOTO_ERROR(H5E_DATATYPE, H5E_CANTCONVERT, FAIL, "unable to convert data values");

            break;

        default:
            HGOTO_ERROR(H5E_DATATYPE, H5E_UNSUPPORTED, FAIL, "unknown conversion command");
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
} /* end H5T__conv_i_complex() */
