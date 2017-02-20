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
 * result is accumulated in output vector.
 *
 * @param[in,out]  pZ     Pointer to input-output vector, 16 bit signed.
 * @param[in]      len    Vector length.
 * @param[in]      radix  Radix.
 * @param[in]      pX     Pointer to input vector, 16 bit signed.
 * @param[in]      pY     Pointer to input vector, 16 bit signed.
 ******************************************************************************/
void vec_mac_s16(int16_t *pZ, int len, int radix, const int16_t *pX,
                 const int16_t *pY)
{
    int n;

    for (n = 0; n < len; n++) {
        pZ[n] += (int16_t)(((int32_t)pX[n] * pY[n]) >> radix);
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (10)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)


/*******************************************************************************
 * This function tests 'vec_mac_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_vec_mac_s16(void)
{
    static int16_t x[4] = {
        CONST(7.9), CONST(4.0), CONST(2.0), CONST(1.0)
    };
    static int16_t y[4] = {
        CONST(2.2), CONST(3.3), CONST(1.1), CONST(0.2)
    };
    int16_t z[4] = {
        CONST(-1.7381835938E+01),
        CONST(-1.3199218750E+01),
        CONST(-2.1992187500E+00),
        CONST(-2.0019531250E-01)
    };
    static int16_t res[4] = {
        CONST(0.0), CONST(0.0), CONST(0.0), CONST(0.0)
    };
    bool flOk = true;

    /* Call 'vec_mac_s16' function */
    vec_mac_s16(z, 4, RADIX, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
