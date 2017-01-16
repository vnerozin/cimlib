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
 * 32 bit complex, result with extended precision.
 *
 * @param[out]  pZ   Pointer to output vector, 64 bit complex.
 * @param[in]   len  Vector length.
 * @param[in]   pX   Pointer to input vector, 32 bit complex.
 * @param[in]   pY   Pointer to input vector, 32 bit complex.
 ******************************************************************************/
void vec_mul_long_c32(cint64_t *pZ, int len, const cint32_t *pX,
                      const cint32_t *pY)
{
    int n;

    for (n = 0; n < len; n++) {
        pZ[n].re = (int64_t)pX[n].re * pY[n].re - (int64_t)pX[n].im * pY[n].im;
        pZ[n].im = (int64_t)pX[n].im * pY[n].re + (int64_t)pX[n].re * pY[n].im;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_mul_long_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mul_long_c32(void)
{
    cint64_t z[4];
    static cint32_t x[4] = {
        {123456789, 98785432}, {123456789, 98785432},
        {123456789, 98785432}, {123456789, 98785432}
    };
    static cint32_t y[4] = {
        {98785432, 123456789}, {98785432, -123456789},
        {-98785432, 123456789}, {-98785432, -123456789}
    };
    static cint64_t res[4] = {
        {0, 25000140325617145},
        {24391464469395696, -5483017174763897},
        {-24391464469395696, 5483017174763897},
        {0, -25000140325617145}
    };
    bool flOk = true;

    /* Call 'vec_mul_long_c32' function */
    vec_mul_long_c32(z, 4, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
