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
 * This function perform subtraction of input values, 32 bit complex.
 *
 * @param[in]  x  Input value, 32 bit complex.
 * @param[in]  y  Input value, 32 bit complex.
 *
 * @return        Result of subtraction, 32 bit complex.
 ******************************************************************************/
cint32_t sc_sub_c32(cint32_t x, cint32_t y)
{
    cint32_t z;

    z.re = x.re - y.re;
    z.im = x.im - y.im;

    return z;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX  (24)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'sc_sub_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_sc_sub_c32(void)
{
    int n;
    cint32_t z[4];
    static cint32_t x[4] = {
        CONST_CPLX(2.1, 0.05),
        CONST_CPLX(0.1, -0.05),
        CONST_CPLX(-5.6, 3.001),
        CONST_CPLX(3.14, 1.0)
    };
    static cint32_t y[4] = {
        CONST_CPLX(2.1, 0.05),
        CONST_CPLX(0.1, -0.05),
        CONST_CPLX(-5.6, 3.001),
        CONST_CPLX(3.14, 1.0)
    };
    static cint32_t res[4] = {
        {0, 0}, {0, 0}, {0, 0}, {0, 0}
    };
    bool flOk = true;

    /* Call 'sc_sub_c32' function */
    for(n = 0; n < 4; n++) {
        z[n] = sc_sub_c32(x[n], y[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
