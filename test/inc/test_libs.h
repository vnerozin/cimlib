/*******************************************************************************
 * Copyright (c) 2017 Vasiliy Nerozin
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE.md for details.
 ******************************************************************************/
#ifndef TEST_LIBS_H_
#define TEST_LIBS_H_


#ifdef __cplusplus
extern "C"
{
#endif


/* -----------------------------------------------------------------------------
 * Includes
 * ---------------------------------------------------------------------------*/
#include <stdint.h>          /* Standard integer types */
#include <stdbool.h>         /* Standard boolean types */
#include <stdio.h>           /* Standard IO library */


/* -----------------------------------------------------------------------------
 * Definitions
 * ---------------------------------------------------------------------------*/

/* Check the correctness of the results, complex */
#define TEST_LIBS_CHECK_RES_CPLX(X, X_, LEN, FLAG)                             \
{                                                                              \
    int n_;                                                                    \
    for (n_ = 0; n_ < (LEN); n_++) {                                           \
        if (((X)[n_].re != (X_)[n_].re) || ((X)[n_].im != (X_)[n_].im)) {      \
            (FLAG) = false;                                                    \
            printf("val #%3d, out = %lld, %lld; ref = %lld, %lld;\n",          \
                   n_,                                                         \
                   (int64_t)(X)[n_].re, (int64_t)(X)[n_].im,                   \
                   (int64_t)(X_)[n_].re, (int64_t)(X_)[n_].im);                \
        }                                                                      \
    }                                                                          \
}

/* Check the correctness of the results, real */
#define TEST_LIBS_CHECK_RES_REAL(X, X_, LEN, FLAG)                             \
{                                                                              \
    int n_;                                                                    \
    for (n_ = 0; n_ < (LEN); n_++) {                                           \
        if ((X)[n_] != (X_)[n_]) {                                             \
            (FLAG) = false;                                                    \
            printf("val #%3d, out = %lld; ref = %lld;\n",                      \
                   n_, (int64_t)(X)[n_], (int64_t)(X_)[n_]);                   \
        }                                                                      \
    }                                                                          \
}


#ifdef __cplusplus
}
#endif


#endif /* TEST_LIBS_H_ */
