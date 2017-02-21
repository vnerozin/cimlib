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
 * This function multiplies two input values, 16 bit signed, result is with
 * saturation control and accumulated in output accumulator.
 *
 * @param[in]  x      Input value, 16 bit signed.
 * @param[in]  y      Input value, 16 bit signed.
 * @param[in]  acc    Accumulator, 16 bit signed.
 * @param[in]  radix  Radix.
 *
 * @return            Accumulator, 16 bit signed.
 ******************************************************************************/
int16_t sc_mac_sat_s16(int16_t x, int16_t y, int16_t acc, int radix)
{
    int32_t tmp;

    tmp = (int32_t)x * y;
    tmp >>= radix;
    tmp += acc;
    CIMLIB_SAT_INT(tmp, INT16_MAX, tmp);
    acc = (int16_t)tmp;

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (12)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_mac_sat_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_mac_sat_s16(void)
{
    int n;
    int16_t acc = 0;
    static int16_t x[4] = {
        CONST(7.9), CONST(4.0), CONST(2.0), CONST(1.1)
    };
    static int16_t y[4] = {
        CONST(1.1), CONST(2.0), CONST(4.0), CONST(7.9)
    };
    bool flOk = true;

    /* Call 'sc_mac_sat_s16' function */
    acc = sc_mac_s16(x[0], y[0], 0, RADIX);
    for(n = 1; n < 4; n++) {
        acc = sc_mac_sat_s16(x[n], y[n], acc, RADIX);
    }

    /* Check the correctness of the results */
    if (acc != INT16_MAX) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
