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
 * This function searches minimum square and it index of vector, 16 bit complex,
 * result is with saturation control.
 *
 * @param[out]  pIdxMin  Index of minimum square.
 * @param[in]   pX       Pointer to input vector, 16 bit complex.
 * @param[in]   len      Vector length.
 * @param[in]   radix    Radix.
 *
 * @return               Minimum energy, 16 bit unsigned.
 ******************************************************************************/
uint16_t vec_min_sqr_sat_c16(int *pIdxMin, const cint16_t *pX, int len,
                             int radix)
{
    int n, idxMin;
    uint16_t minSqr;
    uint32_t minSqrLong, tmp;

    /* Search minimum energy */
    minSqrLong = (uint32_t)pX[0].re * pX[0].re;
    minSqrLong += (uint32_t)pX[0].im * pX[0].im;
    idxMin = 0;

    for (n = 1; n < len; n++) {
        tmp = (uint32_t)pX[n].re * pX[n].re;
        tmp += (uint32_t)pX[n].im * pX[n].im;

        if (tmp < minSqrLong) {
            idxMin = n;
            minSqrLong = tmp;
        }
    }

    minSqrLong >>= radix;
    CIMLIB_SAT_UINT(minSqrLong, UINT16_MAX, minSqrLong);
    minSqr = (uint16_t)minSqrLong;

    /* Return results */
    *pIdxMin = idxMin;
    return minSqr;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (14)
#define CONST(X)            CIMLIB_CONST_U16(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_min_sqr_sat_c16' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_min_sqr_sat_c16(void)
{
    int idxMin;
    uint16_t minSqr;
    static cint16_t x[4] = {
        CONST_CPLX(0.1,  1.9),
        CONST_CPLX(0.12, -0.12),
        CONST_CPLX(-1.9,  1.5),
        CONST_CPLX(0.03, -0.06)
    };
    static uint16_t minRes = CONST(4.4555664062E-03);
    static int idxRes = 3;
    bool flOk = true;

    /* Call 'vec_min_sqr_sat_c16' function */
    minSqr = vec_min_sqr_sat_c16(&idxMin, x, 4, RADIX);

    /* Check the correctness of the results */
    if ((minSqr != minRes) || (idxMin != idxRes)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
