#ifndef FILE_INFO_H
#define FILE_INFO_H

#include <time.h>
#include <limits.h>

typedef enum FILE_INFO_ATTRIBUTES_TAG
{
	FILE_INFO_ATTRIBUTES_NONE =           0,
	FILE_INFO_ATTRIBUTE_ARCHIVE =         1,
	FILE_INFO_ATTRIBUTE_COMPRESSED =      2,
	FILE_INFO_ATTRIBUTE_DIRECTORY =       4,
	FILE_INFO_ATTRIBUTE_ENCRYPTED =       8,
	FILE_INFO_ATTRIBUTE_HIDDEN =         16,
	FILE_INFO_ATTRIBUTE_NORMAL =         32,
	FILE_INFO_ATTRIBUTE_READONLY =       64,
	FILE_INFO_ATTRIBUTE_REPARSE_POINT = 128,
	FILE_INFO_ATTRIBUTE_SYSTEM =        256,
	FILE_INFO_ATTRIBUTE_TEMPORARY =     512
} FILE_INFO_ATTRIBUTES;

typedef struct FILE_INFO_TAG
{
	char* filename;
	time_t creation_time;
	time_t last_change_time;
	time_t last_access_time;
	unsigned long long size_in_bytes;
	FILE_INFO_ATTRIBUTES attributes;
} FILE_INFO;

extern FILE_INFO* file_info_create();
extern void file_info_destroy(FILE_INFO* file_info);

#endif FILE_INFO_H
