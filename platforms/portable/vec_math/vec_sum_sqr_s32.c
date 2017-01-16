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
 * This function calculates sum of squares of vector, 32 bit signed.
 *
 * @param[in]  pX     Pointer to input vector, 32 bit signed.
 * @param[in]  len    Vector length.
 * @param[in]  radix  Radix.
 *
 * @return            Sum of squares, 64 bit unsigned.
 ******************************************************************************/
uint64_t vec_sum_sqr_s32(const int32_t *pX, int len, int radix)
{
    int n;
    uint64_t acc = 0;

    /* For correct rounding add half of radix */
    if (radix != 0) {
        acc = ((uint64_t)1 << (radix - 1));
    }

    for (n = 0; n < len; n++) {
        acc += (uint64_t)pX[n] * pX[n];
    }

    /* Scale radix */
    acc >>= radix;

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX       (20)
#define CONST(X)    CIMLIB_CONST_S32(X, RADIX)
#define CONST_U(X)  CIMLIB_CONST_U32(X, RADIX)


/*******************************************************************************
 * This function tests 'vec_sum_sqr_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_sqr_s32(void)
{
    uint64_t y;
    static int32_t x[4] = {
        CONST(3.0), CONST(4.0), CONST(2.0), CONST(1.0)
    };
    static uint64_t res = CONST_U(30.0);
    bool flOk = true;

    /* Call 'vec_sum_sqr_s32' function */
    y = vec_sum_sqr_s32(x, 4, RADIX);

    /* Check the correctness of the results */
    if (y != res) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
