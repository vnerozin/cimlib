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
 * This function square input value, 16 bit signed, result with saturation
 * control.
 *
 * @param[in]  x      Input value, 16 bit signed.
 * @param[in]  radix  Radix.
 *
 * @return            Square of input value, 16 bit unsigned.
 ******************************************************************************/
uint16_t sc_sqr_sat_s16(int16_t x, int radix)
{
    uint16_t y;
    uint32_t tmp;

    tmp = (uint32_t)(((int32_t)x * x) >> radix);
    CIMLIB_SAT_UINT(tmp, UINT16_MAX, tmp);
    y = (uint16_t)tmp;

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX       (11)
#define CONST(X)    CIMLIB_CONST_S16(X, RADIX)
#define CONST_U(X)  CIMLIB_CONST_U16(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_sqr_sat_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_sqr_sat_s16(void)
{
    int n;
    uint16_t y[4];
    static int16_t x[4] = {
        CONST(3.0), CONST(6.0), CONST(2.0), CONST(1.0)
    };
    static uint16_t res[4] = {
        CONST_U(9.0), UINT16_MAX, CONST_U(4.0), CONST_U(1.0)
    };
    bool flOk = true;

    /* Call 'sc_sqr_sat_s16' function */
    for (n = 0; n < 4; n++) {
        y[n] = sc_sqr_sat_s16(x[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
