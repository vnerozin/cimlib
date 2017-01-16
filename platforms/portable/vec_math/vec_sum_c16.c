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
 * This function calculates sum of vector, 16 bit complex.
 *
 * @param[in]  pX   Pointer to input vector, 16 bit complex.
 * @param[in]  len  Vector length.
 *
 * @return          Sum of vector, 32 bit signed.
 ******************************************************************************/
cint32_t vec_sum_c16(const cint16_t *pX, int len)
{
    int n;
    cint32_t acc;
    int32_t accRe = 0;
    int32_t accIm = 0;

    for (n = 0; n < len; n++) {
        accRe += (int32_t)pX[n].re;
        accIm += (int32_t)pX[n].im;
    }

    acc.re = accRe;
    acc.im = accIm;

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX  (12)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_sum_c16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_c16(void)
{
    cint32_t y;
    static cint16_t in[4] = {
        CONST_CPLX(2.1, 0.05),
        CONST_CPLX(-2.1, -0.05),
        CONST_CPLX(-5.6, 3.0),
        CONST_CPLX(5.6, -3.0)
    };
    bool flOk = true;

    /* Call 'vec_sum_c16' function */
    y = vec_sum_c16(in, 4);

    /* Check the correctness of the results */
    if ((y.re != 0) || (y.im != 0)) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
