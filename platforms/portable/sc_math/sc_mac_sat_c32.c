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
 * This function multiplies two input values, 32 bit complex, result is with
 * saturation control and accumulated in output accumulator.
 *
 * @param[in]  x      Input value, 32 bit complex.
 * @param[in]  y      Input value, 32 bit complex.
 * @param[in]  acc    Accumulator, 32 bit complex.
 * @param[in]  radix  Radix.
 *
 * @return            Accumulator, 32 bit complex.
 ******************************************************************************/
cint32_t sc_mac_sat_c32(cint32_t x, cint32_t y, cint32_t acc, int radix)
{
    int64_t re, im;

    re = (int64_t)x.re * y.re - (int64_t)x.im * y.im;
    im = (int64_t)x.im * y.re + (int64_t)x.re * y.im;
    re >>= radix;
    im >>= radix;
    re += acc.re;
    im += acc.im;
    CIMLIB_SAT_INT(re, INT32_MAX, re);
    CIMLIB_SAT_INT(im, INT32_MAX, im);
    acc.re = (int32_t)re;
    acc.im = (int32_t)im;

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (30)
#define CONST(X)            CIMLIB_CONST_S32(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'sc_mac_sat_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_mac_sat_c32(void)
{
    int n;
    cint32_t acc = {0, 0};
    static cint32_t x[4] = {
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(0.75, -0.33),
        CONST_CPLX(-0.75, 0.33),
        CONST_CPLX(-0.75, -0.33)
    };
    static cint32_t y[4] = {
        CONST_CPLX(0.75, -0.33),
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(-0.75, -0.33),
        CONST_CPLX(-0.75, 0.33)
    };
    static cint32_t res = {INT32_MAX, CONST(0.0)};
    bool flOk = true;

    /* Call 'sc_mac_sat_c32' function */
    for (n = 0; n < 4; n++) {
        acc = sc_mac_sat_c32(x[n], y[n], acc, RADIX);
    }

    /* Check the correctness of the results */
    if ((acc.re != res.re) || (acc.im != res.im)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
