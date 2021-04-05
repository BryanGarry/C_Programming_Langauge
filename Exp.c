#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Exp.h"

// Function that is called anytime a new expression node needs to be created for the data structure
Exp* newExp() {
	Exp* node;
	node = (Exp*)malloc(sizeof(Exp));
	node->data = NULL;
	node->first = NULL;
	node->rest = NULL;
	node->prev = NULL;
}

// Function that is called when a user wants to input an expression
Exp* createExpression() {
	// Define a base expression node
	Exp* base = newExp();

	// Set up a char array to take in user expression, expression must be 100 char or less
	char user_exp[100];

	// Prompt user to enter expression and then read it in
	scanf("%[^\n]%*c", user_exp);

	// Set up a node to keep track of where we are in the expression
	Exp* current_node = (Exp*)malloc(sizeof(Exp));
      	current_node = base;

	// Call the recursive nesting function to load the char array into the data structure
	nestExpression(user_exp, base);

	// Based on the way I defined my functions, I have two extra blank nodes in the beginning of my data structure that i will chose to skip and ignore as it is unecessary
	// for the functionality of the data structure. This comes from the way I chose to create new nodes in the data structure for the beginning of new expressions.
	current_node = current_node->rest;
	current_node = current_node->first;
	current_node->prev == NULL;
	base = current_node;

	return base;
}

// Function that is called to create an expression with an exisiting char array
Exp* createExpressionWithName(char* signature) {
	// Define a base expression node
	Exp* base = newExp();

	// Set up a char array to take in user expression, expression must be 100 char or less
	char user_exp[100];
	strcpy(user_exp, signature);

	// Set up a node to keep track of where we are in the expression
	Exp* current_node = (Exp*)malloc(sizeof(Exp));
      	current_node = base;

	// Call the recursive nesting function to load the char array into the data structure
	nestExpression(user_exp, base);

	// Based on the way I defined my functions, I have two extra blank nodes in the beginning of my data structure that i will chose to skip and ignore as it is unecessary
	// for the functionality of the data structure. This comes from the way I chose to create new nodes in the data structure for the beginning of new expressions.
	current_node = current_node->rest;
	current_node = current_node->first;
	current_node->prev == NULL;
	base = current_node;

	return base;

}

// Function that is used to insert expressions into the data structure
void nestExpression(char input[], Exp* base) {

	// Define a current node to keep track of where I am in the tree and set it to the base expression
	Exp* current_node = (Exp*)malloc(sizeof(Exp));
	current_node = base;

	// Define a root expression to reference when I reach the end of an expression
	Exp* exp_root = (Exp*)malloc(sizeof(Exp));

	// Define a variable to see if the expression is the first to be inserted into the data structure
	int first_char = 1;

	// Main loop of the function that will index through the char array and insert each appropriate char in its place.
	// Also, this will take care of expressions nested within other expressions.
	for (int i = 0; input[i] != '\0'; i++) {
		// If there is a space in the char array, ignore it
		if (input[i] != ' ') {
			// If there is an open parenthesis, that signals a new expression starting 
			if (input[i] == '(') {
				// Define two blank nodes that will be used to set the proper structure for a new expression
				Exp* blank_node1 = newExp();
				Exp* blank_node2 = newExp();
			
				// Attach the first blank node to the existing data structure and move the current node
				current_node->rest = blank_node1;
				blank_node1->prev = current_node;
				current_node = current_node->rest;

				// Define what the root of the expression is to have a value to return to
				exp_root = current_node;

				// Insert the second blank node at the first pointer to signify that this is the start of an expression and not just a new value in the structure
				current_node->first = blank_node2;
				blank_node2->prev = current_node;
				current_node = current_node->first;

				// Set the variable to true for the new nested expression that is now going to be added
				first_char = 1;
			} else if (input[i] == ')') {
				// If the end of a nested expression is reached, return to the root node so that if there is any data left to insert in the upper expression it can be done
				current_node = exp_root;
			} else if (first_char == 1) {
				// Test run to get the full length of the input number
				char characters[100];
				for (int k = 0; k < 100; k++) {
					characters[k] = '\0';
				}
				int index = 0;
				while (input[i] != ' ') {
					if (input[i] == ')') {
						break;
					}
					characters[index] = input[i];
					i++;
					index++;
				}
				i--;
				
				// Special case where this is the first char being inserted into the expression and it needs to only add the data node
				insert(characters, current_node);
				first_char = 0;
			} else {
				// Test run to get the full length of the input number
				char characters[100];
				for (int k = 0; k < 100; k++) {
					characters[k] = '\0';
				}
				int index = 0;
				while (input[i] != ' ') {
					if (input[i] == ')') {
						break;
					}
					characters[index] = input[i];
					i++;
					index++;
				}
				i--;
				
				// General case where a new blank node is needed to further the expression and then add the data node onto this at the first pointer
				Exp* blank_node = newExp();
				current_node->rest = blank_node;
				blank_node->prev = current_node;
				current_node = current_node->rest;
				insert(characters, current_node);
			}
		}
	}	
}

