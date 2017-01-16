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
 * This function calculates logarithm by base 10 of value, 16 bit signed.
 * Returns zero if 'x' is equal zero.
 *
 * @param[in]  x  Value, 16 bit unsigned.
 *
 * @return        Logarithm by base 10 of value, 16 bit signed.
 *                Returns zero if 'x' is equal zero.
 ******************************************************************************/
int16_t sc_log10_u16(uint16_t x, int radix)
{
    int16_t y;

    /* Calculate logarithm by base 2 */
    y = sc_log2_u16(x, radix);

    /* Correct base to base 10 */
    y = sc_mul_s16(CIMLIB_CONST_S16(0.301029995664, 14), y, 14);

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (12)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_log10_u16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_log10_u16(void)
{
    int n;
    int16_t y[6];
    static uint16_t x[6] = {
        CONST(0.0), CONST(1.0), CONST(2.6), CONST(4.1), CONST(0.1), CONST(0.9)
    };
    static int16_t res[6] = {
        CONST( 0.0000000000E+00),
        CONST( 0.0000000000E+00),
        CONST( 4.1479492188E-01),
        CONST( 6.1254882812E-01),
        CONST(-9.9975585938E-01),
        CONST(-4.5898437500E-02)
    };
    bool flOk = true;

    /* Call 'sc_log10_u16' function */
    for (n = 0; n < 6; n++) {
        y[n] = sc_log10_u16(x[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 6, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
