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
 * of vectors, 32 bit complex.
 *
 * @param[in]  pX     Pointer to input vector, 32 bit complex.
 * @param[in]  pY     Pointer to input vector, 32 bit complex.
 * @param[in]  len    Vector length.
 * @param[in]  radix  Radix.
 *
 * @return            Sum of squared differences (subtractions),
 *                    64 bit unsigned.
 ******************************************************************************/
uint64_t vec_sum_sqr_diff_c32(const cint32_t *pX, const cint32_t *pY, int len,
                              int radix)
{
    int n;
    int32_t diff_re, diff_im;
    uint64_t acc = 0;

    /* For correct rounding add half of radix */
    if (radix != 0) {
        acc = 1;
        acc *= ((uint64_t)1 << (radix - 1));
    }

    for (n = 0; n < len; n++) {
        diff_re = pX[n].re - pY[n].re;
        diff_im = pX[n].im - pY[n].im;
        acc += (uint64_t)diff_re * diff_re + (uint64_t)diff_im * diff_im;
    }

    acc >>= radix;

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sum_sqr_diff_c32' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_sqr_diff_c32(void)
{
    uint64_t z;
    static cint32_t x[4] = {
        {4096000, 128000}, {8192000, -128000},
        {-819200, 120008}, {-4090006, 0}
    };
    static cint32_t y[4] = {
        {-4096000, -128000}, {-8192000, 128000},
        {819200, -120008}, {4090006, 0}
    };
    static uint64_t res = 395830029844;
    bool flOk = true;

    /* Call 'vec_sum_sqr_diff_c32' function */
    z = vec_sum_sqr_diff_c32(x, y, 4, 10);

    /* Check the correctness of the results */
    if (z != res) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