// Function that is called when inserting an expression into the data structure
void insert(char x[], Exp* base) {
	Exp* new_node = newExp();
	char* char_array = malloc(100 * sizeof(char));
	strcpy(char_array, x);
	new_node->data = char_array;
	new_node->prev = base;
	base->first = new_node;
}

// Function that is called when a user wants to print an expression, i wrote it to act as a recursive InOrder traversal through a binary tree
void printExpression(Exp* exp, List* table) {
	// Checks to see if the current expression is NULL;
	if (exp == NULL) {
		return;
	}

	// First recursion on the first pointer
	printExpression(exp->first, table);

	// Print data of expression if not NULL
	if (exp->data != NULL) {
		// Check to see if any nodes contain a function definition
		int is_funct = 0;
		is_funct = inTable(exp->data, table);

		// This prints the expression back in a readable format from that data structure
		if (is_funct == 1) {
			printf(" (%s", exp->data);
		} else if (*(exp->data) == '+' || *(exp->data) == '-' || *(exp->data) == '*') {
			printf(" (%s", exp->data);
		} else {
			printf(" %s", exp->data);
		}
	}

	// Second recursion on the rest pointer
	printExpression(exp->rest, table);


	// Check to see if at the end of an expression and then insert a closing )
	if (exp->data == NULL) {
		if (exp->rest == NULL) {
			printf(")");
		}
	}
}

