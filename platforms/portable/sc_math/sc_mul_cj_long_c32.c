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
 * This function multiplies with conjugate two input values, 32 bit complex,
 * result with extended precision.
 *
 * @param[in]  x  Input value, 32 bit complex.
 * @param[in]  y  Input value, 32 bit complex.
 *
 * @return        Conjugate multiply of input values, 64 bit complex.
 ******************************************************************************/
cint64_t sc_mul_cj_long_c32(cint32_t x, cint32_t y)
{
    cint64_t z;

    z.re = (int64_t)x.re * y.re + (int64_t)x.im * y.im;
    z.im = (int64_t)x.im * y.re - (int64_t)x.re * y.im;

    return z;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX  (28)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)
#define CONST_CPLX_LONG(RE, IM)  CIMLIB_CONST_C64(RE, IM, RADIX * 2)


/*******************************************************************************
 * This function tests 'sc_mul_cj_long_c32' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_mul_cj_long_c32(void)
{
    int n;
    cint64_t z[4];
    static cint32_t x[4] = {
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(0.75, 0.33),
    };
    static cint32_t y[4] = {
        CONST_CPLX(0.33, 0.75),
        CONST_CPLX(0.33, -0.75),
        CONST_CPLX(-0.33, 0.75),
        CONST_CPLX(-0.33, -0.75),
    };
    static cint64_t res[4] = {
        CONST_CPLX_LONG( 4.9499999731779098510E-01, -4.5360000118017196335E-01),
        CONST_CPLX_LONG( 0.0000000000000000000E+00,  6.7139999881982803664E-01),
        CONST_CPLX_LONG( 0.0000000000000000000E+00, -6.7139999881982803664E-01),
        CONST_CPLX_LONG(-4.9499999731779098510E-01,  4.5360000118017196335E-01)
    };
    bool flOk = true;

    /* Call 'sc_mul_cj_long_c32' function */
    for (n = 0; n < 4; n++) {
        z[n] = sc_mul_cj_long_c32(x[n], y[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
