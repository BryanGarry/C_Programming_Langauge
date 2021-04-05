#include <stdlib.h>
#include <stdio.h>
#include "Exp.h"

int main() {
	
	// Define a character input variable to be able to take in user input
	char m_string[100];
	char m_input;

	// Define an integer to determine if the program should continue running
	int running;
	running = 1;

	// Define an expression that the user will be interacting with
	//Exp* user_expression;

	// Define a list that will act as the programs symbol table
	List* symbol_table;
	symbol_table = createList();

	// Set up an introdcutory message to the program
	printf("\n___WELCOME TO BRYAN'S PROJECT 2___\n\n");

	printf("For instructions on the program itself and its capablilites, \nplease see the README.txt file\n\n");
	
	// Set up a message to tell the user how to use the program
	printf("INSTRUCTIONS:\n");
	printf("'c' : create a new experssion in the variable 'foo'\n");
	printf("'v' : define a variable\n");
	printf("'d' : define a function without parameters\n");
	printf("'l' : define a function with parameters\n");
	printf("'p' : print a variable / function\n");
	printf("'e' : evaluate a variable / function\n");
	printf("'q' : exit the program\n\n");
	printf("------------------------------------------------------------\n");

	// Set up a loop that continually runs the program until the user decides to quit the program.
	while(running == 1) {
		
		// Read input from the user and then execute the desired instruction. I have this 
		// extra step of only comparing the first char of the entered string in order to 
		// prevent unecessary loops from occuring in the program
		//
		//printf("PLEASE ENTER AN INSTRUCTION: ");
		scanf("%[^\n]%*c", m_string);
		m_input = m_string[0];

		if (m_string[1] != '\0') { // Prompts the user telling them their input is invalid if it is more than a single character
			printf("*INVALID INPUT, PLEASE TRY AGAIN*\n\n");
		} else if (m_input == 'c') { // Create the default variable foo
			declareFOO(symbol_table);
		} else if (m_input == 'p') { // Print the current expression
			print(symbol_table);
			printf("\n");
		} else if (m_input == 'e') { // Evaluate the current expression
			evaluate(symbol_table);
		} else if (m_input == 'q') { // Exits the loop
			running = 0;
			break;
		} else if (m_input == 'v') { // Declare a variable
			declareVariable(symbol_table);	
		} else if (m_input == 'd') { // Define a parameterless function
			declareVariable(symbol_table);
		} else if (m_input == 'l') { // Define a function with parameters
			declareFunction(symbol_table);
		} else { // Prompts the user telling them their input is invalid and resets the loop
			printf("*INVALID INPUT, PLEASE TRY AGAIN*\n\n");
		}
	}
	return 0;
}
