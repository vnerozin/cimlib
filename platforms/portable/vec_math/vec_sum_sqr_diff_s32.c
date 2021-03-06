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
 * This function calculates sum of squared differences (subtractions)
 * of vectors, 32 bit signed.
 *
 * @param[in]  pX     Pointer to input vector, 32 bit signed.
 * @param[in]  pY     Pointer to input vector, 32 bit signed.
 * @param[in]  len    Vector length.
 * @param[in]  radix  Radix.
 *
 * @return            Sum of squared differences (subtractions),
 *                    64 bit unsigned.
 ******************************************************************************/
uint64_t vec_sum_sqr_diff_s32(const int32_t *pX, const int32_t *pY, int len,
                              int radix)
{
    int n;
    int32_t diff;
    uint64_t acc = 0;

    /* For correct rounding add half of radix */
    if (radix != 0) {
        acc = 1;
        acc *= ((uint64_t)1 << (radix - 1));
    }

    for (n = 0; n < len; n++) {
        diff = pX[n] - pY[n];
        acc += (uint64_t)diff * diff;
    }

    acc >>= radix;

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (28)
#define CONST(X)  CIMLIB_CONST_S32(X, RADIX)


/*******************************************************************************
 * This function tests 'vec_sum_sqr_diff_s32' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_sqr_diff_s32(void)
{
    uint64_t z;
    static int32_t x[4] = {
        CONST(2.1), CONST(0.1), CONST(-5.6), CONST(3.14)
    };
    static int32_t y[4] = {
        CONST(2.1), CONST(0.1), CONST(-5.6), CONST(3.14)
    };
    bool flOk = true;

    /* Call 'vec_sum_sqr_diff_s32' function */
    z = vec_sum_sqr_diff_s32(x, y, 4, RADIX);

    /* Check the correctness of the results */
    if (z != 0) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
