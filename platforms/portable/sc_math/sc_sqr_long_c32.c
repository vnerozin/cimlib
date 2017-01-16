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
 * This function square input value, 32 bit complex, result with extended
 * precision.
 *
 * @param[in]  x  Input value, 32 bit complex.
 *
 * @return        Square of input value, 64 bit unsigned.
 ******************************************************************************/
uint64_t sc_sqr_long_c32(cint32_t x)
{
    uint64_t y;

    y = (uint64_t)((int64_t)x.re * x.re);
    y += (uint64_t)((int64_t)x.im * x.im);

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (30)
#define CONST_LONG(X)       CIMLIB_CONST_U64(X, RADIX * 2)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'sc_sqr_long_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_sqr_long_c32(void)
{
    int n;
    uint64_t y[4];
    static cint32_t x[4] = {
        CONST_CPLX( 9.9996948242E-01,  9.9996948242E-01),
        CONST_CPLX( 1.2496948242E-01, -1.2496948242E-01),
        CONST_CPLX( 9.9996948242E-01, -1.0000000000E+00),
        CONST_CPLX( 3.7658691406E-02, -1.3186645508E-01)
    };
    static uint64_t res[4] = {
        CONST_LONG( 1.99987793155014514923E+00),
        CONST_LONG( 3.12347430735826492310E-02),
        CONST_LONG( 1.99993896577507257462E+00),
        CONST_LONG( 1.88069390133023262024E-02)
    };
    bool flOk = true;

    /* Call 'sc_sqr_long_c32' function */
    for(n = 0; n < 4; n++) {
        y[n] = sc_sqr_long_c32(x[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
