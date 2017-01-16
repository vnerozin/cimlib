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
#define RADIX     (12)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)


/* -----------------------------------------------------------------------------
 * Exported functions
 * ---------------------------------------------------------------------------*/

/*******************************************************************************
 * This function calculates squared arctangent of relation 'y' to 'x'
 * normalised by 'pi', 16 bit signed.
 *
 * Reference: Performing efficient arctangent approximation
 *   http://www.embedded.com/design/other/4216719/
 *     Performing-efficient-arctangent-approximation
 *
 * @param[in]  x      Input value, 16 bit signed.
 * @param[in]  y      Input value, 16 bit signed.
 * @param[in]  radix  Radix.
 *
 * @return            Squared arctangent of relation 'y' to 'x' normalised
 *                    by 'pi', 16 bit signed.
 ******************************************************************************/
int16_t sc_atan2_s16(int16_t y, int16_t x, int radix)
{
    int16_t tmp, c28_m_pi, one;
    int16_t arctantent = 0;

    if ((y != 0) || (x != 0)) {
        /* Approximation constant multiplied by pi */
        c28_m_pi = CONST(0.28125 * CIMLIB_PI);
        one = (1 << (radix));

        /* Select octants */
        if (abs(y) < abs(x)) {
            /* Octants: 1, 4, 5, 8 */
            tmp = sc_mul_s16(CONST(CIMLIB_PI), sc_sqr_s16(x, radix), RADIX);
            tmp += sc_mul_s16(c28_m_pi, sc_sqr_s16(y, radix), RADIX);

            if (tmp != 0) {
                arctantent = sc_div_s16(sc_mul_s16(x, y, radix), tmp, radix);
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
            tmp = sc_mul_s16(CONST(CIMLIB_PI), sc_sqr_s16(y, radix), RADIX);
            tmp += sc_mul_s16(c28_m_pi, sc_sqr_s16(x, radix), RADIX);

            if (tmp != 0) {
                arctantent = sc_div_s16(sc_mul_s16(x, y, radix), tmp, radix);
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
 * This function tests 'sc_atan2_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_atan2_s16(void)
{
    int n;
    int16_t z[36];
    static const int16_t x[36] = {
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
    static const int16_t y[36] = {
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
    static const int16_t res[36] = {
        CONST( 1.0000000000E+00), CONST(-9.3481445312E-01),
        CONST(-8.6816406250E-01), CONST(-8.0761718750E-01),
        CONST(-7.6000976562E-01), CONST(-7.2045898438E-01),
        CONST(-6.9067382812E-01), CONST(-6.6699218750E-01),
        CONST(-6.4868164062E-01), CONST(-6.3427734375E-01),
        CONST(-6.2329101562E-01), CONST(-6.1474609375E-01),
        CONST(-6.0839843750E-01), CONST(-6.0375976562E-01),
        CONST(-6.0083007812E-01), CONST(-5.9912109375E-01),
        CONST( 0.0000000000E+00), CONST( 4.0087890625E-01),
        CONST( 3.9916992188E-01), CONST( 3.9624023438E-01),
        CONST( 3.9160156250E-01), CONST( 3.8525390625E-01),
        CONST( 3.7670898438E-01), CONST( 3.6572265625E-01),
        CONST( 3.5131835938E-01), CONST( 3.3300781250E-01),
        CONST( 3.0932617188E-01), CONST( 2.7954101562E-01),
        CONST( 2.3999023438E-01), CONST( 1.9238281250E-01),
        CONST( 1.3183593750E-01), CONST( 6.5185546875E-02),
        CONST( 5.0000000000E-01), CONST(-5.0000000000E-01),
        CONST( 0.0000000000E+00), CONST( 1.0000000000E+00)
    };
    bool flOk = true;

    /* Call 'sc_atan2_s16' function */
    for(n = 0; n < 36; n++) {
        z[n] = sc_atan2_s16(y[n], x[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 36, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
