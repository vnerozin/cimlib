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
 * This function calculates square of each element of vector, 16 bit complex.
 *
 * @param[out]  pY     Pointer to output vector, 16 bit unsigned.
 * @param[in]   len    Vector length.
 * @param[in]   radix  Radix.
 * @param[in]   pX     Pointer to input vector, 16 bit complex.
 ******************************************************************************/
void vec_sqr_c16(uint16_t *pY, int len, int radix, const cint16_t *pX)
{
    int n;
    uint32_t tmp;

    for (n = 0; n < len; n++) {
        tmp = (uint32_t)((int32_t)pX[n].re * pX[n].re);
        tmp += (uint32_t)((int32_t)pX[n].im * pX[n].im);
        pY[n] = (uint16_t)(tmp >> radix);
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sqr_c16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sqr_c16(void)
{
    uint16_t y[4];
    static cint16_t x[4] = {
        {32767, 32767}, {4095, -4095}, {32767, -32768}, {1234, -4321}
    };
    static uint16_t res[4] = {65532, 1023, 65534, 616};
    bool flOk = true;

    /* Call 'vec_sqr_c16' function */
    vec_sqr_c16(y, 4, 15, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
