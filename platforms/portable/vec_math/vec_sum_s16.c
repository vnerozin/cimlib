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
 * This function calculates sum of vector, 16 bit signed.
 *
 * @param[in]  pX   Pointer to input vector, 16 bit signed.
 * @param[in]  len  Vector length.
 *
 * @return          Sum of vector, 32 bit signed.
 ******************************************************************************/
int32_t vec_sum_s16(const int16_t *pX, int len)
{
    int n;
    int32_t acc = 0;

    for (n = 0; n < len; n++) {
        acc += pX[n];
    }

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (12)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)


/*******************************************************************************
 * This function tests 'vec_sum_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_s16(void)
{
    int32_t y;
    static int16_t x[4] = {
        CONST(2.1), CONST(0.1), CONST(-2.1), CONST(-0.1)
    };
    bool flOk = true;

    /* Call 'vec_sum_s16' function */
    y = vec_sum_s16(x, 4);

    /* Check the correctness of the results */
    if (y != 0) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
