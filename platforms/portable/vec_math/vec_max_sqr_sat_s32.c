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
 * This function searches maximum square and it index of vector, 32 bit signed,
 * result is with saturation control.
 *
 * @param[out]  pIdxMax  Index of maximum square.
 * @param[in]   pX       Pointer to input vector, 32 bit signed.
 * @param[in]   len      Vector length.
 * @param[in]   radix    Radix.
 *
 * @return  Maximum energy, 32 bit unsigned.
 ******************************************************************************/
uint32_t vec_max_sqr_sat_s32(int *pIdxMax, const int32_t *pX, int len,
                             int radix)
{
    int n, idxMax;
    uint32_t maxSqr;
    uint64_t maxSqrLong, tmp;

    /* Search maximum energy */
    maxSqrLong = (uint64_t)pX[0] * pX[0];
    idxMax = 0;

    for (n = 1; n < len; n++) {
        tmp = (uint64_t)pX[n] * pX[n];

        if (tmp > maxSqrLong) {
            idxMax = n;
            maxSqrLong = tmp;
        }
    }

    maxSqrLong >>= radix;
    CIMLIB_SAT_UINT(maxSqrLong, UINT32_MAX, maxSqrLong);
    maxSqr = (uint32_t)maxSqrLong;

    /* Return results */
    *pIdxMax = idxMax;
    return maxSqr;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_max_sqr_sat_s32' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_max_sqr_sat_s32(void)
{
    int idxMax;
    uint32_t maxEng;
    static int32_t x[4] = {
        INT32_MAX, -INT32_MAX / 8, INT32_MIN, 1234567
    };
    static uint32_t maxRes = UINT32_MAX;
    static int idxRes = 2;
    bool flOk = true;

    /* Call 'vec_max_sqr_sat_s32' function */
    maxEng = vec_max_sqr_sat_s32(&idxMax, x, 4, 29);

    /* Check the correctness of the results */
    if ((maxEng != maxRes) || (idxMax != idxRes)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
