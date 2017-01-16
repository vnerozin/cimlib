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
 * This function calculates center of mass of vector, 32 bit signed.
 *
 * @param[in]  pX     Pointer to input vector, 32 bit signed.
 * @param[in]  len    Vector length.
 * @param[in]  radix  Radix.
 *
 * @return            Index of center of mass of vector, zero based,
 *                    radix is applied.
 ******************************************************************************/
uint32_t vec_cent_mass_s32(const int32_t *pX, int len, int radix)
{
    int n;
    int32_t x, minX;
    uint32_t centMass;
    int idxMinX = 0;
    int64_t totalMass = 0;
    int64_t weighMass = 0;

    /* Calculate total mass */
    for (n = 0; n < len; n++) {
        x = pX[n];
        totalMass += (int64_t)x;
        weighMass += (int64_t)x * (n + 1);
    }

    /* Calculate center of mass with signed vector correction */
    minX = vec_min_s32(&idxMinX, pX, len);
    weighMass -= (int64_t)len * (len + 1) * (minX / 2);
    totalMass -= (int64_t)len * minX;

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
#define RADIX         (20)
#define CONST_S32(X)  CIMLIB_CONST_S32(X, RADIX)
#define CONST_U32(X)  CIMLIB_CONST_U32(X, RADIX)


/*******************************************************************************
 * This function tests 'test_vec_cent_mass_s32' function. Returns 'true'
 * if validation is successfully done, 'false' - otherwise
 ******************************************************************************/
bool test_vec_cent_mass_s32(void)
{
    uint32_t cm;
    static int32_t x[4] = {
        CONST_S32(1.0), CONST_S32(-4.0), CONST_S32(10.0), CONST_S32(-1.0)
    };
    static uint32_t res = CONST_U32(1.6818180084);
    bool flOk = true;

    /* Call 'vec_cent_mass_s32' function */
    cm = vec_cent_mass_s32(x, 4, RADIX);

    /* Check the correctness of the results */
    if (cm != res) {
        flOk = false;
    }

    return flOk;
}

#endif /* (CIMLIB_BUILD_TEST == 1) */
