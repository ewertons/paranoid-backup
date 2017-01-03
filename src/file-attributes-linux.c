#include "file-attributes.h"

#define RESULT_OK 0

int get_file_attributes(const char* file_path, FILE_ATTRIBUTES* file_attributes)
{
	int result;
	FILE* file;

	if ((file = fopen(file_path, "rb")) == NULL)
	{
		result = __LINE__;
	}
	else
	{
		if (fseek(file, 0, SEEK_END) != 0)
		{
			result = __LINE__;
		}
		else
		{
			file_attributes->size_in_bytes = ftell(file);
			result = RESULT_OK;
		}

		fclose(file);
	}

	return result;
}
