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
 * This function calculates by element complex multiply of input vectors,
 * 16 bit complex, result is with saturation control.
 *
 * @param[out]  pZ     Pointer to output vector, 16 bit complex.
 * @param[in]   len    Vector length.
 * @param[in]   radix  Radix.
 * @param[in]   pX     Pointer to input vector, 16 bit complex.
 * @param[in]   pY     Pointer to input vector, 16 bit complex.
 ******************************************************************************/
void vec_mul_sat_c16(cint16_t *pZ, int len, int radix, const cint16_t *pX,
                     const cint16_t *pY)
{
    int n;
    int32_t re, im;

    for (n = 0; n < len; n++) {
        re = (int32_t)pX[n].re * pY[n].re - (int32_t)pX[n].im * pY[n].im;
        im = (int32_t)pX[n].im * pY[n].re + (int32_t)pX[n].re * pY[n].im;
        re >>= radix;
        im >>= radix;
        CIMLIB_SAT_INT(re, INT16_MAX, re);
        CIMLIB_SAT_INT(im, INT16_MAX, im);
        pZ[n].re = (int16_t)re;
        pZ[n].im = (int16_t)im;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (14)
#define CONST(X)            CIMLIB_CONST_S16(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_mul_sat_c16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mul_sat_c16(void)
{
    cint16_t z[4];
    static cint16_t x[4] = {
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(1.99, 0.33),
        CONST_CPLX(0.75, -1.99),
        CONST_CPLX(0.75, 0.33),
    };
    static cint16_t y[4] = {
        CONST_CPLX(0.33, 0.75),
        CONST_CPLX(1.99, -0.75),
        CONST_CPLX(-0.33, 1.99),
        CONST_CPLX(-0.33, -0.75),
    };
    static cint16_t res[4] = {
        CONST_CPLX(0, 6.7138671875E-01),
        {INT16_MAX, CONST(-8.3581542969E-01)},
        {INT16_MAX, INT16_MAX},
        CONST_CPLX(0, -6.7144775391E-01)
    };
    bool flOk = true;

    /* Call 'vec_mul_sat_c16' function */
    vec_mul_sat_c16(z, 4, RADIX, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
