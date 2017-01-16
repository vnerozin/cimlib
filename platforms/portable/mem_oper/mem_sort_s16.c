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
 * This function sorts elements of vector, 16 bit signed, increscent order.
 *
 * @param[in,out]  pX   Pointer to input-output vector, 16 bit signed.
 * @param[in]      len  Vector length.
 *
 * @return              -
 ******************************************************************************/
void mem_sort_s16(int16_t *pX, int len)
{
    int n, m;
    int16_t tmp;

    /* TODO Update algorithm */
    for (n = 0; n < (len - 1); n++) {
        for (m = 0; m < (len - (n + 1)); m++) {
            if (pX[m] > pX[m + 1]) {
                tmp = pX[m];
                pX[m] = pX[m + 1];
                pX[m + 1] = tmp;
            }
        }
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'mem_sort_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_mem_sort_s16(void)
{
    int16_t data[4] = {INT16_MAX, 1616, -1616, INT16_MIN};
    static int16_t res[4] = {INT16_MIN, -1616, 1616, INT16_MAX};
    bool flOk = true;

    /* Call 'mem_sort_s16' function */
    mem_sort_s16(data, 4);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(data, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
