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
 * This function performs addition of input values, 32 bit complex,
 * result is with saturation control.
 *
 * @param[in]  x  Input value, 32 bit complex.
 * @param[in]  y  Input value, 32 bit complex.
 *
 * @return        Result of addition, 32 bit complex.
 ******************************************************************************/
cint32_t sc_add_sat_c32(cint32_t x, cint32_t y)
{
    cint32_t z;
    int64_t re, im;

    re = (int64_t)x.re + y.re;
    im = (int64_t)x.im + y.im;

    CIMLIB_SAT_INT(re, INT32_MAX, re);
    CIMLIB_SAT_INT(im, INT32_MAX, im);

    z.re = (int32_t)re;
    z.im = (int32_t)im;

    return z;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (28)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'sc_add_sat_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_sc_add_sat_c32(void)
{
    int n;
    cint32_t z[4];
    static cint32_t x[4] = {
        CONST_CPLX(-7.1, 0.05),
        CONST_CPLX(0.1, -0.05),
        CONST_CPLX(5.6, 3.001),
        CONST_CPLX(3.14, 1.0)
    };
    static cint32_t y[4] = {
        CONST_CPLX(-2.1, -0.05),
        CONST_CPLX(-0.1, 0.05),
        CONST_CPLX(5.6, -3.001),
        CONST_CPLX(-3.14, -1.0)
    };
    static cint32_t res[4] = {
        {INT32_MIN, 0}, {0, 0}, {INT32_MAX, 0}, {0, 0}
    };
    bool flOk = true;

    /* Call 'sc_add_sat_c32' function */
    for(n = 0; n < 4; n++) {
        z[n] = sc_add_sat_c32(x[n], y[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
