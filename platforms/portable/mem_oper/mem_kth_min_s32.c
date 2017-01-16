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
 * This function searches k-th minimum element of vector, 32 bit signed.
 *
 * Reference: N. Wirth's book.
 *   http://ndevilla.free.fr/median/median/src/wirth.c
 *
 * @param[in,out]  pX   Pointer to input-output vector, 32 bit signed.
 * @param[in]      len  Vector length.
 * @param[in]      k    Minimum index, zero-based.
 *
 * @return              k-th minimum.
 ******************************************************************************/
int32_t mem_kth_min_s32(int32_t *pX, int len, int k)
{
    int i, j, l, m;
    int32_t x, t;

    l = 0;
    m = len - 1;

    while (l < m) {
        x = pX[k];
        i = l;
        j = m;

        do {
            while (pX[i] < x) {
                i++;
            }

            while (x < pX[j]) {
                j-- ;
            }

            if (i <= j) {
                t = pX[i];
                pX[i] = pX[j];
                pX[j] = t;
                i++;
                j--;
            }
        } while (i <= j);

        if (j < k) {
            l = i;
        }

        if (k < i) {
            m = j;
        }
    }

    return pX[k];
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'mem_kth_min_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_mem_kth_min_s32(void)
{
    int32_t k2, k3;
    int32_t data[4] = {INT32_MAX, 32323232, -32323232, INT32_MIN};
    static int32_t res_k2 = 32323232;
    static int32_t res_k3 = INT32_MAX;
    bool flOk = true;

    /* Call 'mem_kth_min_s32' function */
    k2 = mem_kth_min_s32(data, 4, 2);
    k3 = mem_kth_min_s32(data, 4, 3);

    /* Check the correctness of the result */
    if ((k2 != res_k2) || (k3 != res_k3)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