// Function that recusively evaluates the expression and returns the result
int basicEval(Exp* exp, List* table) {
	// Set up a current_node pointer to traverse through the data structure
	Exp* current_node = (Exp*)malloc(sizeof(Exp));
	current_node = exp;

	// Check to see if the operation is a function or just a basic operation
	if (inTable(current_node->first->data, table) == 1) {
		// If in this branch that means there are parameters which need to be loaded into the local function parameter list
		// This will load the function definition that is stored in the symbol table
		ListNode* funct_node = newListNode();
		funct_node = searchNameST(current_node->first->data, table);

		// Index through the expression to the parameters now
		current_node = current_node->rest;

		// Set up a delimiter to go through the parameter of the function
		char* copy = malloc(100 * sizeof(char));
		strcpy(copy, funct_node->parameters);
		char* ptr = strtok(copy, " ");
		
		// Loop through the parameter list and set values for each parameter until there a no parameters left
		while(ptr != NULL) {
			// Find the parameter in the local symbol table and update its value 
			ListNode* tmp_node = newListNode();
			tmp_node = searchNameST(ptr, funct_node->param_table);
			tmp_node->exp = current_node->first;
			ptr = strtok(NULL, " ");
			current_node = current_node->rest;
		}

		// Now that the parameters are set, call the basicEval function again with the actual expression 
		return basicEval(funct_node->exp, funct_node->param_table);	
	} else {
		// Set up some values to put the evaluation into
		int sum = 0;
		int difference = 0;
		int product = 1;

		// For the difference, need a parameter to tell which value to subtract from
		int first_value = 1;

		// Find the desired operator
		char operator = '\0';
		if (*(current_node->first->data) == '+' || *(current_node->first->data) == '-' || *(current_node->first->data) == '*') {
			operator = *(current_node->first->data);
		}
		current_node = current_node->rest;

		// Value to tell when the end of an expression has been reached
		int end = 0;

		// Loop continuously through this level of the data structure until reaching the end and then return the total value.
		// If there is another expression nested within this expression the function will be called again and return the value of 
		// the nested expression for the calculation of the upper expression.
		while (end != 1) {
			if (operator == '+') {
				if (current_node->first->data == NULL) {
					sum = sum + basicEval(current_node->first, table);
				} else {
					// Check to see if the operand being added is a number or another variable
					if (inTable(current_node->first->data, table) == 1) {
						// Get the variable node and call the basicEval function on it
						ListNode* list_node = newListNode();
						list_node = searchNameST(current_node->first->data, table);
						sum = sum + basicEval(list_node->exp, table);
					} else {
						// Add numbers the usual way, these few lines break up numbers that are more than one digit	
						char number[100];
						for (int k = 0; k < 100; k++) {
							number[k] = '\0';
						}
						strcpy(number, current_node->first->data);
						int tmp = 0;
						int index = 0;
						while (number[index] != '\0') {
							tmp = (10 * tmp) + ((int)number[index] - 48);
							index++;
						}
						sum = sum + tmp;
					}
				}
			}
			if (operator == '-') {
				if (current_node->first->data == NULL) {
					difference = difference - basicEval(current_node->first, table);
				} else {
					if (current_node->rest ==  NULL && first_value) {
						if (inTable(current_node->first->data, table) == 1) {
							// Get the variable node and call the basicEval function on it
							ListNode* list_node = newListNode();
							list_node = searchNameST(current_node->first->data, table);
							difference = 0 - basicEval(list_node->exp, table);
						} else {
							// For numbers that are more than one digit
							char number[100];
							for (int k = 0; k < 100; k++) {
								number[k] = '\0';
							}
							strcpy(number, current_node->first->data);
							int tmp = 0;
							int index = 0;
							while (number[index] != '\0') {
								tmp = (10 * tmp) + ((int)number[index] - 48);
								index++;
							}
							difference = 0 - tmp;
						}
					} else if (first_value) {
						if (inTable(current_node->first->data, table) == 1) {
							// Get the variable node and call the basicEval function on it
							ListNode* list_node = newListNode();
							list_node = searchNameST(current_node->first->data, table);
							difference = basicEval(list_node->exp, table);
						} else {
							// For numbers that are more than one digit
							char number[100];
							for (int k = 0; k < 100; k++) {
								number[k] = '\0';
							}
							strcpy(number, current_node->first->data);
							int tmp = 0;
							int index = 0;
							while (number[index] != '\0') {
								tmp = (10 * tmp) + ((int)number[index] - 48);
								index++;
							}
							difference = tmp;
							first_value = 0;
						}
					} else {
						if (inTable(current_node->first->data, table) == 1) {
							// Get the variable node and call the basicEval function on it
							ListNode* list_node = newListNode();
							list_node = searchNameST(current_node->first->data, table);
							difference = difference - basicEval(list_node->exp, table);
						} else {
							// For numbers that are more than one digit
							char number[100];
							for (int k = 0; k < 100; k++) {
								number[k] = '\0';
							}
							strcpy(number, current_node->first->data);
							int tmp = 0;
							int index = 0;
							while (number[index] != '\0') {
								tmp = (10 * tmp) + ((int)number[index] - 48);
								index++;
							}
							difference = difference - tmp;
						}
					}
				}
			}
			if (operator == '*') {
				if (current_node->first->data == NULL) {
					product = product * basicEval(current_node->first, table);
				} else {
					if (inTable(current_node->first->data, table) == 1) {
						// Get the variable node and call the basicEval function on it
						ListNode* list_node = newListNode();
						list_node = searchNameST(current_node->first->data, table);
						product = product * basicEval(list_node->exp, table);
					} else {
						// For numbers that are more than one digit
						char number[100];
						for (int k = 0; k < 100; k++) {
							number[k] = '\0';
						}
						strcpy(number, current_node->first->data);
						int tmp = 0;
						int index = 0;
						while (number[index] != '\0') {
							tmp = (10 * tmp) + ((int)number[index] - 48);
							index++;
						}
						product = product * tmp;
					}
				}
			}
			
			// Check to see if there is any other expressions to evaluate
			if (current_node->rest == NULL) {
				end = 1;
			} else {
				current_node = current_node->rest;
			}
		}

		// Return the appropriate variable depending on what operation was done. If no operation was done, just return the raw int itself
		if (operator == '+') {
			return sum;
		} else if (operator == '-') {
			return difference;
		} else if (operator == '*') {
			return product;
		} else if (operator == '\0') {
			char number[100];
			for (int k = 0; k < 100; k++) {
				number[k] = '\0';
			}
			strcpy(number, current_node->first->data);
			int tmp = 0;
			int index = 0;
			while (number[index] != '\0') {
				tmp = (10 * tmp) + ((int)number[index] - 48);
				index++;
			}
			return tmp;
		}
	}
}

