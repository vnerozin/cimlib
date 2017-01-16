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
 * This function calculates sum of differences (subtractions) of vectors,
 * 32 bit complex.
 *
 * @param[in]  pX   Pointer to input vector, 32 bit complex.
 * @param[in]  pY   Pointer to input vector, 32 bit complex.
 * @param[in]  len  Vector length.
 *
 * @return          Sum of differences (subtractions), 64 bit complex.
 ******************************************************************************/
cint64_t vec_sum_diff_c32(const cint32_t *pX, const cint32_t *pY, int len)
{
    int n;
    cint64_t acc = {0, 0};

    for (n = 0; n < len; n++) {
        acc.re += pX[n].re - pY[n].re;
        acc.im += pX[n].im - pY[n].im;
    }

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sum_diff_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_diff_c32(void)
{
    cint64_t z;
    static cint32_t x[4] = {
        {INT32_MAX, INT32_MIN + 1}, {INT32_MAX, INT32_MIN + 1},
        {INT32_MIN + 1, INT32_MAX}, {INT32_MIN + 1, INT32_MAX}
    };
    static cint32_t y[4] = {
        {INT32_MAX, INT32_MIN + 1}, {INT32_MAX, INT32_MIN + 1},
        {INT32_MIN + 1, INT32_MAX}, {INT32_MIN + 1, INT32_MAX}
    };
    bool flOk = true;

    /* Call 'vec_sum_diff_c32' function */
    z = vec_sum_diff_c32(x, y, 4);

    /* Check the correctness of the results */
    if ((z.re != 0) || (z.im != 0)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
