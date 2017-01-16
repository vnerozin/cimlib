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
 * This function calculates by element multiply of input vectors, 16 bit signed.
 *
 * @param[out]  pZ     Pointer to output vector, 16 bit signed.
 * @param[in]   len    Vector length.
 * @param[in]   radix  Radix.
 * @param[in]   pX     Pointer to input vector, 16 bit signed.
 * @param[in]   pY     Pointer to input vector, 16 bit signed.
 ******************************************************************************/
void vec_mul_s16(int16_t *pZ, int len, int radix, const int16_t *pX,
                 const int16_t *pY)
{
    int n;
    int32_t tmp;

    for (n = 0; n < len; n++) {
        tmp = (int32_t)pX[n] * pY[n];
        pZ[n] = (int16_t)(tmp >> radix);
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_mul_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mul_s16(void)
{
    int16_t z[4];
    static int16_t x[4] = {100, 1000, 10000, -32768};
    static int16_t y[4] = {-32768, 10000, 1000, 100};
    static int16_t res[4] = {-800, 2441, 2441, -800};
    bool flOk = true;

    /* Call 'vec_mul_s16' function */
    vec_mul_s16(z, 4, 12, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
