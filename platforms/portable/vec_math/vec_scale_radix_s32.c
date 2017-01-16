/*******************************************************************************
 * Copyright (c) 2017 Vasiliy Nerozin
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE.md for details.
 ******************************************************************************/ 

/* -----------------------------------------------------------------------------
 * Includes
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

#define RADIX_HI      (24)
#define CONST_HI(X)   CIMLIB_CONST_S32(X, RADIX_HI)

#define RADIX         (20)
#define CONST(X)      CIMLIB_CONST_S32(X, RADIX)

#define RADIX_LOW     (16)
#define CONST_LOW(X)  CIMLIB_CONST_S32(X, RADIX_LOW)


/*******************************************************************************
 * This function tests 'vec_scale_radix_s32' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_scale_radix_s32(void)
{
    int32_t y[4];
    static int32_t x[4] = {
        CONST(3.0), CONST(6.0), CONST(2.0), CONST(1.0)
    };
    static int32_t res0[4] = {
        CONST_HI(3.0), CONST_HI(6.0), CONST_HI(2.0), CONST_HI(1.0)
    };
    static int32_t res1[4] = {
        CONST_LOW(3.0), CONST_LOW(6.0), CONST_LOW(2.0), CONST_LOW(1.0)
    };
    bool flOk = true;

    /* Call 'vec_scale_radix_s32' function */
    vec_scale_radix_s32(y, 4, RADIX_HI - RADIX, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res0, 4, flOk);

    /* Call 'vec_scale_radix_s32' function */
    vec_scale_radix_s32(y, 4, RADIX_LOW - RADIX, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res1, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
