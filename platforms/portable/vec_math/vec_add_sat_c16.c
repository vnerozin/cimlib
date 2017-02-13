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
 * This function calculates by element addition of two vectors, 16 bit complex,
 * result is with saturation control.
 *
 * @param[out]  pZ   Pointer to output vector, 16 bit complex.
 * @param[in]   len  Vector length.
 * @param[in]   pX   Pointer to input vector, 16 bit complex.
 * @param[in]   pY   Pointer to input vector, 16 bit complex.
 ******************************************************************************/
void vec_add_sat_c16(cint16_t *pZ, int len, const cint16_t *pX,
                     const cint16_t *pY)
{
    int n;
    int32_t re, im;

    for (n = 0; n < len; n++) {
        re = (int32_t)pX[n].re + pY[n].re;
        im = (int32_t)pX[n].im + pY[n].im;

        CIMLIB_SAT_INT(re, INT16_MAX, re);
        CIMLIB_SAT_INT(im, INT16_MAX, im);

        pZ[n].re = (int16_t)re;
        pZ[n].im = (int16_t)im;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (12)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_add_sat_c16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_vec_add_sat_c16(void)
{
    cint16_t z[4];
    static cint16_t x[4] = {
        CONST_CPLX(-7.1, 0.05),
        CONST_CPLX(0.1, -0.05),
        CONST_CPLX(5.6, 3.001),
        CONST_CPLX(3.14, 1.0)
    };
    static cint16_t y[4] = {
        CONST_CPLX(-2.1, -0.05),
        CONST_CPLX(-0.1, 0.05),
        CONST_CPLX(5.6, -3.001),
        CONST_CPLX(-3.14, -1.0)
    };
    static cint16_t res[4] = {
        {INT16_MIN, 0}, {0, 0}, {INT16_MAX, 0}, {0, 0}
    };
    bool flOk = true;

    /* Call 'vec_add_sat_c16' function */
    vec_add_sat_c16(z, 4, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
