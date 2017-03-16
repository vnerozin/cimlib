/*******************************************************************************
 * Copyright (c) 2017 Vasiliy Nerozin
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE.md for details.
 ******************************************************************************/


/* -----------------------------------------------------------------------------
 * Includes
 * ---------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include "mathem.h"             /* Mathematical library */
#include "accel_proc.h"         /* Accelerometer data processing module */


/* -----------------------------------------------------------------------------
 * Definitions
 * ---------------------------------------------------------------------------*/

/* Accelerometer data sample rate, in Hz */
#define ACCEL_FREQS  (32.0)

/* Vibrations level average interval, in seconds */
#define ACCEL_LEN_VIB_AVER  (2.0)

/* Accelerometer filter for angles estimation length, in s */
#define ACCEL_LEN_FILT_ANGLES  (0.5)

/* Alpha for vibration level */
#define ALPHA_LEV_VIBR  \
    (EMA_TIME_2_ALPHA(ACCEL_LEN_VIB_AVER, ACCEL_FREQS))

/* Alpha for accelerometer filter */
#define ALPHA_FILT_ACCEL \
    (EMA_TIME_2_ALPHA(ACCEL_LEN_FILT_ANGLES, ACCEL_FREQS))

/* Number of initialisation samples */
#define NR_INIT_SAMPLES  ((int)(ACCEL_FREQS / 4.0))


/* -----------------------------------------------------------------------------
 * Exported functions
 * ---------------------------------------------------------------------------*/

/*******************************************************************************
 * Initialises accelerometer data analysis module.
 *
 * @param[in]  states  Pointer to states structure.
 ******************************************************************************/
void accel_proc_init(accel_proc_t *states)
{
    states->cnt_init_samples = NR_INIT_SAMPLES;
    states->lev_accel = 0;
    states->filt_axis.x = 0;
    states->filt_axis.y = 0;
    states->filt_axis.z = 0;
}


/*******************************************************************************
 * Process accelerometer data.
 *
 * Algorithms:
 *     * vibrations level estimation;
 *     * pitch, roll and heave estimation;
 *
 * @param[in]  states   Pointer to states structure.
 * @param[in]  samples  Pointer to accelerometer samples vector.
 * @param[in]  len      Length on accelerometer samples vector.
 ******************************************************************************/
void accel_proc_process(accel_proc_t *states, accel_sample_t *samples,
                            int len)
{
    int n;
    int32_t lev_vibr;


    /* Process all samples */
    for (n = 0;  n < len; n++) {

        /* Estimate total acceleration level */
        lev_vibr = (int32_t)sc_sqrt_u64(sc_sqr_long_s32(samples[n].x) +
                                        sc_sqr_long_s32(samples[n].y) +
                                        sc_sqr_long_s32(samples[n].z));

        /* Exclude gravity */
        lev_vibr = abs(lev_vibr - CONST(1.0));

        /* Average result using EMA */
        if (states->cnt_init_samples == NR_INIT_SAMPLES) {
            /* Initialise value */
            states->lev_accel = lev_vibr;
        } else {
            /* Average */
            states->lev_accel =
                sc_ema_s32(states->lev_accel, lev_vibr, ALPHA_LEV_VIBR, RADIX);
        }

        /* Filter accelerometer axis data, using EMA */
        if (states->cnt_init_samples == NR_INIT_SAMPLES) {
            /* Initialise value */
            states->filt_axis.x = samples[n].x;
            states->filt_axis.y = samples[n].y;
            states->filt_axis.z = samples[n].z;
        } else {
            /* Filter */
            states->filt_axis.x =
                sc_ema_s32(states->filt_axis.x, samples[n].x,
                           ALPHA_FILT_ACCEL, RADIX);
            states->filt_axis.y =
                sc_ema_s32(states->filt_axis.y, samples[n].y,
                           ALPHA_FILT_ACCEL, RADIX);
            states->filt_axis.z =
                sc_ema_s32(states->filt_axis.z, samples[n].z,
                           ALPHA_FILT_ACCEL, RADIX);
        }

        /* Update initialisation samples count-down counter */
        if (states->cnt_init_samples > 0) {
            states->cnt_init_samples--;
        }
    }
}


/*******************************************************************************
 * Gets total acceleration level, in m/s2
 *
 * @param[in]  states  Pointer to states structure.
 *
 * @return             Total acceleration level, in m/s2.
 ******************************************************************************/
int32_t accel_proc_get_lev_accel(accel_proc_t *states)
{
    return states->lev_accel;
}


/*******************************************************************************
 * Gets accelerometer pitch, roll and heave angles, in radians.
 *
 * Reference: https://www.nxp.com/files/sensors/doc/app_note/AN3461.pdf
 *
 * @param[in]   states  Pointer to states structure.
 * @param[out]  angles  Accelerometer angles sample, in radians.
 ******************************************************************************/
void accel_proc_get_pitch_roll_heave(accel_proc_t *states,
                                     accel_angles_t *angles)
{
    int32_t tmp;

    /* Split by axis */
    int32_t x = states->filt_axis.x;
    int32_t y = states->filt_axis.y;
    int32_t z = states->filt_axis.z;

    /* Estimate pitch */
    tmp = (int32_t)sc_sqrt_u64(sc_sqr_long_s32(y) + sc_sqr_long_s32(z));
    angles->pitch = sc_atan2_s32(x, tmp, RADIX);

    /* Estimate roll */
    tmp = (int32_t)sc_sqrt_u64(sc_sqr_long_s32(x) + sc_sqr_long_s32(z));
    angles->roll = sc_atan2_s32(y, tmp, RADIX);

    /* Estimate heave */
    tmp = (int32_t)sc_sqrt_u64(sc_sqr_long_s32(x) + sc_sqr_long_s32(y));
    angles->heave = sc_atan2_s32(z, tmp, RADIX);
}
