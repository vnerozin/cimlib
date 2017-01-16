/*******************************************************************************
 * Copyright (c) 2017 Vasiliy Nerozin
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE.md for details.
 ******************************************************************************/ 

/* -----------------------------------------------------------------------------
 * Includes
 * ---------------------------------------------------------------------------*/
#include <stdlib.h>               /* Standard library */
#include "cimlib.h"               /* Library header */


/* -----------------------------------------------------------------------------
 * Exported functions
 * ---------------------------------------------------------------------------*/

/*******************************************************************************
 * This function calculates center of mass of vector, 16 bit signed.
 *
 * @param[in]  pX     Pointer to input vector, 16 bit signed
 * @param[in]  len    Vector length
 * @param[in]  radix  Radix
 *
 * @return            Index of center of mass of vector, zero based,
 *                    radix is applied
 ******************************************************************************/
uint32_t vec_cent_mass_s16(const int16_t *pX, int len, int radix)
{
    int n;
    int16_t x, minX;
    uint32_t centMass;
    int idxMinX = 0;
    int32_t totalMass = 0;
    int32_t weighMass = 0;

    /* Calculate total mass */
    for (n = 0; n < len; n++) {
        x = pX[n];
        totalMass += (int32_t)x;
        weighMass += (int32_t)x * (n + 1);
    }

    /* Calculate center of mass with signed vector correction */
    minX = vec_min_s16(&idxMinX, pX, len);
    weighMass -= (int32_t)len * (len + 1) * (minX / 2);
    totalMass -= (int32_t)len * minX;

    /* Avoid division by zero */
    if (totalMass != 0) {
        centMass = (uint32_t)(((int64_t)weighMass << radix) / totalMass);
        centMass -= (1 << radix);
    } else {
        centMass = 0;
    }

    return centMass;
}


#if (CIMLIB_BUILD_TEST == 1)

/* Simplify macroses for fixed radix */
#define RADIX         (10)
#define CONST_S16(X)  CIMLIB_CONST_S16(X, RADIX)
#define CONST_U32(X)  CIMLIB_CONST_U32(X, RADIX)


/*******************************************************************************
 * This function tests 'test_vec_cent_mass_s16' function. Returns 'true'
 * if validation is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_vec_cent_mass_s16(void)
{
    uint32_t cm;
    static int16_t x[4] = {
        CONST_S16(1.0), CONST_S16(-4.0), CONST_S16(10.0), CONST_S16(-1.0)
    };
    static uint32_t res = CONST_U32(1.681640);
    bool flOk = true;

    /* Call 'vec_cent_mass_s16' function */
    cm = vec_cent_mass_s16(x, 4, RADIX);

    /* Check the correctness of the results */
    if (cm != res) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
