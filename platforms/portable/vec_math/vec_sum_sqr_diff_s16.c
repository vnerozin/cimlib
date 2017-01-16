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
 * This function calculates sum of squared differences (subtractions)
 * of vectors, 16 bit signed.
 *
 * @param[in]  pX     Pointer to input vector, 16 bit signed.
 * @param[in]  pY     Pointer to input vector, 16 bit signed.
 * @param[in]  len    Vector length.
 * @param[in]  radix  Radix.
 *
 * @return            Sum of squared differences (subtractions),
 *                    32 bit unsigned.
 ******************************************************************************/
uint32_t vec_sum_sqr_diff_s16(const int16_t *pX, const int16_t *pY, int len,
                              int radix)
{
    int n;
    int16_t diff;
    uint32_t acc = 0;

    /* For correct rounding add half of radix */
    if (radix != 0) {
        acc = 1;
        acc *= ((uint32_t)1 << (radix - 1));
    }

    for (n = 0; n < len; n++) {
        diff = pX[n] - pY[n];
        acc += (uint32_t)diff * diff;
    }

    acc >>= radix;

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sum_sqr_diff_s16' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_sqr_diff_s16(void)
{
    uint32_t z;
    static int16_t x[4] = {11111, 22222, 3333, 4444};
    static int16_t y[4] = {-4444, -3333, -22222, -11111};
    static uint32_t res = 1748078;
    bool flOk = true;

    /* Call 'vec_sum_sqr_diff_s16' function */
    z = vec_sum_sqr_diff_s16(x, y, 4, 10);

    /* Check the correctness of the results */
    if (z != res) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
