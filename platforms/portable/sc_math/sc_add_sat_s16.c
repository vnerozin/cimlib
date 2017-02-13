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
 * This function performs addition of input values, 16 bit signed,
 * result is with saturation control.
 *
 * @param[in]  x  Input value, 16 bit signed.
 * @param[in]  y  Input value, 16 bit signed.
 *
 * @return        Result of addition, 16 bit signed.
 ******************************************************************************/
int16_t sc_add_sat_s16(int16_t x, int16_t y)
{
    int16_t z;
    int32_t tmp;

    tmp = (int32_t)x + y;
    CIMLIB_SAT_INT(tmp, INT16_MAX, tmp);
    z = (int16_t)tmp;

    return z;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (12)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_add_sat_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_sc_add_sat_s16(void)
{
    int n;
    int16_t z[4];
    static int16_t x[4] = {
        CONST(-7.1), CONST(0.1), CONST(5.6), CONST(3.14)
    };
    static int16_t y[4] = {
        CONST(-2.1), CONST(-0.1), CONST(5.6), CONST(-3.14)
    };
    static int16_t res[4] = {
        INT16_MIN, 0, INT16_MAX, 0
    };
    bool flOk = true;

    /* Call 'sc_add_sat_s16' function */
    for(n = 0; n < 4; n++) {
        z[n] = sc_add_sat_s16(x[n], y[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
