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
 * This function multiplies with conjugate two input values, 32 bit complex,
 * result with saturation control.
 *
 * @param[in]  x      Input value, 32 bit complex.
 * @param[in]  y      Input value, 32 bit complex.
 * @param[in]  radix  Radix.
 *
 * @return            Conjugate multiply of input values, 32 bit complex.
 ******************************************************************************/
cint32_t sc_mul_cj_sat_c32(cint32_t x, cint32_t y, int radix)
{
    cint32_t z;
    int64_t re, im;

    re = (int64_t)x.re * y.re + (int64_t)x.im * y.im;
    im = (int64_t)x.im * y.re - (int64_t)x.re * y.im;
    re >>= radix;
    im >>= radix;
    CIMLIB_SAT_INT(re, INT32_MAX, re);
    CIMLIB_SAT_INT(im, INT32_MAX, im);
    z.re = (int32_t)re;
    z.im = (int32_t)im;

    return z;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (30)
#define CONST(X)            CIMLIB_CONST_S32(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'sc_mul_cj_sat_c32' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_sc_mul_cj_sat_c32(void)
{
    int n;
    cint32_t z[4];
    static cint32_t x[4] = {
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(1.99, 0.33),
        CONST_CPLX(0.75, -1.99),
        CONST_CPLX(0.75, 0.33),
    };
    static cint32_t y[4] = {
        CONST_CPLX(0.33, 0.75),
        CONST_CPLX(1.99, -0.75),
        CONST_CPLX(-0.33, 1.99),
        CONST_CPLX(-0.33, -0.75),
    };
    static cint32_t res[4] = {
        CONST_CPLX( 4.9500000011E-01, -4.5360000059E-01),
        {INT32_MAX, INT32_MAX},
        {INT32_MIN, CONST(-8.3580000047E-01)},
        CONST_CPLX(-4.9500000011E-01,  4.5359999966E-01)
    };
    bool flOk = true;

    /* Call 'sc_mul_cj_sat_c32' function */
    for (n = 0; n < 4; n++) {
        z[n] = sc_mul_cj_sat_c32(x[n], y[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
