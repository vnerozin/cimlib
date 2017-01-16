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
 * This function searches k-th minimum element of vector, 16 bit signed.
 *
 * Reference: N. Wirth's book.
 *   http://ndevilla.free.fr/median/median/src/wirth.c
 *
 * @param[in,out]  pX   Pointer to input-output vector, 16 bit signed.
 * @param[in]      len  Vector length.
 * @param[in]      k    Minimum index, zero-based.
 *
 * @return              k-th minimum.
 ******************************************************************************/
int16_t mem_kth_min_s16(int16_t *pX, int len, int k)
{
    int i, j, l, m;
    int16_t x, t;

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
 * This function tests 'mem_kth_min_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_mem_kth_min_s16(void)
{
    int16_t k2, k3;
    int16_t data[4] = {INT16_MAX, 1616, -1616, INT16_MIN};
    static int16_t res_k2 = 1616;
    static int16_t res_k3 = INT16_MAX;
    bool flOk = true;

    /* Call 'mem_kth_min_s16' function */
    k2 = mem_kth_min_s16(data, 4, 2);
    k3 = mem_kth_min_s16(data, 4, 3);

    /* Check the correctness of the result */
    if ((k2 != res_k2) || (k3 != res_k3)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
