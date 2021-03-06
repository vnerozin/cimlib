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
 * This function calculates by element complex multiply of input vectors,
 * 16 bit signed, result with extended precision.
 *
 * @param[out]  pZ   Pointer to output vector, 32 bit signed.
 * @param[in]   len  Vector length.
 * @param[in]   pX   Pointer to input vector, 16 bit signed.
 * @param[in]   pY   Pointer to input vector, 16 bit signed.
 ******************************************************************************/
void vec_mul_long_s16(int32_t *pZ, int len, const int16_t *pX,
                      const int16_t *pY)
{
    int n;

    for (n = 0; n < len; n++) {
        pZ[n] = (int32_t)pX[n] * pY[n];
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX          (12)
#define CONST(X)       CIMLIB_CONST_S16(X, RADIX)
#define CONST_LONG(X)  CIMLIB_CONST_S32(X, RADIX * 2)


/*******************************************************************************
 * This function tests 'vec_mul_long_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mul_long_s16(void)
{
    int32_t z[4];
    static int16_t x[4] = {
        CONST(7.9), CONST(4.0), CONST(2.0), CONST(1.0)
    };
    static int16_t y[4] = {
        CONST(2.2), CONST(3.3), CONST(1.1), CONST(0.2)
    };
    static int32_t res[4] = {
        CONST_LONG(1.7379399419E+01),
        CONST_LONG(1.3200195312E+01),
        CONST_LONG(2.2001953125E+00),
        CONST_LONG(1.9995117188E-01)
    };
    bool flOk = true;

    /* Call 'vec_mul_long_s16' function */
    vec_mul_long_s16(z, 4, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
