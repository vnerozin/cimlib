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
 * This function calculates sum of squares of vector, 16 bit signed,
 * result with extended precision.
 *
 * @param[in]  pX   Pointer to input vector, 16 bit signed.
 * @param[in]  len  Vector length.
 *
 * @return          Sum of squares, 32 bit unsigned.
 ******************************************************************************/
uint32_t vec_sum_sqr_long_s16(const int16_t *pX, int len)
{
    int n;
    uint32_t acc = 0;

    for (n = 0; n < len; n++) {
        acc += (uint32_t)pX[n] * pX[n];
    }

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX          (12)
#define CONST(X)       CIMLIB_CONST_S16(X, RADIX)
#define CONST_LONG(X)  CIMLIB_CONST_U32(X, RADIX * 2)


/*******************************************************************************
 * This function tests 'vec_sum_sqr_long_s16' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_sqr_long_s16(void)
{
    uint32_t y;
    static int16_t x[4] = {
        CONST(7.9), CONST(4.0), CONST(2.0), CONST(1.0)
    };
    static uint32_t res = CONST_LONG(8.3408457041E+01);
    bool flOk = true;

    /* Call 'vec_sum_sqr_long_s16' function */
    y = vec_sum_sqr_long_s16(x, 4);

    /* Check the correctness of the results */
    if (y != res) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
