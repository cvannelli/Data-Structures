/*Author: Christiano Vannelli
**Date: 02/25/16
**Description: main function that drives the to-do
**  list utilizing a heap.
*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


int main (int argc, const char * argv[])
{
  char cmd = ' ';
  char *newLine;
  DynArr* mainList = createDynArr(10);
  TaskP task;
  int priority;
  char userInput[100];
  char descript[TASK_DESC_SIZE];
  FILE *file;

  printf("\n\n** TO-DO LIST APPLICATION **\n\n");

  do
    {
      printf("Press:\n"
             "'l' to load to-do list from a file\n"
             "'s' to save to-do list to a file\n"
             "'a' to add a new task\n"
             "'g' to get the first task\n"
             "'r' to remove the first task\n"
             "'p' to print the list\n"
             "'e' to exit the program\n"
             );
      /* get input command (from the keyboard) */
      cmd = getchar();
      /* clear the trailing newline character */
      while (getchar() != '\n');

	  switch (cmd)
	  {
	  case 'l':

		  system("clear");

		  printf("Please input a file name: ");
		  /*prompts the user to input a file name*/

		  if (fgets(userInput, sizeof(userInput), stdin) != NULL)
		  {
			  newLine = strchr(userInput, '\n');
			  /* pointer newLine finds the endline character*/

			  if (newLine)
				  *newLine = '\0';
			  /*if the endline character exists, it removes it*/
		  }

		  file = fopen(userInput, "r");

		  /* opens existing file */

		  if (file == NULL)
		  {
			  fprintf(stderr, "Cannot open %s\n", userInput);
			  break;
			  
			  /* prints error message if file cannot be opened*/
		  }


		  loadList(mainList, file);
		  /* calls the loadList function*/

		  fclose(file);
		  /*closes the file*/

		  printf("The file has been loaded!\n\n");
		  /* displays that the file has been loaded*/

		  break;

	  case 's':

		  system("clear");

		  if (sizeDynArr(mainList) > 0)
		  {
			  printf("Please input a file name: ");
			  /*prompts the user to input a file name*/

			  if (fgets(userInput, sizeof(userInput), stdin) != NULL)
			  {
				  newLine = strchr(userInput, '\n');
				  /* pointer newLine finds the endline character*/

				  if (newLine)
					  *newLine = '\0';
				  /*if the endline character exists, it removes it*/
			  }

			  file = fopen(userInput, "w");
			  /* opens and writes to a new file */

			  if (file == NULL)
			  {
				  fprintf(stderr, "Cannot open %s\n", userInput);
				  break;
				  /*prints an error if file cannot be opened*/
			  }

			  saveList(mainList, file);
			  /*calls the saveList function to save the list*/

			  fclose(file);
			  /* closes the file*/

			  printf("The list has been saved! \n\n");
			  /*displays that the list has been saved*/
		  }

		  else
		  {
			  printf("Could not be saved. Your list is currently empty!\n\n");
			  /*prints if the list is empty*/
		  }

		  break;

	  case 'a':

		  system("clear");

		  printf("Please input the task's description: ");
		  /* prompts the user for input*/

		  if (fgets(descript, sizeof(descript), stdin) != NULL)
			  /* user inputs task description*/
		  {
			  newLine = strchr(descript, '\n');
			  /* pointer newLine finds the endline character*/

			  if (newLine)
				  *newLine = '\0';
			  /*if the endline character exists, it removes it*/
		  }

			 
		  do
		  {
			  printf("Please input the task's priority (0-999): ");
			  scanf("%d", &priority);

		  } while (priority > 999 && priority < 0);
		  /* user inputs a valid priority for the task*/


		  while (getchar() != '\n');
		  /* clear the trailing newline character */
		

		  task = createTask(priority, descript);
		  /*create a new task with information*/

		  addHeap(mainList, task, compare);
		  /*add the new task to the heap*/

		  printf("\nThe new task has been added to the To-Do list! \n\n");

		  break;

	  case 'g':

		  system("clear");

		  if (sizeDynArr(mainList) != 0)
		  {
			  task = (TaskP)getMinHeap(mainList);
			  printf("First task: %s\n\n", task->description);
			  /* prints the description of the first task*/
		  }
		  else
		  {
			  printf("The To-Do List is empty!!!\n\n");
			  /*prints that the list is empty*/
		  }

		  break;

	  case 'r':

		  system("clear");

		  if (sizeDynArr(mainList) > 0)
		  {
			  task = (TaskP)getMinHeap(mainList);
			  removeMinHeap(mainList, compare);

			  printf("The first task '%s' has been removed!\n\n", task->description);
			  /* removes the first task and displays a message*/

			  free(task);
			  /*frees task*/
		  }

		  else
		  {
			  printf("The To-Do List is empty!!!\n\n");
			  /* displays if the list is empty and no tasks can be removed */
		  }

		  break;

	  case 'p':
		  system("clear");

		  if (sizeDynArr(mainList) != 0)
		  {
			  printList(mainList);
			  /*prints the list*/
		  }

		  else
		  {
			  printf("The To-Do List is empty!!!\n\n");
			  /*prints statement if list is empty*/
		  }

		  break;

	  case 'e':

		  system("clear");

		  printf("Now exiting program!\n\n");
		  break;

	  default:

		  printf("Please enter a valid command!\n\n");
		  break;
	  }
    }
  while(cmd != 'e');
  /* delete the list */
  deleteDynArr(mainList);

  return 0;
}