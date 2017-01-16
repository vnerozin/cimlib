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
 * This function calculates square of each element of vector, 16 bit signed,
 * result is accumulated with extended precision.
 *
 * @param[out]  pYAcc  Pointer to output accumulation vector, 32 bit unsigned.
 * @param[in]   len    Vector length.
 * @param[in]   pX     Pointer to input vector, 16 bit signed.
 ******************************************************************************/
void vec_sqra_long_s16(uint32_t *pYAcc, int len, const int16_t *pX)
{
    int n;

    for (n = 0; n < len; n++) {
        pYAcc[n] += (uint32_t)pX[n] * pX[n];
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sqra_long_s16' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sqra_long_s16(void)
{
    static int16_t x[4] = {100, 1000, 10000, -10000};
    uint32_t y[4] = {0, 0, 0, 0};
    static uint32_t res[4] = {10000, 1000000, 100000000, 100000000};
    bool flOk = true;

    /* Call 'vec_sqra_long_s16' function */
    vec_sqra_long_s16(y, 4, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
