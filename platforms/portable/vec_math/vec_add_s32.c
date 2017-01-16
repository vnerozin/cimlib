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
 * This function calculates by element addition of two vectors, 32 bit signed.
 *
 * @param[out]  pZ   Pointer to output vector, 32 bit signed.
 * @param[in]   len  Vector length.
 * @param[in]   pX   Pointer to input vector, 32 bit signed.
 * @param[in]   pY   Pointer to input vector, 32 bit signed.
 ******************************************************************************/
void vec_add_s32(int32_t *pZ, int len, const int32_t *pX, const int32_t *pY)
{
    int n;

    for (n = 0; n < len; n++) {
        pZ[n] = (int32_t)(pX[n] + pY[n]);
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (28)
#define CONST(X)  CIMLIB_CONST_S32(X, RADIX)


/*******************************************************************************
 * This function tests 'vec_add_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_vec_add_s32(void)
{
    int32_t z[4];
    static int32_t x[4] = {
        CONST(2.1), CONST(0.1), CONST(-5.6), CONST(3.14)
    };
    static int32_t y[4] = {
        CONST(-2.1), CONST(-0.1), CONST(5.6), CONST(-3.14)
    };
    static int32_t res[4] = {
        0, 0, 0, 0
    };
    bool flOk = true;

    /* Call 'vec_add_s32' function */
    vec_add_s32(z, 4, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
