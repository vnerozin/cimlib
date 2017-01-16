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
 * This function find minimum of two input values, 16 bit signed.
 *
 * @param[in]  x  Input value, 16 bit signed.
 * @param[in]  y  Input value, 16 bit signed.
 *
 * @return        Minimum of input values, 16 bit signed.
 ******************************************************************************/
int16_t sc_min_s16(int16_t x, int16_t y)
{
    if (y < x) {
        x = y;
    }

    return x;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'sc_min_s16' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_sc_min_s16(void)
{
    int n;
    int16_t out[4];
    static int16_t data0[4] = {0, -1, 27, -8};
    static int16_t data1[4] = {1, -80, 1000, 8};
    static int16_t res[4] = {0, -80, 27, -8};
    bool flOk = true;

    /* Call 'sc_min_s16' function */
    for(n = 0; n < 4; n++) {
        out[n] = sc_min_s16(data0[n], data1[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(out, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
