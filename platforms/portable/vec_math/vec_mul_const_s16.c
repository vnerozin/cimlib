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
 * This function calculates by element multiply of vector with constant,
 * 16 bit signed.
 *
 * @param[out]  pY     Pointer to output vector, 16 bit signed.
 * @param[in]   len    Vector length.
 * @param[in]   radix  Radix.
 * @param[in]   pX     Pointer to input vector, 16 bit signed.
 * @param[in]   cnst   Constant, 16 bit signed.
 ******************************************************************************/
void vec_mul_const_s16(int16_t *pY, int len, int radix, const int16_t *pX,
                       int16_t cnst)
{
    int n;

    for (n = 0; n < len; n++) {
        pY[n] = (int16_t)(((int32_t)pX[n] * cnst) >> radix);
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (10)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)


/*******************************************************************************
 * This function tests 'vec_mul_const_s16' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mul_const_s16(void)
{
    int16_t y[4];
    static int16_t x[4] = {
        CONST(7.9), CONST(4.0), CONST(-2.0), CONST(1.0)
    };
    static int16_t cnst = CONST(0.1);
    static int16_t res[4] = {
        CONST(7.8613281250E-01),
        CONST(3.9843750000E-01),
        CONST(-1.9921875000E-01),
        CONST(0.1)
    };
    bool flOk = true;

    /* Call 'vec_mul_const_s16' function */
    vec_mul_const_s16(y, 4, RADIX, x, cnst);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
