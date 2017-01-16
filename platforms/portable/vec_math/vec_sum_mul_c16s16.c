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
 * 16 bit complex and 16 bit signed.
 *
 * @param[in]  len    Vector length.
 * @param[in]  radix  Radix.
 * @param[in]  pX     Pointer to input vector, 16 bit complex.
 * @param[in]  pY     Pointer to input vector, 16 bit signed.
 *
 * @return            Sum of complex multiplies, 32 bit complex.
 ******************************************************************************/
cint32_t vec_sum_mul_c16s16(const cint16_t *pX, const int16_t *pY, int len,
                            int radix)
{
    int n;
    cint32_t acc;
    int32_t accRe = 0;
    int32_t accIm = 0;

    /* For correct rounding add half of radix */
    if (radix != 0) {
        accRe = ((int32_t)1 << (radix - 1));
        accIm = ((int32_t)1 << (radix - 1));
    }

    for (n = 0; n < len; n++) {
        accRe += (int32_t)pX[n].re * pY[n];
        accIm += (int32_t)pX[n].im * pY[n];
    }

    acc.re = accRe >> radix;
    acc.im = accIm >> radix;

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sum_mul_c16s16' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_mul_c16s16(void)
{
    cint32_t z;
    static cint16_t x[4] = {{4096,128}, {8192,-128}, {-8192,128}, {-4096,0}};
    static int16_t y[4] = {1234, 1234, 1234, 1234};
    static cint16_t res = {0, 9872};
    bool flOk = true;

    /* Call 'vec_sum_mul_c16s16' function */
    z = vec_sum_mul_c16s16(x, y, 4, 4);

    /* Check the correctness of the results */
    if ((z.re != res.re) || (z.im != res.im)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
