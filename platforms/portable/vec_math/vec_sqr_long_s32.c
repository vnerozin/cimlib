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
 * This function calculates square of each element of vector, 32 bit signed,
 * result with extended precision.
 *
 * @param[out]  pY   Pointer to output vector, 64 bit unsigned.
 * @param[in]   len  Vector length.
 * @param[in]   pX   Pointer to input vector, 32 bit signed.
 ******************************************************************************/
void vec_sqr_long_s32(uint64_t *pY, int len, const int32_t *pX)
{
    int n;

    for (n = 0; n < len; n++) {
        pY[n] = (uint64_t)pX[n] * pX[n];
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sqr_long_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sqr_long_s32(void)
{
    uint64_t y[4];
    static int32_t x[4] = {100001, 1000001, 10000001, -10000001};
    static uint64_t res[4] = {
        10000200001, 1000002000001,
        100000020000001, 100000020000001
    };
    bool flOk = true;

    /* Call 'vec_sqr_long_s32' function */
    vec_sqr_long_s32(y, 4, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
