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
 * This function perform division of input values, 16 bit signed.
 *
 * @param[in]  x      Dividend, 16 bit signed.
 * @param[in]  y      Divisor, 16 bit signed.
 * @param[in]  radix  Radix.
 *
 * @return            Result of division, 16 bit signed.
 ******************************************************************************/
int16_t sc_div_s16(int16_t x, int16_t y, int radix)
{
    x = (int16_t)(((int32_t)x * (1 << radix)) / y);

    return x;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (12)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_div_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_div_s16(void)
{
    int n;
    int16_t z[4];
    static int16_t x[4] = {
        CONST(7.9), CONST(4.0), CONST(2.0), CONST(1.0)
    };
    static int16_t y[4] = {
        CONST(2.2), CONST(3.3), CONST(1.1), CONST(0.2)
    };
    static int16_t res[4] = {
        CONST(3.5908203125E+00),
        CONST(1.2119140625E+00),
        CONST(1.8178710938E+00),
        CONST(5.0012207031E+00)
    };
    bool flOk = true;

    /* Call 'sc_div_s16' function */
    for(n = 0; n < 4; n++) {
        z[n] = sc_div_s16(x[n], y[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
