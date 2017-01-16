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
 * This function calculates by element complex multiply of input vectors,
 * 32 bit complex, result is with saturation control and accumulated in output
 * vector.
 *
 * @param[in,out]  pZ     Pointer to input-output vector, 32 bit complex.
 * @param[in]      len    Vector length.
 * @param[in]      radix  Radix.
 * @param[in]      pX     Pointer to input vector, 32 bit complex.
 * @param[in]      pY     Pointer to input vector, 32 bit complex.
 ******************************************************************************/
void vec_mac_sat_c32(cint32_t *pZ, int len, int radix, const cint32_t *pX,
                     const cint32_t *pY)
{
    int n;
    int64_t re, im;

    for (n = 0; n < len; n++) {
        re = (int64_t)pX[n].re * pY[n].re - (int64_t)pX[n].im * pY[n].im;
        im = (int64_t)pX[n].im * pY[n].re + (int64_t)pX[n].re * pY[n].im;
        re >>= radix;
        im >>= radix;
        CIMLIB_SAT_INT(re, INT32_MAX, re);
        CIMLIB_SAT_INT(im, INT32_MAX, im);
        pZ[n].re += (int32_t)re;
        pZ[n].im += (int32_t)im;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (28)
#define CONST(X)            CIMLIB_CONST_S32(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_mac_sat_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mac_sat_c32(void)
{
    static cint32_t x[4] = {
        CONST_CPLX(7.9, 0.33),
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(7.9, 0.33),
    };
    static cint32_t y[4] = {
        CONST_CPLX(0.33, 7.9),
        CONST_CPLX(0.33, -0.75),
        CONST_CPLX(-0.33, 0.75),
        CONST_CPLX(-0.33, -7.9),
    };
    cint32_t z[4] = {
        {CONST(0.0), INT32_MIN + 1},
        CONST_CPLX(-4.9499999732E-01,  4.5360000432E-01),
        CONST_CPLX( 4.9499999732E-01, -4.5360000059E-01),
        {CONST(0.0), INT32_MAX}
    };
    static cint32_t res[4] = {
        CONST_CPLX(0.0, 0.0),
        CONST_CPLX(0.0, 0.0),
        CONST_CPLX(0.0, 0.0),
        {CONST(0.0), -1}
    };
    bool flOk = true;

    /* Call 'vec_mac_sat_c32' function */
    vec_mac_sat_c32(z, 4, RADIX, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
