#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlist.h>
#include <apc.h>

// Reverse string
void reverse_str(char *string)
{
	// calculate length
	int length = strlen(string), index = 0;

	char temp;

	// swapping
	while (index < length/2)
	{
		temp = string[index];

		string[index] = string[length - 1 - index];

		string[length - 1 - index] = temp;

		index++;
	}
}

// Slicing data
void slicing_data(char *string, dlist_t **head)
{
	int length = strlen(string);
	char buff[10];
	int index, value;

	// slicing the data by 9 digits
	while ((length - 1) >= 0)
	{
		// get 9 characters
		for (index = 0; index < 9 && (length - 1) >= 0; index++)
		
			buff[index] = string[--length];

		buff[index] = '\0';

		// reverse the string
		reverse_str(buff);

		// convert into value
		sscanf(buff, "%d", &value);

		// store into list
		dl_insert_first(head, value);
	}
}

// Swap list
void swap_list(dlist_t **ptr_1, dlist_t **ptr_2)
{
	dlist_t *temp = *ptr_1;

	*ptr_1 = *ptr_2;

	*ptr_2 = temp;
}

// Get carry
int get_carry(int *ptr_value)
{
	int carry;

	carry = *ptr_value / 1000000000;

	*ptr_value = *ptr_value % 1000000000;

	return carry;
}


/* APC Addition */
dlist_t *apc_addition(dlist_t *head_1, dlist_t *head_2)
{
	// head2 is null and head1 is not null then return head1
	if (head_2 == NULL && head_1 != NULL)

		return head_1;

	// head1 is null and head2 is not null then return head2
	if (head_1 == NULL && head_2 != NULL)

		return head_2;

	int carry = 0, value, count_1 = 0, count_2 = 0;

	dlist_t *ptr_1 = head_1, *ptr_2 = head_2, *head_3 = NULL;

	// to reach last node of head1
	while (ptr_1->next != NULL)
	{
		ptr_1 = ptr_1->next;

		count_1++;
	}

	// to reach last node of head2
	while (ptr_2->next != NULL)
	{
		ptr_2 = ptr_2->next;
	
		count_2++;
	}

	// any list having value 0 then return another list
	if (count_1 == 0 && head_1->data == 0)

		return head_2;

	else if (count_2 == 0 && head_2->data == 0)

		return head_1;

	// take lowest no. of node list into ptr2
	if (count_1 < count_2)
	{
		swap_list(&ptr_1, &ptr_2);
	}

	// sum node by node upto one list reaches null
	while (ptr_1 != NULL && ptr_2 != NULL)
	{
		// add both node data and carry
		value = carry + ptr_1->data + ptr_2->data;

		// get carry
		carry = get_carry(&value);

		// insert value to ans list
		dl_insert_first(&head_3, value);

		// move to prev nodes of list1 and list2
		ptr_1 = ptr_1->prev;
		ptr_2 = ptr_2->prev;
	}

	// copying remaining data upto null
	while (ptr_1 != NULL)
	{
		// add carry and node data
		value = carry + ptr_1->data;

		// get carry
		carry = get_carry(&value);

		// insert that value to ans list
		dl_insert_first(&head_3, value);

		// move to prev node
		ptr_1 = ptr_1->prev;
	}

	// at last carry is present insert that carry to ans list
	if (carry)

		dl_insert_first(&head_3, carry);

	// return ans list
	return head_3;
}


