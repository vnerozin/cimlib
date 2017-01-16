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
 * This function calculates by element complex multiply of input vectors,
 * 16 bit complex, result with extended precision and accumulated to output
 * vector.
 *
 * @param[out]  pZ   Pointer to output vector, 16 bit complex.
 * @param[in]   len  Vector length.
 * @param[in]   pX   Pointer to input vector, 16 bit complex.
 * @param[in]   pY   Pointer to input vector, 16 bit complex.
 ******************************************************************************/
void vec_mac_long_c16(cint32_t *pZ, int len, const cint16_t *pX,
                      const cint16_t *pY)
{
    int n;

    for (n = 0; n < len; n++) {
        pZ[n].re += (int32_t)pX[n].re * pY[n].re - (int32_t)pX[n].im * pY[n].im;
        pZ[n].im += (int32_t)pX[n].im * pY[n].re + (int32_t)pX[n].re * pY[n].im;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX  (14)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)
#define CONST_CPLX_LONG(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX * 2)


/*******************************************************************************
 * This function tests 'vec_mac_long_c16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_vec_mac_long_c16(void)
{
    static cint16_t x[4] = {
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(0.75, 0.33),
        CONST_CPLX(0.75, 0.33),
    };
    static cint16_t y[4] = {
        CONST_CPLX(0.33, 0.75),
        CONST_CPLX(0.33, -0.75),
        CONST_CPLX(-0.33, 0.75),
        CONST_CPLX(-0.33, -0.75),
    };
    cint32_t z[4] = {
        CONST_CPLX_LONG( 0.0000000000E+00, -6.7141127959E-01),
        CONST_CPLX_LONG(-4.9502563477E-01,  4.5358872041E-01),
        CONST_CPLX_LONG( 4.9502563477E-01, -4.5358872041E-01),
        CONST_CPLX_LONG( 0.0000000000E+00,  6.7141127959E-01)
    };
    static cint32_t res[4] = {
        CONST_CPLX(0.0, 0.0),
        CONST_CPLX(0.0, 0.0),
        CONST_CPLX(0.0, 0.0),
        CONST_CPLX(0.0, 0.0),
    };
    bool flOk = true;

    /* Call 'vec_mac_long_c16' function */
    vec_mac_long_c16(z, 4, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
