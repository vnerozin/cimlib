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
 * This function searches maximum square and it index of vector, 32 bit complex.
 *
 * @param[out]  pIdxMax  Index of maximum square.
 * @param[in]   pX       Pointer to input vector, 32 bit complex.
 * @param[in]   len      Vector length.
 * @param[in]   radix    Radix.
 *
 * @return               Maximum energy, 32 bit unsigned.
 ******************************************************************************/
uint32_t vec_max_sqr_c32(int *pIdxMax, const cint32_t *pX, int len, int radix)
{
    int n, idxMax;
    uint32_t maxSqr;
    uint64_t maxSqrLong, tmp;

    /* Search maximum energy */
    maxSqrLong = (uint64_t)pX[0].re * pX[0].re;
    maxSqrLong += (uint64_t)pX[0].im * pX[0].im;
    idxMax = 0;

    for (n = 1; n < len; n++) {
        tmp = (uint64_t)pX[n].re * pX[n].re;
        tmp += (uint64_t)pX[n].im * pX[n].im;

        if (tmp > maxSqrLong) {
            idxMax = n;
            maxSqrLong = tmp;
        }
    }

    maxSqr = (uint32_t)(maxSqrLong >> radix);

    /* Return results */
    *pIdxMax = idxMax;
    return maxSqr;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (20)
#define CONST(X)            CIMLIB_CONST_U32(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_max_sqr_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_max_sqr_c32(void)
{
    int idxMax;
    uint32_t maxEng;
    static cint32_t x[4] = {
        CONST_CPLX( 1.9996948242E-01,  9.9996948242E-01),
        CONST_CPLX( 1.2496948242E-01, -1.2496948242E-01),
        CONST_CPLX( 9.9996948242E-01, -1.0000000000E+00),
        CONST_CPLX( 3.7658691406E-02, -1.3186645508E-01)
    };
    static uint32_t maxRes = CONST(1.9999389648E+00);
    static int idxRes = 2;
    bool flOk = true;

    /* Call 'vec_max_sqr_c32' function */
    maxEng = vec_max_sqr_c32(&idxMax, x, 4, RADIX);

    /* Check the correctness of the results */
    if ((maxEng != maxRes) || (idxMax != idxRes)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
