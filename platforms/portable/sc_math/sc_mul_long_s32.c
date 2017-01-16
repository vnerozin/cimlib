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
 * This function multiplies two input values, 32 bit signed, result with
 * extended precision.
 *
 * @param[in]  x  Input value, 32 bit signed.
 * @param[in]  y  Input value, 32 bit signed.
 *
 * @return        Multiply of input values, 64 bit signed.
 ******************************************************************************/
int64_t sc_mul_long_s32(int32_t x, int32_t y)
{
    int64_t z;

    z = (int64_t)x * y;

    return z;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX          (24)
#define CONST(X)       CIMLIB_CONST_S32(X, RADIX)
#define CONST_LONG(X)  CIMLIB_CONST_S64(X, RADIX * 2)


/*******************************************************************************
 * This function tests 'sc_mul_long_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_mul_long_s32(void)
{
    int n;
    int64_t z[4];
    static int32_t x[4] = {
        CONST(7.9), CONST(4.0), CONST(2.0), CONST(1.0)
    };
    static int32_t y[4] = {
        CONST(2.2), CONST(3.3), CONST(1.1), CONST(0.2)
    };
    static int64_t res[4] = {
        CONST_LONG(1.7379999853372574E+01),
        CONST_LONG(1.3200000047683716E+01),
        CONST_LONG(2.2000000476837158E+00),
        CONST_LONG(1.9999998807907104E-01)
    };
    bool flOk = true;

    /* Call 'sc_mul_long_s32' function */
    for(n = 0; n < 4; n++) {
        z[n] = sc_mul_long_s32(x[n], y[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
