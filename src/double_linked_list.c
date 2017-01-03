#include "double_linked_list.h"
#include <stdlib.h>

int dllist_get_count(DLLIST_NODE* head)
{
	int result = 0;

	if (head != NULL)
	{
		DLLIST_NODE* current = head->next;

		while (current != head)
		{
			result++;
			current = current->next;
		}
	}

	return result;
}

int dllist_insert_after(DLLIST_NODE* head, DLLIST_NODE* new_node)
{
	int result;

	if (head == NULL || new_node == NULL)
	{
		result = __LINE__;
	}
	else
	{
		new_node->next = head->next;
		new_node->previous = head;
		head->next->previous = new_node;
		head->next = new_node;
	}

	return result;
}

int dllist_insert_before(DLLIST_NODE* head, DLLIST_NODE* new_node)
{
	int result;

	if (head == NULL || new_node == NULL)
	{
		result = __LINE__;
	}
	else
	{
		new_node->next = head;
		new_node->previous = head->previous;
		head->previous->next = new_node;
		head->previous = new_node;
	}

	return result;
}

DLLIST_NODE* dllist_remove(DLLIST_NODE* node)
{
	DLLIST_NODE* removed_node;

	if (node == NULL || dllist_get_count(node) <= 1)
	{
		removed_node = NULL;
	}
	else
	{
		node->next->previous = node->previous;
		node->previous->next = node->next;
		node->previous = node->next = NULL;
		removed_node = node;
	}

	return removed_node;
}
