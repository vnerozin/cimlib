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
 * This function calculates sum of squares of vector, 32 bit complex.
 *
 * @param[in]  pX     Pointer to input vector, 32 bit complex.
 * @param[in]  len    Vector length.
 * @param[in]  radix  Radix.
 *
 * @return            Sum of squares, 64 bit unsigned.
 ******************************************************************************/
uint64_t vec_sum_sqr_c32(const cint32_t *pX, int len, int radix)
{
    int n;
    uint64_t acc = 0;

    /* For correct rounding add half of radix */
    if (radix != 0) {
        acc = ((uint64_t)1 << (radix - 1));
    }

    for (n = 0; n < len; n++) {
        acc += (uint64_t)pX[n].re * pX[n].re;
        acc += (uint64_t)pX[n].im * pX[n].im;
    }

    /* Scale radix */
    acc >>= radix;

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (23)
#define CONST(X)            CIMLIB_CONST_U64(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_sum_sqr_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_sqr_c32(void)
{
    uint64_t y;
    static cint32_t x[4] = {
        CONST_CPLX( 9.9996948242E-01,  9.9996948242E-01),
        CONST_CPLX( 1.2496948242E-01, -1.2496948242E-01),
        CONST_CPLX( 9.9996948242E-01, -1.0000000000E+00),
        CONST_CPLX( 3.7658691406E-02, -1.3186645508E-01)
    };
    static uint64_t res = CONST(4.0498585701E+00);
    bool flOk = true;

    /* Call 'vec_sum_sqr_c32' function */
    y = vec_sum_sqr_c32(x, 4, RADIX);

    /* Check the correctness of the results */
    if (y != res) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
