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
 * This function square input value, 32 bit complex, result with saturation
 * control.
 *
 * @param[in]  x      Input value, 32 bit complex.
 * @param[in]  radix  Radix.
 *
 * @return            Square of input value, 32 bit unsigned.
 ******************************************************************************/
uint32_t sc_sqr_sat_c32(cint32_t x, int radix)
{
    uint32_t y;
    uint64_t tmp;

    tmp = (uint64_t)((int64_t)x.re * x.re);
    tmp += (uint64_t)((int64_t)x.im * x.im);
    tmp >>= radix;
    CIMLIB_SAT_UINT(tmp, UINT32_MAX, tmp);
    y = (uint32_t)tmp;

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (28)
#define CONST(X)            CIMLIB_CONST_U32(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'sc_sqr_sat_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_sqr_sat_c32(void)
{
    int n;
    uint32_t y[4];
    static cint32_t x[4] = {
        CONST_CPLX(3.9,  3.9),
        CONST_CPLX(0.12, -0.12),
        CONST_CPLX(-3.9,  3.5),
        CONST_CPLX(0.03, -0.06)
    };
    static uint32_t res[4] = {
        UINT32_MAX,
        CONST(2.8799999505E-02),
        UINT32_MAX,
        CONST(4.4999979436E-03)
    };
    bool flOk = true;

    /* Call 'sc_sqr_sat_c32' function */
    for(n = 0; n < 4; n++) {
        y[n] = sc_sqr_sat_c32(x[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
