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
 * This function searches median element of vector, 16 bit signed.
 *
 * @param[in,out]  pX   Pointer to input-output vector, 16 bit signed.
 * @param[in]      len  Vector length.
 *
 * @return              Median value of vector.
 ******************************************************************************/
int16_t mem_median_s16(int16_t *pX, int len)
{
    int k;
    int16_t med;

    /* For median use 'mem_kth_min_s16' with index of center element */
    k = (len & 1) ? (len / 2) : ((len / 2) - 1);
    med = mem_kth_min_s16(pX, len, k);

    return med;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'mem_median_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_mem_median_s16(void)
{
    int16_t med4, med5;
    int16_t data[5] = {INT16_MAX, 1616, -1616, INT16_MIN, 16};
    static int16_t res_med4 = -1616;
    static int16_t res_med5 = 16;
    bool flOk = true;

    /* Call 'mem_median_s16' function */
    med4 = mem_median_s16(data, 4);
    med5 = mem_median_s16(data, 5);

    /* Check the correctness of the result */
    if ((med4 != res_med4) || (med5 != res_med5)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