/*
// Function that is called when a user wants to append an expression
void appendExpression(Exp* exp) {
	// Prompt the user to enter the expression they wish to append to the main expression
	Exp* new = (Exp*)malloc(sizeof(Exp));
	new = createExpression();

	// Define a current node to keep track of where in the data structure I am
	Exp* current_node = (Exp*)malloc(sizeof(Exp));
	current_node = exp;

	// Index through the expression until the end is reached
	while (current_node->rest != NULL) {
		current_node = current_node->rest;
	}

	// Create a blank node to add the new expression onto, set the pointers, and move current node to the blank node
	Exp* blank_node = newExp();
	current_node->rest = blank_node;
	blank_node->prev = current_node;
	current_node = current_node->rest;

	// Link the new expression onto the main expression
	current_node->first = new;
	new->prev = current_node;
}

// Function that allows for the printing of a subset of an expression
void subset(Exp* exp) {
	// Set up a char array to take in user expression, expression must be 100 char or less
	char subset_exp[100];

	// Prompt user to enter expression and then read it in
	printf("Enter subset expression: ");
	scanf("%[^\n]%*c", subset_exp);

	// Set up a current node to help keep track of where in the data structure i am
	Exp* current_node = (Exp*)malloc(sizeof(Exp));
	current_node = exp;

	// Set up a loop to index through the data structure according to the subset instructions entered to set the current node to the correct node
	for (int i = 0; subset_exp[i] != '\0'; i++) {
		if (subset_exp[i] != ' ') {
			if (subset_exp[i] == 'f') {
				if (current_node->first != NULL) {
					current_node = current_node->first;
				} else {
					printf("\n***INVALID SUBSET SPECIFICATION***\n");
				}
			}
			if (subset_exp[i] == 'r') {
				if (current_node->rest != NULL) {
					current_node = current_node->rest;
				} else {
					printf("\n***INVALID SUBSET SPECIFICATION***\n");
				}
			}
		}
	}
	
	// Call the printExpression() function on the current node
	printExpression(current_node);
}
*/

// Function that creates a list
List* createList() {
	List* list = (List*)malloc(sizeof(List));
	list->root = NULL;
	list->size = 0;
	return list;
}

// Function that creates a new list node
ListNode* newListNode() {
	ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
	new_node->next = NULL;
	new_node->name = NULL;
	new_node->exp = NULL;
	new_node->parameters = NULL;
	new_node->param_table = NULL;
	return new_node;
}

