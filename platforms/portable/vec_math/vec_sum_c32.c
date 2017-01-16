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
 * This function calculates sum of vector, 32 bit complex.
 *
 * @param[in]  pX   Pointer to input vector, 32 bit complex.
 * @param[in]  len  Vector length.
 *
 * @return          Sum of vector, 64 bit complex.
 ******************************************************************************/
cint64_t vec_sum_c32(const cint32_t *pX, int len)
{
    int n;
    cint64_t acc;
    int64_t accRe = 0;
    int64_t accIm = 0;

    for (n = 0; n < len; n++) {
        accRe += (int64_t)pX[n].re;
        accIm += (int64_t)pX[n].im;
    }

    acc.re = accRe;
    acc.im = accIm;

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX  (24)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_sum_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_c32(void)
{
    cint64_t y;
    static cint32_t in[4] = {
        CONST_CPLX(2.1, 0.05),
        CONST_CPLX(-2.1, -0.05),
        CONST_CPLX(-5.6, 3.0),
        CONST_CPLX(5.6, -3.0)
    };
    bool flOk = true;

    /* Call 'vec_sum_c32' function */
    y = vec_sum_c32(in, 4);

    /* Check the correctness of the results */
    if ((y.re != 0) || (y.im != 0)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
