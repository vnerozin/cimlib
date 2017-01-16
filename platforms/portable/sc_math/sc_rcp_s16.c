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
 *      @fn  int16_t sc_rcp_s16(int16_t x,
 *                              int radix)
 *   @param  x      Input value, 16 bit signed
 *   @param  radix  Radix
 *  @return  Reciprocal of input value, 16 bit unsigned
 *   @brief  This function calculates reciprocal of input value, 16 bit signed
 ******************************************************************************/
int16_t sc_rcp_s16(int16_t x, int radix)
{
    int16_t y;
    int32_t tmp;

    tmp = 1;
    tmp <<= (radix * 2);
    tmp /= x;
    y = (int16_t)tmp;

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (12)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_rcp_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_rcp_s16(void)
{
    int n;
    int16_t y[4];
    static int16_t x[4] = {
        1, INT16_MAX, INT16_MIN, CONST(1.0)
    };
    static int16_t res[4] = {
        0, CONST(0.125), CONST(-0.125), CONST(1.0)
    };
    bool flOk = true;

    /* Call 'sc_rcp_s16' function */
    for(n = 0; n < 4; n++) {
        y[n] = sc_rcp_s16(x[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
