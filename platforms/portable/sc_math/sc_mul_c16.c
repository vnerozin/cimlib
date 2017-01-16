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
 * This function multiplies two input values, 16 bit complex.
 *
 * @param[in]  x      Input value, 16 bit complex.
 * @param[in]  y      Input value, 16 bit complex.
 * @param[in]  radix  Radix.
 *
 * @return            Multiply of input values, 16 bit complex.
 ******************************************************************************/
cint16_t sc_mul_c16(cint16_t x, cint16_t y, int radix)
{
    cint16_t z;
    int32_t re, im;

    re = (int32_t)x.re * y.re - (int32_t)x.im * y.im;
    im = (int32_t)x.im * y.re + (int32_t)x.re * y.im;
    z.re = (int16_t)(re >> radix);
    z.im = (int16_t)(im >> radix);

    return z;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX  (14)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'sc_mul_c16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_sc_mul_c16(void)
{
    int n;
    cint16_t z[4];
    static cint16_t x[4] = {
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(0.75, 0.33),
    };
    static cint16_t y[4] = {
        CONST_CPLX(0.33, 0.75),
        CONST_CPLX(0.33, -0.75),
        CONST_CPLX(-0.33, 0.75),
        CONST_CPLX(-0.33, -0.75),
    };
    static cint16_t res[4] = {
        CONST_CPLX( 0.0000000000E+00,  6.7138671875E-01),
        CONST_CPLX( 4.9499511719E-01, -4.5361328125E-01),
        CONST_CPLX(-4.9505615234E-01,  4.5355224609E-01),
        CONST_CPLX( 0.0000000000E+00, -6.7144775391E-01)
    };
    bool flOk = true;

    /* Call 'sc_mul_c16' function */
    for (n = 0; n < 4; n++) {
        z[n] = sc_mul_c16(x[n], y[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
