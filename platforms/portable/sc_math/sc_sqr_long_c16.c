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
 * This function square input value, 16 bit complex, result with extended
 * precision.
 *
 * @param[in]  x  Input value, 16 bit complex.
 *
 * @return        Square of input value, 32 bit unsigned.
 ******************************************************************************/
uint32_t sc_sqr_long_c16(cint16_t x)
{
    uint32_t y;

    y = (uint32_t)((int32_t)x.re * x.re);
    y += (uint32_t)((int32_t)x.im * x.im);

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (15)
#define CONST_LONG(X)       CIMLIB_CONST_U32(X, RADIX * 2)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'sc_sqr_long_c16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_sqr_long_c16(void)
{
    int n;
    uint32_t y[4];
    static cint16_t x[4] = {
        CONST_CPLX( 9.9996948242E-01,  9.9996948242E-01),
        CONST_CPLX( 1.2496948242E-01, -1.2496948242E-01),
        CONST_CPLX( 9.9996948242E-01, -1.0000000000E+00),
        CONST_CPLX( 3.7658691406E-02, -1.3186645508E-01)
    };
    static uint32_t res[4] = {
        CONST_LONG( 1.9998779316E+00),
        CONST_LONG( 3.1234743074E-02),
        CONST_LONG( 1.9999389658E+00),
        CONST_LONG( 1.8806939013E-02)
    };
    bool flOk = true;

    /* Call 'sc_sqr_long_c16' function */
    for(n = 0; n < 4; n++) {
        y[n] = sc_sqr_long_c16(x[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
