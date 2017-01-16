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
 * This function calculates by element multiply of vector with constant,
 * 32 bit complex, result is with saturation control.
 *
 * @param[out]  pY     Pointer to output vector, 32 bit complex.
 * @param[in]   len    Vector length.
 * @param[in]   radix  Radix.
 * @param[in]   pX     Pointer to input vector, 32 bit complex.
 * @param[in]   cnst   Constant, 32 bit complex.
 ******************************************************************************/
void vec_mul_const_sat_c32(cint32_t *pY, int len, int radix, const cint32_t *pX,
                           cint32_t cnst)
{
    int n;
    int64_t re, im;

    for (n = 0; n < len; n++) {
        re = (int64_t)pX[n].re * cnst.re - (int64_t)pX[n].im * cnst.im;
        im = (int64_t)pX[n].im * cnst.re + (int64_t)pX[n].re * cnst.im;
        re >>= radix;
        im >>= radix;
        CIMLIB_SAT_INT(re, INT32_MAX, re);
        CIMLIB_SAT_INT(im, INT32_MAX, im);
        pY[n].re = (int32_t)re;
        pY[n].im = (int32_t)im;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_mul_const_sat_c32' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mul_const_sat_c32(void)
{
    cint32_t y[4];
    static cint32_t x[4] = {
        {11111111, -2222222}, {-3333333, 2044444400},
        {55555555, -6666666}, {-2137777700, 8888888}
    };
    static cint32_t res[4] = {
        {21111111, -10000000}, {1015555534, INT32_MAX},
        {107777777, -41111110}, {INT32_MIN, 1086666626}
    };
    static cint32_t cnst = {
         CIMLIB_CONST_S32(2.0, 24),
        -CIMLIB_CONST_S32(0.5, 24)
    };
    bool flOk = true;

    /* Call 'vec_mul_const_sat_c32' function */
    vec_mul_const_sat_c32(y, 4, 24, x, cnst);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
