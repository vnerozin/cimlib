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
 * This function perform division of input values, 32 bit signed.
 *
 * @param[in]  x      Dividend, 32 bit signed.
 * @param[in]  y      Divisor, 32 bit signed.
 * @param[in]  radix  Radix.
 *
 * @return            Result of division, 32 bit signed.
 ******************************************************************************/
int32_t sc_div_s32(int32_t x, int32_t y, int radix)
{
    x = (int32_t)(((int64_t)x * (1 << radix)) / y);

    return x;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (24)
#define CONST(X)  CIMLIB_CONST_S32(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_div_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_div_s32(void)
{
    int n;
    int32_t z[4];
    static int32_t x[4] = {
        CONST(7.9), CONST(4.0), CONST(2.0), CONST(1.0)
    };
    static int32_t y[4] = {
        CONST(2.2), CONST(3.3), CONST(1.1), CONST(0.2)
    };
    static int32_t res[4] = {
        CONST( 3.5909090638E+00),
        CONST( 1.2121211886E+00),
        CONST( 1.8181817532E+00),
        CONST( 5.0000002980E+00)
    };
    bool flOk = true;

    /* Call 'sc_div_s32' function */
    for(n = 0; n < 4; n++) {
        z[n] = sc_div_s32(x[n], y[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
