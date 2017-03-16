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
 * This function calculates arctangent of relation 'y' to 'x'
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
 * @return            Arctangent of relation 'y' to 'x' normalised
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

            if (y > 0) {
                /* Octants: 2, 3 */
                arctantent = one / 2 - arctantent;
            } else {
                /* Octants: 6, 7 */
                if (y < 0) {
                    arctantent = -one / 2 - arctantent;
                } else {
                    if (x > 0) {
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
    int16_t z[24];
    static const int16_t y[24] = {
        CONST(-1.0000000000E+00), CONST(-9.0000000000E-01),
        CONST(-8.0000000000E-01), CONST(-7.0000000000E-01),
        CONST(-6.0000000000E-01), CONST(-5.0000000000E-01),
        CONST(-4.0000000000E-01), CONST(-3.0000000000E-01),
        CONST(-2.0000000000E-01), CONST(-1.0000000000E-01),
        CONST( 0.0000000000E+00), CONST( 1.0000000000E-01),
        CONST( 2.0000000000E-01), CONST( 3.0000000000E-01),
        CONST( 4.0000000000E-01), CONST( 5.0000000000E-01),
        CONST( 6.0000000000E-01), CONST( 7.0000000000E-01),
        CONST( 8.0000000000E-01), CONST( 9.0000000000E-01),
        CONST( 1.0000000000E+00), CONST(-1.0000000000E+00),
        CONST( 1.0000000000E+00), CONST( 0.0000000000E+00)
    };
    static const int16_t x[24] = {
        CONST( 1.0000000000E-01), CONST( 1.0000000000E-01),
        CONST( 1.0000000000E-01), CONST( 1.0000000000E-01),
        CONST( 1.0000000000E-01), CONST( 1.0000000000E-01),
        CONST( 1.0000000000E-01), CONST( 1.0000000000E-01),
        CONST( 1.0000000000E-01), CONST( 1.0000000000E-01),
        CONST( 1.0000000000E-01), CONST( 1.0000000000E-01),
        CONST( 1.0000000000E-01), CONST( 1.0000000000E-01),
        CONST( 1.0000000000E-01), CONST( 1.0000000000E-01),
        CONST( 1.0000000000E-01), CONST( 1.0000000000E-01),
        CONST( 1.0000000000E-01), CONST( 1.0000000000E-01),
        CONST( 1.0000000000E-01), CONST( 0.0000000000E+00),
        CONST( 0.0000000000E+00), CONST( 0.0000000000E+00)
    };
    static const int16_t res[24] = {
        CONST(-4.6826171875E-01), CONST(-4.6484375000E-01),
        CONST(-4.6044921875E-01), CONST(-4.5483398438E-01),
        CONST(-4.4726562500E-01), CONST(-4.3701171875E-01),
        CONST(-4.2187500000E-01), CONST(-3.9599609375E-01),
        CONST(-3.5058593750E-01), CONST(-2.4414062500E-01),
        CONST( 0.0000000000E+00), CONST( 2.5000000000E-01),
        CONST( 3.5229492188E-01), CONST( 3.9697265625E-01),
        CONST( 4.2236328125E-01), CONST( 4.3701171875E-01),
        CONST( 4.4750976562E-01), CONST( 4.5507812500E-01),
        CONST( 4.6044921875E-01), CONST( 4.6484375000E-01),
        CONST( 4.6826171875E-01), CONST(-5.0000000000E-01),
        CONST( 5.0000000000E-01), CONST( 0.0000000000E+00)
    };
    bool flOk = true;

    /* Call 'sc_atan2_s16' function */
    for(n = 0; n < 24; n++) {
        z[n] = sc_atan2_s16(y[n], x[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 24, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
