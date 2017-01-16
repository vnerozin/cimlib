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
 * This function perform division of input values, 16 bit complex.
 *
 * @param[in]  x      Dividend, 16 bit complex.
 * @param[in]  y      Divisor, 16 bit complex.
 * @param[in]  radix  Radix.
 *
 * @return            Result of division, 16 bit complex.
 ******************************************************************************/
cint16_t sc_div_c16(cint16_t x, cint16_t y, int radix)
{
    cint16_t z;
    int32_t y2;

    /* TODO Do we need 'y2' as 32bit value? */

    y2 = ((int32_t)y.re * y.re + (int32_t)y.im * y.im) / (1 << radix);
    z.re = (int16_t)(((int32_t)x.re * y.re + (int32_t)x.im * y.im) / y2);
    z.im = (int16_t)(((int32_t)x.im * y.re - (int32_t)x.re * y.im) / y2);

    return z;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX  (12)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'sc_div_c16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_div_c16(void)
{
    int n;
    cint16_t z[4];
    static cint16_t x[4] = {
        CONST_CPLX(1.0, 1.0),
        CONST_CPLX(1.0, 1.0),
        CONST_CPLX(7.9, -0.1),
        CONST_CPLX(0.01, -7.9)
    };
    static cint16_t y[4] = {
        CONST_CPLX(1.0, 1.0),
        CONST_CPLX(1.0, -1.0),
        CONST_CPLX(0.1, -3.0),
        CONST_CPLX(0.01, -1.0)
    };
    static cint16_t res[4] = {
        CONST_CPLX(1.0, 0),
        CONST_CPLX(0, 1.0),
        CONST_CPLX(1.2084960938E-01, 2.6291503906E+00),
        CONST_CPLX(7.8999023438E+00, -6.8847656250E-02)
    };
    bool flOk = true;

    /* Call 'sc_div_c16' function */
    for(n = 0; n < 4; n++) {
        z[n] = sc_div_c16(x[n], y[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
