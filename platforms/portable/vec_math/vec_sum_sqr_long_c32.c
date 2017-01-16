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
 * This function calculates sum of squares of vector, 32 bit complex,
 * result with extended precision.
 *
 * @param[in]  pX   Pointer to input vector, 32 bit complex.
 * @param[in]  len  Vector length.
 *
 * @return          Sum of squares, 64 bit unsigned.
 ******************************************************************************/
uint64_t vec_sum_sqr_long_c32(const cint32_t *pX, int len)
{
    int n;
    uint64_t tmp;
    uint64_t acc = 0;

    for (n = 0; n < len; n++) {
        tmp = (uint64_t)pX[n].re * pX[n].re;
        tmp += (uint64_t)pX[n].im * pX[n].im;
        acc += tmp;
    }

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sum_sqr_long_c32' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_sqr_long_c32(void)
{
    uint64_t y;
    static cint32_t x[4] = {
        {4096000,128000}, {8192000,-128000},
        {-8192000,128000}, {-4096000,0}
    };
    static uint64_t res = 167821312000000;
    bool flOk = true;

    /* Call 'vec_sum_sqr_long_c32' function */
    y = vec_sum_sqr_long_c32(x, 4);

    /* Check the correctness of the results */
    if (y != res) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
