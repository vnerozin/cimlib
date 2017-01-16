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
 * This function calculates square root of value, 64 bit unsigned.
 *
 * @param[in]  x  Value, 64 bit unsigned.
 *
 * @return        Square root of value, 32 bit unsigned.
 ******************************************************************************/
uint32_t sc_sqrt_u64(uint64_t x)
{
    uint32_t y, t, s;

    y = (1 << (sc_log2_int_u64(x) >> 1));
    s = y >> 1;
    t = y + s;

    while (s > 0) {
        if (((uint64_t)t * t) <= x) {
            y = t;
        }

        s >>= 1;
        t = y + s;
    }

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX           (40)
#define CONST_U32(X)    CIMLIB_CONST_U32(X, RADIX / 2)
#define CONST_U64(X)    CIMLIB_CONST_U64(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_sqrt_u64' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_sqrt_u64(void)
{
    int n;
    uint32_t y[4];
    static uint64_t x[4] = {
        CONST_U64(9.0), CONST_U64(36.0), CONST_U64(4.0), CONST_U64(1.0)
    };
    static uint32_t res[4] = {
        CONST_U32(3.0), CONST_U32(6.0), CONST_U32(2.0), CONST_U32(1.0)
    };
    bool flOk = true;

    /* Call 'sc_sqrt_u64' function */
    for (n = 0; n < 4; n++) {
        y[n] = sc_sqrt_u64(x[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
