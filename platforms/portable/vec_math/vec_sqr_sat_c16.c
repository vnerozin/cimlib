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
 * This function calculates square of each element of vector, 16 bit complex,
 * result with saturation control.
 *
 * @param[out]  pY     Pointer to output vector, 16 bit unsigned.
 * @param[in]   len    Vector length.
 * @param[in]   radix  Radix.
 * @param[in]   pX     Pointer to input vector, 16 bit complex.
 ******************************************************************************/
void vec_sqr_sat_c16(uint16_t *pY, int len, int radix, const cint16_t *pX)
{
    int n;
    uint32_t tmp;

    for (n = 0; n < len; n++) {
        tmp = (uint32_t)pX[n].re * pX[n].re;
        tmp += (uint32_t)pX[n].im * pX[n].im;
        tmp >>= radix;
        CIMLIB_SAT_UINT(tmp, UINT16_MAX, tmp);
        pY[n] = (uint16_t)tmp;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (14)
#define CONST(X)            CIMLIB_CONST_U16(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_sqr_sat_c16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sqr_sat_c16(void)
{
    uint16_t y[4];
    static cint16_t x[4] = {
        CONST_CPLX(1.9,  1.9),
        CONST_CPLX(0.12, -0.12),
        CONST_CPLX(-1.9,  1.5),
        CONST_CPLX(0.03, -0.06)
    };
    static uint16_t res[4] = {
        UINT16_MAX,
        CONST( 2.8747558594E-02),
        UINT16_MAX,
        CONST( 4.4555664062E-03)
    };
    bool flOk = true;

    /* Call 'vec_sqr_sat_c16' function */
    vec_sqr_sat_c16(y, 4, RADIX, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
