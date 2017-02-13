/*******************************************************************************
 * Copyright (c) 2017 Vasiliy Nerozin
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE.md for details.
 ******************************************************************************/
#ifndef CIMLIB_H
#define CIMLIB_H


#ifdef __cplusplus
extern "C"
{
#endif


/* -----------------------------------------------------------------------------
 * Includes
 * ---------------------------------------------------------------------------*/
#include <stdint.h>          /* Standard integer types */
#include <stdbool.h>         /* Standard boolean types */
#if (CIMLIB_BUILD_TEST == 1)
#include "test_libs.h"       /* Libraries test functions */
#endif /* (CIMLIB_BUILD_TEST == 1) */


/* -----------------------------------------------------------------------------
 * Definitions
 * ---------------------------------------------------------------------------*/

/* Float to fixed point value conversion */
#define CIMLIB_FIXED_S16(X, RADIX)                                             \
    ((int16_t)((X) / (1 << (RADIX))))

#define CIMLIB_FIXED_S32(X, RADIX)                                             \
    ((int32_t)((X) / (1 << (RADIX))))


/* Float to fixed point constants conversion.
 * Note: Use this only for constants conversion
 * */
#define CIMLIB_ROUND(X)  (((X) < 0) ? ((X) - 0.5) : ((X) + 0.5))

#define CIMLIB_CONST_S16(X, RADIX)                                             \
    ((int16_t)CIMLIB_ROUND((X) * ((int16_t)1 << (RADIX))))

#define CIMLIB_CONST_S32(X, RADIX)                                             \
    ((int32_t)CIMLIB_ROUND((X) * ((int32_t)1 << (RADIX))))

#define CIMLIB_CONST_S64(X, RADIX)                                             \
    ((int64_t)CIMLIB_ROUND((X) * ((int64_t)1 << (RADIX))))


#define CIMLIB_CONST_U16(X, RADIX)                                             \
    ((uint16_t)CIMLIB_ROUND((X) * ((uint16_t)1 << (RADIX))))

#define CIMLIB_CONST_U32(X, RADIX)                                             \
    ((uint32_t)CIMLIB_ROUND((X) * ((uint32_t)1 << (RADIX))))

#define CIMLIB_CONST_U64(X, RADIX)                                             \
    ((uint64_t)CIMLIB_ROUND((X) * ((uint64_t)1 << (RADIX))))


#define CIMLIB_CONST_C16(RE, IM, RADIX)                                        \
    {CIMLIB_CONST_S16(RE, RADIX), CIMLIB_CONST_S16(IM, RADIX)}

#define CIMLIB_CONST_C32(RE, IM, RADIX)                                        \
    {CIMLIB_CONST_S32(RE, RADIX), CIMLIB_CONST_S32(IM, RADIX)}

#define CIMLIB_CONST_C64(RE, IM, RADIX)                                        \
    {CIMLIB_CONST_S64(RE, RADIX), CIMLIB_CONST_S64(IM, RADIX)}


/* Get integer and fractional part */
#define CIMLIB_INT_PART_S16(X, RADIX)                                          \
    ((int16_t)((X) / (1 << (RADIX))))

#define CIMLIB_INT_PART_S32(X, RADIX)                                          \
    ((int32_t)((X) / (1 << (RADIX))))

/* TODO Add 'FRAC' definition */


/* Saturate signed value */
#define CIMLIB_SAT_INT(Y, LIM, X)                                              \
{                                                                              \
    (Y) = (X);                                                                 \
    if ((X) > (LIM)) (Y) = (LIM);                                              \
    if ((X) < (-(LIM) - 1)) (Y) = (-(LIM) - 1);                                \
}                                                                              \

/* Saturate unsigned value */
#define CIMLIB_SAT_UINT(Y, LIM, X)                                             \
{                                                                              \
    (Y) = (X);                                                                 \
    if ((X) > (LIM)) (Y) = (LIM);                                              \
}


/* Converts time constant to EMA averaging constant
 *
 * TIME  - EMA time constant, in s
 * FREQS - sample rate, in Hz
 * RADIX - alpha radix
 *
 * Note: This is approximation for true formula for FW implementation.
 *       True formula:
 *              alpha = 1.0 - exp(-(1.0 / freqs) / time)
 *
 * */
#define CIMLIB_EMA_TIME_2_ALPHA_S16(TIME, FREQS, RADIX)  \
    (CIMLIB_CONST_S16((TIME) / (FREQS), (RADIX)))

#define CIMLIB_EMA_TIME_2_ALPHA_S32(TIME, FREQS, RADIX)  \
    (CIMLIB_CONST_S32((TIME) / (FREQS), (RADIX)))


/* Constants */
#define CIMLIB_PI  (3.141592653590)


/* -----------------------------------------------------------------------------
 * Types
 * ---------------------------------------------------------------------------*/

/** Complex 16 bit signed integer type */
typedef struct {
    int16_t re;                          /**< Real */
    int16_t im;                          /**< Imaginary */

} cint16_t;


/** Complex 32 bit signed integer type */
typedef struct {
    int32_t re;                          /**< Real */
    int32_t im;                          /**< Imaginary */

} cint32_t;


/** Complex 64 bit signed integer type */
typedef struct {
    int64_t re;                          /**< Real */
    int64_t im;                          /**< Imaginary */

} cint64_t;


/* -----------------------------------------------------------------------------
 * Exported functions
 * ---------------------------------------------------------------------------*/

/** Memory operations library */

int16_t mem_kth_min_s16(int16_t *pX, int len, int k);

int32_t mem_kth_min_s32(int32_t *pX, int len, int k);

int16_t mem_median_s16(int16_t *pX, int len);

int32_t mem_median_s32(int32_t *pX, int len);

void mem_sort_s16(int16_t *pX, int len);

void mem_sort_s32(int32_t *pX, int len);


/** Scalar math library */

cint16_t sc_add_c16(cint16_t x, cint16_t y);

cint32_t sc_add_c32(cint32_t x, cint32_t y);

int16_t sc_atan2_s16(int16_t y, int16_t x, int radix);

int32_t sc_atan2_s32(int32_t y, int32_t x, int radix);

int16_t sc_cos_s16(int16_t x, int radix);

int32_t sc_cos_s32(int32_t x, int radix);

cint16_t sc_div_c16(cint16_t x, cint16_t y, int radix);

cint32_t sc_div_c32(cint32_t x, cint32_t y, int radix);

int16_t sc_div_s16(int16_t x, int16_t y, int radix);

int32_t sc_div_s32(int32_t x, int32_t y, int radix);

int16_t sc_ema_s16(int16_t acc, int16_t x, int16_t alpha, int radix);

int32_t sc_ema_s32(int32_t acc, int32_t x, int32_t alpha, int radix);

int16_t sc_ln_u16(uint16_t x, int radix);

int32_t sc_ln_u32(uint32_t x, int radix);

int16_t sc_log10_u16(uint16_t x, int radix);

int32_t sc_log10_u32(uint32_t x, int radix);

int sc_log2_int_u16(uint16_t x);

int sc_log2_int_u32(uint32_t x);

int sc_log2_int_u64(uint64_t x);

int16_t sc_log2_u16(uint16_t x, int radix);

int32_t sc_log2_u32(uint32_t x, int radix);

uint16_t sc_mag_c16(cint16_t x);

uint32_t sc_mag_c32(cint32_t x);

int16_t sc_max_s16(int16_t x, int16_t y);

int32_t sc_max_s32(int32_t x, int32_t y);

int16_t sc_min_s16(int16_t x, int16_t y);

int32_t sc_min_s32(int32_t x, int32_t y);

cint16_t sc_mul_c16(cint16_t x, cint16_t y, int radix);

cint16_t sc_mul_c16s16(cint16_t x, int16_t y, int radix);

cint32_t sc_mul_c32(cint32_t x, cint32_t y, int radix);

cint32_t sc_mul_c32s32(cint32_t x, int32_t y, int radix);

cint16_t sc_mul_cj_c16(cint16_t x, cint16_t y, int radix);

cint32_t sc_mul_cj_c32(cint32_t x, cint32_t y, int radix);

cint32_t sc_mul_cj_long_c16(cint16_t x, cint16_t y);

cint64_t sc_mul_cj_long_c32(cint32_t x, cint32_t y);

cint16_t sc_mul_cj_sat_c16(cint16_t x, cint16_t y, int radix);

cint32_t sc_mul_cj_sat_c32(cint32_t x, cint32_t y, int radix);

cint32_t sc_mul_long_c16(cint16_t x, cint16_t y);

cint64_t sc_mul_long_c32(cint32_t x, cint32_t y);

int32_t sc_mul_long_s16(int16_t x, int16_t y);

int64_t sc_mul_long_s32(int32_t x, int32_t y);

int16_t sc_mul_s16(int16_t x, int16_t y, int radix);

int32_t sc_mul_s32(int32_t x, int32_t y, int radix);

cint16_t sc_mul_sat_c16(cint16_t x, cint16_t y, int radix);

cint32_t sc_mul_sat_c32(cint32_t x, cint32_t y, int radix);

int16_t sc_mul_sat_s16(int16_t x, int16_t y, int radix);

int32_t sc_mul_sat_s32(int32_t x, int32_t y, int radix);

cint16_t sc_norm_c16(cint16_t x, int radix);

cint32_t sc_norm_c32(cint32_t x, int radix);

int16_t sc_rcp_s16(int16_t x, int radix);

int32_t sc_rcp_s32(int32_t x, int radix);

int16_t sc_sin_s16(int16_t x, int radix);

int32_t sc_sin_s32(int32_t x, int radix);

uint16_t sc_sqr_c16(cint16_t x, int radix);

uint32_t sc_sqr_c32(cint32_t x, int radix);

uint32_t sc_sqr_long_c16(cint16_t x);

uint64_t sc_sqr_long_c32(cint32_t x);

uint32_t sc_sqr_long_s16(int16_t x);

uint64_t sc_sqr_long_s32(int32_t x);

uint16_t sc_sqr_s16(int16_t x, int radix);

uint32_t sc_sqr_s32(int32_t x, int radix);

uint16_t sc_sqr_sat_s16(int16_t x, int radix);

uint32_t sc_sqr_sat_s32(int32_t x, int radix);

uint16_t sc_sqr_sat_c16(cint16_t x, int radix);

uint32_t sc_sqr_sat_c32(cint32_t x, int radix);

uint16_t sc_sqrt_u32(uint32_t x);

uint32_t sc_sqrt_u64(uint64_t x);

cint16_t sc_sub_c16(cint16_t x, cint16_t y);

cint32_t sc_sub_c32(cint32_t x, cint32_t y);


/** Vector math library */

void vec_abs_s16(int16_t *pY, int len, const int16_t *pX);

void vec_abs_s32(int32_t *pY, int len, const int32_t *pX);

void vec_abs_s64(int64_t *pY, int len, const int64_t *pX);

void vec_add_c16(cint16_t *pZ, int len, const cint16_t *pX, const cint16_t *pY);

void vec_add_c32(cint32_t *pZ, int len, const cint32_t *pX, const cint32_t *pY);

void vec_add_const_c16(cint16_t *pY, int len, const cint16_t *pX,
                       cint16_t cnst);

void vec_add_const_c32(cint32_t *pY, int len, const cint32_t *pX,
                       cint32_t cnst);

void vec_add_const_s16(int16_t *pY, int len, const int16_t *pX, int16_t cnst);

void vec_add_const_s32(int32_t *pY, int len, const int32_t *pX, int32_t cnst);

void vec_add_const_sat_c16(cint16_t *pY, int len, const cint16_t *pX,
                           cint16_t cnst);

void vec_add_const_sat_c32(cint32_t *pY, int len, const cint32_t *pX,
                           cint32_t cnst);

void vec_add_const_sat_s16(int16_t *pY, int len, const int16_t *pX,
                           int16_t cnst);

void vec_add_const_sat_s32(int32_t *pY, int len, const int32_t *pX,
                           int32_t cnst);

void vec_add_s16(int16_t *pZ, int len, const int16_t *pX, const int16_t *pY);

void vec_add_s32(int32_t *pZ, int len, const int32_t *pX, const int32_t *pY);

void vec_add_sat_c16(cint16_t *pZ, int len, const cint16_t *pX,
                     const cint16_t *pY);

void vec_add_sat_c32(cint32_t *pZ, int len, const cint32_t *pX,
                     const cint32_t *pY);

void vec_add_sat_s16(int16_t *pZ, int len, const int16_t *pX,
                     const int16_t *pY);

void vec_add_sat_s32(int32_t *pZ, int len, const int32_t *pX,
                     const int32_t *pY);

uint32_t vec_cent_mass_s16(const int16_t *pX, int len, int radix);

uint32_t vec_cent_mass_s32(const int32_t *pX, int len, int radix);

uint32_t vec_cent_mass_u16(const uint16_t *pX, int len, int radix);

uint32_t vec_cent_mass_u32(const uint32_t *pX, int len, int radix);

void vec_ema_s16(int16_t *pAcc, int len, int16_t alpha, int radix,
                 const int16_t *pX);

void vec_ema_s32(int32_t *pAcc, int len, int32_t alpha, int radix,
                 const int32_t *pX);

void vec_mac_c16(cint16_t *pZ, int len, int radix, const cint16_t *pX,
                 const cint16_t *pY);

void vec_mac_c32(cint32_t *pZ, int len, int radix, const cint32_t *pX,
                 const cint32_t *pY);

void vec_mac_s16(int16_t *pZ, int len, int radix, const int16_t *pX,
                 const int16_t *pY);

void vec_mac_s32(int32_t *pZ, int len, int radix, const int32_t *pX,
                 const int32_t *pY);

void vec_mac_sat_c16(cint16_t *pZ, int len, int radix, const cint16_t *pX,
                     const cint16_t *pY);

void vec_mac_sat_c32(cint32_t *pZ, int len, int radix, const cint32_t *pX,
                     const cint32_t *pY);

void vec_mac_sat_s16(int16_t *pZ, int len, int radix, const int16_t *pX,
                     const int16_t *pY);

void vec_mac_sat_s32(int32_t *pZ, int len, int radix, const int32_t *pX,
                     const int32_t *pY);

void vec_mac_cj_c16(cint16_t *pZ, int len, int radix, const cint16_t *pX,
                    const cint16_t *pY);

void vec_mac_cj_c32(cint32_t *pZ, int len, int radix, const cint32_t *pX,
                    const cint32_t *pY);

void vec_mac_cj_long_c16(cint32_t *pZ, int len, const cint16_t *pX,
                         const cint16_t *pY);

void vec_mac_cj_long_c32(cint64_t *pZ, int len, const cint32_t *pX,
                         const cint32_t *pY);

void vec_mac_long_c16(cint32_t *pZ, int len, const cint16_t *pX,
                      const cint16_t *pY);

void vec_mac_long_c32(cint64_t *pZ, int len, const cint32_t *pX,
                      const cint32_t *pY);

void vec_mac_long_s16(int32_t *pZ, int len, const int16_t *pX,
                      const int16_t *pY);

void vec_mac_long_s32(int64_t *pZ, int len, const int32_t *pX,
                      const int32_t *pY);

void vec_mag_c16(uint16_t *pY, int len, const cint16_t *pX);

void vec_mag_c32(uint32_t *pY, int len, const cint32_t *pX);

int16_t vec_max_s16(int *pIdxMax, const int16_t *pX, int len);

int32_t vec_max_s32(int *pIdxMax, const int32_t *pX, int len);

uint16_t vec_max_sqr_c16(int *pIdxMax, const cint16_t *pX, int len, int radix);

uint32_t vec_max_sqr_c32(int *pIdxMax, const cint32_t *pX, int len, int radix);

uint16_t vec_max_sqr_s16(int *pIdxMax, const int16_t *pX, int len, int radix);

uint32_t vec_max_sqr_s32(int *pIdxMax, const int32_t *pX, int len, int radix);

uint16_t vec_max_sqr_sat_c16(int *pIdxMax, const cint16_t *pX, int len,
                             int radix);

uint32_t vec_max_sqr_sat_c32(int *pIdxMax, const cint32_t *pX, int len,
                             int radix);

uint16_t vec_max_sqr_sat_s16(int *pIdxMax, const int16_t *pX, int len,
                             int radix);

uint32_t vec_max_sqr_sat_s32(int *pIdxMax, const int32_t *pX, int len,
                             int radix);

int16_t vec_min_s16(int *pIdxMin, const int16_t *pX, int len);

int32_t vec_min_s32(int *pIdxMin, const int32_t *pX, int len);

void vec_mul_c16(cint16_t *pZ, int len, int radix, const cint16_t *pX,
                 const cint16_t *pY);

void vec_mul_c16s16(cint16_t *pZ, int len, int radix, const cint16_t *pX,
                    const int16_t *pY);

void vec_mul_c32(cint32_t *pZ, int len, int radix, const cint32_t *pX,
                 const cint32_t *pY);

void vec_mul_c32s32(cint32_t *pZ, int len, int radix, const cint32_t *pX,
                    const int32_t *pY);

void vec_mul_cj_c16(cint16_t *pZ, int len, int radix, const cint16_t *pX,
                    const cint16_t *pY);

void vec_mul_cj_c32(cint32_t *pZ, int len, int radix, const cint32_t *pX,
                    const cint32_t *pY);

void vec_mul_cj_long_c16(cint32_t *pZ, int len, const cint16_t *pX,
                         const cint16_t *pY);

void vec_mul_cj_long_c32(cint64_t *pZ, int len, const cint32_t *pX,
                         const cint32_t *pY);

void vec_mul_cj_sat_c16(cint16_t *pZ, int len, int radix, const cint16_t *pX,
                        const cint16_t *pY);

void vec_mul_cj_sat_c32(cint32_t *pZ, int len, int radix, const cint32_t *pX,
                        const cint32_t *pY);

void vec_mul_const_c16(cint16_t *pY, int len, int radix, const cint16_t *pX,
                       cint16_t cnst);

void vec_mul_const_c32(cint32_t *pY, int len, int radix, const cint32_t *pX,
                       cint32_t cnst);

void vec_mul_const_s16(int16_t *pY, int len, int radix, const int16_t *pX,
                       int16_t cnst);

void vec_mul_const_s32(int32_t *pY, int len, int radix, const int32_t *pX,
                       int32_t cnst);

void vec_mul_const_sat_c16(cint16_t *pY, int len, int radix, const cint16_t *pX,
                           cint16_t cnst);

void vec_mul_const_sat_c32(cint32_t *pY, int len, int radix, const cint32_t *pX,
                           cint32_t cnst);

void vec_mul_const_sat_s16(int16_t *pY, int len, int radix, const int16_t *pX,
                           int16_t cnst);

void vec_mul_const_sat_s32(int32_t *pY, int len, int radix, const int32_t *pX,
                           int32_t cnst);

void vec_mul_long_c16(cint32_t *pZ, int len, const cint16_t *pX,
                      const cint16_t *pY);

void vec_mul_long_c32(cint64_t *pZ, int len, const cint32_t *pX,
                      const cint32_t *pY);

void vec_mul_long_s16(int32_t *pZ, int len, const int16_t *pX,
                      const int16_t *pY);

void vec_mul_long_s32(int64_t *pZ, int len, const int32_t *pX,
                      const int32_t *pY);

void vec_mul_s16(int16_t *pZ, int len, int radix, const int16_t *pX,
                 const int16_t *pY);

void vec_mul_s32(int32_t *pZ, int len, int radix, const int32_t *pX,
                 const int32_t *pY);

void vec_mul_sat_c16(cint16_t *pZ, int len, int radix, const cint16_t *pX,
                     const cint16_t *pY);

void vec_mul_sat_c32(cint32_t *pZ, int len, int radix, const cint32_t *pX,
                     const cint32_t *pY);

void vec_mul_sat_s16(int16_t *pZ, int len, int radix, const int16_t *pX,
                     const int16_t *pY);

void vec_mul_sat_s32(int32_t *pZ, int len, int radix, const int32_t *pX,
                     const int32_t *pY);

void vec_scale_radix_s16(int16_t *pY, int len, int radix, const int16_t *pX);

void vec_scale_radix_s32(int32_t *pY, int len, int offset, const int32_t *pX);

void vec_sqr_c16(uint16_t *pY, int len, int radix, const cint16_t *pX);

void vec_sqr_c32(uint32_t *pY, int len, int radix, const cint32_t *pX);

void vec_sqr_long_c16(uint32_t *pY, int len, const cint16_t *pX);

void vec_sqr_long_c32(uint64_t *pY, int len, const cint32_t *pX);

void vec_sqr_long_s16(uint32_t *pY, int len, const int16_t *pX);

void vec_sqr_long_s32(uint64_t *pY, int len, const int32_t *pX);

void vec_sqr_s16(uint16_t *pY, int len, int radix, const int16_t *pX);

void vec_sqr_s32(uint32_t *pY, int len, int radix, const int32_t *pX);

void vec_sqr_sat_c16(uint16_t *pY, int len, int radix, const cint16_t *pX);

void vec_sqr_sat_c32(uint32_t *pY, int len, int radix, const cint32_t *pX);

void vec_sqr_sat_s16(uint16_t *pY, int len, int radix, const int16_t *pX);

void vec_sqr_sat_s32(uint32_t *pY, int len, int radix, const int32_t *pX);

void vec_sqra_long_c16(uint32_t *pYAcc, int len, const cint16_t *pX);

void vec_sqra_long_c32(uint64_t *pYAcc, int len, const cint32_t *pX);

void vec_sqra_long_s16(uint32_t *pYAcc, int len, const int16_t *pX);

void vec_sqra_long_s32(uint64_t *pYAcc, int len, const int32_t *pX);

void vec_sub_c16(cint16_t *pZ, int len, const cint16_t *pX, const cint16_t *pY);

void vec_sub_c32(cint32_t *pZ, int len, const cint32_t *pX, const cint32_t *pY);

void vec_sub_s16(int16_t *pZ, int len, const int16_t *pX, const int16_t *pY);

void vec_sub_s32(int32_t *pZ, int len, const int32_t *pX, const int32_t *pY);

cint32_t vec_sum_c16(const cint16_t *pX, int len);

cint64_t vec_sum_c32(const cint32_t *pX, int len);

cint32_t vec_sum_diff_c16(const cint16_t *pX, const cint16_t *pY, int len);

cint64_t vec_sum_diff_c32(const cint32_t *pX, const cint32_t *pY, int len);

int32_t vec_sum_diff_s16(const int16_t *pX, const int16_t *pY, int len);

int64_t vec_sum_diff_s32(const int32_t *pX, const int32_t *pY, int len);

uint32_t vec_sum_mag_c16(const cint16_t *pX, int len);

uint64_t vec_sum_mag_c32(const cint32_t *pX, int len);

cint32_t vec_sum_mul_c16(const cint16_t *pX, const cint16_t *pY, int len,
                         int radix);

cint32_t vec_sum_mul_c16s16(const cint16_t *pX, const int16_t *pY, int len,
                            int radix);

cint64_t vec_sum_mul_c32(const cint32_t *pX, const cint32_t *pY, int len,
                         int radix);

cint64_t vec_sum_mul_c32s32(const cint32_t *pX, const int32_t *pY, int len,
                            int radix);

cint32_t vec_sum_mul_cj_c16(const cint16_t *pX, const cint16_t *pY, int len,
                            int radix);

cint64_t vec_sum_mul_cj_c32(const cint32_t *pX, const cint32_t *pY, int len,
                            int radix);

int32_t vec_sum_mul_s16(const int16_t *pX, const int16_t *pY, int len,
                        int radix);

int64_t vec_sum_mul_s32(const int32_t *pX, const int32_t *pY, int len,
                        int radix);

int32_t vec_sum_s16(const int16_t *pX, int len);

int64_t vec_sum_s32(const int32_t *pX, int len);

uint32_t vec_sum_sqr_c16(const cint16_t *pX, int len, int radix);

uint64_t vec_sum_sqr_c32(const cint32_t *pX, int len, int radix);

uint32_t vec_sum_sqr_diff_c16(const cint16_t *pX, const cint16_t *pY, int len,
                              int radix);

uint64_t vec_sum_sqr_diff_c32(const cint32_t *pX, const cint32_t *pY, int len,
                              int radix);

uint32_t vec_sum_sqr_diff_s16(const int16_t *pX, const int16_t *pY, int len,
                              int radix);

uint64_t vec_sum_sqr_diff_s32(const int32_t *pX, const int32_t *pY, int len,
                              int radix);

uint32_t vec_sum_sqr_long_c16(const cint16_t *pX, int len);

uint64_t vec_sum_sqr_long_c32(const cint32_t *pX, int len);

uint32_t vec_sum_sqr_long_s16(const int16_t *pX, int len);

uint64_t vec_sum_sqr_long_s32(const int32_t *pX, int len);

uint32_t vec_sum_sqr_s16(const int16_t *pX, int len, int radix);

uint64_t vec_sum_sqr_s32(const int32_t *pX, int len, int radix);


#if (CIMLIB_BUILD_TEST == 1)
/** Tests for memory operations library */
bool test_mem_kth_min_s16(void);
bool test_mem_kth_min_s32(void);
bool test_mem_median_s16(void);
bool test_mem_median_s32(void);
bool test_mem_sort_s16(void);
bool test_mem_sort_s32(void);


/** Tests for scalar math library */
bool test_sc_add_c16(void);
bool test_sc_add_c32(void);
bool test_sc_atan2_s16(void);
bool test_sc_atan2_s32(void);
bool test_sc_cos_s16(void);
bool test_sc_cos_s32(void);
bool test_sc_div_c16(void);
bool test_sc_div_c32(void);
bool test_sc_div_s16(void);
bool test_sc_div_s32(void);
bool test_sc_ema_s16(void);
bool test_sc_ema_s32(void);
bool test_sc_ln_u16(void);
bool test_sc_ln_u32(void);
bool test_sc_log10_u16(void);
bool test_sc_log10_u32(void);
bool test_sc_log2_int_u16(void);
bool test_sc_log2_int_u32(void);
bool test_sc_log2_int_u64(void);
bool test_sc_log2_u16(void);
bool test_sc_log2_u32(void);
bool test_sc_mag_c16(void);
bool test_sc_mag_c32(void);
bool test_sc_max_s16(void);
bool test_sc_max_s32(void);
bool test_sc_min_s16(void);
bool test_sc_min_s32(void);
bool test_sc_mul_c16(void);
bool test_sc_mul_c16s16(void);
bool test_sc_mul_c32(void);
bool test_sc_mul_c32s32(void);
bool test_sc_mul_cj_c16(void);
bool test_sc_mul_cj_c32(void);
bool test_sc_mul_cj_long_c16(void);
bool test_sc_mul_cj_long_c32(void);
bool test_sc_mul_cj_sat_c16(void);
bool test_sc_mul_cj_sat_c32(void);
bool test_sc_mul_long_c16(void);
bool test_sc_mul_long_c32(void);
bool test_sc_mul_long_s16(void);
bool test_sc_mul_long_s32(void);
bool test_sc_mul_s16(void);
bool test_sc_mul_s32(void);
bool test_sc_mul_sat_c16(void);
bool test_sc_mul_sat_c32(void);
bool test_sc_mul_sat_s16(void);
bool test_sc_mul_sat_s32(void);
bool test_sc_norm_c16(void);
bool test_sc_norm_c32(void);
bool test_sc_rcp_s16(void);
bool test_sc_rcp_s32(void);
bool test_sc_sin_s16(void);
bool test_sc_sin_s32(void);
bool test_sc_sqr_c16(void);
bool test_sc_sqr_c32(void);
bool test_sc_sqr_long_c16(void);
bool test_sc_sqr_long_c32(void);
bool test_sc_sqr_long_s16(void);
bool test_sc_sqr_long_s32(void);
bool test_sc_sqr_s16(void);
bool test_sc_sqr_s32(void);
bool test_sc_sqr_sat_c16(void);
bool test_sc_sqr_sat_c32(void);
bool test_sc_sqr_sat_s16(void);
bool test_sc_sqr_sat_s32(void);
bool test_sc_sqrt_u32(void);
bool test_sc_sqrt_u64(void);
bool test_sc_sub_c16(void);
bool test_sc_sub_c32(void);


/** Tests for vector math library */
bool test_vec_abs_s16(void);
bool test_vec_abs_s32(void);
bool test_vec_abs_s64(void);
bool test_vec_add_c16(void);
bool test_vec_add_c32(void);
bool test_vec_add_const_c16(void);
bool test_vec_add_const_c32(void);
bool test_vec_add_const_s16(void);
bool test_vec_add_const_s32(void);
bool test_vec_add_const_sat_c16(void);
bool test_vec_add_const_sat_c32(void);
bool test_vec_add_const_sat_s16(void);
bool test_vec_add_const_sat_s32(void);
bool test_vec_add_s16(void);
bool test_vec_add_s32(void);
bool test_vec_add_sat_c16(void);
bool test_vec_add_sat_c32(void);
bool test_vec_add_sat_s16(void);
bool test_vec_add_sat_s32(void);
bool test_vec_cent_mass_s16(void);
bool test_vec_cent_mass_s32(void);
bool test_vec_cent_mass_u16(void);
bool test_vec_cent_mass_u32(void);
bool test_vec_ema_s16(void);
bool test_vec_ema_s32(void);
bool test_vec_mac_c16(void);
bool test_vec_mac_c32(void);
bool test_vec_mac_cj_c16(void);
bool test_vec_mac_cj_c32(void);
bool test_vec_mac_cj_long_c16(void);
bool test_vec_mac_cj_long_c32(void);
bool test_vec_mac_long_c16(void);
bool test_vec_mac_long_c32(void);
bool test_vec_mac_long_s16(void);
bool test_vec_mac_long_s32(void);
bool test_vec_mac_s16(void);
bool test_vec_mac_s32(void);
bool test_vec_mac_sat_c16(void);
bool test_vec_mac_sat_c32(void);
bool test_vec_mac_sat_s16(void);
bool test_vec_mac_sat_s32(void);
bool test_vec_mag_c16(void);
bool test_vec_mag_c32(void);
bool test_vec_max_s16(void);
bool test_vec_max_s32(void);
bool test_vec_max_sqr_c16(void);
bool test_vec_max_sqr_c32(void);
bool test_vec_max_sqr_s16(void);
bool test_vec_max_sqr_s32(void);
bool test_vec_max_sqr_sat_c16(void);
bool test_vec_max_sqr_sat_c32(void);
bool test_vec_max_sqr_sat_s16(void);
bool test_vec_max_sqr_sat_s32(void);
bool test_vec_min_s16(void);
bool test_vec_min_s32(void);
bool test_vec_mul_c16(void);
bool test_vec_mul_c16s16(void);
bool test_vec_mul_c32(void);
bool test_vec_mul_c32s32(void);
bool test_vec_mul_cj_c16(void);
bool test_vec_mul_cj_c32(void);
bool test_vec_mul_cj_long_c16(void);
bool test_vec_mul_cj_long_c32(void);
bool test_vec_mul_cj_sat_c16(void);
bool test_vec_mul_cj_sat_c32(void);
bool test_vec_mul_const_c16(void);
bool test_vec_mul_const_c32(void);
bool test_vec_mul_const_s16(void);
bool test_vec_mul_const_s32(void);
bool test_vec_mul_const_sat_c16(void);
bool test_vec_mul_const_sat_c32(void);
bool test_vec_mul_const_sat_s16(void);
bool test_vec_mul_const_sat_s32(void);
bool test_vec_mul_long_c16(void);
bool test_vec_mul_long_c32(void);
bool test_vec_mul_long_s16(void);
bool test_vec_mul_long_s32(void);
bool test_vec_mul_s16(void);
bool test_vec_mul_s32(void);
bool test_vec_mul_sat_c16(void);
bool test_vec_mul_sat_c32(void);
bool test_vec_mul_sat_s16(void);
bool test_vec_mul_sat_s32(void);
bool test_vec_scale_radix_s16(void);
bool test_vec_scale_radix_s32(void);
bool test_vec_sqr_c16(void);
bool test_vec_sqr_c32(void);
bool test_vec_sqr_long_c16(void);
bool test_vec_sqr_long_c32(void);
bool test_vec_sqr_long_s16(void);
bool test_vec_sqr_long_s32(void);
bool test_vec_sqr_s16(void);
bool test_vec_sqr_s32(void);
bool test_vec_sqr_sat_c16(void);
bool test_vec_sqr_sat_c32(void);
bool test_vec_sqr_sat_s16(void);
bool test_vec_sqr_sat_s32(void);
bool test_vec_sqra_long_c16(void);
bool test_vec_sqra_long_c32(void);
bool test_vec_sqra_long_s16(void);
bool test_vec_sqra_long_s32(void);
bool test_vec_sub_c16(void);
bool test_vec_sub_c32(void);
bool test_vec_sub_s16(void);
bool test_vec_sub_s32(void);
bool test_vec_sum_c16(void);
bool test_vec_sum_c32(void);
bool test_vec_sum_diff_c16(void);
bool test_vec_sum_diff_c32(void);
bool test_vec_sum_diff_s16(void);
bool test_vec_sum_diff_s32(void);
bool test_vec_sum_mag_c16(void);
bool test_vec_sum_mag_c32(void);
bool test_vec_sum_mul_c16(void);
bool test_vec_sum_mul_c16s16(void);
bool test_vec_sum_mul_c32(void);
bool test_vec_sum_mul_c32s32(void);
bool test_vec_sum_mul_cj_c16(void);
bool test_vec_sum_mul_cj_c32(void);
bool test_vec_sum_mul_s16(void);
bool test_vec_sum_mul_s32(void);
bool test_vec_sum_s16(void);
bool test_vec_sum_s32(void);
bool test_vec_sum_sqr_c16(void);
bool test_vec_sum_sqr_c32(void);
bool test_vec_sum_sqr_diff_c16(void);
bool test_vec_sum_sqr_diff_c32(void);
bool test_vec_sum_sqr_diff_s16(void);
bool test_vec_sum_sqr_diff_s32(void);
bool test_vec_sum_sqr_long_c16(void);
bool test_vec_sum_sqr_long_c32(void);
bool test_vec_sum_sqr_long_s16(void);
bool test_vec_sum_sqr_long_s32(void);
bool test_vec_sum_sqr_s16(void);
bool test_vec_sum_sqr_s32(void);
#endif /* (CIMLIB_BUILD_TEST == 1) */


#ifdef __cplusplus
}
#endif


#endif /* CIMLIB_H */
