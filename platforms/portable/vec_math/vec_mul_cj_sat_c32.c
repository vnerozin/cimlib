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
 * This function calculates by element complex conjugate multiply of input
 * vectors, 32 bit complex, result with saturation control.
 *
 * @param[out]  pZ     Pointer to output vector, 32 bit complex.
 * @param[in]   len    Vector length.
 * @param[in]   radix  Radix.
 * @param[in]   pX     Pointer to input vector, 32 bit complex.
 * @param[in]   pY     Pointer to input vector, 32 bit complex.
 ******************************************************************************/
void vec_mul_cj_sat_c32(cint32_t *pZ, int len, int radix, const cint32_t *pX,
                        const cint32_t *pY)
{
    int n;
    int64_t re, im;

    for (n = 0; n < len; n++) {
        re = (int64_t)pX[n].re * pY[n].re + (int64_t)pX[n].im * pY[n].im;
        im = (int64_t)pX[n].im * pY[n].re - (int64_t)pX[n].re * pY[n].im;
        re >>= radix;
        im >>= radix;
        CIMLIB_SAT_INT(re, INT32_MAX, re);
        CIMLIB_SAT_INT(im, INT32_MAX, im);
        pZ[n].re = (int32_t)re;
        pZ[n].im = (int32_t)im;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (30)
#define CONST(X)            CIMLIB_CONST_S32(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_mul_cj_sat_c32' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mul_cj_sat_c32(void)
{
    cint32_t z[4];
    static cint32_t x[4] = {
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(1.99, 0.33),
        CONST_CPLX(0.75, -1.99),
        CONST_CPLX(0.75, 0.33),
    };
    static cint32_t y[4] = {
        CONST_CPLX(0.33, 0.75),
        CONST_CPLX(1.99, -0.75),
        CONST_CPLX(-0.33, 1.99),
        CONST_CPLX(-0.33, -0.75),
    };
    static cint32_t res[4] = {
        CONST_CPLX( 4.9500000011E-01, -4.5360000059E-01),
        {INT32_MAX, INT32_MAX},
        {INT32_MIN, CONST(-8.3580000047E-01)},
        CONST_CPLX(-4.9500000011E-01,  4.5359999966E-01)
    };
    bool flOk = true;

    /* Call 'vec_mul_cj_sat_c32' function */
    vec_mul_cj_sat_c32(z, 4, RADIX, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
