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
 * 32 bit signed, result is with saturation control.
 *
 * @param[out]  pY     Pointer to output vector, 32 bit signed.
 * @param[in]   len    Vector length.
 * @param[in]   radix  Radix.
 * @param[in]   pX     Pointer to input vector, 32 bit signed.
 * @param[in]   cnst   Constant, 32 bit signed.
 ******************************************************************************/
void vec_mul_const_sat_s32(int32_t *pY, int len, int radix, const int32_t *pX,
                           int32_t cnst)
{
    int n;
    int64_t tmp;

    for (n = 0; n < len; n++) {
        tmp = ((int64_t)pX[n] * cnst) >> radix;
        CIMLIB_SAT_INT(tmp, INT32_MAX, tmp);
        pY[n] = (int32_t)tmp;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (28)
#define CONST(X)  CIMLIB_CONST_S32(X, RADIX)


/*******************************************************************************
 * This function tests 'vec_mul_const_sat_s32' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mul_const_sat_s32(void)
{
    int32_t y[4];
    static int32_t x[4] = {
        CONST(7.9), CONST(4.0), CONST(-2.0), CONST(-7.9)
    };
    static int32_t cnst = CONST(1.1);
    static int32_t res[4] = {
        INT32_MAX,
        CONST( 4.4000000060E+00),
        CONST(-2.2000000030E+00),
        INT32_MIN
    };
    bool flOk = true;

    /* Call 'vec_mul_const_sat_s32' function */
    vec_mul_const_sat_s32(y, 4, RADIX, x, cnst);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
