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
 * This function searches maximum square and it index of vector, 16 bit signed.
 *
 * @param[out]  pIdxMax  Index of maximum square.
 * @param[in]   pX       Pointer to input vector, 16 bit signed.
 * @param[in]   len      Vector length.
 * @param[in]   radix    Radix.
 *
 * @return               Maximum energy, 16 bit unsigned.
 ******************************************************************************/
uint16_t vec_max_sqr_s16(int *pIdxMax, const int16_t *pX, int len, int radix)
{
    int n, idxMax;
    uint16_t maxSqr;
    uint32_t maxSqrLong, tmp;

    /* Search maximum energy */
    maxSqrLong = (uint32_t)pX[0] * pX[0];
    idxMax = 0;

    for (n = 1; n < len; n++) {
        tmp = (uint32_t)pX[n] * pX[n];

        if (tmp > maxSqrLong) {
            idxMax = n;
            maxSqrLong = tmp;
        }
    }

    maxSqr = (uint16_t)(maxSqrLong >> radix);

    /* Return results */
    *pIdxMax = idxMax;
    return maxSqr;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_max_sqr_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_max_sqr_s16(void)
{
    int idxMax;
    uint16_t maxEng;
    static int16_t x[4] = {INT16_MAX, -4095, INT16_MIN, 1234};
    static uint16_t maxRes = INT16_MAX + 1;
    static int idxRes = 2;
    bool flOk = true;

    /* Call 'vec_max_sqr_s16' function */
    maxEng = vec_max_sqr_s16(&idxMax, x, 4, 15);

    /* Check the correctness of the results */
    if ((maxEng != maxRes) || (idxMax != idxRes)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
