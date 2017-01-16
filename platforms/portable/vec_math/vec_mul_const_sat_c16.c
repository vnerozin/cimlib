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
 * 16 bit complex, result is with saturation control.
 *
 * @param[out]  pY     Pointer to output vector, 16 bit complex.
 * @param[in]   len    Vector length.
 * @param[in]   radix  Radix.
 * @param[in]   pX     Pointer to input vector, 16 bit complex.
 * @param[in]   cnst   Constant, 16 bit complex.
 ******************************************************************************/
void vec_mul_const_sat_c16(cint16_t *pY, int len, int radix, const cint16_t *pX,
                           cint16_t cnst)
{
    int n;
    int32_t re, im;

    for (n = 0; n < len; n++) {
        re = (int32_t)pX[n].re * cnst.re - (int32_t)pX[n].im * cnst.im;
        im = (int32_t)pX[n].im * cnst.re + (int32_t)pX[n].re * cnst.im;
        re >>= radix;
        im >>= radix;
        CIMLIB_SAT_INT(re, INT16_MAX, re);
        CIMLIB_SAT_INT(im, INT16_MAX, im);
        pY[n].re = (int16_t)re;
        pY[n].im = (int16_t)im;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (14)
#define CONST(X)            CIMLIB_CONST_S16(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_mul_const_sat_c16' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mul_const_sat_c16(void)
{
    cint16_t y[4];
    static cint16_t x[4] = {
        CONST_CPLX(0.33, 0.75),
        CONST_CPLX(1.33, -1.9),
        CONST_CPLX(-1.33, 1.9),
        CONST_CPLX(-0.33, -0.75)
    };
    static cint16_t res[4] = {
        CONST_CPLX(1.1547851562E-01,  9.3383789062E-01),
        {INT16_MAX, CONST(-1.6510620117E+00)},
        {INT16_MIN, CONST( 1.6510009766E+00)},
        CONST_CPLX(-1.1553955078E-01, -9.3389892578E-01)
    };
    static cint16_t cnst = CONST_CPLX(1.1, 0.33);
    bool flOk = true;

    /* Call 'vec_mul_const_sat_c16' function */
    vec_mul_const_sat_c16(y, 4, RADIX, x, cnst);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
