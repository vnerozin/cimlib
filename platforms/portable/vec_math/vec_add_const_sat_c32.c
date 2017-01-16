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
 * This function calculates by element addition of vector with constant,
 * 32 bit complex, result is with saturation control.
 *
 * @param[out]  pY    Pointer to output vector, 32 bit complex.
 * @param[in]   len   Vector length.
 * @param[in]   pX    Pointer to input vector, 32 bit complex.
 * @param[in]   cnst  Constant, 32 bit complex.
 ******************************************************************************/
void vec_add_const_sat_c32(cint32_t *pY, int len, const cint32_t *pX,
                           cint32_t cnst)
{
    int n;
    int64_t re, im;
    int32_t cnst_re, cnst_im;

    cnst_re = cnst.re;
    cnst_im = cnst.im;

    for (n = 0; n < len; n++) {
        re = (int64_t)pX[n].re + cnst_re;
        im = (int64_t)pX[n].im + cnst_im;

        CIMLIB_SAT_INT(re, INT32_MAX, re);
        CIMLIB_SAT_INT(im, INT32_MAX, im);

        pY[n].re = (int32_t)re;
        pY[n].im = (int32_t)im;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (28)
#define CONST(X)            CIMLIB_CONST_S32(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_add_const_sat_c32' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_vec_add_const_sat_c32(void)
{
    cint32_t y[4];
    static cint32_t cnst = CONST_CPLX(5.0, -7.0);
    static cint32_t x[4] = {
        CONST_CPLX(2.1, -1.0),
        CONST_CPLX(-5.0, 7.0),
        CONST_CPLX(-5.6, 3.001),
        CONST_CPLX(3.14, -1.0)
    };
    static cint32_t res[4] = {
        {CONST(7.1), INT32_MIN},
        CONST_CPLX(0.0, 0.0),
        CONST_CPLX(-0.6, -3.999),
        {INT32_MAX, INT32_MIN}
    };
    bool flOk = true;

    /* Call 'vec_add_const_sat_c32' function */
    vec_add_const_sat_c32(y, 4, x, cnst);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
