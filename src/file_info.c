#include "file_info.h"

FILE_INFO* file_info_create()
{
	FILE_INFO* file_info;
	file_info = (FILE_INFO*)malloc(sizeof(FILE_INFO));
	return file_info;
}

void file_info_destroy(FILE_INFO* file_info)
{
	if (file_info != NULL)
	{
		free(file_info->filename);
		free(file_info);
	}
}