/* APC Subtraction */
dlist_t *apc_subtraction(dlist_t *head_1, dlist_t *head_2)
{
	int borrow = 1000000000, value, count_1 = 0, count_2 = 0, flag = 0;

	dlist_t *ptr_1 = head_1, *ptr_2 = head_2, *head_3 = NULL, *ptr = NULL;

	// to reach last node of list1
	while (ptr_1->next != NULL)
	{
		ptr_1 = ptr_1->next;

		count_1++;
	}

	// to reach last node of list2
	while (ptr_2->next != NULL)
	{
		ptr_2 = ptr_2->next;

		count_2++;
	}

	// no. of nodes of list1 and 2 are equal 
	if(count_1 == count_2)
	{
		dlist_t *p_1 = head_1, *p_2 = head_2;

		// both list data are equal
		while (p_1 != NULL && p_1->data == p_2->data)
		{
			p_1 = p_1->next;
			p_2 = p_2->next;			
		}		

		// the ptr reaches null then return ans as zero
		if (p_1 == NULL)
		{
			dl_insert_first(&head_3, 0);
			
			return head_3;
		}

		// which list data is maximun take that into ptr1 and set the flag
		else if (p_2->data > p_1->data)
		{
			flag = 1;
			swap_list(&ptr_1, &ptr_2);
		}
	}

	// count2 having max no. of nodes then swap ptr1 and ptr2
	if (count_1 < count_2)
	{
		flag = 1;
		swap_list(&ptr_1, &ptr_2);
	}

	// do the subtraction upto any one ptr reaches null 
	while (ptr_1 != NULL && ptr_2 != NULL)
	{
		// ptr1 data is lessthan ptr2 data then borrow
		if (ptr_1->data < ptr_2->data)
		{
			// add the borrow to ptr1 data
			ptr_1->data = ptr_1->data + borrow;

			// subtract 1 from the prev data
			if (ptr_1->prev != NULL)
			{
				ptr_1->prev->data = ptr_1->prev->data - 1;
			}
		}

		// subtracted result
		value = ptr_1->data - ptr_2->data;

		// insert result to res list
		dl_insert_first(&head_3, value);

		// move ptr1 and ptr2 to prev nodes
		ptr_1 = ptr_1->prev;
		ptr_2 = ptr_2->prev;
	}

	// copying remaining data upto ptr1 prev reaches null
	while (ptr_1 != NULL)
	{
		dl_insert_first(&head_3, ptr_1->data);

		ptr_1 = ptr_1->prev;
	}

	while (head_3 != NULL && head_3->data == 0)
	{
		ptr = head_3;

		head_3 = head_3->next;

		head_3->prev = NULL;

		free(ptr);
	}
	
	if (flag)

		head_3->data = head_3->data * -1;

	// return result list
	return head_3;
}

// Read APC Inputs
char *read_apc_inputs(void)
{
	char *ptr = NULL, ch;

	char array[10];

	int index = 0, count = 0, position = 0, size = 0;
	// read inputs each time 10 charcters
	while ( (ch = getchar()) )
	{
		// the character not a number then print error
		if (!('0' <= ch && ch <= '9' || ch == '.' || ch == '\n'))
		{
			printf("Invalid data\n");

			return NULL;
		}

		if (ch != '\n')
		
			array[index++] = ch;
		
		// when index reaches 10 
		if (index == 10 || ch == '\n')
		{
			array[index] = '\0';

			// calculate the prev read string size
			size = size + strlen(array);

			// reallocate memory and copy the new read data
			ptr = (char *) realloc(ptr, size + 1);

			strcpy((ptr + strlen(ptr)), array);

			ptr[size] = '\0';

			memset(array, 0, 10);

			if (ch == '\n')

				break;

			// set the index value to 0
			index = 0;
		}
	}

	ptr[size] = '\0';

	return ptr;
}

// Add zeros
void add_zeros(dlist_t **head, int limit)
{
	dlist_t *n_head = NULL, *pans = NULL;
	int index;

	// multiply that many times
	for (index = 0; index < limit; index++)
	{
		n_head = apc_addition(*head, n_head);
	}

	// update the head
	*head = n_head;
}

// Calculate the limits
void calculate_limits(int value, int *limit_1, int *limit_2)
{
	// last 5 digits
	*limit_1 = value % 100000;

	// remaining digits
	*limit_2 = value / 100000;
}


