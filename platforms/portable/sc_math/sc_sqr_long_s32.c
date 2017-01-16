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
 * This function square input value, 32 bit signed, result with extended
 * precision.
 *
 * @param[in]  x  Input value, 32 bit signed.
 *
 * @return        Square of input value, 64 bit unsigned.
 ******************************************************************************/
uint64_t sc_sqr_long_s32(int32_t x)
{
    uint64_t y;

    y = (uint64_t)((int64_t)x * x);

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX          (24)
#define CONST(X)       CIMLIB_CONST_S32(X, RADIX)
#define CONST_LONG(X)  CIMLIB_CONST_U64(X, RADIX * 2)


/*******************************************************************************
 * This function tests 'sc_sqr_long_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_sqr_long_s32(void)
{
    int n;
    uint64_t y[4];
    static int32_t x[4] = {
        CONST(7.9), CONST(4.0), CONST(2.0), CONST(1.0)
    };
    static uint64_t res[4] = {
        CONST_LONG( 6.24099996232986455880E+01),
        CONST_LONG( 1.6000000000E+01),
        CONST_LONG( 4.0000000000E+00),
        CONST_LONG( 1.0000000000E+00)
    };
    bool flOk = true;

    /* Call 'sc_sqr_long_s32' function */
    for(n = 0; n < 4; n++) {
        y[n] = sc_sqr_long_s32(x[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
