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
 * This function calculates by element complex conjugate multiply of input
 * vectors, 32 bit complex, result with extended precision and accumulated to
 * output vector.
 *
 * @param[out]  pZ   Pointer to output vector, 32 bit complex.
 * @param[in]   len  Vector length.
 * @param[in]   pX   Pointer to input vector, 32 bit complex.
 * @param[in]   pY   Pointer to input vector, 32 bit complex.
 ******************************************************************************/
void vec_mac_cj_long_c32(cint64_t *pZ, int len, const cint32_t *pX,
                         const cint32_t *pY)
{
    int n;

    for (n = 0; n < len; n++) {
        pZ[n].re += (int64_t)pX[n].re * pY[n].re + (int64_t)pX[n].im * pY[n].im;
        pZ[n].im += (int64_t)pX[n].im * pY[n].re - (int64_t)pX[n].re * pY[n].im;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX  (28)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)
#define CONST_CPLX_LONG(RE, IM)  CIMLIB_CONST_C64(RE, IM, RADIX * 2)


/*******************************************************************************
 * This function tests 'vec_mac_cj_long_c32' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mac_cj_long_c32(void)
{
    static cint32_t x[4] = {
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(0.75, 0.33),
    };
    static cint32_t y[4] = {
        CONST_CPLX(0.33, 0.75),
        CONST_CPLX(0.33, -0.75),
        CONST_CPLX(-0.33, 0.75),
        CONST_CPLX(-0.33, -0.75),
    };
    cint64_t z[4] = {
        CONST_CPLX_LONG(-4.9499999731779098510E-01,  4.5360000118017196335E-01),
        CONST_CPLX_LONG( 0.0000000000000000000E+00, -6.7139999881982803664E-01),
        CONST_CPLX_LONG( 0.0000000000000000000E+00,  6.7139999881982803664E-01),
        CONST_CPLX_LONG( 4.9499999731779098510E-01, -4.5360000118017196335E-01)
    };
    static cint64_t res[4] = {
        CONST_CPLX(0.0, 0.0),
        CONST_CPLX(0.0, 0.0),
        CONST_CPLX(0.0, 0.0),
        CONST_CPLX(0.0, 0.0),
    };
    bool flOk = true;

    /* Call 'vec_mac_cj_long_c32' function */
    vec_mac_cj_long_c32(z, 4, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
