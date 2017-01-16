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
 * 16 bit complex, result with extended precision.
 *
 * @param[out]  pZ   Pointer to output vector, 32 bit complex.
 * @param[in]   len  Vector length.
 * @param[in]   pX   Pointer to input vector, 16 bit complex.
 * @param[in]   pY   Pointer to input vector, 16 bit complex.
 ******************************************************************************/
void vec_mul_long_c16(cint32_t *pZ, int len, const cint16_t *pX,
                      const cint16_t *pY)
{
    int n;

    for (n = 0; n < len; n++) {
        pZ[n].re = (int32_t)pX[n].re * pY[n].re - (int32_t)pX[n].im * pY[n].im;
        pZ[n].im = (int32_t)pX[n].im * pY[n].re + (int32_t)pX[n].re * pY[n].im;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_mul_long_c16' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mul_long_c16(void)
{
    cint32_t z[4];
    static cint16_t x[4] = {
        {12345, 5432}, {12345, 5432}, {12345, 5432}, {12345, 5432}
    };
    static cint16_t y[4] = {
        {5432, 12345}, {5432, -12345}, {-5432, 12345}, {-5432, -12345}
    };
    static cint32_t res[4] = {
        {0, 181905649}, {134116080, -122892401},
        {-134116080, 122892401}, {0, -181905649}
    };
    bool flOk = true;

    /* Call 'vec_mul_long_c16' function */
    vec_mul_long_c16(z, 4, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
