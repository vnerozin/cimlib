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
 * This function multiplies two input values, 32 bit signed, result is
 * accumulated in output accumulator.
 *
 * @param[in]  x      Input value, 32 bit signed.
 * @param[in]  y      Input value, 32 bit signed.
 * @param[in]  acc    Accumulator, 32 bit signed.
 * @param[in]  radix  Radix.
 *
 * @return            Accumulator, 32 bit signed.
 ******************************************************************************/
int32_t sc_mac_s32(int32_t x, int32_t y, int32_t acc, int radix)
{
    acc += (int32_t)(((int64_t)x * y) >> radix);

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (20)
#define CONST(X)  CIMLIB_CONST_S32(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_mac_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_mac_s32(void)
{
    int n;
    int32_t acc = 0;
    static int32_t x[4] = {
        CONST(7.9), CONST(4.0), CONST(2.0), CONST(1.0)
    };
    static int32_t y[4] = {
        CONST(-1.0), CONST(-2.0), CONST(4.0), CONST(7.9)
    };
    bool flOk = true;

    /* Call 'sc_mac_s32' function */
    acc = sc_mac_s32(x[0], y[0], 0, RADIX);
    for(n = 1; n < 4; n++) {
        acc = sc_mac_s32(x[n], y[n], acc, RADIX);
    }

    /* Check the correctness of the results */
    if (acc != 0) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
