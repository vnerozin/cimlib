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
 * This function calculates reciprocal of input value, 32 bit signed.
 *
 * @param[in]  x      Input value, 32 bit signed.
 * @param[in]  radix  Radix.
 *
 * @return            Reciprocal of input value, 32 bit unsigned.
 ******************************************************************************/
int32_t sc_rcp_s32(int32_t x, int radix)
{
    int32_t y;
    int64_t tmp;

    tmp = 1;
    tmp <<= (radix * 2);
    tmp /= x;
    y = (int32_t)tmp;

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (24)
#define CONST(X)  CIMLIB_CONST_S32(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_rcp_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_rcp_s32(void)
{
    int n;
    int32_t y[4];
    static int32_t x[4] = {
        1, INT32_MAX, INT32_MIN, CONST(1.0)
    };
    static int32_t res[4] = {
        0, CONST(7.8125E-03), CONST(-7.8125E-03), CONST(1.0)
    };
    bool flOk = true;

    /* Call 'sc_rcp_s32' function */
    for(n = 0; n < 4; n++) {
        y[n] = sc_rcp_s32(x[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
