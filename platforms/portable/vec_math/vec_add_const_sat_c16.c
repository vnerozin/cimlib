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
 * 16 bit complex, result is with saturation control.
 *
 * @param[out]  pY    Pointer to output vector, 16 bit complex.
 * @param[in]   len   Vector length.
 * @param[in]   pX    Pointer to input vector, 16 bit complex.
 * @param[in]   cnst  Constant, 16 bit complex.
 ******************************************************************************/
void vec_add_const_sat_c16(cint16_t *pY, int len, const cint16_t *pX,
                           cint16_t cnst)
{
    int n;
    int32_t re, im;
    int16_t cnst_re, cnst_im;

    cnst_re = cnst.re;
    cnst_im = cnst.im;

    for (n = 0; n < len; n++) {
        re = pX[n].re + cnst_re;
        im = pX[n].im + cnst_im;

        CIMLIB_SAT_INT(re, INT16_MAX, re);
        CIMLIB_SAT_INT(im, INT16_MAX, im);

        pY[n].re = (int16_t)re;
        pY[n].im = (int16_t)im;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (12)
#define CONST(X)            CIMLIB_CONST_S16(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_add_const_sat_c16' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_vec_add_const_sat_c16(void)
{
    cint16_t y[4];
    static cint16_t cnst = CONST_CPLX(5.0, -7.0);
    static cint16_t x[4] = {
        CONST_CPLX(2.1, -1.0),
        CONST_CPLX(-5.0, 7.0),
        CONST_CPLX(-5.6, 3.001),
        CONST_CPLX(3.14, -1.0)
    };
    static cint16_t res[4] = {
        {CONST(7.1), INT16_MIN},
        CONST_CPLX(0.0, 0.0),
        CONST_CPLX(-0.6, -3.999),
        {INT16_MAX, INT16_MIN}
    };
    bool flOk = true;

    /* Call 'vec_add_const_sat_c16' function */
    vec_add_const_sat_c16(y, 4, x, cnst);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
