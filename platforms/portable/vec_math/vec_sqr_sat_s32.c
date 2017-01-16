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
 * This function calculates square of each element of vector, 32 bit signed,
 * result with saturation control.
 *
 * @param[out]  pY     Pointer to output vector, 32 bit unsigned.
 * @param[in]   len    Vector length.
 * @param[in]   radix  Radix.
 * @param[in]   pX     Pointer to input vector, 32 bit signed.
 ******************************************************************************/
void vec_sqr_sat_s32(uint32_t *pY, int len, int radix, const int32_t *pX)
{
    int n;
    uint64_t tmp;

    for (n = 0; n < len; n++) {
        tmp = (uint64_t)pX[n] * pX[n];
        tmp >>= radix;
        CIMLIB_SAT_UINT(tmp, UINT32_MAX, tmp);
        pY[n] = (uint32_t)tmp;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX       (28)
#define CONST(X)    CIMLIB_CONST_S32(X, RADIX)
#define CONST_U(X)  CIMLIB_CONST_U32(X, RADIX)


/*******************************************************************************
 * This function tests 'vec_sqr_sat_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sqr_sat_s32(void)
{
    uint32_t y[4];
    static int32_t x[4] = {
        CONST(3.0), CONST(6.0), CONST(2.0), CONST(1.0)
    };
    static uint32_t res[4] = {
        CONST_U(9.0), UINT32_MAX, CONST_U(4.0), CONST_U(1.0)
    };
    bool flOk = true;

    /* Call 'vec_sqr_sat_s32' function */
    vec_sqr_sat_s32(y, 4, RADIX, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
