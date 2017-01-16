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
 * This function multiplies two input values, 16 bit signed, result with
 * extended precision.
 *
 * @param[in]  x  Input value, 16 bit signed.
 * @param[in]  y  Input value, 16 bit signed.
 *
 * @return        Multiply of input values, 32 bit signed.
 ******************************************************************************/
int32_t sc_mul_long_s16(int16_t x, int16_t y)
{
    int32_t z;

    z = (int32_t)x * y;

    return z;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX          (12)
#define CONST(X)       CIMLIB_CONST_S16(X, RADIX)
#define CONST_LONG(X)  CIMLIB_CONST_S32(X, RADIX * 2)


/*******************************************************************************
 * This function tests 'sc_mul_long_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_mul_long_s16(void)
{
    int n;
    int32_t z[4];
    static int16_t x[4] = {
        CONST(7.9), CONST(4.0), CONST(2.0), CONST(1.0)
    };
    static int16_t y[4] = {
        CONST(2.2), CONST(3.3), CONST(1.1), CONST(0.2)
    };
    static int32_t res[4] = {
        CONST_LONG(1.7379399419E+01),
        CONST_LONG(1.3200195312E+01),
        CONST_LONG(2.2001953125E+00),
        CONST_LONG(1.9995117188E-01)
    };
    bool flOk = true;

    /* Call 'sc_mul_long_s16' function */
    for(n = 0; n < 4; n++) {
        z[n] = sc_mul_long_s16(x[n], y[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
