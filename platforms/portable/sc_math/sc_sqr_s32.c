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
 * This function square input value, 32 bit signed.
 *
 * @param[in]  x      Input value, 32 bit signed.
 * @param[in]  radix  Radix.
 *
 * @return            Square of input value, 32 bit unsigned.
 ******************************************************************************/
uint32_t sc_sqr_s32(int32_t x, int radix)
{
    uint32_t y;

    y = (uint32_t)(((int64_t)x * x) >> radix);

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX       (20)
#define CONST(X)    CIMLIB_CONST_S32(X, RADIX)
#define CONST_U(X)  CIMLIB_CONST_U32(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_sqr_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_sqr_s32(void)
{
    int n;
    uint32_t y[4];
    static int32_t x[4] = {
        CONST(3.0), CONST(4.0), CONST(2.0), CONST(1.0)
    };
    static uint32_t res[4] = {
        CONST_U(9.0), CONST_U(16.0), CONST_U(4.0), CONST_U(1.0)
    };
    bool flOk = true;

    /* Call 'sc_sqr_s32' function */
    for (n = 0; n < 4; n++) {
        y[n] = sc_sqr_s32(x[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
