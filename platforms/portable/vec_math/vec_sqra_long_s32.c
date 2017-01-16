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
 * This function calculates square of each element of vector, 32 bit signed,
 * result is accumulated with extended precision.
 *
 * @param[in,out]  pYAcc  Pointer to input-output accumulation vector,
 *                        32 bit unsigned.
 * @param[in]      len    Vector length.
 * @param[in]      pX     Pointer to input vector, 32 bit signed.
 ******************************************************************************/
void vec_sqra_long_s32(uint64_t *pYAcc, int len, const int32_t *pX)
{
    int n;

    for (n = 0; n < len; n++) {
        pYAcc[n] += (uint64_t)pX[n] * pX[n];
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'test_vec_sqra_long_s32' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sqra_long_s32(void)
{
    static int32_t x[4] = {100001, 1000001, 10000001, -10000001};
    uint64_t y[4] = {0, 0, 0, 0};
    static uint64_t res[4] = {
        10000200001, 1000002000001,
        100000020000001, 100000020000001
    };
    bool flOk = true;

    /* Call 'vec_sqra_long_s32' function */
    vec_sqra_long_s32(y, 4, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
