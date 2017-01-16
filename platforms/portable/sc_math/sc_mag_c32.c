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
 * 32 bit complex.
 *
 * @param[in]  x  Value, 32 bit complex.
 *
 * @return        Absolute complex (magnitude) of value, 32 bit unsigned.
 ******************************************************************************/
uint32_t sc_mag_c32(cint32_t x)
{
    uint32_t y;
    uint64_t eng;

    eng = (uint64_t)((int64_t)x.re * x.re + (int64_t)x.im * x.im);
    y = sc_sqrt_u64(eng);

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (24)
#define CONST(X)            CIMLIB_CONST_S32(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'sc_mag_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_sc_mag_c32(void)
{
    int n;
    uint32_t y[4];
    static cint32_t x[4] = {
        CONST_CPLX(1.2799999994E+02,  1.2799999994E+02),
        CONST_CPLX(1.0000000000E+00, -1.0000000000E+00),
        CONST_CPLX(1.2799999994E+02, -1.2800000000E+02),
        CONST_CPLX(7.3585980535E+00, -5.8868784964E+01)
    };
    static uint32_t res[4] = {
        3037000498,                    /* Only for test purposes */
        CONST(1.4142135382E+00),
        3037000499,                    /* Only for test purposes */
        CONST(5.9326914668E+01)
    };
    bool flOk = true;

    /* Call 'sc_mag_c32' function */
    for (n = 0; n < 4; n++) {
        y[n] = sc_mag_c32(x[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
