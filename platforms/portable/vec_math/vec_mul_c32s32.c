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
 * This function calculates by element multiply of vectors, 32 bit complex and
 * 32 bit signed.
 *
 * @param[out]  pZ     Pointer to output vector, 32 bit complex.
 * @param[in]   len    Vector length.
 * @param[in]   radix  Radix.
 * @param[in]   pX     Pointer to input vector, 32 bit complex.
 * @param[in]   pY     Pointer to input vector, 32 bit signed.
 ******************************************************************************/
void vec_mul_c32s32(cint32_t *pZ, int len, int radix, const cint32_t *pX,
                    const int32_t *pY)
{
    int n;
    int64_t re, im;

    for (n = 0; n < len; n++) {
        re = (int64_t)pX[n].re * pY[n];
        im = (int64_t)pX[n].im * pY[n];
        pZ[n].re = (int32_t)(re >> radix);
        pZ[n].im = (int32_t)(im >> radix);
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_mul_c32s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mul_c32s32(void)
{
    cint32_t z[4];
    static cint32_t x[4] = {
        {98785432, 123456789}, {98785432, -123456789},
        {-98785432, 123456789}, {-98785432, -123456789}
    };
    static int32_t y[4] = {150000, 300000, 450000, 600000};
    static cint32_t res[4] = {
        {56525477, 70642541}, {113050955, -141285083},
        {-169576433, 211927623}, {-226101911, -282570166}
    };
    bool flOk = true;

    /* Call 'vec_mul_c32s32' function */
    vec_mul_c32s32(z, 4, 18, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
