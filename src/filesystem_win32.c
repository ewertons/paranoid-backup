#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <strsafe.h>

#include "filesystem.h"

#ifndef RESULT_OK
#define RESULT_OK 0
#endif RESULT_OK

typedef struct FILESYSTEM_STREAM_TAG
{
	char* path;
	int count;
	HANDLE find_handle;
} FILESYSTEM_STREAM;


// Helper Functions

static char* clone_char_str(const char* str)
{
	char* clone_str;

	if (str == NULL)
	{
		clone_str = NULL;
	}
	else if ((clone_str = (char*)malloc(sizeof(char) * (strlen(str) + 1))) != NULL)
	{
		strcpy(clone_str, str);
	}

	return clone_str;
}

static time_t filetime_to_timet(FILETIME* ft)
{
	ULARGE_INTEGER ull;
	ull.LowPart = ft->dwLowDateTime;
	ull.HighPart = ft->dwHighDateTime;
	return ull.QuadPart / 10000000ULL - 11644473600ULL;
}

static int file_info_parse_from_WIN32_FIND_DATA(WIN32_FIND_DATA* find_data, FILE_INFO* file_info)
{
	int result;

	if ((file_info->filename = clone_char_str(&find_data->cFileName)) == NULL)
	{
		result = __LINE__;
	}
	else
	{
		file_info->creation_time = filetime_to_timet(&find_data->ftCreationTime);
		file_info->last_access_time = filetime_to_timet(&find_data->ftLastAccessTime);
		file_info->last_change_time = filetime_to_timet(&find_data->ftLastWriteTime);
		file_info->size_in_bytes = find_data->nFileSizeHigh * MAXDWORD + find_data->nFileSizeHigh + find_data->nFileSizeLow;

		file_info->attributes = FILE_INFO_ATTRIBUTES_NONE;
		if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) != 0)
			file_info->attributes |= FILE_INFO_ATTRIBUTE_ARCHIVE;
		if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED) != 0)
			file_info->attributes |= FILE_INFO_ATTRIBUTE_COMPRESSED;
		if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
			file_info->attributes |= FILE_INFO_ATTRIBUTE_DIRECTORY;
		if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED) != 0)
			file_info->attributes |= FILE_INFO_ATTRIBUTE_ENCRYPTED;
		if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0)
			file_info->attributes |= FILE_INFO_ATTRIBUTE_HIDDEN;
		if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_NORMAL) != 0)
			file_info->attributes |= FILE_INFO_ATTRIBUTE_NORMAL;
		if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_READONLY) != 0)
			file_info->attributes |= FILE_INFO_ATTRIBUTE_READONLY;
		if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) != 0)
			file_info->attributes |= FILE_INFO_ATTRIBUTE_REPARSE_POINT;
		if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) != 0)
			file_info->attributes |= FILE_INFO_ATTRIBUTE_SYSTEM;
		if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY) != 0)
			file_info->attributes |= FILE_INFO_ATTRIBUTE_TEMPORARY;

		result = RESULT_OK;
	}

	return result;
}

