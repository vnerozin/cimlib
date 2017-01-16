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
 * result is accumulated with extended precision.
 *
 * @param[in,out]  pYAcc  Pointer to input-output accumulation vector,
 *                        32 bit unsigned.
 * @param[in]      len    Vector length.
 * @param[in]      pX     Pointer to input vector, 16 bit complex.
 ******************************************************************************/
void vec_sqra_long_c16(uint32_t *pYAcc, int len, const cint16_t *pX)
{
    int n;
    uint32_t tmp;

    for (n = 0; n < len; n++) {
        tmp = (uint32_t)pX[n].re * pX[n].re;
        tmp += (uint32_t)pX[n].im * pX[n].im;
        pYAcc[n] += tmp;
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (15)
#define CONST_LONG(X)       CIMLIB_CONST_U32(X, RADIX * 2)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_sqra_long_c16' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sqra_long_c16(void)
{
    static cint16_t x[4] = {
        CONST_CPLX( 9.9996948242E-01,  9.9996948242E-01),
        CONST_CPLX( 1.2496948242E-01, -1.2496948242E-01),
        CONST_CPLX( 9.9996948242E-01, -1.0000000000E+00),
        CONST_CPLX( 3.7658691406E-02, -1.3186645508E-01)
    };
    uint32_t y[4] = {0, 0, 0, 0};
    static uint32_t res[4] = {
        CONST_LONG( 1.9998779316E+00),
        CONST_LONG( 3.1234743074E-02),
        CONST_LONG( 1.9999389658E+00),
        CONST_LONG( 1.8806939013E-02)
    };
    bool flOk = true;

    /* Call 'vec_sqra_long_c16' function */
    vec_sqra_long_c16(y, 4, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
