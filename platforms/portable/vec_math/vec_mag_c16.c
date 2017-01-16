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
 * This function calculates absolute complex (magnitude) value of each element
 * of vector, 16 bit complex.
 *
 * @param[out]  pY   Pointer to output vector, 16 bit unsigned.
 * @param[in]   len  Vector length.
 * @param[in]   pX   Pointer to input vector, 16 bit complex.
 ******************************************************************************/
void vec_mag_c16(uint16_t *pY, int len, const cint16_t *pX)
{
    int n;
    uint32_t eng;

    for (n = 0; n < len; n++) {
        eng = (uint32_t)(pX[n].re * pX[n].re + pX[n].im * pX[n].im);
        pY[n] = sc_sqrt_u32(eng);
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (10)
#define CONST(X)            CIMLIB_CONST_U16(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_mag_c16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mag_c16(void)
{
    uint16_t y[4];
    static cint16_t x[4] = {
        CONST_CPLX(2.1, 0.05),
        CONST_CPLX(0.1, -0.05),
        CONST_CPLX(-5.6, 3.001),
        CONST_CPLX(3.14, 1.0)
    };
    static uint16_t res[4] = {
        CONST(2.0996093750E+00),
        CONST(1.1132812500E-01),
        CONST(6.3525390625E+00),
        CONST(3.2949218750E+00)
    };
    bool flOk = true;

    /* Call 'vec_mag_c16' function */
    vec_mag_c16(y, 4, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