static FILE_INFO* file_info_create_from_WIN32_FIND_DATA(WIN32_FIND_DATA* find_data)
{
	FILE_INFO* file_info;

	if ((file_info = file_info_create()) != NULL)
	{
		if ((file_info->filename = clone_char_str(&find_data->cFileName)) == NULL)
		{
			file_info_destroy(file_info);
			file_info = NULL;
		}
		else
		{
			file_info->creation_time = filetime_to_timet(&find_data->ftCreationTime);
			file_info->last_access_time = filetime_to_timet(&find_data->ftLastAccessTime);
			file_info->last_change_time = filetime_to_timet(&find_data->ftLastWriteTime);
			file_info->size_in_bytes = find_data->nFileSizeHigh * MAXDWORD + find_data->nFileSizeHigh + find_data->nFileSizeLow;

			file_info->attributes = FILE_INFO_ATTRIBUTES_NONE;
			if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) != 0)
				file_info->attributes |= FILE_INFO_ATTRIBUTE_ARCHIVE;
			if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED) != 0)
				file_info->attributes |= FILE_INFO_ATTRIBUTE_COMPRESSED;
			if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
				file_info->attributes |= FILE_INFO_ATTRIBUTE_DIRECTORY;
			if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED) != 0)
				file_info->attributes |= FILE_INFO_ATTRIBUTE_ENCRYPTED;
			if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0)
				file_info->attributes |= FILE_INFO_ATTRIBUTE_HIDDEN;
			if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_NORMAL) != 0)
				file_info->attributes |= FILE_INFO_ATTRIBUTE_NORMAL;
			if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_READONLY) != 0)
				file_info->attributes |= FILE_INFO_ATTRIBUTE_READONLY;
			if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) != 0)
				file_info->attributes |= FILE_INFO_ATTRIBUTE_REPARSE_POINT;
			if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) != 0)
				file_info->attributes |= FILE_INFO_ATTRIBUTE_SYSTEM;
			if ((find_data->dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY) != 0)
				file_info->attributes |= FILE_INFO_ATTRIBUTE_TEMPORARY;
		}
	}

	return file_info;
}


// Public API

void filesystem_destroy_stream(FILESYSTEM_STREAM_HANDLE stream_handle)
{
	if (stream_handle != NULL)
	{
		FILESYSTEM_STREAM* stream = (FILESYSTEM_STREAM*)stream_handle;
		
		if (stream->find_handle != NULL)
		{
			FindClose(stream->find_handle);
		}
		free(stream->path);
		free(stream);
	}
}

int filesystem_create_stream(const char* path, FILESYSTEM_STREAM_HANDLE* stream_handle)
{
	int result;

	if (path == NULL || stream_handle == NULL)
	{
		result = __LINE__;
	}
	else
	{
		FILESYSTEM_STREAM* fss;

		if ((fss = (FILESYSTEM_STREAM*)malloc(sizeof(FILESYSTEM_STREAM))) == NULL)
		{
			result = __LINE__;
		}
		else if ((fss->path = clone_char_str(path)) == NULL)
		{
			result = __LINE__;
		}
		else
		{
			fss->find_handle = NULL;
			fss->count = 0;
			*stream_handle = (FILESYSTEM_STREAM_HANDLE)fss;
			result = RESULT_OK;
		}

		if (result != RESULT_OK)
		{
			filesystem_destroy_stream(fss);
		}
	}

	return result;
}

FS_READ_NEXT_RESULT filesystem_read_next(FILESYSTEM_STREAM_HANDLE stream_handle, FILE_INFO** file_info)
{
	FS_READ_NEXT_RESULT result;

	if (stream_handle == NULL || file_info == NULL)
	{
		result = FS_READ_NEXT_RESULT_INVALID_ARG;
	}
	else
	{
		FILESYSTEM_STREAM* stream = (FILESYSTEM_STREAM*)stream_handle;

		WIN32_FIND_DATA find_file_data;
		int file_found = 0;

		if (stream->find_handle == NULL)
		{
			TCHAR szDir[MAX_PATH];
			StringCchCopy(szDir, MAX_PATH, stream->path);
			StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

			if ((stream->find_handle = FindFirstFile(szDir, &find_file_data)) != INVALID_HANDLE_VALUE)
			{
				file_found = 1;
			}
		}
		else
		{
			if (FindNextFile(stream->find_handle, &find_file_data) != 0)
			{
				file_found = 1;
			}
		}

		if (file_found)
		{
			stream->count++;

			if ((*file_info = file_info_create_from_WIN32_FIND_DATA(&find_file_data)) == NULL)
			{
				result = FS_READ_NEXT_RESULT_FAILED_PARSING_FILE_INFO;
			}
			else
			{
				result = FS_READ_NEXT_RESULT_FILE_ITEM_FOUND;
			}
		}
		else
		{
			switch (GetLastError())
			{
				case ERROR_NO_MORE_FILES:
				default:
					result = FS_READ_NEXT_RESULT_NO_MORE_FILES;
					break;
			}
		}
	}

	return result;
}