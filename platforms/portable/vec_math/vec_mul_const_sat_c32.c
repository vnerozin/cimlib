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

/* Simplify macroses for fixed radix */
#define RADIX               (30)
#define CONST(X)            CIMLIB_CONST_S32(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_mul_const_sat_c32' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mul_const_sat_c32(void)
{
    cint32_t y[4];
    static cint32_t x[4] = {
        CONST_CPLX(0.33, 0.75),
        CONST_CPLX(1.33, -1.9),
        CONST_CPLX(-1.33, 1.9),
        CONST_CPLX(-0.33, -0.75)
    };
    static cint32_t res[4] = {
        CONST_CPLX(1.1549999937E-01, 9.3389999960E-01),
        {INT32_MAX, CONST(-1.6511000004E+00)},
        {INT32_MIN, CONST( 1.6510999994E+00)},
        CONST_CPLX(-1.1550000031E-01, -9.3390000053E-01)
    };
    static cint32_t cnst = CONST_CPLX(1.1, 0.33);
    bool flOk = true;

    /* Call 'vec_mul_const_sat_c32' function */
    vec_mul_const_sat_c32(y, 4, RADIX, x, cnst);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(y, res, 4, flOk);

    return flOk;
}
#endif /* (CIMLIB_BUILD_TEST == 1) */
