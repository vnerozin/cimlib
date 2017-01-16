/*******************************************************************************
 * Copyright (c) 2017 Vasiliy Nerozin
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE.md for details.
 ******************************************************************************/ 

/* -----------------------------------------------------------------------------
 * Includes
 * ---------------------------------------------------------------------------*/
#include <stdlib.h>
#include "cimlib.h"               /* Library header */


/* -----------------------------------------------------------------------------
 * Definitions
 * ---------------------------------------------------------------------------*/

/* Simplify macroses for fixed radix */
#define RADIX     (28)
#define CONST(X)  CIMLIB_CONST_S32(X, RADIX)


/* -----------------------------------------------------------------------------
 * Exported functions
 * ---------------------------------------------------------------------------*/

/*******************************************************************************
 * This function calculates squared arctangent of relation 'y' to 'x'
 * normalised by 'pi', 32 bit signed.
 *
 * Reference: Performing efficient arctangent approximation
 *   http://www.embedded.com/design/other/4216719/
 *     Performing-efficient-arctangent-approximation
 *
 * @param[in]  x      Input value, 32 bit signed.
 * @param[in]  y      Input value, 32 bit signed.
 * @param[in]  radix  Radix.
 *
 * @return            Squared arctangent of relation 'y' to 'x' normalised
 *                    by 'pi', 32 bit signed.
 ******************************************************************************/
int32_t sc_atan2_s32(int32_t y, int32_t x, int radix)
{
    int32_t tmp, c28_m_pi, one;
    int32_t arctantent = 0;

    if ((y != 0) || (x != 0)) {
        /* Approximation constant multiplied by pi */
        c28_m_pi = CONST(0.28125 * CIMLIB_PI);
        one = (1 << (radix));

        /* Select octants */
        if (abs(y) < abs(x)) {
            /* Octants: 1, 4, 5, 8 */
            tmp = sc_mul_s32(CONST(CIMLIB_PI), sc_sqr_s32(x, radix), RADIX);
            tmp += sc_mul_s32(c28_m_pi, sc_sqr_s32(y, radix), RADIX);

            if (tmp != 0) {
                arctantent = sc_div_s32(sc_mul_s32(x, y, radix), tmp, radix);
            } else {
                arctantent = 0;
            }

            if (x <= 0) {
                /* Octants: 4, 5 */
                if (y >= 0) {
                    arctantent = one + arctantent;
                } else {
                    arctantent = -one + arctantent;
                }
            }
        } else {
            /* Octants: 2, 3, 6, 7 */
            tmp = sc_mul_s32(CONST(CIMLIB_PI), sc_sqr_s32(y, radix), RADIX);
            tmp += sc_mul_s32(c28_m_pi, sc_sqr_s32(x, radix), RADIX);

            if (tmp != 0) {
                arctantent = sc_div_s32(sc_mul_s32(x, y, radix), tmp, radix);
            } else {
                arctantent = 0;
            }

            if (x > 0) {
                /* Octants: 2, 3 */
                arctantent = one / 2 - arctantent;
            } else {
                /* Octants: 6, 7 */
                if (x < 0) {
                    arctantent = -one / 2 - arctantent;
                } else {
                    if (y > 0) {
                        arctantent = one / 2;
                    } else {
                        arctantent = -one / 2;
                    }
                }
            }
        }
    }

    return arctantent;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'sc_atan2_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_atan2_s32(void)
{
    int n;
    int32_t z[36];
    static const int32_t x[36] = {
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
        CONST( 8.7500000000E-01), CONST( 9.3725585938E-01),
        CONST( 0.0000000000E+00), CONST( 0.0000000000E+00),
        CONST( 1.0000000000E+00), CONST(-1.0000000000E+00)
    };
    static const int32_t y[36] = {
        CONST( 0.0000000000E+00), CONST(-1.9458007812E-01),
        CONST(-3.8208007812E-01), CONST(-5.5590820312E-01),
        CONST(-7.0776367188E-01), CONST(-8.3251953125E-01),
        CONST(-9.2431640625E-01), CONST(-9.8095703125E-01),
        CONST(-1.0000000000E+00), CONST(-9.8095703125E-01),
        CONST(-9.2431640625E-01), CONST(-8.3227539062E-01),
        CONST(-7.0776367188E-01), CONST(-5.5590820312E-01),
        CONST(-3.8208007812E-01), CONST(-1.9384765625E-01),
        CONST( 0.0000000000E+00), CONST( 1.9384765625E-01),
        CONST( 3.8208007812E-01), CONST( 5.5590820312E-01),
        CONST( 7.0776367188E-01), CONST( 8.3227539062E-01),
        CONST( 9.2431640625E-01), CONST( 9.8095703125E-01),
        CONST( 1.0000000000E+00), CONST( 9.8095703125E-01),
        CONST( 9.2431640625E-01), CONST( 8.3251953125E-01),
        CONST( 7.0776367188E-01), CONST( 5.5590820312E-01),
        CONST( 3.8208007812E-01), CONST( 1.9458007812E-01),
        CONST( 1.0000000000E+00), CONST(-1.0000000000E+00),
        CONST( 0.0000000000E+00), CONST( 0.0000000000E+00)
    };
    static const int32_t res[36] = {
        CONST( 1.0000000000E+00), CONST(-9.3470837548E-01),
        CONST(-8.6808035150E-01), CONST(-8.0755169317E-01),
        CONST(-7.5978191942E-01), CONST(-7.2050595284E-01),
        CONST(-6.9070971757E-01), CONST(-6.6707444564E-01),
        CONST(-6.4869950712E-01), CONST(-6.3444280624E-01),
        CONST(-6.2342623249E-01), CONST(-6.1495962739E-01),
        CONST(-6.0862338170E-01), CONST(-6.0403285176E-01),
        CONST(-6.0109397396E-01), CONST(-5.9971356392E-01),
        CONST( 0.0000000000E+00), CONST( 4.0028643608E-01),
        CONST( 3.9890602604E-01), CONST( 3.9596714824E-01),
        CONST( 3.9137661830E-01), CONST( 3.8504037261E-01),
        CONST( 3.7657376751E-01), CONST( 3.6555719376E-01),
        CONST( 3.5130049288E-01), CONST( 3.3292555436E-01),
        CONST( 3.0929028243E-01), CONST( 2.7949404716E-01),
        CONST( 2.4021808058E-01), CONST( 1.9244830683E-01),
        CONST( 1.3191964850E-01), CONST( 6.5291624516E-02),
        CONST( 5.0000000000E-01), CONST(-5.0000000000E-01),
        CONST( 0.0000000000E+00), CONST( 1.0000000000E+00)
    };
    bool flOk = true;

    /* Call 'sc_atan2_s32' function */
    for(n = 0; n < 36; n++) {
        z[n] = sc_atan2_s32(y[n], x[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 36, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