/* APC Multiplication*/
dlist_t *apc_multiplication(dlist_t *head_1, dlist_t *head_2)
{
	dlist_t *ans_1 = NULL, *ans_2 = NULL, *ans_t = NULL, *p_ans = NULL;

	dlist_t *ptr_1 = head_1, *ptr_2 = head_2, *pans = NULL;

	int count_1 = 0, count_2 = 0, count = 0, limit_1 = 0, limit_2 = 0, flag = 0, index, jdx;

	// to reach last nod of list1
	while (ptr_1->next != NULL)
	{
		ptr_1 = ptr_1->next;
		count_1++;
	}

	// to reach last nod of list2
	while (ptr_2->next != NULL)
	{
		ptr_2 = ptr_2->next;
		count_2++;
	}

	// count1 is lessthan the count2 then swap ptrs
	if (count_1 < count_2)
	{
		swap_list(&ptr_1, &ptr_2);

		ptr_1 = head_2;
	}

	// any one of the data is zero then return zero as result
	if (count_1 == 0 && head_1->data == 0)
	{
		dl_insert_first(&p_ans, 0);

		return p_ans;
	}

	else if (count_2 == 0 && head_2->data == 0)
	{
		dl_insert_first(&p_ans, 0);

		return p_ans;
	}

	// multiply upto ptr2 reaches null
	while (ptr_2 != NULL)
	{
		ans_1 = NULL, ans_2 = NULL;

		// calculate limits
		calculate_limits(ptr_2->data, &limit_1, &limit_2);	

		// multiply by limit1
		for (index = 0; index < limit_1; index++)
		{
			ans_1 = apc_addition(ptr_1, ans_1);
		}

		// multiply by limit2
		for (index = 0; index < limit_2; index++)
		{
			ans_2 = apc_addition(ptr_1, ans_2);	
		}

		// add zeros to ans2
		if (ans_2 != NULL)

			add_zeros(&ans_2, 100000);

		// add both ans found by limit1 and limit2
		ans_t = apc_addition(ans_1, ans_2);

		// flag is 1
		if (flag)
		{
			count++;

			// insert 0 value upto count
			for (jdx = 0; jdx < count; jdx++)

				dl_insert_last(&ans_t, 0);
		}

		else

			flag = 1;

		// add prev and new multiplication values
		p_ans = apc_addition(ans_t, p_ans);

		// move ptr to prev node
		ptr_2 = ptr_2->prev;
	}

	// return multiplication res
	return p_ans;
}

// Get quotient 
dlist_t *get_quotient(dlist_t **head_1, dlist_t *head_2)
{
	dlist_t *head_3 = NULL, *result = *head_1, *value = NULL, *prv_1 = NULL, *prv_2 = NULL, *p_1 = NULL, *p_2 = NULL;
	int flag = 0, count_1 = 0, count_2 = 0;
	
	dl_insert_first(&head_3, 0);
	dl_insert_first(&value, 1);

	// subtract head_1 recursively by head_2
	while (1)
	{
		prv_1 = result;

		result = apc_subtraction(result, head_2);
		dl_delete_list(&prv_1);
 
		p_1 = result, p_2 = head_2;
		
		count_1 = 0, count_2 = 0;
	
		// check the count_1 and count_2 values
		while (p_1->next != NULL)
		{
			count_1++;
			p_1 = p_1->next;
		}
		
		while (p_2->next != NULL)
		{
			count_2++;
			p_2 = p_2->next;
		}
		
		p_1 = result, p_2 = head_2;
	
		// check for valid data
		while (count_1 == count_2 && p_1 != NULL && p_2 != NULL && p_1->data == p_2->data)
		{
			p_1 = p_1->next;
			p_2 = p_2->next;
		}

		// break the loop
		if (count_1 == count_2 && p_1 != NULL && p_2 != NULL && p_1->data < p_2->data)
		
			flag = 1;
		
		else if (count_1 > count_2)

			flag = 0;

		// break the loop
		if (result != NULL && result->next == NULL && result->data == 0)
		{
			head_3 = apc_addition(head_3, value);
	
			break;
		}
		// the data is less then stop the loop
		else if (count_1 == count_2 && result != NULL && flag)

			break;

		else
		
			// count the successive subtraction
			head_3 = apc_addition(head_3, value);
	}

	*head_1 = result;

	// return count
	return head_3;
}

