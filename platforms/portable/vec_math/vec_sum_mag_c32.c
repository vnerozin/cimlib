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
 * vector, 32 bit complex.
 *
 * @param[in]  pX   Pointer to input vector, 32 bit complex.
 * @param[in]  len  Vector length.
 *
 * @return          Sum of absolute complex values (magnitudes),
 *                  64 bit unsigned.
 ******************************************************************************/
uint64_t vec_sum_mag_c32(const cint32_t *pX, int len)
{
    int n;
    uint64_t eng;
    uint64_t acc = 0;

    for (n = 0; n < len; n++) {
        eng = (uint64_t)pX[n].re * pX[n].re + (uint64_t)pX[n].im * pX[n].im;
        acc += sc_sqrt_u64(eng);
    }

    return acc;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sum_mag_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sum_mag_c32(void)
{
    uint64_t y;
    static cint32_t x[4] = {
        {CIMLIB_CONST_S32(-1.0, 30), CIMLIB_CONST_S32(1.0, 30)},
        {CIMLIB_CONST_S32(1.0, 30), CIMLIB_CONST_S32(-1.0, 30)},
        {CIMLIB_CONST_S32(-1.0, 30), CIMLIB_CONST_S32(1.0, 30)},
        {CIMLIB_CONST_S32(1.0, 30), CIMLIB_CONST_S32(-1.0, 30)},
    };
    static uint64_t res = 6074000996;
    bool flOk = true;

    /* Call 'vec_sum_mag_c32' function */
    y = vec_sum_mag_c32(x, 4);

    /* Check the correctness of the results */
    if (y != res) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
