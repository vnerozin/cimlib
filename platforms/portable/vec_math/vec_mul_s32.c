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
 * This function calculates by element multiply of input vectors, 32 bit signed.
 *
 * @param[out]  pZ     Pointer to output vector, 32 bit signed.
 * @param[in]   len    Vector length.
 * @param[in]   radix  Radix.
 * @param[in]   pX     Pointer to input vector, 32 bit signed.
 * @param[in]   pY     Pointer to input vector, 32 bit signed.
 ******************************************************************************/
void vec_mul_s32(int32_t *pZ, int len, int radix, const int32_t *pX,
                 const int32_t *pY)
{
    int n;

    for (n = 0; n < len; n++) {
        pZ[n] = (int32_t)(((int64_t)pX[n] * pY[n]) >> radix);
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_mul_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mul_s32(void)
{
    int32_t z[4];
    static int32_t x[4] = {100000, 1000000, 1000000, INT32_MIN};
    static int32_t y[4] = {INT32_MIN, 100000, 1000, 100};
    static int32_t res[4] = {-819200000, 381469, 3814, -819200};
    bool flOk = true;

    /* Call 'vec_mul_s32' function */
    vec_mul_s32(z, 4, 18, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
