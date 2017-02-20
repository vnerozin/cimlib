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
 * This function multiplies with conjugate two input values, 16 bit complex,
 * result is accumulated in output accumulator.
 *
 * @param[in]  x      Input value, 16 bit complex.
 * @param[in]  y      Input value, 16 bit complex.
 * @param[in]  acc    Accumulator, 16 bit complex.
 * @param[in]  radix  Radix.
 *
 * @return            Accumulator, 16 bit complex.
 ******************************************************************************/
cint16_t sc_mac_cj_c16(cint16_t x, cint16_t y, cint16_t acc, int radix)
{
    int32_t re, im;

    re = (int32_t)x.re * y.re + (int32_t)x.im * y.im;
    im = (int32_t)x.im * y.re - (int32_t)x.re * y.im;
    acc.re += (int16_t)(re >> radix);
    acc.im += (int16_t)(im >> radix);

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (10)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'sc_mac_cj_c16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_mac_cj_c16(void)
{
    int n;
    cint16_t acc = {0, 0};
    static cint16_t x[4] = {
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(0.75, -0.33),
        CONST_CPLX(-0.75, 0.33),
        CONST_CPLX(-0.75, -0.33)
    };
    static cint16_t y[4] = {
        CONST_CPLX(0.75, -0.33),
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(-0.75, -0.33),
        CONST_CPLX(-0.75, 0.33)
    };
    static cint16_t res = CONST_CPLX(1.8125000000E+00, 0);
    bool flOk = true;

    /* Call 'sc_mac_cj_c16' function */
    for (n = 0; n < 4; n++) {
        acc = sc_mac_cj_c16(x[n], y[n], acc, RADIX);
    }

    /* Check the correctness of the results */
    if ((acc.re != res.re) || (acc.im != res.im)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
