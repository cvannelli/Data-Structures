/*Author: Christiano Vannelli
**Date: 01-22-16
**Description: contains functions for stack application
*/


/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"
#include <assert.h>


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post: returns 1 if balanced, 0 if not	
*/
int isBalanced(char* s)
{
	assert(s != 0);
	/* asserts that s is not NULL*/

	DynArr *balanceStack = newDynArr(4);
	/* creates a new stack the size of 4*/

	char x;
	int status = 1;
	/* variables for the character and a flag for the status
	** of stack
	*/

	while (x != '\0' && status == 1)
	{
		x = nextChar(s);
		/* x = the next character in the string
		** each iteration of the while-loop
		*/

		switch (x)
		{
		case '(':
			pushDynArr(balanceStack, ')');
			break;

		case '[':
			pushDynArr(balanceStack, ']');
			break;

		case '{':
			pushDynArr(balanceStack, '}');
			break;

		/* if an open parenthesis is found, then a 
		** closed parenthesis is pushed to the stack
		*/

		case ')':
			if ((!isEmptyDynArr(balanceStack))
				&& x == topDynArr(balanceStack) )
			{
				popDynArr(balanceStack);
				/* pops the closed parenthesis off
				** the stack if x matches the top
				** of the stack and the stack is 
				** not empty
				*/

			}
			else
			{
				status = 0;
				/* breaks the while-loop, meaning the
				** string is not balanced
				*/
			}
			break;

		case ']':
			if ((!isEmptyDynArr(balanceStack)) 
				&& x == topDynArr(balanceStack))
			{
				popDynArr(balanceStack);
				/* pops the closed bracket off
				** the stack if x matches the top
				** of the stack and the stack is
				** not empty
				*/
			}
			else
			{
				status = 0;
				/* breaks the while-loop, meaning the
				** string is not balanced
				*/
			}
			break;

		case '}':
			if ((!isEmptyDynArr(balanceStack))
				&& x == topDynArr(balanceStack))
			{
				popDynArr(balanceStack);
				/* pops the closed brace off
				** the stack if x matches the top
				** of the stack and the stack is
				** not empty
				*/
			}
			else
			{
				status = 0;
				/* breaks the while-loop, meaning the
				** string is not balanced
				*/
			}
			break;
		default:

			break;
			/* default for if non-parenthesis character is read*/
		}
	} 


	if (!(isEmptyDynArr(balanceStack)))
	{
		status = 0;
		/* if stack is not empty, then the
		** string was not balanced
		*/
	}

	deleteDynArr(balanceStack);
	/* frees up memory in the stack*/

	return status;
	/*returns 1 if stack is balanced, 0 if not*/
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	if (s == NULL)
	{
		printf("User did not input string.\n");

		return 0;
		
		/*added for testing if a string was not input*/
	}

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}