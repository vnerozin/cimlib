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
 * This function calculates cosine of input value normalised by 'pi,
 * 16 bit signed. Input value limits are [-1.0..1.0].
 *
 * @param  x      Value normalised by 'pi', 16 bit signed.
 * @param  radix  Radix.
 *
 * @return        Cosine of value, 16 bit signed.
 ******************************************************************************/
int16_t sc_cos_s16(int16_t x, int radix)
{
    int16_t cosine;

    /* Calculate cosine as cos = sin(x + pi / 2) */

    /* Add 'pi / 2' */
    x += (1 << (radix - 1));

    /* Wrap input angle to [-1.0..1.0] range */
    if (x > (1 << radix)) {
        x -= (1 << (radix + 1));
    }

    /* Sine */
    cosine = sc_sin_s16(x, radix);

    return cosine;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (12)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_cos_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_cos_s16(void)
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
        CONST(-1.0000000000E+00), CONST(-9.8095703125E-01),
        CONST(-9.2431640625E-01), CONST(-8.3227539062E-01),
        CONST(-7.0776367188E-01), CONST(-5.5541992188E-01),
        CONST(-3.8208007812E-01), CONST(-1.9409179688E-01),
        CONST( 0.0000000000E+00), CONST( 1.9384765625E-01),
        CONST( 3.8183593750E-01), CONST( 5.5566406250E-01),
        CONST( 7.0751953125E-01), CONST( 8.3203125000E-01),
        CONST( 9.2407226562E-01), CONST( 9.8071289062E-01),
        CONST( 1.0000000000E+00), CONST( 9.8071289062E-01),
        CONST( 9.2407226562E-01), CONST( 8.3203125000E-01),
        CONST( 7.0751953125E-01), CONST( 5.5566406250E-01),
        CONST( 3.8183593750E-01), CONST( 1.9384765625E-01),
        CONST( 0.0000000000E+00), CONST(-1.9409179688E-01),
        CONST(-3.8208007812E-01), CONST(-5.5541992188E-01),
        CONST(-7.0776367188E-01), CONST(-8.3227539062E-01),
        CONST(-9.2431640625E-01), CONST(-9.8095703125E-01)
    };
    bool flOk = true;

    /* Call 'sc_cos_s16' function */
    for(n = 0; n < 32; n++) {
        y[n] = sc_cos_s16(x[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 32, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
