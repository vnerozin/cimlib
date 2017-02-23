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
 * This function searches minimum square and it index of vector, 16 bit signed,
 * result is with saturation control.
 *
 * @param[out]  pIdxMin  Index of minimum square.
 * @param[in]   pX       Pointer to input vector, 16 bit signed.
 * @param[in]   len      Vector length.
 * @param[in]   radix    Radix.
 *
 * @return               Minimum energy, 16 bit unsigned.
 ******************************************************************************/
uint16_t vec_min_sqr_sat_s16(int *pIdxMin, const int16_t *pX, int len,
                             int radix)
{
    int n, idxMin;
    uint16_t minSqr;
    uint32_t minSqrLong, tmp;

    /* Search minimum energy */
    minSqrLong = (uint32_t)pX[0] * pX[0];
    idxMin = 0;

    for (n = 1; n < len; n++) {
        tmp = (uint32_t)pX[n] * pX[n];

        if (tmp < minSqrLong) {
            idxMin = n;
            minSqrLong = tmp;
        }
    }

    minSqrLong >>= radix;
    CIMLIB_SAT_UINT(minSqrLong, UINT32_MAX, minSqrLong);
    minSqr = (uint16_t)minSqrLong;

    /* Return results */
    *pIdxMin = idxMin;
    return minSqr;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX       (11)
#define CONST(X)    CIMLIB_CONST_S16(X, RADIX)
#define CONST_U(X)  CIMLIB_CONST_U16(X, RADIX)


/*******************************************************************************
 * This function tests 'vec_min_sqr_sat_s16' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_min_sqr_sat_s16(void)
{
    int idxMin;
    uint16_t minSqr;
    static int16_t x[4] = {
        CONST(3.0), CONST(4.0), CONST(1.0), CONST(2.0)
    };
    static uint16_t maxRes = CONST_U(1.0);
    static int idxRes = 2;
    bool flOk = true;

    /* Call 'vec_min_sqr_sat_s16' function */
    minSqr = vec_min_sqr_sat_s16(&idxMin, x, 4, RADIX);

    /* Check the correctness of the results */
    if ((minSqr != maxRes) || (idxMin != idxRes)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
