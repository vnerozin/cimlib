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

/******************************************************************************
 * This function calculates integer logarithm by base 2 of value,
 * 32 bit unsigned. Returns zero if 'x' is equal zero.
 *
 * @param[in]  x  Value, 32 bit unsigned.
 *
 * @return        Integer logarithm by base 2 of value, returns zero
 *                if 'x' is equal zero.
 ******************************************************************************/
int sc_log2_int_u32(uint32_t x)
{
    int result;
    static const int tableLog2[32] = {
        0,  9,  1, 10, 13, 21,  2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
        8, 12, 20, 28, 15, 17, 24,  7, 19, 27, 23,  6, 26,  5, 4, 31
    };

    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    result = tableLog2[(uint32_t)(x * 0x07C4ACDD) >> 27];

    return result;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'sc_log2_int_u32' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_log2_int_u32(void)
{
    int n;
    int y[4];
    static uint32_t x[4] = {0, (1 << 14), 7654321, 0xFFFFFFFF};
    static int res[4] = {0, 14, 22, 31};
    bool flOk = true;

    /* Call 'sc_log2_int_u32' function */
    for(n = 0; n < 4; n++) {
        y[n] = sc_log2_int_u32(x[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
