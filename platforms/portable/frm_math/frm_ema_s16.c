/*******************************************************************************
 * Copyright (c) 2017 Vasiliy Nerozin
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE.md for details.
 ******************************************************************************/ 

/* -----------------------------------------------------------------------------
 * Includes
 * ---------------------------------------------------------------------------*/
#include <string.h>
#include "cimlib.h"               /* Library header */


/* -----------------------------------------------------------------------------
 * Exported functions
 * ---------------------------------------------------------------------------*/

/*******************************************************************************
 * This function perform EMA (Exponential Moving Average) of vector,
 * frame based, 16 bit signed. Use 'CIMLIB_EMA_TIME_2_ALPHA_S16' macro
 * to convert EMA time constant into alpha.
 *
 * @param[in,out]  pX     Pointer to input/output vector, 16 bit signed.
 * @param[in]      len    Vector length.
 * @param[in]      acc    Accumulator (previous EMA), 16 bit signed.
 * @param[in]      alpha  Alpha, [0..1.0], 16 bit signed.
 * @param[in]      radix  Radix.
 *
 * @return                New EMA (accumulator), 16 bit signed.
 ******************************************************************************/
int16_t frm_ema_s16(int16_t *pX, int len, int16_t acc, int16_t alpha, int radix)
{
    int n;
    int32_t tmp;
    int16_t rnd = 0;

    /* For correct rounding add half of radix */
    if (radix != 0) {
        rnd = (1 << (radix - 1));
    }

    /* EMA */
    for (n = 0; n < len; n++) {
        tmp = (int32_t)alpha * (pX[n] - acc);
        acc += (int16_t)((tmp + rnd) >> radix);
        pX[n] = acc;
    }

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (12)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)
#define EMA_TIME_2_ALPHA(TIME, FREQS)  \
    CIMLIB_EMA_TIME_2_ALPHA_S16(TIME, FREQS, RADIX)


/*******************************************************************************
 * This function tests 'frm_ema_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_frm_ema_s16(void)
{
    int16_t z[4];
    static int16_t alpha = EMA_TIME_2_ALPHA(1.0, 20.0);
    static int16_t res[4] = {
        CONST(9.4995117188E-01),
        CONST(9.0234375000E-01),
        CONST(8.5717773438E-01),
        CONST(8.1420898438E-01)
    };
    bool flOk = true;

    /* Reset output vector */
    (void)memset(z, 0, 4 * sizeof(int16_t));

    /* Call 'sc_ema_s16' function */
    (void)frm_ema_s16(z, 4, CONST(1.0), alpha, RADIX);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