// APC Division
dlist_t *apc_division(dlist_t *head_1, dlist_t *head_2)
{
	dlist_t *ptr_1 = head_1, *ptr_2 = head_2, *head_3 = NULL, *q_head = NULL, *p_head = NULL, *t_head = NULL, *p_1 = NULL, *p_2 = NULL;

	int index, count_1 = 0, count_2 = 0, flag = 0;

	// count no.of nodes in list1
	while (ptr_1->next != NULL)
	{
		count_1++;

		ptr_1 = ptr_1->next;
	}

	// count no.of nodes in list2
	while (ptr_2->next != NULL)
	{
		count_2++;

		ptr_2 = ptr_2->next;
	}

	// Error print
	if (count_2 == 0 && head_2->data == 0)
	{
		printf("Error...Invalid operation\n");

		return NULL;
	}

	// return 0 if list 1 data is lessthan the list2
	if (count_1 < count_2)
	{
		dl_insert_last(&p_head, 0);

		return p_head;
	} 

	// take the valid data
	else if (count_1 == count_2)
	{
		p_1 = head_1, p_2 = head_2;

		while (p_1 != NULL && p_1->data == p_2->data)
		{
			p_1 = p_1->next;
			p_2 = p_2->next;
		}

		// return 0 if list 1 data is lessthan the list2
		if (p_1 != NULL && p_1->data < p_2->data)
		{
			dl_insert_last(&p_head, 0);

			return p_head;
		}
	}

	ptr_1 = head_1;

	// when quotient becomes 0 break the loop
	while (1)
	{
		// get list 2 no.of nodes from list 1
		for (index = 0; index <= count_2 && ptr_1 != NULL; index++)
		{
			dl_insert_last(&head_3, ptr_1->data);

			ptr_1 = ptr_1->next;
		}

		p_1 = head_3, p_2 = head_2;

		// to check the data is valid for operation
		while (p_1 != NULL && p_1->data >= p_2->data)
		{
			p_1 = p_1->next;
			p_2 = p_2->next;
		}

		// data is not valid take the next node
		if (p_1 != NULL && p_1->data < p_2->data)
		
			flag = 1;

		else

			flag = 0;

		// list 1 head  data is less than take next node too
		if (flag && ptr_1 != NULL)
		{
			dl_insert_last(&head_3, ptr_1->data);

			ptr_1 = ptr_1->next;
		}

		// get quotient function call
		q_head = get_quotient(&head_3, head_2);

		ptr_2 = q_head;

		count_1 = 0;

		// count nodes in q_head
		while (ptr_2 != NULL && ptr_2->next != NULL)
		{
			count_1++;

			ptr_2 = ptr_2->next;
		}

		// add count_1 no of zero nodes to p_head
		for (index = 0; index < count_1; index++)

			dl_insert_last(&p_head, 0);

		// add p_head and q_head
		p_head = apc_addition(p_head, q_head);
	
		// ptr_1 reaches 0 stop
		if (ptr_1 == NULL)

			break;
	}

	// return ans
	return p_head;
}


// Find floating point
int find_fpoint(char *string, char **wpart, char **fpart)
{
	int index;
	*wpart = string;

	for (index = 0; string[index] != '\0'; index++)
	{
		if (string[index] == '.')
		{
			*fpart = string + index + 1;

			string[index] = '\0';

			return strlen(*fpart);
		}
	}

	return 0;
}

// slicing data from msb
void f_slicing_data(char *string, dlist_t **head)
{
	int length = strlen(string);
	char buff[10];
	int index, value, j_index = 0;

	// slicing the data by 9 digits
	while (j_index < length)
	{
		// get 9 characters
		for (index = 0; index < 9 && j_index < length; index++)
		{
			buff[index] = string[j_index++];

			if (j_index == length && index != 8)
			{
				index++;

				while (index < 9)

					buff[index++] = '0';	
			}
		}

		buff[index] = '\0';

		// convert into value
		sscanf(buff, "%d", &value);

		// store into list
		dl_insert_last(head, value);
	}
}

// floating part equalize the no. of nodes
void equal_no_of_nodes_fpart(dlist_t **fhead_1, dlist_t **fhead_2)
{
	dlist_t *ptr_1 = *fhead_1, *ptr_2 = *fhead_2;
	int count_1 = 0, count_2 = 0;

	while (ptr_1->next != NULL)
	{
		ptr_1 = ptr_1->next;

		count_1++;
	}

	while (ptr_2->next != NULL)
	{
		ptr_2 = ptr_2->next;

		count_2++;
	}

	if (count_1 > count_2)
	{
		while (count_1 != count_2++)

			dl_insert_last(fhead_2, 0);
	}

	else if (count_1 < count_2)
	{
		while (count_2 != count_1++)

			dl_insert_last(fhead_1, 0);
	}
}

// carry from the fpart add into wpart
void add_carry_towpart(dlist_t **wresult, dlist_t **fresult, dlist_t *head)
{
	dlist_t *ptr = head, *c_list = NULL;

	int f_count = 0, count = 0;

	while (ptr->next != NULL)
	{
		count++;

		ptr = ptr->next;
	}

	ptr = *fresult;

	while (ptr->next != NULL)
	{
		f_count++;

		ptr = ptr->next;
	}

	// extract carry value
	if (f_count != count)
	{
		c_list = *fresult;

		*fresult = c_list->next;

		(*fresult)->prev = NULL;

		c_list->next = NULL;		
	}

	// addition function call
	*wresult = apc_addition(*wresult, c_list);
}

