#include <stdio.h>
#include <stdlib.h>
#include <dlist.h>


// Create Node
dlist_t *dl_create_node(int value)
{
	// allocate memory
	dlist_t *new = malloc(sizeof(dlist_t));

	// store value
	new->data = value;

	// make structure ptr NULL
	new->next = NULL;
	new->prev = NULL;

	// return address
	return new;
}


// Insert first
void dl_insert_first(dlist_t **head, int value)
{
	// No list then create a node
	if (*head == NULL)
	{
		*head = dl_create_node(value);
	}

	// Create node and update the head
	else
	{
		dlist_t *new = dl_create_node(value);

		new->next = *head;

		(*head)->prev = new;

		*head = new;
	}
}


// Insert last
void dl_insert_last(dlist_t **head, int value)
{
	// No list then create a node
	if (*head == NULL)
	{		
		*head = dl_create_node(value);
	}

	// Create node and insert after last node
	else
	{
		dlist_t *new = dl_create_node(value);

		dlist_t *ptr = *head;

		// get the last node
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}

		// insert the new node at last
		ptr->next = new;

		new->prev = ptr;
	}
}


// Print list
void dl_print_list(dlist_t *head)
{
	// Error print
	if (head == NULL)

		printf("No list is present\n");
	
	else
	{
		dlist_t *ptr = head;

		// print data upto ptr become null
		while (ptr != NULL)
		{
			printf("%d\t", ptr->data);

			ptr = ptr->next;
		}

		printf("\n");
	}
}


// Delete first
void dl_delete_first(dlist_t **head)
{
	// Error print
	if (*head == NULL)

		printf("No list is present\n");

	// Delete header node and update the new header
	else
	{
		dlist_t *ptr = *head;

		*head = (*head)->next;

		free(ptr);	

		if (*head != NULL)

			(*head)->prev = NULL;
	}
}


// Delete last 
void dl_delete_last(dlist_t **head)
{
	// Error print
	if (*head == NULL)

		printf("No list is present\n");

	// get the last node and delete and also make the previous node null
	else
	{
		dlist_t *ptr = *head;

		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}

		if (ptr != *head)
			
			ptr->prev->next = NULL;

		else

			*head = NULL;

		free(ptr);
	}
}


// Insert after
void dl_insert_after(dlist_t **head, int element, int value)
{
	// Error print
	if (*head == NULL)

		printf("No list is present\n");

	else
	{
		dlist_t *ptr = *head;

		// find element position
		while (ptr != NULL && ptr->data != element)

			ptr = ptr->next;

		// print error if element is not found
		if (ptr == NULL)

			printf("Element is not found\n");
		
		// create new node and insert after the find position
		else
		{
			dlist_t *new = dl_create_node(value);

			new->prev = ptr;

			new->next = ptr->next;

			ptr->next = new;

			if (new->next != NULL)
		
				new->next->prev = new;
		}	
	}
}


// Insert before
void dl_insert_before(dlist_t **head, int element, int value)
{
	// Error print
	if (*head == NULL)

		printf("No list is present\n");

	else
	{
		dlist_t *ptr = *head;

		// find element position
		while (ptr != NULL && ptr->data != element)

			ptr = ptr->next;

		// print error if element is not found
		if (ptr == NULL)

			printf("Element is not found\n");
		
		// create new node and insert before the element position
		else
		{
			dlist_t *new = dl_create_node(value);

			if (ptr != *head)
			{
				new->prev = ptr->prev;

				ptr->prev->next = new;
			}

			else
			{
				*head = new;
			}
			
			new->next = ptr;

			ptr->prev = new;
		}
	}
}


// Delete element
void dl_delete_element(dlist_t **head, int element)
{
	// Error print
	if (*head == NULL)

		printf("No list is present\n");

	else
	{
		dlist_t *ptr = *head;

		// find element position
		while (ptr != NULL && ptr->data != element)

			ptr = ptr->next;

		// print error if element is not found
		if (ptr == NULL)

			printf("Element is not found\n");
		
		// delete the element 
		else
		{
			if (ptr != *head)
			{
				ptr->prev->next = ptr->next;

				if (ptr->next != NULL)
					
					ptr->next->prev = ptr->prev;
			}

			else
			{
				*head = (*head)->next;
			}

			free(ptr);
		}
	}
}


// Find node
dlist_t *dl_find_node(dlist_t *head, int element)
{
	// Error print
	if (head == NULL)

		printf("No list is present\n");

	else
	{
		dlist_t *ptr = head;

		// find element node
		while (ptr != NULL && ptr->data != element)

			ptr = ptr->next;

		// print error if element is not present
		if (ptr == NULL)

			printf("Element is not found\n");
	
		// return ptr
		else
		{
			return ptr;					
		}
	}

	return NULL;
}


// Delete list
void dl_delete_list(dlist_t **head)
{
	// print error
	if (*head == NULL)

		printf("No list is present\n");

	else
	{
		dlist_t *ptr = *head;

		// delete node upto head become null
		while (ptr != NULL)
		{
			*head = (*head)->next;

			ptr->prev = NULL;

			ptr->next = NULL;
			
			free(ptr);

			ptr = *head;
		}
	}
}


