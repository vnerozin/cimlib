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
 * This function square input value, 16 bit complex, result with saturation
 * control.
 *
 * @param[in]  x      Input value, 16 bit complex.
 * @param[in]  radix  Radix.
 *
 * @return            Square of input value, 16 bit unsigned.
 ******************************************************************************/
uint16_t sc_sqr_sat_c16(cint16_t x, int radix)
{
    uint16_t y;
    uint32_t tmp;

    tmp = (uint32_t)((int32_t)x.re * x.re);
    tmp += (uint32_t)((int32_t)x.im * x.im);
    tmp >>= radix;
    CIMLIB_SAT_UINT(tmp, UINT16_MAX, tmp);
    y = (uint16_t)tmp;

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (14)
#define CONST(X)            CIMLIB_CONST_U16(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'sc_sqr_sat_c16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_sqr_sat_c16(void)
{
    int n;
    uint16_t y[4];
    static cint16_t x[4] = {
        CONST_CPLX(1.9,  1.9),
        CONST_CPLX(0.12, -0.12),
        CONST_CPLX(-1.9,  1.5),
        CONST_CPLX(0.03, -0.06)
    };
    static uint16_t res[4] = {
        UINT16_MAX,
        CONST( 2.8747558594E-02),
        UINT16_MAX,
        CONST( 4.4555664062E-03)
    };
    bool flOk = true;

    /* Call 'sc_sqr_sat_c16' function */
    for(n = 0; n < 4; n++) {
        y[n] = sc_sqr_sat_c16(x[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
