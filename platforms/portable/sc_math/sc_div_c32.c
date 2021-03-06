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
 * This function perform division of input values, 32 bit complex.
 *
 * @param[in]  x      Dividend, 32 bit complex.
 * @param[in]  y      Divisor, 32 bit complex.
 * @param[in]  radix  Radix.
 *
 * @return            Result of division, 32 bit complex.
 ******************************************************************************/
cint32_t sc_div_c32(cint32_t x, cint32_t y, int radix)
{
    cint32_t z;
    int32_t y2;

    y2 = (int32_t)(((int64_t)y.re * y.re +
                    (int64_t)y.im * y.im) / (1 << radix));
    z.re = (int32_t)(((int64_t)x.re * y.re + (int64_t)x.im * y.im) / y2);
    z.im = (int32_t)(((int64_t)x.im * y.re - (int64_t)x.re * y.im) / y2);

    return z;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX  (24)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'sc_div_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_div_c32(void)
{
    int n;
    cint32_t z[4];
    static cint32_t x[4] = {
        CONST_CPLX(1.0, 1.0),
        CONST_CPLX(1.0, 1.0),
        CONST_CPLX(7.9, -0.1),
        CONST_CPLX(0.01, -7.9)
    };
    static cint32_t y[4] = {
        CONST_CPLX(1.0, 1.0),
        CONST_CPLX(1.0, -1.0),
        CONST_CPLX(0.1, -3.0),
        CONST_CPLX(0.01, -1.0)
    };
    static cint32_t res[4] = {
        CONST_CPLX(1.0, 0),
        CONST_CPLX(0, 1.0),
        CONST_CPLX(1.2097668648E-01, 2.6293007135E+00),
        CONST_CPLX(7.8993103504E+00, -6.8993031979E-02)
    };
    bool flOk = true;

    /* Call 'sc_div_c32' function */
    for(n = 0; n < 4; n++) {
        z[n] = sc_div_c32(x[n], y[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
