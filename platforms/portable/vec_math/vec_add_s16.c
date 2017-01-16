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
 * This function calculates by element addition of two vectors, 16 bit signed.
 *
 * @param[out]  pZ   Pointer to output vector, 16 bit signed.
 * @param[in]   len  Vector length.
 * @param[in]   pX   Pointer to input vector, 16 bit signed.
 * @param[in]   pY   Pointer to input vector, 16 bit signed.
 ******************************************************************************/
void vec_add_s16(int16_t *pZ, int len, const int16_t *pX, const int16_t *pY)
{
    int n;

    for (n = 0; n < len; n++) {
        pZ[n] = (int16_t)(pX[n] + pY[n]);
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (12)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)


/*******************************************************************************
 * This function tests 'vec_add_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_vec_add_s16(void)
{
    int16_t z[4];
    static int16_t x[4] = {
        CONST(2.1), CONST(0.1), CONST(-5.6), CONST(3.14)
    };
    static int16_t y[4] = {
        CONST(-2.1), CONST(-0.1), CONST(5.6), CONST(-3.14)
    };
    static int16_t res[4] = {
        0, 0, 0, 0
    };
    bool flOk = true;

    /* Call 'vec_add_s16' function */
    vec_add_s16(z, 4, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
