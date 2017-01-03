#include "filesystem_tree.h"
#include "filesystem.h"

#define RESULT_OK 0

static int filesystem_create_tree_node(FILE_INFO* fi, FS_TREE_NODE* parent, FS_TREE_NODE* previous)
{
	int result;

	FS_TREE_NODE* new_node;

	if ((new_node = (FS_TREE_NODE*)malloc(sizeof(FS_TREE_NODE))) == NULL)
	{
		result = __LINE__;
	}
	else
	{
		memset(new_node, 0, sizeof(FS_TREE_NODE));

		new_node->file = fi;
		new_node->parent = parent;
		new_node->previous = previous;
		previous->next = new_node;
		
		if (parent->child == NULL)
		{
			parent->child = new_node;
		}

		result = RESULT_OK;
	}

	return result;
}

int filesystem_read(const char* path, int recursively, FS_TREE_NODE** root)
{
	int result;

	FILESYSTEM_STREAM_HANDLE fsstream;
	
	if (filesystem_create_stream(path, &fsstream) == RESULT_OK)
	{
		FS_READ_NEXT_RESULT read_result;
		FILE_INFO* fi;
		FS_TREE_NODE* parent, *previous, *current;

		while ((read_result = filesystem_read_next(fsstream, &fi)) == FS_READ_NEXT_RESULT_FILE_ITEM_FOUND)
		{
			if (current = filesystem_create_tree_node(fi, parent, previous) != RESULT_OK)
			{
				result = __LINE__;
			}
			else
			{

			}
		}
	}
	else
	{
		root = NULL;
	}

	return result;
}

void filesystem_free(FS_TREE_NODE* root)
{

}
