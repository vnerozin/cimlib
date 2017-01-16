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
 * This function calculates sum of multiplies of vectors, 16 bit signed.
 *
 * @param[in]  pX     Pointer to input vector, 16 bit signed.
 * @param[in]  pY     Pointer to input vector, 16 bit signed.
 * @param[in]  len    Vector length.
 * @param[in]  radix  Radix.
 *
 * @return            Sum of multiplies, 32 bit signed.
 ******************************************************************************/
int32_t vec_sum_mul_s16(const int16_t *pX, const int16_t *pY, int len,
                        int radix)
{
    int n;
    int32_t acc = 0;

    /* For correct rounding add half of radix */
    if (radix != 0) {
        acc = ((int32_t)1 << (radix - 1));
    }

    for (n = 0; n < len; n++) {
        acc += (int32_t)pX[n] * pY[n];
    }

    acc >>= radix;

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (10)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)


/*******************************************************************************
 * This function tests 'vec_sum_mul_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_mul_s16(void)
{
    int32_t z;
    static int16_t x[4] = {
        CONST(7.9), CONST(4.0), CONST(2.0), CONST(1.0)
    };
    static int16_t y[4] = {
        CONST(-1.0), CONST(-2.0), CONST(4.0), CONST(7.9)
    };
    static int32_t res = 0;
    bool flOk = true;

    /* Call 'vec_sum_mul_s16' function */
    z = vec_sum_mul_s16(x, y, 4, RADIX);

    /* Check the correctness of the results */
    if (z != res) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
