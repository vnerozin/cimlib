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
 * This function searches minimum square and it index of vector, 32 bit complex.
 *
 * @param[out]  pIdxMin  Index of minimum square.
 * @param[in]   pX       Pointer to input vector, 32 bit complex.
 * @param[in]   len      Vector length.
 * @param[in]   radix    Radix.
 *
 * @return               Minimum energy, 32 bit unsigned.
 ******************************************************************************/
uint32_t vec_min_sqr_c32(int *pIdxMin, const cint32_t *pX, int len, int radix)
{
    int n, idxMin;
    uint32_t minSqr;
    uint64_t minSqrLong, tmp;

    /* Search minimum energy */
    minSqrLong = (uint64_t)pX[0].re * pX[0].re;
    minSqrLong += (uint64_t)pX[0].im * pX[0].im;
    idxMin = 0;

    for (n = 1; n < len; n++) {
        tmp = (uint64_t)pX[n].re * pX[n].re;
        tmp += (uint64_t)pX[n].im * pX[n].im;

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
#define RADIX               (20)
#define CONST(X)            CIMLIB_CONST_U32(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_min_sqr_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_min_sqr_c32(void)
{
    int idxMin;
    uint32_t minEng;
    static cint32_t x[4] = {
        CONST_CPLX( 1.9996948242E-01,  9.9996948242E-01),
        CONST_CPLX( 1.2496948242E-01, -1.2496948242E-01),
        CONST_CPLX( 3.7658691406E-02, -1.3186645508E-01),
        CONST_CPLX( 9.9996948242E-01, -1.0000000000E+00)
    };
    static uint32_t minRes = CONST(1.8806457520E-02);
    static int idxRes = 2;
    bool flOk = true;

    /* Call 'vec_min_sqr_c32' function */
    minEng = vec_min_sqr_c32(&idxMin, x, 4, RADIX);

    /* Check the correctness of the results */
    if ((minEng != minRes) || (idxMin != idxRes)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
