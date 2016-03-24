/*Author: Christiano Vannelli
**Date: 01/29/16
**Description: Implementation of a double linked list
*/

#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


/* Double Link*/
struct DLink {
	TYPE value;
	struct DLink * next;
	struct DLink * prev;
};

/* Double Linked List with Head and Tail Sentinels  */

struct linkedList{
	int size;
	struct DLink *firstLink;
	struct DLink *lastLink;
};

/*
	initList
	param lst the linkedList
	pre: lst is not null
	post: lst size is 0
*/

void _initList (struct linkedList *lst) {
  
	lst->firstLink = malloc(sizeof(struct DLink));
	assert(lst->firstLink != 0);
	
	lst->lastLink = malloc(sizeof(struct DLink));
	assert(lst->lastLink !=0);

	lst->firstLink->next = lst->lastLink;
	lst->lastLink->prev = lst->firstLink;

	lst ->firstLink->prev = 0;
	lst->lastLink->next = 0;

	lst->size = 0;

	assert(lst->size == 0);
}

/*
 createList
 param: none
 pre: none
 post: firstLink and lastLink reference sentinels
 */

struct linkedList *createLinkedList()
{
	struct linkedList *newList = malloc(sizeof(struct linkedList));
	_initList(newList);
	return(newList);
}

/*
	_addLinkBeforeBefore
	param: lst the linkedList
	param: l the  link to add before
	param: v the value to add
	pre: lst is not null
	pre: l is not null
	post: lst is not empty
*/

/* Adds Before the provided link, l */

void _addLinkBefore(struct linkedList *lst, struct DLink *l, TYPE v)
{
	assert(l != 0);
	assert(lst != 0);
	/*confirms the linkledList and DLink are not null*/

	struct DLink *newLink = (struct DLink *) malloc(sizeof(struct DLink));
	/* allocate memory for new dlink*/

	assert(newLink != 0);
	/* asserts memory has been allocated*/

	l->prev->next = newLink;
	/* sets the link previous to link's next to the new link*/

	newLink->value = v;
	/* assigns value to e*/

	newLink->next = l;
	/* sets newLink's next to point to the parameter */

	newLink->prev = l->prev;
	/* sets newLink's prev to point to the parameter's prev*/

	l->prev = newLink;
	/* sets lnk's previous to newLink*/

	lst->size++;
	/* increments the size*/

	assert(lst->size > 0);
	/* confirms the list is not empty*/
}


/*
	addFrontList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addFrontList(struct linkedList *lst, TYPE e)
{
	assert(lst != 0);
	/* confirms lst is not null*/

	_addLinkBefore(lst, lst->firstLink->next, e);
	/* calls upon function with pointer to front of list
	** and designated value as parameters
	*/

	assert(lst->size > 0);
	/* confirms size of list is greater than 1*/
}

/*
	addBackList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addBackList(struct linkedList *lst, TYPE e) {
  
	assert(lst != 0);
	/* confirms lst is not null*/

	_addLinkBefore(lst, lst->lastLink, e);
	/* calls upon function with pointer to back of list
	** and designated value as parameters
	*/

	assert(lst->size > 0);
	/* confirms size of list is greater than 1*/
}

/*
	frontList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: none
*/

TYPE frontList (struct linkedList *lst) {
	
	assert(lst != 0);
	/* confirms lst is not null*/

	assert(!isEmptyList(lst));
	/* asserts the linked list is not empty*/

	return lst->firstLink->next->value;
	/* returns the value of the front of the linked list*/
}

/*
	backList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: lst is not empty
*/

TYPE backList(struct linkedList *lst)
{
	assert(lst != 0);
	/* confirms lst is not null*/

	assert(!isEmptyList(lst));
	/* asserts the linked list is not empty*/
	
	return lst->lastLink->prev->value;
	/* returns the value of the back of the linked list*/
}

/*
	_removeLink
	param: lst the linkedList
	param: l the link to be removed
	pre: lst is not null
	pre: l is not null
	post: lst size is reduced by 1
*/

