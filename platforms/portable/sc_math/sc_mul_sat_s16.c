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
 * This function multiplies two input values, 16 bit signed, result is with
 * saturation control.
 *
 * @param[in]  x      Input value, 16 bit signed.
 * @param[in]  y      Input value, 16 bit signed.
 * @param[in]  radix  Radix.
 *
 * @return            Minimum of input values, 16 bit signed.
 ******************************************************************************/
int16_t sc_mul_sat_s16(int16_t x, int16_t y, int radix)
{
    int16_t z;
    int32_t tmp;

    tmp = ((int32_t)x * y) >> radix;
    CIMLIB_SAT_INT(tmp, INT16_MAX, tmp);
    z = (int16_t)tmp;

    return z;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (10)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_mul_sat_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_mul_sat_s16(void)
{
    int n;
    int16_t z[4];
    static int16_t x[4] = {
        CONST(7.9), CONST(4.0), CONST(2.0), CONST(-7.9)
    };
    static int16_t y[4] = {
        CONST(7.9), CONST(3.3), CONST(1.1), CONST(7.9)
    };
    static int16_t res[4] = {
        INT16_MAX,
        CONST( 1.3199218750E+01),
        CONST( 2.1992187500E+00),
        INT16_MIN
    };
    bool flOk = true;

    /* Call 'sc_mul_sat_s16' function */
    for(n = 0; n < 4; n++) {
        z[n] = sc_mul_sat_s16(x[n], y[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
