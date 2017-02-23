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
 * This function searches minimum square and it index of vector, 32 bit signed.
 *
 * @param[out]  pIdxMin  Index of minimum square.
 * @param[in]   pX       Pointer to input vector, 32 bit signed.
 * @param[in]   len      Vector length.
 * @param[in]   radix    Radix.
 *
 * @return               Minimum energy, 32 bit unsigned.
 ******************************************************************************/
uint32_t vec_min_sqr_s32(int *pIdxMin, const int32_t *pX, int len, int radix)
{
    int n, idxMin;
    uint32_t minSqr;
    uint64_t minSqrLong, tmp;

    /* Search minimum energy */
    minSqrLong = (uint64_t)pX[0] * pX[0];
    idxMin = 0;

    for (n = 1; n < len; n++) {
        tmp = (uint64_t)pX[n] * pX[n];

        if (tmp < minSqrLong) {
            idxMin = n;
            minSqrLong = tmp;
        }
    }

    minSqr = (uint32_t)(minSqrLong >> radix);

    /* Return results */
    *pIdxMin = idxMin;
    return minSqr;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX       (20)
#define CONST(X)    CIMLIB_CONST_S32(X, RADIX)
#define CONST_U(X)  CIMLIB_CONST_U32(X, RADIX)


/*******************************************************************************
 * This function tests 'vec_min_sqr_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_min_sqr_s32(void)
{
    int idxMin;
    uint32_t minSqr;
    static int32_t x[4] = {
        CONST(3.0), CONST(4.0), CONST(1.0), CONST(2.0)
    };
    static uint32_t maxRes = CONST_U(1.0);
    static int idxRes = 2;
    bool flOk = true;

    /* Call 'vec_min_sqr_s32' function */
    minSqr = vec_min_sqr_s32(&idxMin, x, 4, RADIX);

    /* Check the correctness of the results */
    if ((minSqr != maxRes) || (idxMin != idxRes)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
