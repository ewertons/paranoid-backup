#ifndef FILESYSTEM_TREE_H
#define FILESYSTEM_TREE_H

#include <stdlib.h>
#include "double_linked_list.h"
#include "file_info.h"

typedef struct FS_TREE_NODE_TAG
{
	FILE_INFO* file;
	FILE_INFO* parent;
	FILE_INFO* child;
	FILE_INFO* previous;
	FILE_INFO* next;
} FS_TREE_NODE;

extern int filesystem_read(const char* path, int recursively, FS_TREE_NODE** root)
extern void filesystem_free(FS_TREE_NODE* root);

#endif FILESYSTEM_TREE_H