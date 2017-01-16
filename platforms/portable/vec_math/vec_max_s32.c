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
 * This function searches maximum and it index of input vector, 32 bit signed.
 *
 * @param[out]  pIdxMax  Pointer to output maximum index.
 * @param[in]   pX       Pointer to input vector, 32 bit signed.
 * @param[in]   len      Vector length.
 *
 * @return               Maximum, 32 bit signed.
 ******************************************************************************/
int32_t vec_max_s32(int *pIdxMax, const int32_t *pX, int len)
{
    int i, idxMax;
    int32_t maxX;

    /* Search maximum */
    idxMax = 0;
    maxX = pX[0];

    for (i = 1; i < len; i++) {
        if (pX[i] > maxX) {
            idxMax = i;
            maxX = pX[i];
        }
    }

    /* Return results */
    *pIdxMax = idxMax;
    return maxX;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (24)
#define CONST(X)  CIMLIB_CONST_S32(X, RADIX)


/*******************************************************************************
 * This function tests 'vec_max_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_vec_max_s32(void)
{
    int idxMax;
    int32_t maxX;
    int32_t in[4] = {
        CONST(2.1), CONST(0.1), CONST(3.14), CONST(-5.6)
    };
    static int32_t maxRes = CONST(3.14);
    static int idxRes = 2;
    bool flOk = true;

    /* Call 'vec_max_s32' function */
    maxX = vec_max_s32(&idxMax, in, 4);

    /* Check the correctness of the results */
    if ((maxX != maxRes) || (idxMax != idxRes)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
