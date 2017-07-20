#include <stdio.h>
#include <string.h>
#include <dlist.h>
#include <apc.h>

/************************************************* APC ***************************************************************/

int main()
{
	// declarations
	char *num_1 = NULL, *num_2 = NULL, ch, *wpart_1 = NULL,*wpart_2 = NULL, *fpart_1 = NULL, *fpart_2 = NULL; 
	int operator, flag = 1, value_1 = 0, value_2 = 0, length = 0, sign_1 = 0, sign_2 = 0;
	dlist_t *head_1 = NULL, *head_2 = NULL, *result = NULL, *whead_1 = NULL, *whead_2 = NULL, *fhead_1 = NULL, *fhead_2 = NULL, *fresult = NULL, *wresult = NULL;

	do
	{
		head_1 = NULL, head_2 = NULL, num_1 = NULL, num_2 = NULL, result = NULL;
		whead_1 = NULL, whead_2 = NULL, fhead_1 = NULL, fhead_2 = NULL, fresult = NULL, wresult = NULL;

		// print options to user
		printf("OPTIONS :\n\t1. Addition\n\t2. Subtraction\n\t3. Multiplication\n\t4. Division\n\n");

		// read option
		printf("Enter the option : ");
		scanf("%d", &operator);

		// read num1
		getchar();
		printf("\n\nEnter the number 1: \n");
		num_1 = read_apc_inputs();

		if (num_1 == NULL)
		{
			return 0;
		}
		
		// read num2
		printf("\nEnter the number 2: \n");
		num_2 = read_apc_inputs();

		// error termination
		if (num_2 == NULL)
		{
			return 0;
		}
		
		// finding the floating point in string1
		value_1 = find_fpoint(num_1, &wpart_1, &fpart_1);

		// finding the floating point in string2
		value_2 = find_fpoint(num_2, &wpart_2, &fpart_2);

		// removing zeros
		if ((value_1 || value_2) && operator == 3)
		{
			strcat(wpart_1, fpart_1);	
			strcat(wpart_2, fpart_2);

			length = strlen(wpart_1);

			while (wpart_1[--length] == '0')
			{
				value_1--;
			}

			wpart_1[length + 1] = '\0';
			
			length = strlen(wpart_2);

			while (wpart_2[--length] == '0')
			{
				value_2--;
			}

			wpart_2[length + 1] = '\0';
			
			slicing_data(wpart_1, &head_1);
			slicing_data(wpart_2, &head_2);
		}
		
		// floating point number
		else if (value_1 || value_2)
		{
			// slicing the whole number part
			slicing_data(wpart_1, &whead_1);
			slicing_data(wpart_2, &whead_2);

			// slicing the fraction part
			f_slicing_data(fpart_1, &fhead_1);
			f_slicing_data(fpart_2, &fhead_2);

			// make equal no.of nodes in fractional list
			equal_no_of_nodes_fpart(&fhead_1, &fhead_2);

			flag = 0;
		}

		// integers
		else
		{
			flag = 1;

			// slicing num1
			slicing_data(num_1, &head_1);

			// slicing num2
			slicing_data(num_2, &head_2);
		}

		// choose the operation
		switch(operator)
		{
			// Addition
			case 1:

				// integers
				if (flag)
				{
					result = apc_addition(head_1, head_2);

					// print the result
					print_dlist_string(result);
				}

				// floating point number
				else
				{
					// whole number addition
					wresult = apc_addition(whead_1, whead_2);

					// fractional number addition
					fresult = apc_addition(fhead_1, fhead_2);

					add_carry_towpart(&wresult, &fresult, fhead_1);

					// print the result
					print_dlist_string(wresult);
					printf(".");
					print_dlist_string(fresult);
				}

				printf("\n");

				break;

			// Subtraction
			case 2:

				// integers
				if (flag)
				{
					result = apc_subtraction(head_1, head_2);

					// print the result
					print_dlist_string(result);
				}

				// floating point number
				else
				{
					// whole number subtraction
					wresult = apc_subtraction(whead_1, whead_2);

					// fractional number subtraction
					if (wresult->data < 0)

						fresult = apc_fpart_subtraction(fhead_2, fhead_1);
					else	

						fresult = apc_fpart_subtraction(fhead_1, fhead_2);

					borrow_from_wpart(&wresult, &fresult);

					// print the result
					print_dlist_string(wresult);
					printf(".");
					print_dlist_string(fresult);
				}

				printf("\n");

				break;

			// Multiplication
			case 3:

				result = apc_multiplication(head_1, head_2);

				if (value_1 || value_2)

					print_mul_string(result, value_1 + value_2);

				else

					print_dlist_string(result);

				printf("\n");

				break;

			// Division
			case 4:

				result = apc_division(head_1, head_2);

				if (result != NULL)
				
					print_dlist_string(result);
				
				printf("\n");

				break;
		}

		// to continue the program
		printf("Do you want to continue(y/Y | n/N)...");
		scanf("\n%c", &ch);

		// ch y/Y restarts the program
	} while (ch == 'y' || ch == 'Y');

	return 0;
}
