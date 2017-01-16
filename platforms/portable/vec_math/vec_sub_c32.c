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
 * This function calculates by element subtraction of two vectors,
 * 32 bit complex.
 *
 * @param[out]  pZ   Pointer to output vector, 32 bit complex.
 * @param[in]   len  Vector length.
 * @param[in]   pX   Pointer to input vector, 32 bit complex.
 * @param[in]   pY   Pointer to input vector, 32 bit complex.
 ******************************************************************************/
void vec_sub_c32(cint32_t *pZ, int len, const cint32_t *pX, const cint32_t *pY)
{
    int n;

    for (n = 0; n < len; n++) {
        pZ[n].re = (int32_t)(pX[n].re - pY[n].re);
        pZ[n].im = (int32_t)(pX[n].im - pY[n].im);
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_sub_c32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_sub_c32(void)
{
    cint32_t z[4];
    static cint32_t x[4] = {
        {11111111, -2222222}, {333333, 4444444},
        {-1111111, 22222222}, {-333333, -444444}
    };
    static cint32_t y[4] = {
        {11111111, -2222222}, {333333, 4444444},
        {-1111111, 22222222}, {-333333, -444444}
    };
    static cint32_t res[4] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
    bool flOk = true;

    /* Call 'vec_sub_c32' function */
    vec_sub_c32(z, 4, x, y);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_CPLX(z, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