// Function that inserts an item into the list
void insertInList(List* list, ListNode* new_node) {
	// Check to see if the list has a root node
	if (list->root == NULL) {
		list->root = new_node;
		return;
	} else if (strcmp(list->root->name, new_node->name) == 0) { // Checks to see if the variable name is already defined that way it will just change what is stored in the variable
		list->root->exp = new_node->exp;	
	} else {
		insertInListRecursive(list->root, new_node); // Call recursive insert function
	}
}

// Recursive insert function that will go through and place the new node in the next available spot
void insertInListRecursive(ListNode* parent_node, ListNode* new_node) {
	// Checks to see if the variable already exists and if so it just updates the expression contained in the variable
	if (strcmp(parent_node->name, new_node->name) == 0) {
		parent_node->exp = new_node->exp;
		return;
	} else if (parent_node->next == NULL) { // Insert new variables at the end of the list
		parent_node->next = new_node;
	} else {
		insertInListRecursive(parent_node->next, new_node); // Index down the list until an open spot is found to insert the variable
	}
}

// Function that takes in the users input for a variable and stores the data accordingly
void declareVariable(List* table) {
	// Define a expression node as well as a char pointer for the variable name
	Exp* exp = newExp();
	char* var_ptr = malloc(100 * sizeof(char));

	// Set up a char array to take in user input for variable
	char var_array[100];

	// Take in user input for variable name and corresponding expression
	scanf("%[^\n]%*c", var_array);

	// Copy the input variable name to the char pointer
	strcpy(var_ptr, var_array);
	
	// Get an expression from the user to associate with this variable
	exp = createExpression();

	// Combine these parameters to make a single node to store in the list
	ListNode* new_node = newListNode();
	new_node->name = var_ptr;
	new_node->exp = exp;

	// Store the new variable in the symbol table
	insertInList(table, new_node);
}

// Function that declares a variable with a specific name
void declareVariableWithName(char* input_name, List* table) {
	// Delcare a new node to add to the list
	ListNode* new_node = newListNode();
	new_node->name = input_name;

	// Store new node in the list
	insertInList(table, new_node);
}

// Function that is called that will update the value of the foo variable
void declareFOO(List* table) {
	// Define a expression node as well as a char pointer for the variable name
	Exp* exp = newExp();
	char* var_ptr = malloc(100 * sizeof(char));

	// Set up a char array to take in user input for variable
	char var_array[100];
	var_array[0] = 'f';
	var_array[1] = 'o';
	var_array[2] = 'o';

	// Copy the input variable name to the char pointer
	strcpy(var_ptr, var_array);
	
	// Get an expression from the user to associate with this variable
	exp = createExpression();

	// Combine these parameters to make a single node to store in the list
	ListNode* new_node = newListNode();
	new_node->name = var_ptr;
	new_node->exp = exp;

	// Store the new variable in the symbol table
	insertInList(table, new_node);
}

// Function that evaluates the variable/function
void evaluate(List* table) {
	// Get the desired variable/function from the user
	ListNode* list_node = newListNode();
	list_node = searchST(table);

	// Initialize a node to keep track of the variable expression to compare to built in functions 'a', 'f', and 'r'
	Exp* current_node = newExp();
	current_node = list_node->exp;

	// Check to see if the variable exists and if it does then evaluate the expression
	if (list_node == NULL) {
		printf("VARIABLE DOES NOT EXIST\n");
		return; 
	} else {
		printf("%d\n", basicEval(list_node->exp, table));
	}
}

// Function that is called to append two expressions together
Exp* append(Exp* first_exp, Exp* second_exp) {
	// Define a current node to keep track of where in the data structure I am
	Exp* current_node = (Exp*)malloc(sizeof(Exp));
	current_node = first_exp;

	// Index through the expression until the end is reached
	while (current_node->rest != NULL) {
		current_node = current_node->rest;
	}

	// Create a blank node to add the new expression onto, set the pointers, and move current node to the blank node
	Exp* blank_node = newExp();
	current_node->rest = blank_node;
	blank_node->prev = current_node;
	current_node = current_node->rest;

	// Link the new expression onto the main expression
	current_node->first = second_exp;
	second_exp->prev = current_node;
}


