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
 * of vector, 32 bit complex.
 *
 * @param[out]  pY   Pointer to output vector, 32 bit unsigned.
 * @param[in]   len  Vector length.
 * @param[in]   pX   Pointer to input vector, 32 bit complex.
 ******************************************************************************/
void vec_mag_c32(uint32_t *pY, int len, const cint32_t *pX)
{
    int n;
    uint64_t eng;

    for (n = 0; n < len; n++) {
        eng = (uint64_t)((int64_t)pX[n].re * pX[n].re +
                         (int64_t)pX[n].im * pX[n].im);
        pY[n] = sc_sqrt_u64(eng);
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (20)
#define CONST(X)            CIMLIB_CONST_U32(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C32(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_mag_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_mag_c32(void)
{
    uint32_t y[4];
    static cint32_t x[4] = {
        CONST_CPLX(2.1, 0.05),
        CONST_CPLX(0.1, -0.05),
        CONST_CPLX(-5.6, 3.001),
        CONST_CPLX(3.14, 1.0)
    };
    static uint32_t res[4] = {
        CONST(2.1005954742E+00),
        CONST(1.1180305481E-01),
        CONST(6.3534240723E+00),
        CONST(3.2953901291E+00)
    };
    bool flOk = true;

    /* Call 'vec_mag_c32' function */
    vec_mag_c32(y, 4, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
