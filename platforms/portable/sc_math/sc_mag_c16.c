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
 * This function calculates absolute complex (magnitude) of value,
 * 16 bit complex.
 *
 * @param[in]  x  Value, 16 bit complex.
 *
 * @return        Absolute complex (magnitude) of value, 16 bit unsigned.
 ******************************************************************************/
uint16_t sc_mag_c16(cint16_t x)
{
    uint16_t y;
    uint32_t eng;

    eng = (uint32_t)((int32_t)x.re * x.re + (int32_t)x.im * x.im);
    y = sc_sqrt_u32(eng);

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (12)
#define CONST(X)            CIMLIB_CONST_S16(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'sc_mag_c16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_sc_mag_c16(void)
{
    int n;
    uint16_t y[4];
    static cint16_t x[4] = {
        CONST_CPLX(7.9997558594E+00,  7.9997558594E+00),
        CONST_CPLX(9.9975585938E-01, -9.9975585938E-01),
        CONST_CPLX(7.9997558594E+00, -8.0000000000E+00),
        CONST_CPLX(3.0126953125E-01, -1.0549316406E+00)
    };
    static uint16_t res[4] = {
        46339,                         /* Only for test purposes */
        CONST(1.4138183594E+00),
        46340,                         /* Only for test purposes */
        CONST(1.0969238281E+00)
    };
    bool flOk = true;

    /* Call 'sc_mag_c16' function */
    for (n = 0; n < 4; n++) {
        y[n] = sc_mag_c16(x[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
