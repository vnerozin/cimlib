/*******************************************************************************
 * Copyright (c) 2017 Vasiliy Nerozin
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE.md for details.
 ******************************************************************************/ 

/* -----------------------------------------------------------------------------
 * Includes
 * ---------------------------------------------------------------------------*/
#include <stdlib.h>
#include "cimlib.h"               /* Library header */


/* -----------------------------------------------------------------------------
 * Exported functions
 * ---------------------------------------------------------------------------*/

/*******************************************************************************
 * This function calculates by element absolute value of input vector,
 * 16 bit signed.
 *
 * @param[out]  pY   Pointer to output vector, 16 bit signed.
 * @param[in]   len  Vector length.
 * @param[in]   pX   Pointer to input vector, 16 bit signed.
 ******************************************************************************/
void vec_abs_s16(int16_t *pY, int len, const int16_t *pX)
{
    int n;

    for (n = 0; n < len; n++) {
        pY[n] = (int16_t)abs(pX[n]);
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (10)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)


/*******************************************************************************
 * This function tests 'vec_abs_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_abs_s16(void)
{
    int16_t y[4];
    static int16_t x[4] = {
        CONST(7.9), CONST(-4.0), CONST(2.0), CONST(-1.0)
    };
    static int16_t res[4] = {
        CONST(7.9), CONST(4.0), CONST(2.0), CONST(1.0)
    };
    bool flOk = true;

    /* Call 'vec_abs_s16' function */
    vec_abs_s16(y, 4, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
