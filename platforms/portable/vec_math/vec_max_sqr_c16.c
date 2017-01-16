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
 * This function searches maximum square and it index of vector, 16 bit complex.
 *
 * @param[out]  pIdxMax  Index of maximum square.
 * @param[in]   pX       Pointer to input vector, 16 bit complex.
 * @param[in]   len      Vector length.
 * @param[in]   radix    Radix.
 *
 * @return               Maximum energy, 16 bit unsigned.
 ******************************************************************************/
uint16_t vec_max_sqr_c16(int *pIdxMax, const cint16_t *pX, int len, int radix)
{
    int n, idxMax;
    uint16_t maxSqr;
    uint32_t maxSqrLong, tmp;

    /* Search maximum energy */
    maxSqrLong = (uint32_t)pX[0].re * pX[0].re;
    maxSqrLong += (uint32_t)pX[0].im * pX[0].im;
    idxMax = 0;

    for (n = 1; n < len; n++) {
        tmp = (uint32_t)pX[n].re * pX[n].re;
        tmp += (uint32_t)pX[n].im * pX[n].im;

        if (tmp > maxSqrLong) {
            idxMax = n;
            maxSqrLong = tmp;
        }
    }

    maxSqr = (uint16_t)(maxSqrLong >> radix);

    /* Return results */
    *pIdxMax = idxMax;
    return maxSqr;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (10)
#define CONST(X)            CIMLIB_CONST_U16(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_max_sqr_c16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_max_sqr_c16(void)
{
    int idxMax;
    uint16_t maxEng;
    static cint16_t x[4] = {
        CONST_CPLX( 1.9996948242E-01,  9.9996948242E-01),
        CONST_CPLX( 1.2496948242E-01, -1.2496948242E-01),
        CONST_CPLX( 9.9996948242E-01, -1.0000000000E+00),
        CONST_CPLX( 3.7658691406E-02, -1.3186645508E-01)
    };
    static uint16_t maxRes = CONST(1.9999389648E+00);
    static int idxRes = 2;
    bool flOk = true;

    /* Call 'vec_max_sqr_c16' function */
    maxEng = vec_max_sqr_c16(&idxMax, x, 4, RADIX);

    /* Check the correctness of the results */
    if ((maxEng != maxRes) || (idxMax != idxRes)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
