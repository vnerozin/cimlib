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
#include <string.h>
#include "csv.h"             /* CSV file functions */


/*******************************************************************************
 * Gets field from CSV file string in string format.
 *
 * @param[in,out]  line  Input CSV file string, will be modified while parsing.
 * @param[in]      num   Field number.
 *
 * @return               Field from CSV file string in string format.
 ******************************************************************************/
const char* csv_get_field_string(char* line, int num)
{
    const char *tok;

    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")) {
        if (!--num) {
            return tok;
        }
    }

    return NULL;
}


/*******************************************************************************
 * Gets field from CSV file string in 'int32' format.
 *
 * @param[in]  line  Input CSV file string.
 * @param[in]  num   Field number.
 *
 * @return           Field from CSV file string in 'int32' format.
 ******************************************************************************/
int32_t csv_get_field_int32(const char* line, int num)
{
    int32_t result;

    char *tmp_str = strdup(line);
    const char *field = csv_get_field_string(tmp_str, num);

    sscanf(field, "%d", &result);

    free(tmp_str);

    return result;
}


/*******************************************************************************
 * Gets field from CSV file string in 'double' format.
 *
 * @param[in]  line  Input CSV file string.
 * @param[in]  num   Field number.
 *
 * @return           Field from CSV file string in 'double' format.
 ******************************************************************************/
double csv_get_field_double(const char* line, int num)
{
    double result;

    char *tmp_str = strdup(line);
    const char *field = csv_get_field_string(tmp_str, num);

    sscanf(field, "%lf", &result);

    free(tmp_str);

    return result;
}
