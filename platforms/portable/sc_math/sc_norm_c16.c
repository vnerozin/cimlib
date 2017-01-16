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
 * This function normalises input value by it's magnitude, 16 bit complex.
 *
 * @param[in]  x      Input value, 16 bit complex.
 * @param[in]  radix  Radix.
 *
 * @return            Normalised input value by it's magnitude, 16 bit complex.
 ******************************************************************************/
cint16_t sc_norm_c16(cint16_t x, int radix)
{
    cint16_t y;
    int16_t norm;

    norm = (int16_t)sc_mag_c16(x);

    /* Avoid division by zero */
    if (norm > 0) {
        norm = sc_rcp_s16(norm, radix);
    }

    y.re = sc_mul_s16(x.re, norm, radix);
    y.im = sc_mul_s16(x.im, norm, radix);

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX  (10)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'test_sc_norm_c16' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_norm_c16(void)
{
    int n;
    cint16_t y[4];
    static cint16_t x[4] = {
        CONST_CPLX( 1.2055664062E+01,  5.3046875000E+00),
        CONST_CPLX(-1.2055664062E+01, -5.3046875000E+00),
        CONST_CPLX(-1.2055664062E+01,  5.3046875000E+00),
        CONST_CPLX( 1.2055664062E+01, -5.3046875000E+00)
    };
    static cint16_t res[4] = {
        CONST_CPLX( 9.0625000000E-01,  3.9843750000E-01),
        CONST_CPLX(-9.0722656250E-01, -3.9941406250E-01),
        CONST_CPLX(-9.0722656250E-01,  3.9843750000E-01),
        CONST_CPLX( 9.0625000000E-01, -3.9941406250E-01)
    };
    bool flOk = true;

    /* Call 'sc_norm_c16' function */
    for (n = 0; n < 4; n++) {
        y[n] = sc_norm_c16(x[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
