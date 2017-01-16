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
 * This function scales base radix of input vector, 16 bit signed
 *
 * @param[out]  pY      Pointer to output vector, 16 bit signed
 * @param[in]   len     Vector length
 * @param[in]   offset  Scale radix offset, number of shifts right, if negative;
 *                      if positive - left shifts
 * @param[in]   pX      Pointer to input vector, 16 bit signed
 ******************************************************************************/
void vec_scale_radix_s16(int16_t *pY, int len, int offset, const int16_t *pX)
{
    int n;

    if (offset > 0) {
        for (n = 0; n < len; n++) {
            pY[n] = (int16_t)(pX[n] << offset);
        }
    } else if (offset < 0) {
        offset = -offset;
        for (n = 0; n < len; n++) {
            pY[n] = (int16_t)(pX[n] >> offset);
        }
    }
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'vec_scale_radix_s16' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_vec_scale_radix_s16(void)
{
    int16_t y[4];
    static int16_t x[4] = {30, 20, -234, 234};
    static int16_t res0[4] = {240, 160, -1872, 1872};
    static int16_t res1[4] = {3, 2, -30, 29};
    bool flOk = true;

    /* Call 'vec_scale_radix_s16' function */
    vec_scale_radix_s16(y, 4, 3, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res0, 4, flOk);

    /* Call 'vec_scale_radix_s16' function */
    vec_scale_radix_s16(y, 4, -3, x);

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res1, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
