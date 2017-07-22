#ifndef APC_H
#define APC_H

char *read_apc_inputs(void);
void slicing_data(char *string, dlist_t **head);

dlist_t *apc_addition(dlist_t *head_1, dlist_t *head_2);
dlist_t *apc_subtraction(dlist_t *head_1, dlist_t *head_2);
dlist_t *apc_multiplication(dlist_t *head_1, dlist_t *head_2);
dlist_t *apc_division(dlist_t *head_1, dlist_t *head_2);

int find_fpoint(char *string, char **wpart, char **fpart);
void f_slicing_data(char *string, dlist_t **head);
void equal_no_of_nodes_fpart(dlist_t **fhead_1, dlist_t **fhead_2);
void add_carry_towpart(dlist_t **wresult, dlist_t **fresult, dlist_t *head_1);
void borrow_from_wpart(dlist_t **wresult, dlist_t **fresult);
dlist_t *apc_fpart_subtraction(dlist_t *head_1, dlist_t *head_2);
dlist_t *new_multiplication(dlist_t *head_1, dlist_t *head_2);
void power_of_num(dlist_t *head, int limit);
dlist_t *get_quotient(dlist_t **head_1, dlist_t *head_2);
void print_dlist_string(dlist_t *head);
void print_mul_string(dlist_t *head, int f_point);

#endif