void _removeLink(struct linkedList *lst, struct DLink *l)
{

	assert(l != 0);
	assert(lst != 0);
	/*confirms the linkledList and DLink are not null*/

	l->next->prev = l->prev;
	/* sets the next link's prev to the parameter link's prev */

	l->prev->next = l->next;
	/* sets the previous link's next to the parameter link's next */

	lst->size--;
	/* decrements the size of the linked list */

	free(l);
	/* frees memory from the removed link */
}

/*
	removeFrontList
	param: lst the linkedList
	pre:lst is not null
	pre: lst is not empty
	post: size is reduced by 1
*/

void removeFrontList(struct linkedList *lst) {
   	
	assert(lst != 0);
	/* confirms lst is not null*/

	assert(!isEmptyList(lst));
	/*confirms list is not empty*/

	_removeLink(lst, lst->firstLink->next);
	/*removes the front link*/
}

/*
	removeBackList
	param: lst the linkedList
	pre: lst is not null
	pre:lst is not empty
	post: size reduced by 1
*/

void removeBackList(struct linkedList *lst)
{	
	assert(lst != 0);
	/* confirms lst is not null*/

	assert(!isEmptyList(lst));
	/*confirms list is not empty*/

	_removeLink(lst, lst->lastLink->prev);
	/*removes the last link*/
}

/*
	isEmptyList
	param: lst the linkedList
	pre: lst is not null
	post: none
*/

int isEmptyList(struct linkedList *lst) {
 	
	assert(lst != 0);
	/* asserts lst is not null*/

	if (lst->size == 0)
	{
		return 1;
		/* return 1 if list is empty*/
	}

	return 0;
	/*otherwise return 0*/
}


/* Function to print list
 Pre: lst is not null
 */
void _printList(struct linkedList* lst)
{
	assert(lst != 0);
	/* confirms lst is not null*/

	struct DLink *tempLink = lst->firstLink;
	/*temporary pointer to a DLink is created*/

	while (tempLink->next != 0)
	{
		tempLink = tempLink->next;
		printf("%d", tempLink->value);

		/*prints the value of tempLink
		**until tempLink->next == null
		*/
	}
}

/* 
	Add an item to the bag
	param: 	lst		pointer to the bag
	param: 	v		value to be added
	pre:	lst is not null
	post:	a link storing val is added to the bag
 */
void addList(struct linkedList *lst, TYPE v)
{
	assert(lst != 0);
	/*confirms lst is not null*/

	addBackList(lst, v);
	/*adds v to the back of the list*/
}

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	lst		pointer to the bag
	param:	e		the value to look for in the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	no changes to the bag
*/
int containsList (struct linkedList *lst, TYPE e) {
	
	assert(lst != 0);
	/* confirms lst is not null*/

	assert(!isEmptyList(lst));
	/*confirms list is not empty*/

	struct DLink *tempLink = lst->firstLink->next;
	/* a temporary link is created set to the front link */

	for (int i = 0; i < lst->size; i++)
	{
		if (tempLink->value == e)
		{
			return 1;
			/* returns 1 if the value matches the parameter*/
		}

		else
		{
			tempLink = tempLink->next;
			/*otherwise changes tempLink to the next link in the list*/
		}
	}

	return 0;
	/*returns 0 if the value is not found*/
}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	lst		pointer to the bag
	param:	e		the value to be removed from the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	e has been removed
	post:	size of the bag is reduced by 1
*/
void removeList (struct linkedList *lst, TYPE e) {
	
	assert(lst != 0);
	/* confirms lst is not null*/

	assert(!isEmptyList(lst));
	/*confirms list is not empty*/

	struct DLink *tempLink = lst->firstLink->next;
	/* a temporary link is created set to the front link */


	for (int i = 0; i < lst->size; i++)
	{
		if (tempLink->value == e)
		{
			_removeLink(lst, tempLink);
			/* removes the link if the value matches*/
		}

		else
		{
			tempLink = tempLink->next;
			/*otherwise changes tempLink to the next link in the list*/
		}
	}
}