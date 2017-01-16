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

/******************************************************************************
 * This function calculates logarithm by base 2 of value, 32 bit signed.
 * Returns zero if 'x' is equal zero.
 *
 * Reference: A Fast Binary Logarithm Algorithm
 *   http://www.claysturner.com/dsp/binarylogarithm.pdf
 *
 * @param[in]  x  Value, 32 bit unsigned.
 *
 * @return        Logarithm by base 2 of value, 32 bit signed.
 *                Returns zero if 'x' is equal zero.
 ******************************************************************************/
int32_t sc_log2_u32(uint32_t x, int radix)
{
    int n;
    int32_t y = 0;
    int32_t b = (1 << (radix - 1));
    uint32_t one = (1 << radix);
    uint32_t two = (1 << (radix + 1));

    /* Only in 'x' not equal zero */
    if (x != 0) {
        /* Normalise 'x' to be in [1.0..2.0] range */
        while (x < one) {
            x <<= 1;
            y -= one;
        }

        while (x >= two) {
            x >>= 1;
            y += one;
        }

        /* Find mantissa */
        for (n = 0; n < radix; n++) {
            x = (uint32_t)(((uint64_t)x * x) >> radix);

            if (x >= two) {
                x >>= 1;
                y += b;
            }

            b >>= 1;
        }
    }

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (24)
#define CONST(X)  CIMLIB_CONST_S32(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_log2_u32' function. Returns 'true' if validation is
 * successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_log2_u32(void)
{
    int n;
    int32_t y[6];
    static uint32_t x[6] = {
        CONST(0.0), CONST(1.0), CONST(2.6), CONST(4.1), CONST(0.1), CONST(0.9)
    };
    static int32_t res[6] = {
        CONST( 0.0000000000E+00),
        CONST( 0.0000000000E+00),
        CONST( 1.3785115480E+00),
        CONST( 2.0356237888E+00),
        CONST(-3.3219278455E+00),
        CONST(-1.5200316906E-01)
    };
    bool flOk = true;

    /* Call 'sc_log2_u32' function */
    for (n = 0; n < 6; n++) {
        y[n] = sc_log2_u32(x[n], RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 6, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
