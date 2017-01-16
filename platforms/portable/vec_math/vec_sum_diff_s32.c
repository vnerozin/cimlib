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
 * This function calculates sum of differences (subtractions) of vectors,
 * 32 bit signed.
 *
 * @param[in]  pX   Pointer to input vector, 32 bit signed.
 * @param[in]  pY   Pointer to input vector, 32 bit signed.
 * @param[in]  len  Vector length.
 *
 * @return          Sum of differences (subtractions), 64 bit signed.
 ******************************************************************************/
int64_t vec_sum_diff_s32(const int32_t *pX, const int32_t *pY, int len)
{
    int n;
    int64_t acc = 0;

    for (n = 0; n < len; n++) {
        acc += pX[n] - pY[n];
    }

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sum_diff_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_diff_s32(void)
{
    int64_t z;
    static int32_t x[4] = { INT32_MAX, INT32_MIN, INT32_MAX, INT32_MIN };
    static int32_t y[4] = { INT32_MAX, INT32_MIN, INT32_MAX, INT32_MIN };
    bool flOk = true;

    /* Call 'vec_sum_diff_s32' function */
    z = vec_sum_diff_s32(x, y, 4);

    /* Check the correctness of the results */
    if (z != 0) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
