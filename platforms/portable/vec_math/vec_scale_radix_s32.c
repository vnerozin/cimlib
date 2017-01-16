/*******************************************************************************
 * Copyright (c) 2017 Vasiliy Nerozin
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE.md for details.
 ******************************************************************************/ 

/* -----------------------------------------------------------------------------
 * Include files
 * ---------------------------------------------------------------------------*/
#include "cimlib.h"               /* Library header */


/* -----------------------------------------------------------------------------
 * Exported functions
 * ---------------------------------------------------------------------------*/

/*******************************************************************************
 * This function scales base radix of input vector, 32 bit signed.
 *
 * @param[out]  pY      Pointer to output vector, 32 bit signed.
 * @param[in]   len     Vector length.
 * @param[in]   offset  Scale radix offset, number of shifts right, if negative;
 *                      if positive - left shifts.
 * @param[in]   pX      Pointer to input vector, 32 bit signed.
 ******************************************************************************/
void vec_scale_radix_s32(int32_t *pY, int len, int offset, const int32_t *pX)
{
    int n;

    if (offset > 0) {
        for (n = 0; n < len; n++) {
            pY[n] = (int32_t)(pX[n] << offset);
        }
    } else if (offset < 0) {
        offset = -offset;
        for (n = 0; n < len; n++) {
            pY[n] = (int32_t)(pX[n] >> offset);
        }
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_scale_radix_s32' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_scale_radix_s32(void)
{
    int32_t y[4];
    static int32_t x[4] = {
        CIMLIB_CONST_S32(4.1, 24),
        CIMLIB_CONST_S32(2.6, 24),
        CIMLIB_CONST_S32(-1.4, 24),
        CIMLIB_CONST_S32(5.3, 24)
    };
    static int32_t res0[4] = {
        550292688, 348966096, -187904816, 711353960
    };
    static int32_t res1[4] = {
        CIMLIB_CONST_S32(4.1, 21),
        CIMLIB_CONST_S32(2.6, 21),
        -2936013,
        11114905
    };
    bool flOk = true;

    /* Call 'vec_scale_radix_s32' function */
    vec_scale_radix_s32(y, 4, 3, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res0, 4, flOk);

    /* Call 'vec_scale_radix_s32' function */
    vec_scale_radix_s32(y, 4, -3, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res1, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
