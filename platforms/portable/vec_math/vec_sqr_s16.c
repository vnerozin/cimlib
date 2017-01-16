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
 * This function calculates square of each element of vector, 16 bit signed.
 *
 * @param[out]  pY     Pointer to output vector, 16 bit unsigned.
 * @param[in]   len    Vector length.
 * @param[in]   radix  Radix.
 * @param[in]   pX     Pointer to input vector, 16 bit signed.
 ******************************************************************************/
void vec_sqr_s16(uint16_t *pY, int len, int radix, const int16_t *pX)
{
    int n;
    uint32_t tmp;

    for (n = 0; n < len; n++) {
        tmp = (uint32_t)((int32_t)pX[n] * pX[n]);
        pY[n] = (uint16_t)(tmp >> radix);
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX       (10)
#define CONST(X)    CIMLIB_CONST_S16(X, RADIX)
#define CONST_U(X)  CIMLIB_CONST_U16(X, RADIX)


/*******************************************************************************
 * This function tests 'vec_sqr_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sqr_s16(void)
{
    uint16_t y[4];
    static int16_t x[4] = {
        CONST(3.0), CONST(4.0), CONST(2.0), CONST(1.0)
    };
    static uint16_t res[4] = {
        CONST_U(9.0), CONST_U(16.0), CONST_U(4.0), CONST_U(1.0)
    };
    bool flOk = true;

    /* Call 'vec_sqr_s16' function */
    vec_sqr_s16(y, 4, RADIX, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
