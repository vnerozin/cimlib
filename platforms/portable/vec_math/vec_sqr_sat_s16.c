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
 * result with saturation control.
 *
 * @param[out]  pY     Pointer to output vector, 16 bit unsigned.
 * @param[in]   len    Vector length.
 * @param[in]   radix  Radix.
 * @param[in]   pX     Pointer to input vector, 16 bit signed.
 ******************************************************************************/
void vec_sqr_sat_s16(uint16_t *pY, int len, int radix, const int16_t *pX)
{
    int n;
    uint32_t tmp;

    for (n = 0; n < len; n++) {
        tmp = (uint32_t)pX[n] * pX[n];
        tmp >>= radix;
        CIMLIB_SAT_UINT(tmp, UINT16_MAX, tmp);
        pY[n] = (uint16_t)tmp;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sqr_sat_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sqr_sat_s16(void)
{
    uint16_t y[4];
    static int16_t x[4] = {100, 1000, 10000, -10000};
    static uint16_t res[4] = {9, 976, UINT16_MAX, UINT16_MAX};
    bool flOk = true;

    /* Call 'vec_sqr_sat_s16' function */
    vec_sqr_sat_s16(y, 4, 10, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
