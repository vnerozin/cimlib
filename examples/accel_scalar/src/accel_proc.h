/*******************************************************************************
 * Copyright (c) 2017 Vasiliy Nerozin
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE.md for details.
 ******************************************************************************/
#ifndef ACCEL_PROC_H
#define ACCEL_PROC_H


/* -----------------------------------------------------------------------------
 * Includes
 * ---------------------------------------------------------------------------*/
#include <stdbool.h>
#include "mathem.h"          /* Mathematical library */


/* -----------------------------------------------------------------------------
 * Types
 * ---------------------------------------------------------------------------*/

/** Accelerometer sample */
typedef struct {
    int32_t x;          /**< X axis sample, in G */
    int32_t y;          /**< Y axis sample, in G */
    int32_t z;          /**< Z axis sample, in G */

} accel_sample_t;


/** Accelerometer angles sample structure, in radians */
typedef struct {
    int32_t pitch;     /**< Pitch angle, in radians */
    int32_t roll;      /**< Roll angle, in radians */
    int32_t heave;     /**< Heave angle, in radians */

} accel_angles_t;


/** Accelerometer data processing module states structure */
typedef struct {
    int cnt_init_samples;         /**< Initialisation samples count-down counter */
    int32_t lev_accel;            /**< Total acceleration level, m/s2 */
    accel_sample_t filt_axis;     /**< Filtered accelerometer axis */

} accel_proc_t;


/* -----------------------------------------------------------------------------
 * Exported functions
 * ---------------------------------------------------------------------------*/

void accel_proc_init(accel_proc_t *states);

void accel_proc_process(accel_proc_t *states, accel_sample_t *samples, int len);

int32_t accel_proc_get_lev_accel(accel_proc_t *states);

void accel_proc_get_pitch_roll_heave(accel_proc_t *states,
                                     accel_angles_t *angles);

#endif /* ACCEL_PROC_H */
