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
 * This function calculates by element multiply of vectors, 16 bit complex and
 * 16 bit signed.
 *
 * @param[out]  pZ     Pointer to output vector, 16 bit complex.
 * @param[in]   len    Vector length.
 * @param[in]   radix  Radix.
 * @param[in]   pX     Pointer to input vector, 16 bit complex.
 * @param[in]   pY     Pointer to input vector, 16 bit signed.
 ******************************************************************************/
void vec_mul_c16s16(cint16_t *pZ, int len, int radix, const cint16_t *pX,
                    const int16_t *pY)
{
    int n;
    int32_t re, im;

    for (n = 0; n < len; n++) {
        re = (int32_t)pX[n].re * pY[n];
        im = (int32_t)pX[n].im * pY[n];
        pZ[n].re = (int16_t)(re >> radix);
        pZ[n].im = (int16_t)(im >> radix);
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_mul_c16s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mul_c16s16(void)
{
    cint16_t z[4];
    static cint16_t x[4] = {
        {4096, 128}, {8192, -128}, {-8192, 128}, {-4096, 0}
    };
    static int16_t y[4] = {150, 300, 450, 600};
    static cint16_t res[4] = {
        {2400, 75}, {9600, -150}, {-14400, 225}, {-9600, 0}
    };
    bool flOk = true;

    /* Call 'vec_mul_c16s16' function */
    vec_mul_c16s16(z, 4, 8, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
