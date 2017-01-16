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

/******************************************************************************
 * This function calculates natural logarithm of value, 16 bit signed.
 * Returns zero if 'x' is equal zero.
 *
 * @param[in]  x  Value, 16 bit unsigned.
 *
 * @return        Natural logarithm of value, 16 bit signed.
 *                Returns zero if 'x' is equal zero.
 ******************************************************************************/
int16_t sc_ln_u16(uint16_t x, int radix)
{
    int16_t y;

    /* Calculate logarithm by base 2 */
    y = sc_log2_u16(x, radix);

    /* Correct base to natural */
    y = sc_mul_s16(CIMLIB_CONST_S16(0.693147180559, 14), y, 14);

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (12)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_ln_u16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_ln_u16(void)
{
    int n;
    int16_t y[6];
    static uint16_t x[6] = {
        CONST(0.0), CONST(1.0), CONST(2.6), CONST(4.1), CONST(0.1), CONST(0.9)
    };
    static int16_t res[6] = {
        CONST( 0.0000000000E+00),
        CONST( 0.0000000000E+00),
        CONST( 9.5507812500E-01),
        CONST( 1.4106445312E+00),
        CONST(-2.3020019531E+00),
        CONST(-1.0571289062E-01)
    };
    bool flOk = true;

    /* Call 'sc_ln_u16' function */
    for (n = 0; n < 6; n++) {
        y[n] = sc_ln_u16(x[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 6, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
