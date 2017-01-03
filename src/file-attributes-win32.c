#include "file-attributes.h"
#include <sys/stat.h>
#include <time.h>

#define RESULT_OK 0

int get_file_attributes(const char* file_path, FILE_ATTRIBUTES* file_attributes)
{
	int result;
	struct stat stat_struct;

	if (stat(file_path, &stat_struct) != RESULT_OK)
	{
		result = __LINE__;
	}
	else
	{
		file_attributes->size_in_bytes = stat_struct.st_size;
		file_attributes->create_time = stat_struct.st_ctime;
		file_attributes->last_change_time = stat_struct.st_mtime;
		file_attributes->last_access_time = stat_struct.st_atime;
		result = RESULT_OK;
	}

	return result;
}

int compare_file_attributes(FILE_ATTRIBUTES* fa_reference, FILE_ATTRIBUTES* fa, FILE_ATTRIBUTES_COMPARISON* comp_result)
{
	int result;

	if (fa_reference == NULL || fa == NULL|| comp_result == NULL)
	{
		result = __LINE__;
	}
	else
	{
		double create_time_diff = difftime(fa_reference->create_time, fa->create_time);

		if (create_time_diff < 0)
		{
			comp_result->date_created = FILE_DATE_NEWER;
		}
		else if (create_time_diff > 0)
		{
			comp_result->date_created = FILE_DATE_OLDER;
		}
		else
		{
			comp_result->date_created = FILE_DATE_EQUAL;
		}

		result = RESULT_OK;
	}

	return result;
}