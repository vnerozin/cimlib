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
 * 64 bit unsigned. Returns zero if 'x' is equal zero.
 *
 * @param[in]  x  Value, 64 bit unsigned.
 *
 * @return        Integer logarithm by base 2 of value, returns zero
 *                if 'x' is equal zero.
 ******************************************************************************/
int sc_log2_int_u64(uint64_t x)
{
    int result;
    uint32_t y;
    static const uint8_t tableLog2[32] = {
        0,  9,  1, 10, 13, 21,  2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
        8, 12, 20, 28, 15, 17, 24,  7, 19, 27, 23,  6, 26,  5, 4, 31
    };

    /* Check high word */
    result = 32;
    y = (uint32_t)(x >> 32);
    if (y == 0) {
        result = 0;
        y = (uint32_t)x;
    }

    /* Check low word */
    y |= y >> 1;
    y |= y >> 2;
    y |= y >> 4;
    y |= y >> 8;
    y |= y >> 16;
    result += tableLog2[(uint32_t)(y * 0x07C4ACDD) >> 27];

    return result;
}


#if (CIMLIB_BUILD_TEST == 1)

/*******************************************************************************
 * This function tests 'sc_log2_int_u64' function. Returns 'true' if
 * validation is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_log2_int_u64(void)
{
    int n;
    int y[4];
    static uint64_t x[4] = {
        0, ((uint64_t)1 << 31), 765321765321, 0xFFFFFFFFFFFFFFFF
    };
    static int res[4] = {0, 31, 39, 63};
    bool flOk = true;

    /* Call 'sc_log2_int_u64' function */
    for(n = 0; n < 4; n++) {
        y[n] = sc_log2_int_u64(x[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
