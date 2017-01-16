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
 * This function searches median element of vector, 32 bit signed.
 *
 * @param[in,out]  pX   Pointer to input-output vector, 32 bit signed.
 * @param[in]      len  Vector length.
 *
 * @return              Median value of vector.
 ******************************************************************************/
int32_t mem_median_s32(int32_t *pX, int len)
{
    int k;
    int32_t med;

    /* For median use 'mem_kth_min_s32' with index of center element */
    k = (len & 1) ? (len / 2) : ((len / 2) - 1);
    med = mem_kth_min_s32(pX, len, k);

    return med;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'mem_median_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_mem_median_s32(void)
{
    int32_t med4, med5;
    int32_t data[5] = {INT32_MAX, 32323232, -32323232, INT32_MIN, 32};
    static int32_t res_med4 = -32323232;
    static int32_t res_med5 = 32;
    bool flOk = true;

    /* Call 'mem_median_s32' function */
    med4 = mem_median_s32(data, 4);
    med5 = mem_median_s32(data, 5);

    /* Check the correctness of the result */
    if ((med4 != res_med4) || (med5 != res_med5)) {
        flOk = false;
    }

    return flOk;
}


#endif /* (CIMLIB_BUILD_TEST == 1) */
