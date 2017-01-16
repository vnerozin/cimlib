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
 * This function searches minimum and it index of input vector, 32 bit signed.
 *
 * @param[out]  pIdxMax  Pointer to output minimum index.
 * @param[in]   pX       Pointer to input vector, 32 bit signed.
 * @param[in]   len      Vector length.
 *
 * @return               Minimum, 32 bit signed.
 ******************************************************************************/
int32_t vec_min_s32(int *pIdxMin, const int32_t *pX, int len)
{
    int i, idxMin;
    int32_t minX;

    /* Search minimum */
    idxMin = 0;
    minX = pX[0];

    for (i = 1; i < len; i++) {
        if (pX[i] < minX) {
            idxMin = i;
            minX = pX[i];
        }
    }

    /* Return results */
    *pIdxMin = idxMin;
    return minX;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_min_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_min_s32(void)
{
    int idxMax;
    int32_t maxX;
    int32_t in[4] = {-11, 0, INT32_MIN, 1 << 24};
    int32_t maxRes = INT32_MIN;
    int idxRes = 2;
    bool flOk = true;

    /* Call 'vec_min_s32' function */
    maxX = vec_min_s32(&idxMax, in, 4);

    /* Check the correctness of the results */
    if ((maxX != maxRes) || (idxMax != idxRes)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
