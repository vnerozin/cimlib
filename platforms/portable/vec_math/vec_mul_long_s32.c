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
 * This function calculates by element complex multiply of input vectors,
 * 32 bit signed, result with extended precision.
 *
 * @param[out]  pZ   Pointer to output vector, 64 bit signed.
 * @param[in]   len  Vector length.
 * @param[in]   pX   Pointer to input vector, 32 bit signed.
 * @param[in]   pY   Pointer to input vector, 32 bit signed.
 ******************************************************************************/
void vec_mul_long_s32(int64_t *pZ, int len, const int32_t *pX,
                      const int32_t *pY)
{
    int n;

    for (n = 0; n < len; n++) {
        pZ[n] = (int64_t)pX[n] * pY[n];
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_mul_long_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mul_long_s32(void)
{
    int64_t z[4];
    static int32_t x[4] = {100000, 1000000, 1000000, INT32_MIN};
    static int32_t y[4] = {INT32_MIN, 100000, 1000, 100};
    static int64_t res[4] = {
        -214748364800000, 100000000000, 1000000000, -214748364800
    };
    bool flOk = true;

    /* Call 'vec_mul_long_s32' function */
    vec_mul_long_s32(z, 4, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
