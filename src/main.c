#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "filesystem.h"

#define RESULT_OK 0

int main(int argc, char** argv)
{
	FILESYSTEM_STREAM_HANDLE fsstream = NULL;

	//const char* path = "C:\\";
	const char* path = "C:\\Users\\ewertons\\paranoyd-backup";
	//const char* path = "c:\\Users\\ewertons";
	//char* path = argv[1];

	if (filesystem_create_stream(path, &fsstream) == RESULT_OK)
	{
		FILE_INFO* fi;

		while (filesystem_read_next(fsstream, &fi) == FS_READ_NEXT_RESULT_FILE_ITEM_FOUND)
		{
			if (fi->attributes & FILE_INFO_ATTRIBUTE_DIRECTORY)
			{
				printf("path\\%s; DIR\r\n", fi->filename);
			}
			else if (fi->attributes & FILE_INFO_ATTRIBUTE_ARCHIVE)
			{
				printf("path\\%s %lld bytes\r\n", fi->filename, fi->size_in_bytes);
			}

			file_info_destroy(fi);
		}

		filesystem_destroy_stream(fsstream);
	}
	
	return 0;
}