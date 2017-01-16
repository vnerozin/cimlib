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
 * This function calculates by element multiply of input vectors, 32 bit signed,
 * result is with saturation control and accumulated in output vector.
 *
 * @param[in,out]  pZ     Pointer to input-output vector, 32 bit signed.
 * @param[in]      len    Vector length.
 * @param[in]      radix  Radix.
 * @param[in]      pX     Pointer to input vector, 32 bit signed.
 * @param[in]      pY     Pointer to input vector, 32 bit signed.
 ******************************************************************************/
void vec_mac_sat_s32(int32_t *pZ, int len, int radix, const int32_t *pX,
                     const int32_t *pY)
{
    int n;
    int64_t tmp;

    for (n = 0; n < len; n++) {
        tmp = ((int64_t)pX[n] * pY[n]) >> radix;
        CIMLIB_SAT_INT(tmp, INT32_MAX, tmp);
        pZ[n] += (int32_t)tmp;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (20)
#define CONST(X)  CIMLIB_CONST_S32(X, RADIX)


/*******************************************************************************
 * This function tests 'vec_mac_sat_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_vec_mac_sat_s32(void)
{
    static int32_t x[4] = {
        CONST(63.9), CONST(4.0), CONST(2.0), CONST(63.9)
    };
    static int32_t y[4] = {
        CONST(63.9), CONST(3.3), CONST(1.1), CONST(-63.9)
    };
    int32_t z[4] = {
        INT32_MIN + 1,
        CONST(-1.3200000763E+01),
        CONST(-2.2000007629E+00),
        INT32_MAX
    };
    static int32_t res[4] = {
        CONST(0.0), CONST(0.0), CONST(0.0), -1
    };
    bool flOk = true;

    /* Call 'vec_mac_sat_s32' function */
    vec_mac_sat_s32(z, 4, RADIX, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
