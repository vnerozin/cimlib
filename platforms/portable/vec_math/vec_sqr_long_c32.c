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
 * This function calculates square of each element of vector, 32 bit complex,
 * result with extended precision.
 *
 * @param[out]  pY   Pointer to output vector, 32 bit unsigned.
 * @param[in]   len  Vector length.
 * @param[in]   pX   Pointer to input vector, 32 bit complex.
 ******************************************************************************/
void vec_sqr_long_c32(uint64_t *pY, int len, const cint32_t *pX)
{
    int n;
    uint64_t tmp;

    for (n = 0; n < len; n++) {
        tmp = (uint64_t)pX[n].re * pX[n].re;
        tmp += (uint64_t)pX[n].im * pX[n].im;
        pY[n] = tmp;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sqr_long_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sqr_long_c32(void)
{
    uint64_t y[4];
    static cint32_t x[4] = {
        {(1 << 23), (1 << 23)}, {4095, -4095},
        {-(1 << 23), -32768}, {12345678, -6754321}
    };
    static uint64_t res[4] = {
        140737488355328, 33538050,
        70369817919488, 198036617450725
    };
    bool flOk = true;

    /* Call 'vec_sqr_long_c32' function */
    vec_sqr_long_c32(y, 4, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
