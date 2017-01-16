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
 * This function calculates sum of multiplies of vectors, 32 bit signed.
 *
 * @param[in]  pX     Pointer to input vector, 32 bit signed.
 * @param[in]  pY     Pointer to input vector, 32 bit signed.
 * @param[in]  len    Vector length.
 * @param[in]  radix  Radix.
 *
 * @return            Sum of multiplies, 32 bit signed.
 ******************************************************************************/
int64_t vec_sum_mul_s32(const int32_t *pX, const int32_t *pY, int len,
                        int radix)
{
    int n;
    int64_t acc = 0;

    /* For correct rounding add half of radix */
    if (radix != 0) {
        acc = ((int64_t)1 << (radix - 1));
    }

    for (n = 0; n < len; n++) {
        acc += (int64_t)pX[n] * pY[n];
    }

    acc >>= radix;

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sum_mul_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_mul_s32(void)
{
    int64_t z;
    static int32_t x[4] = {100, 1000, 10000, INT32_MIN};
    static int32_t y[4] = {INT32_MIN, 10000, 1000, 100};
    static int64_t res = -6710573900;
    bool flOk = true;

    /* Call 'vec_sum_mul_s32' function */
    z = vec_sum_mul_s32(x, y, 4, 6);

    /* Check the correctness of the results */
    if (z != res) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
