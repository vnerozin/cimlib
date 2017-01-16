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
 * This function calculates cosine of input value normalised by 'pi,
 * 32 bit signed. Input value limits are [-1.0..1.0].
 *
 * @param[in]  x      Value normalised by 'pi', 32 bit signed.
 * @param[in]  radix  Radix.
 *
 * @return            Cosine of value, 32 bit signed.
 ******************************************************************************/
int32_t sc_cos_s32(int32_t x, int radix)
{
    int32_t cosine;

    /* Calculate cosine as cos = sin(x + pi / 2) */

    /* Add 'pi / 2' */
    x += (1 << (radix - 1));

    /* Wrap input angle to -1.0..1.0 range */
    if (x > (1 << radix)) {
        x -= (1 << (radix + 1));
    }

    /* Sine */
    cosine = sc_sin_s32(x, radix);

    return cosine;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (24)
#define CONST(X)  CIMLIB_CONST_S32(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_cos_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_cos_s32(void)
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
        CONST(-1.0000000000E+00), CONST(-9.8076534271E-01),
        CONST(-9.2431640625E-01), CONST(-8.3218383789E-01),
        CONST(-7.0781248808E-01), CONST(-5.5517613888E-01),
        CONST(-3.8212889433E-01), CONST(-1.9400024414E-01),
        CONST( 0.0000000000E+00), CONST( 1.9400018454E-01),
        CONST( 3.8212883472E-01), CONST( 5.5581659079E-01),
        CONST( 7.0781242847E-01), CONST( 8.3218377829E-01),
        CONST( 9.2431634665E-01), CONST( 9.8091423512E-01),
        CONST( 1.0000000000E+00), CONST( 9.8091423512E-01),
        CONST( 9.2431634665E-01), CONST( 8.3218377829E-01),
        CONST( 7.0781242847E-01), CONST( 5.5581659079E-01),
        CONST( 3.8212883472E-01), CONST( 1.9400018454E-01),
        CONST( 0.0000000000E+00), CONST(-1.9400024414E-01),
        CONST(-3.8212889433E-01), CONST(-5.5517613888E-01),
        CONST(-7.0781248808E-01), CONST(-8.3218383789E-01),
        CONST(-9.2431640625E-01), CONST(-9.8076534271E-01)
    };
    bool flOk = true;

    /* Call 'sc_cos_s32' function */
    for(n = 0; n < 32; n++) {
        y[n] = sc_cos_s32(x[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 32, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
