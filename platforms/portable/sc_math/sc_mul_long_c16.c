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
 * This function multiplies two input values, 16 bit complex, result with
 * extended precision.
 *
 * @param[in]  x  Input value, 16 bit complex.
 * @param[in]  y  Input value, 16 bit complex.
 *
 * @return        Multiply of input values, 32 bit complex.
 ******************************************************************************/
cint32_t sc_mul_long_c16(cint16_t x, cint16_t y)
{
    cint32_t z;

    z.re = (int32_t)x.re * y.re - (int32_t)x.im * y.im;
    z.im = (int32_t)x.im * y.re + (int32_t)x.re * y.im;

    return z;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX  (14)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)
#define CONST_CPLX_LONG(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX * 2)


/*******************************************************************************
 * This function tests 'sc_mul_long_c16' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_mul_long_c16(void)
{
    int n;
    cint32_t z[4];
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
    static cint32_t res[4] = {
        CONST_CPLX_LONG( 0.0000000000E+00,  6.7141127959E-01),
        CONST_CPLX_LONG( 4.9502563477E-01, -4.5358872041E-01),
        CONST_CPLX_LONG(-4.9502563477E-01,  4.5358872041E-01),
        CONST_CPLX_LONG( 0.0000000000E+00, -6.7141127959E-01)
    };
    bool flOk = true;

    /* Call 'sc_mul_long_c16' function */
    for (n = 0; n < 4; n++) {
        z[n] = sc_mul_long_c16(x[n], y[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
