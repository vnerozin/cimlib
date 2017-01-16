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
 * This function calculates square of each element of vector, 32 bit complex,
 * result is accumulated with extended precision.
 *
 * @param[in,out]  pYAcc  Pointer to input-output accumulation vector,
 *                        32 bit unsigned.
 * @param[in]      len    Vector length.
 * @param[in]      pX     Pointer to input vector, 32 bit complex.
 ******************************************************************************/
void vec_sqra_long_c32(uint64_t *pYAcc, int len, const cint32_t *pX)
{
    int n;
    uint64_t tmp;

    for (n = 0; n < len; n++) {
        tmp = (uint64_t)pX[n].re * pX[n].re;
        tmp += (uint64_t)pX[n].im * pX[n].im;
        pYAcc[n] += tmp;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sqra_long_c32' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sqra_long_c32(void)
{
    static cint32_t x[4] = {
        {327670, 327671}, {40950000, -40951111},
        {32767111, -3276811}, {1234567, -7654321}
    };
    uint64_t y[4] = {0, 0, 0, 0};
    static uint64_t res[4] = {
        214735913141, 3353895992134321, 1084421053616042, 60112785648530
    };
    bool flOk = true;

    /* Call 'vec_sqra_long_c32' function */
    vec_sqra_long_c32(y, 4, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
