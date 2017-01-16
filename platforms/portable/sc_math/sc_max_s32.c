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
 * This function find maximum of two input values, 32 bit signed.
 *
 * @param[in]  x  Input value, 32 bit signed.
 * @param[in]  y  Input value, 32 bit signed.
 *
 * @return        Maximum of input values, 32 bit signed.
 ******************************************************************************/
int32_t sc_max_s32(int32_t x, int32_t y)
{
    if (y > x) {
        x = y;
    }

    return x;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'sc_max_s32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_sc_max_s32(void)
{
    int n;
    int32_t out[4];
    static int32_t data0[4] = {0, -12223, 27, -8};
    static int32_t data1[4] = {1, -80, 10000000, 8};
    static int32_t res[4] = {1, -80, 10000000, 8};
    bool flOk = true;

    /* Call 'sc_max_s32' function */
    for(n = 0; n < 4; n++) {
        out[n] = sc_max_s32(data0[n], data1[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(out, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
