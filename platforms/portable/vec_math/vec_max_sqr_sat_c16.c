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
 * This function searches maximum square and it index of vector, 16 bit complex,
 * result is with saturation control.
 *
 * @param[out]  pIdxMax  Index of maximum square.
 * @param[in]   pX       Pointer to input vector, 16 bit complex.
 * @param[in]   len      Vector length.
 * @param[in]   radix    Radix.
 *
 * @return               Maximum energy, 16 bit unsigned.
 ******************************************************************************/
uint16_t vec_max_sqr_sat_c16(int *pIdxMax, const cint16_t *pX, int len,
                             int radix)
{
    int n, idxMax;
    uint16_t maxSqr;
    uint32_t maxSqrLong, tmp;

    /* Search maximum energy */
    maxSqrLong = (uint32_t)pX[0].re * pX[0].re;
    maxSqrLong += (uint32_t)pX[0].im * pX[0].im;
    idxMax = 0;

    for (n = 1; n < len; n++) {
        tmp = (uint32_t)pX[n].re * pX[n].re;
        tmp += (uint32_t)pX[n].im * pX[n].im;

        if (tmp > maxSqrLong) {
            idxMax = n;
            maxSqrLong = tmp;
        }
    }

    maxSqrLong >>= radix;
    CIMLIB_SAT_UINT(maxSqrLong, UINT16_MAX, maxSqrLong);
    maxSqr = (uint16_t)maxSqrLong;

    /* Return results */
    *pIdxMax = idxMax;
    return maxSqr;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_max_sqr_sat_c16' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_max_sqr_sat_c16(void)
{
    int idxMax;
    uint16_t maxEng;
    static cint16_t x[4] = {
        {32767, 32767}, {4095, -4095}, {32767, -32768}, {1234, -4321}
    };
    static uint16_t maxRes = UINT16_MAX;
    static int idxRes = 2;
    bool flOk = true;

    /* Call 'vec_max_sqr_sat_c16' function */
    maxEng = vec_max_sqr_sat_c16(&idxMax, x, 4, 14);

    /* Check the correctness of the results */
    if ((maxEng != maxRes) || (idxMax != idxRes)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
