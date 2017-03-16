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
#include "csv.h"             /* CSV file functions */
#include "accel_proc.h"      /* Accelerometer data processing module */


/* -----------------------------------------------------------------------------
 * Definitions
 * ---------------------------------------------------------------------------*/

/* Accelerometer data file, format is CSV */
#define FILE_ACCEL_DATA  ("../../examples/data/accel_32hz_1k.csv")

/* Number of header lines in accelerometer data file */
#define FILE_ACCEL_DATA_NR_HEADER_LINES  (1)

/* -----------------------------------------------------------------------------
 * Functions
 * ---------------------------------------------------------------------------*/

/*******************************************************************************
 * Main function.
 *
 * @param[in]  argc  Number of input arguments.
 * @param[in]  argv  Arguments values.
 *
 * @return           Program status.
 ******************************************************************************/
int main(int argc, char** argv)
{
    int n;
    int32_t lev_vibr;
    FILE *file_csv;
    char line_csv[128];
    accel_angles_t angles;
    accel_sample_t sample;
    accel_proc_t accel_proc;


    /* Reset samples counter */
    int cnt_samples = 0;

    /* Initialise accelerometer data analysis module */
    accel_proc_init(&accel_proc);

    /* Open accelerometer data CSV file */
    file_csv = fopen(FILE_ACCEL_DATA, "r");

    /* Skip header lines from CSV file */
    for (n = 0; n < FILE_ACCEL_DATA_NR_HEADER_LINES; n++) {
        fgets(line_csv, sizeof(line_csv), file_csv);
    }

    printf("--------------------------------------------------------------\n");
    printf("| Sample | Force, m/s2 | Pitch, deg | Roll, deg | Heave, deg |\n");
    printf("--------------------------------------------------------------\n");

    /* Load accelerometer data from file.
     * [X, Y, Z] columns [2, 3, 4] */
    while (fgets(line_csv, sizeof(line_csv), file_csv)) {
        /* Load sample and convert into G from mG in fixed point format */
        sample.x = FIXED(csv_get_field_int32(line_csv, 1)) / 1000;
        sample.y = FIXED(csv_get_field_int32(line_csv, 2)) / 1000;
        sample.z = FIXED(csv_get_field_int32(line_csv, 3)) / 1000;

        /* Process sample */
        accel_proc_process(&accel_proc, &sample, 1);

        /* Get force and angles */
        lev_vibr = accel_proc_get_lev_accel(&accel_proc);
        accel_proc_get_pitch_roll_heave(&accel_proc, &angles);

        /* Print results */
        printf("| %6d | %11.8f | %10.1f | %9.1f | %10.1f |\n",
            cnt_samples,
            TO_DOUBLE(lev_vibr),
            180.0 * TO_DOUBLE(angles.pitch),
            180.0 * TO_DOUBLE(angles.roll),
            180.0 * TO_DOUBLE(angles.heave));

        /* Count samples */
        cnt_samples++;
    }

    printf("--------------------------------------------------------------\n");

    return 0;
}
