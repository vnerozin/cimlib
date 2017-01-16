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
 * This function calculates sum of squares of vector, 16 bit signed.
 *
 * @param[in]  pX     Pointer to input vector, 16 bit signed.
 * @param[in]  len    Vector length.
 * @param[in]  radix  Radix.
 *
 * @return            Sum of squares, 32 bit unsigned.
 ******************************************************************************/
uint32_t vec_sum_sqr_s16(const int16_t *pX, int len, int radix)
{
    int n;
    uint32_t acc = 0;

    /* For correct rounding add half of radix */
    if (radix != 0) {
        acc = ((uint32_t)1 << (radix - 1));
    }

    for (n = 0; n < len; n++) {
        acc += (uint32_t)pX[n] * pX[n];
    }

    /* Scale radix */
    acc >>= radix;

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sum_sqr_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_sqr_s16(void)
{
    uint32_t y;
    static int16_t x[4] = {4096, 8192, -8192, -4096};
    static uint32_t res = 163840;
    bool flOk = true;

    /* Call 'vec_sum_sqr_s16' function */
    y = vec_sum_sqr_s16(x, 4, 10);

    /* Check the correctness of the results */
    if (y != res) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
