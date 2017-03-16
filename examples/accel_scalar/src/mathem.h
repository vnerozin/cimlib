/*******************************************************************************
 * Copyright (c) 2017 Vasiliy Nerozin
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE.md for details.
 ******************************************************************************/
#ifndef MATHEM_H
#define MATHEM_H


/* -----------------------------------------------------------------------------
 * Includes
 * ---------------------------------------------------------------------------*/
#include <math.h>
#include <stdint.h>
#include "cimlib.h"               /* CIMLIB library header */


/* -----------------------------------------------------------------------------
 * Definitions
 * ---------------------------------------------------------------------------*/

/* Fixed point base radix */
#define RADIX  (14)

/* Simplify macroses for fixed radix */
#define CONST(X)  CIMLIB_CONST_S32(X, RADIX)

#define FIXED(X)  CIMLIB_FIXED_S32(X, RADIX)

#define EMA_TIME_2_ALPHA(TIME, FREQS)  \
    CIMLIB_EMA_TIME_2_ALPHA_S32(TIME, FREQS, RADIX)

#define TO_DOUBLE(X)  CIMLIB_DOUBLE(X, RADIX)


#endif /* MATHEM_H */
