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
 * This function calculates square root of value, 32 bit unsigned.
 *
 * @param[in]  x  Value, 32 bit unsigned.
 *
 * @return        Square root of value, 16 bit unsigned.
 ******************************************************************************/
uint16_t sc_sqrt_u32(uint32_t x)
{
    uint16_t y, t, s;

    y = (1 << (sc_log2_int_u32(x) >> 1));
    s = y >> 1;
    t = y + s;

    while (s > 0) {
        if (((uint32_t)t * t) <= x) {
            y = t;
        }

        s >>= 1;
        t = y + s;
    }

    return y;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX           (20)
#define CONST_U16(X)    CIMLIB_CONST_U16(X, RADIX / 2)
#define CONST_U32(X)    CIMLIB_CONST_U32(X, RADIX)


/*******************************************************************************
 * This function tests 'sc_sqrt_u32' function. Returns 'true' if validation
 * is successfully done, 'false' - otherwise.
 ******************************************************************************/
bool test_sc_sqrt_u32(void)
{
    int n;
    uint16_t y[4];
    static uint32_t x[4] = {
        CONST_U32(9.0), CONST_U32(36.0), CONST_U32(4.0), CONST_U32(1.0)
    };
    static uint16_t res[4] = {
        CONST_U16(3.0), CONST_U16(6.0), CONST_U16(2.0), CONST_U16(1.0)
    };
    bool flOk = true;

    /* Call 'sc_sqrt_u32' function */
    for (n = 0; n < 4; n++) {
        y[n] = sc_sqrt_u32(x[n]);
    }

    /* Check the correctness of the result */
    TEST_LIBS_CHECK_RES_REAL(y, res, 4, flOk);

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
