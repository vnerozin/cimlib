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
 * This function calculates square of each element of vector, 16 bit signed,
 * result with extended precision.
 *
 * @param[out]  pY   Pointer to output vector, 32 bit unsigned.
 * @param[in]   len  Vector length.
 * @param[in]   pX   Pointer to input vector, 16 bit signed.
 ******************************************************************************/
void vec_sqr_long_s16(uint32_t *pY, int len, const int16_t *pX)
{
    int n;

    for (n = 0; n < len; n++) {
        pY[n] = (uint32_t)pX[n] * pX[n];
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX          (12)
#define CONST(X)       CIMLIB_CONST_S16(X, RADIX)
#define CONST_LONG(X)  CIMLIB_CONST_U32(X, RADIX * 2)


/*******************************************************************************
 * This function tests 'vec_sqr_long_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sqr_long_s16(void)
{
    uint32_t y[4];
    static int16_t x[4] = {
        CONST(7.9), CONST(4.0), CONST(2.0), CONST(1.0)
    };
    static uint32_t res[4] = {
        CONST_LONG( 6.2408457041E+01),
        CONST_LONG( 1.6000000000E+01),
        CONST_LONG( 4.0000000000E+00),
        CONST_LONG( 1.0000000000E+00)
    };
    bool flOk = true;

    /* Call 'vec_sqr_long_s16' function */
    vec_sqr_long_s16(y, 4, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
