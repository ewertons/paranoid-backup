#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "file_info.h"

typedef struct FILESYSTEM_STREAM_TAG* FILESYSTEM_STREAM_HANDLE;

typedef enum FS_READ_NEXT_RESULT_TAG
{
	FS_READ_NEXT_RESULT_INVALID_ARG,
	FS_READ_NEXT_RESULT_FILE_ITEM_FOUND,
	FS_READ_NEXT_RESULT_NO_MORE_FILES,
	FS_READ_NEXT_RESULT_FAILED_PARSING_FILE_INFO
} FS_READ_NEXT_RESULT;

extern int filesystem_create_stream(const char* path, FILESYSTEM_STREAM_HANDLE* stream_handle);
extern FS_READ_NEXT_RESULT filesystem_read_next(FILESYSTEM_STREAM_HANDLE stream_handle, FILE_INFO** file_info);
extern void filesystem_destroy_stream(FILESYSTEM_STREAM_HANDLE stream_handle);

#endif FILESYSTEM_H