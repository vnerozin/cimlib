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
 * This function performs by element EMA (Exponential Moving Average) of vector,
 * 16 bit signed. Use 'CIMLIB_EMA_TIME_2_ALPHA_S16' macro to convert EMA time
 * constant into alpha.
 *
 * @param[in,out]  pAcc   Pointer to input/output accumulator vector
 *                        (previous EMA -> new EMA), 16 bit signed.
 * @param[in]      len    Vector length.
 * @param[in]      alpha  Alpha, 0..1.0, 16 bit signed.
 * @param[in]      radix  Radix.
 * @param[in]      pX     Pointer to input vector, 16 bit signed.
 ******************************************************************************/
void vec_ema_s16(int16_t *pAcc, int len, int16_t alpha, int radix,
                 const int16_t *pX)
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
        tmp = (int32_t)alpha * (pX[n] - pAcc[n]) + rnd;
        pAcc[n] += (int16_t)(tmp >> radix);
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (12)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)
#define EMA_TIME_2_ALPHA(TIME, FREQS)  \
    CIMLIB_EMA_TIME_2_ALPHA_S16(TIME, FREQS, RADIX)


/*******************************************************************************
 * This function tests 'test_vec_ema_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_vec_ema_s16(void)
{
    int n;
    int16_t acc[4] = {
        CONST(1.0), CONST(1.0), CONST(1.0), CONST(1.0)
    };
    static int16_t x[4] = {
        CONST(0.4), CONST(0.3), CONST(0.2), CONST(0.1)
    };
    static int16_t alpha = EMA_TIME_2_ALPHA(1.0, 20.0);
    static int16_t res[4] = {
        CONST(9.1430664062E-01),
        CONST(9.0014648438E-01),
        CONST(8.8574218750E-01),
        CONST(8.7158203125E-01)
    };
    bool flOk = true;

    /* Call 'vec_ema_s16' function */
    for (n = 0; n < 3; n++) {
        vec_ema_s16(acc, 4, alpha, RADIX, x);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(acc, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