// get borrow from wpart
void borrow_from_wpart(dlist_t **wresult, dlist_t **fresult)
{
	// fraction part is negative value borrow from wpart
	if ((*fresult)->data < 0)
	{
		(*fresult)->data = (*fresult)->data * -1;

		dlist_t *ptr = *wresult;

		while (ptr->next != NULL)
		{
			ptr = ptr->next;		
		}

		if ((*wresult)->data < 0)
			ptr->data = ptr->data + 1;
		else
			ptr->data = ptr->data - 1;
	}
}

/* APC Fractional part Subtraction */
dlist_t *apc_fpart_subtraction(dlist_t *head_1, dlist_t *head_2)
{
	int borrow = 1000000000, value, count_1 = 0, count_2 = 0, flag = 0;

	dlist_t *ptr_1 = head_1, *ptr_2 = head_2, *head_3 = NULL;

	// to reach last node of list1
	while (ptr_1->next != NULL)
	
		ptr_1 = ptr_1->next;
	
	// to reach last node of list2
	while (ptr_2->next != NULL)
	
		ptr_2 = ptr_2->next;

	dlist_t *p_1 = head_1, *p_2 = head_2;

	while (p_1 != NULL && p_1->data == p_2->data)
	{
		p_1 = p_1->next;
		p_2 = p_2->next;
	}

	if (p_1 != NULL && p_1->data < p_2->data)

		flag = 1;

	// do the subtraction upto any one ptr reaches null 
	while (ptr_1 != NULL && ptr_2 != NULL)
	{
		// ptr1 data is lessthan ptr2 data then borrow
		if (ptr_1->data < ptr_2->data)
		{
			// add the borrow to ptr1 data
			ptr_1->data = ptr_1->data + borrow;

			// subtract 1 from the prev data
			if (ptr_1->prev != NULL)
			
				ptr_1->prev->data = ptr_1->prev->data - 1;
		}

		// subtracted result
		value = ptr_1->data - ptr_2->data;

		// insert result to res list
		dl_insert_first(&head_3, value);

		// move ptr1 and ptr2 to prev nodes
		ptr_1 = ptr_1->prev;
		ptr_2 = ptr_2->prev;
	}

	if (flag)

		head_3->data = head_3->data * -1; 	

	// return result list
	return head_3;
}


void print_dlist_string(dlist_t *head)
{
	if (head == NULL)

		return;

	dlist_t *ptr = head;

	int count = 0, index = 0, idx = 0, flag = 0;

	while (ptr->next != NULL)
	{
		ptr = ptr->next;

		count++;
	}

	int length = (count + 1) * 9 + 1;

	char array[length];

	while (ptr != NULL)
	{
		for (index = 0; index < 9; index++)
		{
			if (ptr->data < 0)
			{
				flag = 1;
				
				ptr->data = ptr->data * -1;
			}

			array[idx++] = ptr->data % 10 + 48;

			ptr->data = ptr->data /10;
		}
			
		ptr = ptr->prev;
	}

	if (flag)
	{
		array[idx++] = '-';
	
		flag = 0;
	}
	
	array[idx] = '\0';

	reverse_str(array);

	index = 0;

	if (array[index] == '-')
	{
		index++;
	
		flag = 1;
	}

	while (array[index] == '0')
	{
		index++;
	}

	if (flag)
	{
		array[--index] = '-';
	}

	if (array[index] == '\0')
	
		printf("0\n");

	else

		printf("%s", array + index);
}


void print_mul_string(dlist_t *head, int f_point)
{
	if (head == NULL)

		return;

	dlist_t *ptr = head;

	int count = 0, index = 0, idx = 0, flag = 0;

	while (ptr->next != NULL)
	{
		ptr = ptr->next;

		count++;
	}

	int length = (count + 1) * 9 + 1;

	char array[length];

	while (ptr != NULL)
	{
		for (index = 0; index < 9; index++)
		{
			if (ptr->data < 0)
			{
				flag = 1;
				
				ptr->data = ptr->data * -1;
			}

			if (idx != 0 && idx == f_point)

				array[idx++] = '.';
			
			array[idx++] = ptr->data % 10 + 48;

			ptr->data = ptr->data /10;
		}
			
		ptr = ptr->prev;
	}

	if (flag)
	{
		array[idx++] = '-';
	
		flag = 0;
	}

	array[idx] = '\0';

	reverse_str(array);

	index = 0;

	if (array[index] == '-')
	{
		index++;
	
		flag = 1;
	}

	while (array[index] == '0')
	{
		index++;
	}

	if (flag)
	{
		array[--index] = '-';
	}

	printf("%s\n", array + index);
}
