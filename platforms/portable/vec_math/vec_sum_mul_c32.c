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
 * This function calculates sum of complex multiplies of vectors,
 * 32 bit complex.
 *
 * @param[in]  pX     Pointer to input vector, 32 bit complex.
 * @param[in]  pY     Pointer to input vector, 32 bit complex.
 * @param[in]  len    Vector length.
 * @param[in]  radix  Radix.
 *
 * @return            Sum of complex multiplies, 64 bit complex.
 ******************************************************************************/
cint64_t vec_sum_mul_c32(const cint32_t *pX, const cint32_t *pY, int len,
                         int radix)
{
    int n;
    cint64_t acc;
    int64_t accRe = 0;
    int64_t accIm = 0;

    /* For correct rounding add half of radix */
    if (radix != 0) {
        accRe = ((int64_t)1 << (radix - 1));
        accIm = ((int64_t)1 << (radix - 1));
    }

    for (n = 0; n < len; n++) {
        accRe += (int64_t)pX[n].re * pY[n].re - (int64_t)pX[n].im * pY[n].im;
        accIm += (int64_t)pX[n].im * pY[n].re + (int64_t)pX[n].re * pY[n].im;
    }

    acc.re = accRe >> radix;
    acc.im = accIm >> radix;

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sum_mul_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_mul_c32(void)
{
    cint64_t z;
    static cint32_t x[4] = {
        {(1 << 23), 128}, {-(1 << 23), -128},
        {(1 << 23), 128}, {-(1 << 23), 0}
    };
    static cint32_t y[4] = {
        {-(1 << 23), 128}, {(1 << 23), -128},
        {-(1 << 23), 128}, {(1 << 23), 0}
    };
    static cint64_t res = {-274877906992, 0};
    bool flOk = true;

    /* Call 'vec_sum_mul_c32' function */
    z = vec_sum_mul_c32(x, y, 4, 10);

    /* Check the correctness of the results */
    if ((z.re != res.re) || (z.im != res.im)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
