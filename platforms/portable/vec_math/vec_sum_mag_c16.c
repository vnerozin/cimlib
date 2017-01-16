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
 * This function calculates sum of absolute complex values (magnitudes) of
 * vector, 16 bit complex.
 *
 * @param[in]  pX   Pointer to input vector, 16 bit complex.
 * @param[in]  len  Vector length.
 * @return          Sum of absolute complex values (magnitudes),
 *                  32 bit unsigned.
 ******************************************************************************/
uint32_t vec_sum_mag_c16(const cint16_t *pX, int len)
{
    int n;
    uint32_t eng;
    uint32_t acc = 0;

    for (n = 0; n < len; n++) {
        eng = (uint32_t)pX[n].re * pX[n].re + (uint32_t)pX[n].im * pX[n].im;
        acc += sc_sqrt_u32(eng);
    }

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX               (10)
#define CONST(X)            CIMLIB_CONST_U32(X, RADIX)
#define CONST_CPLX(RE, IM)  CIMLIB_CONST_C16(RE, IM, RADIX)


/*******************************************************************************
 * This function tests 'vec_sum_mag_c16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_mag_c16(void)
{
    uint32_t y;
    static cint16_t x[4] = {
        CONST_CPLX(2.1, 0.05),
        CONST_CPLX(0.1, -0.05),
        CONST_CPLX(-5.6, 3.001),
        CONST_CPLX(3.14, 1.0)
    };
    static uint32_t res = CONST(1.1858398438E+01);
    bool flOk = true;

    /* Call 'vec_sum_mag_c16' function */
    y = vec_sum_mag_c16(x, 4);

    /* Check the correctness of the results */
    if (y != res) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
