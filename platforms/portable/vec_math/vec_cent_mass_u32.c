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
 * This function calculates center of mass of vector, 32 bit unsigned.
 *
 * @param[in]  pX     Pointer to input vector, 32 bit unsigned.
 * @param[in]  len    Vector length.
 * @param[in]  radix  Radix.
 *
 * @return            Index of center of mass of vector, zero based,
 *                    radix is applied.
 ******************************************************************************/
uint32_t vec_cent_mass_u32(const uint32_t *pX, int len, int radix)
{
    int n;
    uint32_t x;
    uint32_t centMass;
    uint32_t totalMass = 0;
    uint64_t weighMass = 0;

    /* Calculate total mass */
    for (n = 0; n < len; n++) {
        x = pX[n];
        totalMass += (uint64_t)x;
        weighMass += (uint64_t)x * (n + 1);
    }

    /* Calculate center of mass */

    /* Avoid division by zero */
    if (totalMass != 0) {
        centMass = (uint32_t)((weighMass << radix) / totalMass);
        centMass -= (1 << radix);
    } else {
        centMass = 0;
    }

    return centMass;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX     (20)
#define CONST(X)  CIMLIB_CONST_U32(X, RADIX)


/*******************************************************************************
 * This function tests 'test_vec_cent_mass_u32' function. Returns 'true'
 * if validation is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_vec_cent_mass_u32(void)
{
    uint32_t cm;
    static uint32_t x[4] = {
        CONST(1.0), CONST(4.0), CONST(10.0), CONST(1.0)
    };
    static uint32_t res = CONST(1.6875);
    bool flOk = true;

    /* Call 'vec_cent_mass_u32' function */
    cm = vec_cent_mass_u32(x, 4, RADIX);

    /* Check the correctness of the results */
    if (cm != res) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