// Function that prints out the expression of a variable/function
void print(List* table) {
	// Define a node that will hold the variable we wish to print
	ListNode* node = newListNode();
	node = searchST(table);

	// Check to see if the variable exists and if it does then print the expression
	if (node == NULL) {
		printf("VARIABLE DOES NOT EXIST");
		return;
	} else {
		printExpression(node->exp, table);
	}
}

// Function that is called and searches throught the symbol table to find a variable/function
ListNode* searchST(List* symbol_table) {
	// Define a table node for indexing through the symbol table
	ListNode* table_node = newListNode();
	table_node = symbol_table->root;

	// Get the desired variable/function name from the user
	char* var_ptr = malloc(100 * sizeof(char));
	char var_array[100];
	scanf("%[^\n]%*c", var_array);
	strcpy(var_ptr, var_array);

	// Loop through the symbol table until the desired node is found
	while (table_node != NULL) {
		if (strcmp(table_node->name, var_ptr) == 0) {
			break;
		}
		table_node = table_node->next;
	}
	
	// Return the node of the variable
	return table_node;
}

// Function that is called and searches throught the sumbol table to find a variable/function of a specific name
ListNode* searchNameST(char* input_name, List* symbol_table) {
	// Define a table node for indexing through the symbol table
	ListNode* table_node = newListNode();
	table_node = symbol_table->root;

	// Loop through the symbol table until the desired node is found
	while (table_node != NULL) {
		if (strcmp(table_node->name, input_name) == 0) {
			break;
		}
		table_node = table_node->next;
	}
	
	// Return the node of the variable
	return table_node;
}

// Function that declares a new function and adds it to the symbol table
void declareFunction(List* table) {
	// Define a expression node as well as a char pointer for the function name
	Exp* exp = newExp();
	char* funct_ptr = malloc(100 * sizeof(char));
	char* funct_param = malloc(100 * sizeof(char));

	// Set up char arrays to take in user input for function
	char funct_array[100];
	char funct_param_array[100];

	// Take in user input for function name and corresponding expression
	scanf("%[^\n]%*c", funct_array);

	// Copy the input function name to the char pointer
	strcpy(funct_ptr, funct_array);

	// Take in the parameters for the function
	scanf("%[^\n]%*c", funct_param_array);

	// Copt the input parameters to the char pointer
	strcpy(funct_param, funct_param_array);
	
	// Get an expression from the user to associate with this variable
	exp = createExpression();

	// Create a new local symbol table for the function
	List* local_table = createList();

	// Combine these parameters to make a single node to store in the list
	ListNode* new_node = newListNode();
	new_node->name = funct_ptr;
	new_node->parameters = funct_param;
	new_node->exp = exp;
	new_node->param_table = local_table;

	// Loop through the parameters and add them to the parameter table in the function
	char* copy = malloc(100 * sizeof(char));
	strcpy(copy, funct_param);
	char* ptr = strtok(copy, " ");
	while (ptr != NULL) {
		declareVariableWithName(ptr, new_node->param_table);
		ptr = strtok(NULL, " ");
	}
		
	//printf("%s\n", new_node->parameters);

	// Store the new variable in the symbol table
	insertInList(table, new_node);
}

// Function that searchs through the symbol table and returns 1 if the desired char* is there or 0 otherwise
int inTable(char* funct_name, List* table) {
	// Define a table node for indexing through the symbol table
	ListNode* table_node = newListNode();
	table_node = table->root;

	// Loop through the symbol table until the desired node is found
	while (table_node != NULL) {
		if (strcmp(table_node->name, funct_name) == 0) {
			break;
		}
		table_node = table_node->next;
	}

	if (table_node != NULL) {
		return 1;
	} else {
		return 0;
	}
}
