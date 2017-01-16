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
 * This function calculates by element multiply of vector with constant,
 * 32 bit signed.
 *
 * @param[out]  pY     Pointer to output vector, 32 bit signed.
 * @param[in]   len    Vector length.
 * @param[in]   radix  Radix.
 * @param[in]   pX     Pointer to input vector, 32 bit signed.
 * @param[in]   cnst   Constant, 32 bit signed.
 ******************************************************************************/
void vec_mul_const_s32(int32_t *pY, int len, int radix, const int32_t *pX,
                       int32_t cnst)
{
    int n;

    for (n = 0; n < len; n++) {
        pY[n] = (int32_t)(((int64_t)pX[n] * cnst) >> radix);
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_mul_const_s32' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mul_const_s32(void)
{
    int32_t y[4];
    static int32_t x[4] = {333333, 222222, -234567890, 234567890};
    static int32_t cnst = CIMLIB_CONST_S32(2.0, 24);
    static int32_t res[4] = {666666, 444444, -469135780, 469135780};
    bool flOk = true;

    /* Call 'vec_mul_const_s32' function */
    vec_mul_const_s32(y, 4, 24, x, cnst);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
