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
 * This function calculates sum of squared differences (subtractions) of
 * vectors, 16 bit complex.
 *
 * @param[in]  pX     Pointer to input vector, 16 bit complex.
 * @param[in]  pY     Pointer to input vector, 16 bit complex.
 * @param[in]  len    Vector length.
 * @param[in]  radix  Radix.
 *
 * @return            Sum of squared differences (subtractions),
 *                    32 bit unsigned.
 ******************************************************************************/
uint32_t vec_sum_sqr_diff_c16(const cint16_t *pX, const cint16_t *pY, int len,
                              int radix)
{
    int n;
    int16_t diff_re, diff_im;
    uint32_t acc = 0;

    /* For correct rounding add half of radix */
    if (radix != 0) {
        acc = 1;
        acc *= ((uint32_t)1 << (radix - 1));
    }

    for (n = 0; n < len; n++) {
        diff_re = pX[n].re - pY[n].re;
        diff_im = pX[n].im - pY[n].im;
        acc += (uint32_t)diff_re * diff_re + (uint32_t)diff_im * diff_im;
    }

    acc >>= radix;

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sum_sqr_diff_c16' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_sqr_diff_c16(void)
{
    uint32_t z;
    static cint16_t x[4] = {{4096,128}, {8192,-128}, {-8192,128}, {-4096,0}};
    static cint16_t y[4] = {{-4096,-128}, {-8192,128}, {8192,-128}, {4096,0}};
    static uint32_t res = 655552;
    bool flOk = true;

    /* Call 'vec_sum_sqr_diff_c16' function */
    z = vec_sum_sqr_diff_c16(x, y, 4, 10);

    /* Check the correctness of the results */
    if (z != res) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
