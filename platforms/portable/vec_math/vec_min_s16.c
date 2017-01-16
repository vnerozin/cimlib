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
 * This function searches minimum and it index of input vector, 16 bit signed.
 *
 * @param[out]  pIdxMax  Pointer to output minimum index.
 * @param[in]   pX       Pointer to input vector, 16 bit signed.
 * @param[in]   len      Vector length.
 *
 * @return               Minimum, 16 bit signed.
 ******************************************************************************/
int16_t vec_min_s16(int *pIdxMin, const int16_t *pX, int len)
{
    int i, idxMin;
    int16_t minX;

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

/* Simplify macroses for fixed radix */
#define RADIX     (12)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)


/*******************************************************************************
 * This function tests 'vec_min_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_min_s16(void)
{
    int idxMax;
    int16_t maxX;
    int16_t in[4] = {
        CONST(2.1), CONST(0.1), CONST(3.14), CONST(-5.6)
    };
    int16_t maxRes = CONST(-5.6);
    int idxRes = 3;
    bool flOk = true;

    /* Call 'vec_min_s16' function */
    maxX = vec_min_s16(&idxMax, in, 4);

    /* Check the correctness of the results */
    if ((maxX != maxRes) || (idxMax != idxRes)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
