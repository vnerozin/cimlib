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
 * This function calculates by element multiply of input vectors, 16 bit signed,
 * result is with saturation control.
 *
 * @param[out]  pZ     Pointer to output vector, 16 bit signed.
 * @param[in]   len    Vector length.
 * @param[in]   radix  Radix.
 * @param[in]   pX     Pointer to input vector, 16 bit signed.
 * @param[in]   pY     Pointer to input vector, 16 bit signed.
 ******************************************************************************/
void vec_mul_sat_s16(int16_t *pZ, int len, int radix, const int16_t *pX,
                     const int16_t *pY)
{
    int n;
    int32_t tmp;

    for (n = 0; n < len; n++) {
        tmp = (int32_t)pX[n] * pY[n];
        tmp >>= radix;
        CIMLIB_SAT_INT(tmp, INT16_MAX, tmp);
        pZ[n] = (int16_t)tmp;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (10)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)


/*******************************************************************************
 * This function tests 'vec_mul_sat_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mul_sat_s16(void)
{
    int16_t z[4];
    static int16_t x[4] = {
        CONST(7.9), CONST(4.0), CONST(2.0), CONST(-7.9)
    };
    static int16_t y[4] = {
        CONST(7.9), CONST(3.3), CONST(1.1), CONST(7.9)
    };
    static int16_t res[4] = {
        INT16_MAX,
        CONST( 1.3199218750E+01),
        CONST( 2.1992187500E+00),
        INT16_MIN
    };
    bool flOk = true;

    /* Call 'vec_mul_sat_s16' function */
    vec_mul_sat_s16(z, 4, RADIX, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
