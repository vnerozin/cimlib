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
 * This function calculates sum of differences (subtractions) of vectors,
 * 16 bit signed.
 *
 * @param[in]  pX   Pointer to input vector, 16 bit signed.
 * @param[in]  pY   Pointer to input vector, 16 bit signed.
 * @param[in]  len  Vector length.
 *
 * @return          Sum of differences (subtractions), 32 bit signed.
 ******************************************************************************/
int32_t vec_sum_diff_s16(const int16_t *pX, const int16_t *pY, int len)
{
    int n;
    int32_t acc = 0;

    for (n = 0; n < len; n++) {
        acc += pX[n] - pY[n];
    }

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sum_diff_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_diff_s16(void)
{
    int32_t z;
    static int16_t x[4] = { 32767, -32767, -32767, 32767 };
    static int16_t y[4] = { 32767, -32767, -32767, 32767 };
    bool flOk = true;

    /* Call 'vec_sum_diff_s16' function */
    z = vec_sum_diff_s16(x, y, 4);

    /* Check the correctness of the results */
    if (z != 0) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
