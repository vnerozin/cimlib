/*******************************************************************************
 * Copyright (c) 2017 Vasiliy Nerozin
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE.md for details.
 ******************************************************************************/
#ifndef CSV_H
#define CSV_H


/* -----------------------------------------------------------------------------
 * Exported functions
 * ---------------------------------------------------------------------------*/

const char* csv_get_field_string(char* line, int num);

int32_t csv_get_field_int32(const char* line, int num);

double csv_get_field_double(const char* line, int num);


#endif /* CSV_H */
