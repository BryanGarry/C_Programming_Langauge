INSTRUCTIONS FOR BRYAN'S PROJECT 2
----------------------------------

THINGS TO KNOW:
>> The program has certain limitations to it that must be followed in order
to get proper functionality. The first and most important of which is that
the user inputs the correct format required on each line otherwise it will
result in a segmentation fault. By this I mean that if the user enters a 'v'
to define a variable, the next line must be the name of the variable and the
line after that must be the expression. This may seem straight forward but
there is no formatting checks in place currently to halt the program before
causing a fault.

>> Formatting for functions with parameters is very specific for this program.
Defining a function with parameters should work as expected, but when defining
a variable to use a function with parameters as its operation, the format
should look as follow:
	'l'
	f1
	x y
	(+ x y)
	'v'
	b12
	(f1 (###) (###))
When defining a variable with a function in it, the parameters that are to be
passed to the function must be put in their own individual set of parenthesis.
The program was made this way to help the parsing instruction determine what
the desired parameter actually is.

>> There is no 'a', 'f', or 'r' functions built into the program. I could not
figure out how to implement these functions to mesh with the rest of the
existing software.

>> Defined variables cannot be passed as parameters into functions. Each
parameter that is desired to be entered into a function must be explicitly
written out within parenthesis.
	