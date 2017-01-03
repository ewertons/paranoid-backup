#ifndef FILE_ATTRIBUTES_H 
#define FILE_ATTRIBUTES_H

#include <stdio.h>

typedef struct FILE_ATTRIBUTES_TAG
{
	long size_in_bytes;
	time_t create_time;
	time_t last_change_time;
	time_t last_access_time;
} FILE_ATTRIBUTES;

typedef enum FILE_ATTRIBUTES_DATE_COMPARISON_TAG
{
	FILE_DATE_OLDER,
	FILE_DATE_EQUAL,
	FILE_DATE_NEWER
} FILE_ATTRIBUTES_DATE_COMPARISON;

typedef enum FILE_ATTRIBUTES_SIZE_COMPARISON_TAG
{
	FILE_SIZE_SMALLER,
	FILE_SIZE_EQUAL,
	FILE_SIZE_LARGER
} FILE_ATTRIBUTES_SIZE_COMPARISON;

typedef struct FILE_ATTRIBUTES_COMPARISON_TAG
{
	FILE_ATTRIBUTES_DATE_COMPARISON date_created;
	FILE_ATTRIBUTES_SIZE_COMPARISON size;
} FILE_ATTRIBUTES_COMPARISON;


extern int get_file_attributes(const char* file_path, FILE_ATTRIBUTES* file_attributes);
extern int compare_file_attributes(FILE_ATTRIBUTES* fa_reference, FILE_ATTRIBUTES* fa, FILE_ATTRIBUTES_COMPARISON* comp_result);

#endif FILE_ATTRIBUTES_H
