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
 * Definitions
 * ---------------------------------------------------------------------------*/

/* Maximum possible radix */
#define RADIX  (14)

/* Short constants macros */
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)


/* -----------------------------------------------------------------------------
 * Exported functions
 * ---------------------------------------------------------------------------*/

/*******************************************************************************
 * This function calculates sine of input value normalised by 'pi,
 * 16 bit signed. Input value limits are -1.0..1.0.
 *
 * @param[in]  x      Value normalised by 'pi', 16 bit signed.
 * @param[in]  radix  Radix.
 *
 * @return            Sine of value, 16 bit signed.
 ******************************************************************************/
int16_t sc_sin_s16(int16_t x, int radix)
{
    int16_t y, tmp, one;

    /* Constants */
    one = (1 << radix);

    /* Use cubic interpolation */
    if (x < 0) {
        /* y = 4.0 * x * (x + 1.0) */
        y = sc_mul_s16(x, x + one, radix - 2);
    }
    else {
        /* y = 4.0 * x * (1.0 - x) */
        y = sc_mul_s16(x, one - x, radix - 2);
    }

    if (y < 0) {
        /* y = 0.225 * (y * -y - y) + y; */
        tmp = (-y - one);
    }
    else {
        /* y = 0.225 * (y * y - y) + y; */
        tmp = (y - one);
    }

    tmp = sc_mul_s16(tmp, CONST(0.225), RADIX);
    tmp += one;

    y = sc_mul_s16(y, tmp, radix);

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'sc_sin_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_sin_s16(void)
{
    int n;
    int16_t y[32];
    static const int16_t x[32] = {
        CONST(-1.0000000000E+00), CONST(-9.3725585938E-01),
        CONST(-8.7500000000E-01), CONST(-8.1250000000E-01),
        CONST(-7.5000000000E-01), CONST(-6.8725585938E-01),
        CONST(-6.2500000000E-01), CONST(-5.6250000000E-01),
        CONST(-5.0000000000E-01), CONST(-4.3750000000E-01),
        CONST(-3.7500000000E-01), CONST(-3.1250000000E-01),
        CONST(-2.5000000000E-01), CONST(-1.8750000000E-01),
        CONST(-1.2500000000E-01), CONST(-6.2500000000E-02),
        CONST( 0.0000000000E+00), CONST( 6.2500000000E-02),
        CONST( 1.2500000000E-01), CONST( 1.8750000000E-01),
        CONST( 2.5000000000E-01), CONST( 3.1250000000E-01),
        CONST( 3.7500000000E-01), CONST( 4.3750000000E-01),
        CONST( 5.0000000000E-01), CONST( 5.6250000000E-01),
        CONST( 6.2500000000E-01), CONST( 6.8725585938E-01),
        CONST( 7.5000000000E-01), CONST( 8.1250000000E-01),
        CONST( 8.7500000000E-01), CONST( 9.3725585938E-01)
    };
    static const int16_t res[32] = {
        CONST( 0.0000000000E+00), CONST(-1.9476318359E-01),
        CONST(-3.8214111328E-01), CONST(-5.5584716797E-01),
        CONST(-7.0782470703E-01), CONST(-8.3264160156E-01),
        CONST(-9.2431640625E-01), CONST(-9.8089599609E-01),
        CONST(-1.0000000000E+00), CONST(-9.8089599609E-01),
        CONST(-9.2431640625E-01), CONST(-8.3215332031E-01),
        CONST(-7.0782470703E-01), CONST(-5.5584716797E-01),
        CONST(-3.8214111328E-01), CONST(-1.9403076172E-01),
        CONST( 0.0000000000E+00), CONST( 1.9396972656E-01),
        CONST( 3.8208007812E-01), CONST( 5.5578613281E-01),
        CONST( 7.0776367188E-01), CONST( 8.3209228516E-01),
        CONST( 9.2425537109E-01), CONST( 9.8083496094E-01),
        CONST( 1.0000000000E+00), CONST( 9.8083496094E-01),
        CONST( 9.2425537109E-01), CONST( 8.3245849609E-01),
        CONST( 7.0776367188E-01), CONST( 5.5578613281E-01),
        CONST( 3.8208007812E-01), CONST( 1.9464111328E-01)
    };
    bool flOk = true;

    /* Call 'sc_sin_s16' function */
    for(n = 0; n < 32; n++) {
        y[n] = sc_sin_s16(x[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 32, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
