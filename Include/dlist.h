#ifndef DLIST_H
#define DLIST_H

// dlist_t structure definition
typedef struct dl_node
{
	int data;

	struct dl_node *prev, *next; 

} dlist_t;

// Create node
dlist_t *dl_create_node(int val);

// Insert first
void dl_insert_first(dlist_t **head, int value);

// Insert last
void dl_insert_last(dlist_t **head, int value);

// Print list
void dl_print_list(dlist_t *head);

// Delete first
void dl_delete_first(dlist_t **head);

// Delete last
void dl_delete_last(dlist_t **head);

// Delete element
void dl_delete_element(dlist_t **head, int value);

// Insert After Element
void dl_insert_after(dlist_t **head, int element, int value);

// Insert before Element
void dl_insert_before(dlist_t **head, int element, int value);

// Find node
dlist_t *dl_find_node(dlist_t *head, int element);

// Delete list
void dl_delete_list(dlist_t **head);

// Insert nth Position
void dl_insert_nthpos(dlist_t **head, int position, int value);

// Get nth last
dlist_t *dl_get_nth_last(dlist_t *head, int num);

#endif
