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
 * Definitions
 * ---------------------------------------------------------------------------*/

/* Maximum possible radix */
#define RADIX  (28)

/* Short constants macros */
#define CONST(X)  CIMLIB_CONST_S32(X, RADIX)


/* -----------------------------------------------------------------------------
 * Exported functions
 * ---------------------------------------------------------------------------*/

/*******************************************************************************
 * This function calculates sine of input value normalised by 'pi,
 * 32 bit signed. Input value limits are -1.0..1.0.
 *
 * @param[in]  x      Value normalised by 'pi', 32 bit signed.
 * @param[in]  radix  Radix.
 *
 * @return            Sine of value, 32 bit signed.
 ******************************************************************************/
int32_t sc_sin_s32(int32_t x, int radix)
{
    int32_t y, tmp, one;

    /* Constants */
    one = (1 << radix);

    /* Use cubic interpolation */
    if (x < 0) {
        /* y = 4.0 * x * (x + 1.0) */
        y = sc_mul_s32(x, x + one, radix - 2);
    } else {
        /* y = 4.0 * x * (1.0 - x) */
        y = sc_mul_s32(x, one - x, radix - 2);
    }

    if (y < 0) {
        /* y = 0.225 * (y * -y - y) + y; */
        tmp = (-y - one);
    } else {
        /* y = 0.225 * (y * y - y) + y; */
        tmp = (y - one);
    }

    tmp = sc_mul_s32(tmp, CONST(0.225), RADIX);
    tmp += one;

    y = sc_mul_s32(y, tmp, radix);

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'sc_sin_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_sin_s32(void)
{
    int n;
    int32_t y[32];
    static const int32_t x[32] = {
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
    static const int32_t res[32] = {
        CONST( 0.0000000000E+00), CONST(-1.9475255162E-01),
        CONST(-3.8212890550E-01), CONST(-5.5581665039E-01),
        CONST(-7.0781249925E-01), CONST(-8.3260902390E-01),
        CONST(-9.2431640625E-01), CONST(-9.8091430590E-01),
        CONST(-1.0000000000E+00), CONST(-9.8091430590E-01),
        CONST(-9.2431640625E-01), CONST(-8.3218383789E-01),
        CONST(-7.0781249925E-01), CONST(-5.5581665039E-01),
        CONST(-3.8212890550E-01), CONST(-1.9400024414E-01),
        CONST( 0.0000000000E+00), CONST( 1.9400024042E-01),
        CONST( 3.8212890178E-01), CONST( 5.5581664667E-01),
        CONST( 7.0781249553E-01), CONST( 8.3218383417E-01),
        CONST( 9.2431640252E-01), CONST( 9.8091430217E-01),
        CONST( 1.0000000000E+00), CONST( 9.8091430217E-01),
        CONST( 9.2431640252E-01), CONST( 8.3260902017E-01),
        CONST( 7.0781249553E-01), CONST( 5.5581664667E-01),
        CONST( 3.8212890178E-01), CONST( 1.9475254789E-01)
    };
    bool flOk = true;

    /* Call 'sc_sin_s32' function */
    for(n = 0; n < 32; n++) {
        y[n] = sc_sin_s32(x[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 32, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
