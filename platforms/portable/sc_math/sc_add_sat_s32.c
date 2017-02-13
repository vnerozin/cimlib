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
 * This function performs addition of input values, 32 bit signed,
 * result is with saturation control.
 *
 * @param[in]  x  Input value, 32 bit signed.
 * @param[in]  y  Input value, 32 bit signed.
 *
 * @return        Result of addition, 32 bit signed.
 ******************************************************************************/
int32_t sc_add_sat_s32(int32_t x, int32_t y)
{
    int32_t z;
    int64_t tmp;

    tmp = (int64_t)x + y;
    CIMLIB_SAT_INT(tmp, INT32_MAX, tmp);
    z = (int32_t)tmp;

    return z;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (28)
#define CONST(X)  CIMLIB_CONST_S32(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_add_sat_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_sc_add_sat_s32(void)
{
    int n;
    int32_t z[4];
    static int32_t x[4] = {
        CONST(-7.1), CONST(0.1), CONST(5.6), CONST(3.14)
    };
    static int32_t y[4] = {
        CONST(-2.1), CONST(-0.1), CONST(5.6), CONST(-3.14)
    };
    static int32_t res[4] = {
        INT32_MIN, 0, INT32_MAX, 0
    };
    bool flOk = true;

    /* Call 'sc_add_sat_s32' function */
    for(n = 0; n < 4; n++) {
        z[n] = sc_add_sat_s32(x[n], y[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
