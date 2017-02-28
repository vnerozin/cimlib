/*******************************************************************************
 * Copyright (c) 2017 Vasiliy Nerozin
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE.md for details.
 ******************************************************************************/

/* -----------------------------------------------------------------------------
 * Includes
 * ---------------------------------------------------------------------------*/
#include <stdint.h>          /* Standard integer types */
#include <stdbool.h>         /* Standard boolean types */
#include <stdio.h>           /* Standard IO library */
#include "cimlib.h"          /* Library header */
#include "test_libs.h"       /* Libraries test functions */


/* -----------------------------------------------------------------------------
 * Definitions
 * ---------------------------------------------------------------------------*/

/* Test execution macro */
#define TEST(func, flPass)                                                     \
{                                                                              \
    bool flOk;                                                                 \
    (flOk) = test_##func();                                                    \
    (flPass) = ((flPass) && (flOk));                                           \
    printf("  %24s -> ", #func);                                               \
    if ((flOk) == 0) {                                                         \
        printf("failed\n");                                                    \
    }                                                                          \
    else {                                                                     \
        printf("passed\n");                                                    \
    }                                                                          \
}


/* -----------------------------------------------------------------------------
 * Exported functions
 * ---------------------------------------------------------------------------*/

/*******************************************************************************
 * All libraries test.
 *
 * @param[in]  platform  Platform name, string.
 *
 * @return               All libraries test status, 'true' - passed,
 *                       'false' - otherwise.
 ******************************************************************************/
bool test_all(const char *platform)
{
    bool flPass = true;

    printf("\nTest '%s' platform libraries:\n", platform);

    printf("\nTest frame math library:\n");

    TEST(frm_ema_s16, flPass);
    TEST(frm_ema_s32, flPass);


    printf("\nTest memory operations library:\n");

    TEST(mem_kth_min_s16, flPass);
    TEST(mem_kth_min_s32, flPass);
    TEST(mem_median_s16,  flPass);
    TEST(mem_median_s32,  flPass);
    TEST(mem_sort_s16,    flPass);
    TEST(mem_sort_s32,    flPass);


    printf("\nTest scalar math library:\n");

    TEST(sc_add_c16,         flPass);
    TEST(sc_add_c32,         flPass);
    TEST(sc_add_sat_c16,     flPass);
    TEST(sc_add_sat_c32,     flPass);
    TEST(sc_add_sat_s16,     flPass);
    TEST(sc_add_sat_s32,     flPass);
    TEST(sc_atan2_s16,       flPass);
    TEST(sc_atan2_s32,       flPass);
    TEST(sc_cos_s16,         flPass);
    TEST(sc_cos_s32,         flPass);
    TEST(sc_div_c16,         flPass);
    TEST(sc_div_c32,         flPass);
    TEST(sc_div_s16,         flPass);
    TEST(sc_div_s32,         flPass);
    TEST(sc_ema_s16,         flPass);
    TEST(sc_ema_s32,         flPass);
    TEST(sc_ln_u16,          flPass);
    TEST(sc_ln_u32,          flPass);
    TEST(sc_log10_u16,       flPass);
    TEST(sc_log10_u32,       flPass);
    TEST(sc_log2_int_u16,    flPass);
    TEST(sc_log2_int_u32,    flPass);
    TEST(sc_log2_int_u64,    flPass);
    TEST(sc_log2_u16,        flPass);
    TEST(sc_log2_u32,        flPass);
    TEST(sc_mac_c16,         flPass);
    TEST(sc_mac_c32,         flPass);
    TEST(sc_mac_cj_c16,      flPass);
    TEST(sc_mac_cj_c32,      flPass);
    TEST(sc_mac_cj_long_c16, flPass);
    TEST(sc_mac_cj_long_c32, flPass);
    TEST(sc_mac_long_c16,    flPass);
    TEST(sc_mac_long_c32,    flPass);
    TEST(sc_mac_long_s16,    flPass);
    TEST(sc_mac_long_s32,    flPass);
    TEST(sc_mac_s16,         flPass);
    TEST(sc_mac_s32,         flPass);
    TEST(sc_mac_sat_c16,     flPass);
    TEST(sc_mac_sat_c32,     flPass);
    TEST(sc_mac_sat_s16,     flPass);
    TEST(sc_mac_sat_s32,     flPass);
    TEST(sc_mag_c16,         flPass);
    TEST(sc_mag_c32,         flPass);
    TEST(sc_max_s16,         flPass);
    TEST(sc_max_s32,         flPass);
    TEST(sc_min_s16,         flPass);
    TEST(sc_min_s32,         flPass);
    TEST(sc_mul_c16,         flPass);
    TEST(sc_mul_c16s16,      flPass);
    TEST(sc_mul_c32,         flPass);
    TEST(sc_mul_c32s32,      flPass);
    TEST(sc_mul_cj_c16,      flPass);
    TEST(sc_mul_cj_c32,      flPass);
    TEST(sc_mul_cj_long_c16, flPass);
    TEST(sc_mul_cj_long_c32, flPass);
    TEST(sc_mul_cj_sat_c16,  flPass);
    TEST(sc_mul_cj_sat_c32,  flPass);
    TEST(sc_mul_long_c16,    flPass);
    TEST(sc_mul_long_c32,    flPass);
    TEST(sc_mul_long_s16,    flPass);
    TEST(sc_mul_long_s32,    flPass);
    TEST(sc_mul_s16,         flPass);
    TEST(sc_mul_s32,         flPass);
    TEST(sc_mul_sat_c16,     flPass);
    TEST(sc_mul_sat_c32,     flPass);
    TEST(sc_mul_sat_s16,     flPass);
    TEST(sc_mul_sat_s32,     flPass);
    TEST(sc_norm_c16,        flPass);
    TEST(sc_norm_c32,        flPass);
    TEST(sc_rcp_s16,         flPass);
    TEST(sc_rcp_s32,         flPass);
    TEST(sc_sin_s16,         flPass);
    TEST(sc_sin_s32,         flPass);
    TEST(sc_sqr_c16,         flPass);
    TEST(sc_sqr_c32,         flPass);
    TEST(sc_sqr_long_c16,    flPass);
    TEST(sc_sqr_long_c32,    flPass);
    TEST(sc_sqr_long_s16,    flPass);
    TEST(sc_sqr_long_s32,    flPass);
    TEST(sc_sqr_s16,         flPass);
    TEST(sc_sqr_s32,         flPass);
    TEST(sc_sqr_sat_c16,     flPass);
    TEST(sc_sqr_sat_c32,     flPass);
    TEST(sc_sqr_sat_s16,     flPass);
    TEST(sc_sqr_sat_s32,     flPass);
    TEST(sc_sqrt_u32,        flPass);
    TEST(sc_sqrt_u64,        flPass);
    TEST(sc_sub_c16,         flPass);
    TEST(sc_sub_c32,         flPass);


    printf("\nTest vector math library:\n");

    TEST(vec_abs_s16,           flPass);
    TEST(vec_abs_s32,           flPass);
    TEST(vec_abs_s64,           flPass);
    TEST(vec_add_c16,           flPass);
    TEST(vec_add_c32,           flPass);
    TEST(vec_add_const_c16,     flPass);
    TEST(vec_add_const_c32,     flPass);
    TEST(vec_add_const_s16,     flPass);
    TEST(vec_add_const_s32,     flPass);
    TEST(vec_add_const_sat_c16, flPass);
    TEST(vec_add_const_sat_c32, flPass);
    TEST(vec_add_const_sat_s16, flPass);
    TEST(vec_add_const_sat_s32, flPass);
    TEST(vec_add_s16,           flPass);
    TEST(vec_add_s32,           flPass);
    TEST(vec_add_sat_c16,       flPass);
    TEST(vec_add_sat_c32,       flPass);
    TEST(vec_add_sat_s16,       flPass);
    TEST(vec_add_sat_s32,       flPass);
    TEST(vec_cent_mass_s16,     flPass);
    TEST(vec_cent_mass_s32,     flPass);
    TEST(vec_cent_mass_u16,     flPass);
    TEST(vec_cent_mass_u32,     flPass);
    TEST(vec_ema_s16,           flPass);
    TEST(vec_ema_s32,           flPass);
    TEST(vec_mac_c16,           flPass);
    TEST(vec_mac_c32,           flPass);
    TEST(vec_mac_cj_c16,        flPass);
    TEST(vec_mac_cj_c32,        flPass);
    TEST(vec_mac_cj_long_c16,   flPass);
    TEST(vec_mac_cj_long_c32,   flPass);
    TEST(vec_mac_cj_sat_c16,    flPass);
    TEST(vec_mac_cj_sat_c32,    flPass);
    TEST(vec_mac_long_c16,      flPass);
    TEST(vec_mac_long_c32,      flPass);
    TEST(vec_mac_long_s16,      flPass);
    TEST(vec_mac_long_s32,      flPass);
    TEST(vec_mac_s16,           flPass);
    TEST(vec_mac_s32,           flPass);
    TEST(vec_mac_sat_c16,       flPass);
    TEST(vec_mac_sat_c32,       flPass);
    TEST(vec_mac_sat_s16,       flPass);
    TEST(vec_mac_sat_s32,       flPass);
    TEST(vec_mag_c16,           flPass);
    TEST(vec_mag_c32,           flPass);
    TEST(vec_max_s16,           flPass);
    TEST(vec_max_s32,           flPass);
    TEST(vec_max_sqr_c16,       flPass);
    TEST(vec_max_sqr_c32,       flPass);
    TEST(vec_max_sqr_s16,       flPass);
    TEST(vec_max_sqr_s32,       flPass);
    TEST(vec_max_sqr_sat_c16,   flPass);
    TEST(vec_max_sqr_sat_c32,   flPass);
    TEST(vec_max_sqr_sat_s16,   flPass);
    TEST(vec_max_sqr_sat_s32,   flPass);
    TEST(vec_min_s16,           flPass);
    TEST(vec_min_s32,           flPass);
    TEST(vec_min_sqr_c16,       flPass);
    TEST(vec_min_sqr_c32,       flPass);
    TEST(vec_min_sqr_s16,       flPass);
    TEST(vec_min_sqr_s32,       flPass);
    TEST(vec_min_sqr_sat_c16,   flPass);
    TEST(vec_min_sqr_sat_c32,   flPass);
    TEST(vec_min_sqr_sat_s16,   flPass);
    TEST(vec_min_sqr_sat_s32,   flPass);
    TEST(vec_mul_c16,           flPass);
    TEST(vec_mul_c16s16,        flPass);
    TEST(vec_mul_c32,           flPass);
    TEST(vec_mul_c32s32,        flPass);
    TEST(vec_mul_cj_c16,        flPass);
    TEST(vec_mul_cj_c32,        flPass);
    TEST(vec_mul_cj_long_c16,   flPass);
    TEST(vec_mul_cj_long_c32,   flPass);
    TEST(vec_mul_cj_sat_c16,    flPass);
    TEST(vec_mul_cj_sat_c32,    flPass);
    TEST(vec_mul_const_c16,     flPass);
    TEST(vec_mul_const_c32,     flPass);
    TEST(vec_mul_const_s16,     flPass);
    TEST(vec_mul_const_s32,     flPass);
    TEST(vec_mul_const_sat_c16, flPass);
    TEST(vec_mul_const_sat_c32, flPass);
    TEST(vec_mul_const_sat_s16, flPass);
    TEST(vec_mul_const_sat_s32, flPass);
    TEST(vec_mul_long_c16,      flPass);
    TEST(vec_mul_long_c32,      flPass);
    TEST(vec_mul_long_s16,      flPass);
    TEST(vec_mul_long_s32,      flPass);
    TEST(vec_mul_s16,           flPass);
    TEST(vec_mul_s32,           flPass);
    TEST(vec_mul_sat_c16,       flPass);
    TEST(vec_mul_sat_c32,       flPass);
    TEST(vec_mul_sat_s16,       flPass);
    TEST(vec_mul_sat_s32,       flPass);
    TEST(vec_scale_radix_s16,   flPass);
    TEST(vec_scale_radix_s32,   flPass);
    TEST(vec_sqr_c16,           flPass);
    TEST(vec_sqr_c32,           flPass);
    TEST(vec_sqr_long_c16,      flPass);
    TEST(vec_sqr_long_c32,      flPass);
    TEST(vec_sqr_long_s16,      flPass);
    TEST(vec_sqr_long_s32,      flPass);
    TEST(vec_sqr_s16,           flPass);
    TEST(vec_sqr_s32,           flPass);
    TEST(vec_sqr_sat_c16,       flPass);
    TEST(vec_sqr_sat_c32,       flPass);
    TEST(vec_sqr_sat_s16,       flPass);
    TEST(vec_sqr_sat_s32,       flPass);
    TEST(vec_sqra_long_c16,     flPass);
    TEST(vec_sqra_long_c32,     flPass);
    TEST(vec_sqra_long_s16,     flPass);
    TEST(vec_sqra_long_s32,     flPass);
    TEST(vec_sub_c16,           flPass);
    TEST(vec_sub_c32,           flPass);
    TEST(vec_sub_s16,           flPass);
    TEST(vec_sub_s32,           flPass);
    TEST(vec_sub_sat_c16,       flPass);
    TEST(vec_sub_sat_c32,       flPass);
    TEST(vec_sub_sat_s16,       flPass);
    TEST(vec_sub_sat_s32,       flPass);
    TEST(vec_sum_c16,           flPass);
    TEST(vec_sum_c32,           flPass);
    TEST(vec_sum_diff_c16,      flPass);
    TEST(vec_sum_diff_c32,      flPass);
    TEST(vec_sum_diff_s16,      flPass);
    TEST(vec_sum_diff_s32,      flPass);
    TEST(vec_sum_mag_c16,       flPass);
    TEST(vec_sum_mag_c32,       flPass);
    TEST(vec_sum_mul_c16,       flPass);
    TEST(vec_sum_mul_c16s16,    flPass);
    TEST(vec_sum_mul_c32,       flPass);
    TEST(vec_sum_mul_c32s32,    flPass);
    TEST(vec_sum_mul_cj_c16,    flPass);
    TEST(vec_sum_mul_cj_c32,    flPass);
    TEST(vec_sum_mul_s16,       flPass);
    TEST(vec_sum_mul_s32,       flPass);
    TEST(vec_sum_s16,           flPass);
    TEST(vec_sum_s32,           flPass);
    TEST(vec_sum_sqr_c16,       flPass);
    TEST(vec_sum_sqr_c32,       flPass);
    TEST(vec_sum_sqr_diff_c16,  flPass);
    TEST(vec_sum_sqr_diff_c32,  flPass);
    TEST(vec_sum_sqr_diff_s16,  flPass);
    TEST(vec_sum_sqr_diff_s32,  flPass);
    TEST(vec_sum_sqr_long_c16,  flPass);
    TEST(vec_sum_sqr_long_c32,  flPass);
    TEST(vec_sum_sqr_long_s16,  flPass);
    TEST(vec_sum_sqr_long_s32,  flPass);
    TEST(vec_sum_sqr_s16,       flPass);
    TEST(vec_sum_sqr_s32,       flPass);


    if (flPass == true) {
        printf("\nTest for '%s' platform is successfully passed.\n", platform);
    } else {
        printf("\nTest for '%s' platform is failed.\n", platform);
    }

    return flPass;
}


#if (CIMLIB_BUILD_TEST_STANDALONE == 1)
/*******************************************************************************
 * Main function for standalone test.
 ******************************************************************************/
int main(int argc, char *argv[])
{
    (void)argc;

    /* Test platform library */
    (void)test_all(argv[1]);

    return 0;
}
#endif /* (CIMLIB_BUILD_TEST_STANDALONE == 1) */
