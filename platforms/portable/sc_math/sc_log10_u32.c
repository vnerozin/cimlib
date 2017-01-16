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

/******************************************************************************
 * This function calculates logarithm by base 10 of value, 32 bit signed.
 * Returns zero if 'x' is equal zero.
 *
 * @param[in]  x  Value, 32 bit unsigned.
 *
 * @return        Logarithm by base 10 of value, 32 bit signed.
 *                Returns zero if 'x' is equal zero.
 ******************************************************************************/
int32_t sc_log10_u32(uint32_t x, int radix)
{
    int32_t y;

    /* Calculate logarithm by base 2 */
    y = sc_log2_u32(x, radix);

    /* Correct base to base 10 */
    y = sc_mul_s32(CIMLIB_CONST_S32(0.301029995664, 28), y, 28);

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (24)
#define CONST(X)  CIMLIB_CONST_S32(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_log10_u32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_log10_u32(void)
{
    int n;
    int32_t y[6];
    static uint32_t x[6] = {
        CONST(0.0), CONST(1.0), CONST(2.6), CONST(4.1), CONST(0.1), CONST(0.9)
    };
    static int32_t res[6] = {
        CONST( 0.0000000000E+00),
        CONST( 0.0000000000E+00),
        CONST( 4.1497331858E-01),
        CONST( 6.1278378963E-01),
        CONST(-9.9999994040E-01),
        CONST(-4.5757532120E-02)
    };
    bool flOk = true;

    /* Call 'sc_log10_u32' function */
    for (n = 0; n < 6; n++) {
        y[n] = sc_log10_u32(x[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 6, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
