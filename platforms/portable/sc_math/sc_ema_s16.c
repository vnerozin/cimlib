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
 * This function perform EMA (Exponential Moving Average) of input value,
 * 16 bit signed. Use 'CIMLIB_EMA_TIME_2_ALPHA_S16' macro to convert EMA time
 * constant into alpha.
 *
 * @param[in]  acc    Accumulator (previous EMA), 16 bit signed.
 * @param[in]  x      New value, 16 bit signed.
 * @param[in]  alpha  Alpha, [0..1.0], 16 bit signed.
 * @param[in]  radix  Radix.
 *
 * @return            New EMA (accumulator), 16 bit signed.
 ******************************************************************************/
int16_t sc_ema_s16(int16_t acc, int16_t x, int16_t alpha, int radix)
{
    int16_t rnd = 0;

    /* For correct rounding add half of radix */
    if (radix != 0) {
        rnd = (1 << (radix - 1));
    }

    /* EMA */
    acc += (int16_t)(((int32_t)alpha * (x - acc) + rnd) / (1 << radix));

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (12)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)
#define EMA_TIME_2_ALPHA(TIME, FREQS)  \
    CIMLIB_EMA_TIME_2_ALPHA_S16(TIME, FREQS, RADIX)


/*******************************************************************************
 * This function tests 'sc_ema_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_ema_s16(void)
{
    int n;
    int16_t z[4];
    static int16_t x = CONST(0.2);
    static int16_t alpha = EMA_TIME_2_ALPHA(1.0, 20.0);
    static int16_t res[4] = {
        CONST(1.0000000000E+00),
        CONST(9.6020507812E-01),
        CONST(9.2236328125E-01),
        CONST(8.8647460938E-01)
    };
    bool flOk = true;

    /* Call 'sc_ema_s16' function */
    z[0] = CONST(1.0);

    for(n = 1; n < 4; n++) {
        z[n] = sc_ema_s16(z[n - 1], x, alpha, RADIX);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
