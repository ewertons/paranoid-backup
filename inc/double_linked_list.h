#ifndef DOUBLE_LINKED_LIST
#define DOUBLE_LINKED_LIST

typedef struct DLLIST_NODE_TAG
{
	DLLIST_NODE* previous;
	DLLIST_NODE* next;
} DLLIST_NODE;

#define dllist_get_node_value(address, type, field) ((type *)((uintptr_t)(address) - offsetof(type, field)))

extern int dllist_get_count(DLLIST_NODE* head);
extern int dllist_insert_after(DLLIST_NODE* head, DLLIST_NODE* new_node);
extern int dllist_insert_before(DLLIST_NODE* head, DLLIST_NODE* new_node);
extern DLLIST_NODE* dllist_remove(DLLIST_NODE* node);


#endif DOUBLE_LINKED_LIST