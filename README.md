# DS-APC


Before Running this program in ur system:

In command line run this:
	
	export LD_LIBRARY_PATH = "/home/.../Library"

	(* in your system where your r having this Library folder give that path)


Arbitrary Precision Calculator

Introduction:

	To implement addition, subtraction, multiplication and division operations for bignum and also floating point numbers by using double linked list.

Addition:

	Step 1: Read num1 and num2
	Step 2: Count no. of nodes in num1 list and num2 list and reach the last nodes of both lists
	Step 3: Take list which is having less no. of nodes into ptr_1
	Step 4: Take another list into ptr_2
	Step 5: Add nodes and store it in value 
	Step 6: Extract the carry and add with next addition result
	Step 7: One of the list is completed add the carry with remaining nodes
	Step 8: Two list are over if carry is present the create the node and store 

Subtraction:

	Step 1: Read num1 and num2
	Step 2: Count no. of nodes in num1 list and num2 list and reach the last nodes of both lists
	Step 3: Both list having same no. of nodes then check the data, if same then return 0
	Step 4: Take list which is having larger no. of nodes into ptr_1
	Step 5: Take another list into ptr_2
	Step 6: If ptr_2 data is greater than ptr_1 data then borrow from previous node
	Step 7: Subtract nodes and store it in value in dlist
	Step 8: One of the list is completed then copy remaining nodes
	Step 9: Two list are over if sign flag is set then add ‘ - ’ in output

Multiplication:

	Step 1: Read num1 and num2
	Step 2: Count no. of nodes in num1 list and num2 list and reach the last nodes of both lists
	Step 3: Both list having same no. of nodes then check the data, if same then return 0
	Step 4: Take list which is having larger no. of nodes into ptr_1
	Step 5: Take another list into ptr_2
	Step 6: Split the ptr_2 data into two limits upto that limits call the addition function upto ptr_2 becomes null
	Step 7: Add two multiplication value and store it in output dlist

Divition:

	Get quotient :

		Step 1: Get two lists
		Step 2: Start Subtracting list2 from list1
		Step 3: when the list1 data is lessthan list2 data then stop the loop
		Step 4: return count value

	Division :

		Step 1: Get num1 and num2 lists
		Step 2: Count the no. of nodes in list1 and list2
		Step 3: Extract count_2 no. of data from list2 
		Step 4: Call the quotient function
		Step 5: Store the count value
		Step 6: Repeatedly call the quotien function and store the count value upto list 1 gets over


Advantages:

	1. Larger number basic arithmetic operations are possible
	2. Arithmentic operations on floating numbers are possible

Future Implementations:

	1. Division for very larger divedend and very small divisor is not possible (its giving killed because at some point no memory available to procedd further)

	2. Modulus and power operation

	3. This is for only 2 positive numbers, planning to do this for multiple numbers and also negative numbers








