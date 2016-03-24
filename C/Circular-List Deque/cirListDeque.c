/*Author: Christiano Vannelli
**Date: 01/29/16
**Description: Implementation of a circular linked deque
*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "cirListDeque.h"

/* Double Link Struture */
struct DLink {
	TYPE value;/* value of the link */
	struct DLink * next;/* pointer to the next link */
	struct DLink * prev;/* pointer to the previous link */
};

# define TYPE_SENTINEL_VALUE DBL_MAX 


/* ************************************************************************
 Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
 ************************************************************************ */

struct cirListDeque {
	int size;/* number of links in the deque */
	struct DLink *Sentinel;	/* pointer to the sentinel */
};
/* internal functions prototypes */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);



/* ************************************************************************
	Deque Functions
************************************************************************ */

/* Initialize deque.

	param: 	q		pointer to the deque
	pre:	q is not null
	post:	q->Sentinel is allocated and q->size equals zero
*/
void _initCirListDeque (struct cirListDeque *q) 
{
	assert(q != 0);
	/*confirm q is not null*/

	q->Sentinel = (struct DLink *)malloc(sizeof(struct DLink));
	/* allocates sentinel*/

	assert(q->Sentinel != 0);
	/*confirms allocation*/

	q->Sentinel->next = q->Sentinel;
	q->Sentinel->prev = q->Sentinel;
	/*sets up next and prev of the sentinel*/

	q->size = 0;
	/*size set to 0*/
}

/*
 create a new circular list deque
 
 */

struct cirListDeque *createCirListDeque()
{
	struct cirListDeque *newCL = malloc(sizeof(struct cirListDeque));
	_initCirListDeque(newCL);
	return(newCL);
}


/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{
	struct DLink *newDL = malloc(sizeof(struct DLink));
	/*allocate new DLink*/
	
	assert(newDL != 0);
	/*confirms allocation*/

	newDL->value = val;
	/*assigns value to the new DLink*/

	return newDL;
	/* returns the created DLink*/
}

/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	v		value of the new link to be added after the existing link
	pre:	q is not null
	pre: 	lnk is not null
	pre:	lnk is in the deque 
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v)
{
	assert(q != 0);
	assert(lnk != 0);
	/*confirms q and lnk are not null*/

	struct DLink *newLink = _createLink(v);
	/*creates a new link with the value from the parameter*/

	lnk->next->prev = newLink;
	/* sets the link's next's previous to the new link*/

	newLink->next = lnk->next;
	/* sets the new link's next to the existing link's next*/

	lnk->next = newLink;
	/* sets the new link after the existing link*/

	newLink->prev = lnk;
	/* sets the new link's previous to the existing link*/

	q->size++;
	/*increments the size of the deque*/
}

/* Adds a link to the back of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val) 
{
	assert(q != 0);
	/*confirms that q is not null*/

	_addLinkAfter(q, q->Sentinel->prev, val);
	/*adds a link to the back of the deque with the proper value*/
}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{
	assert(q != 0);
	/*confirms that q is not null*/

	_addLinkAfter(q, q->Sentinel, val);
	/*adds a link to the front of the deque with the proper value*/
}

/* Get the value of the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q) 
{
	assert(q != 0);
	/*confirms q is not null*/

	assert(q->size > 0);
	/*confirms q is not empty*/

	return(q->Sentinel->next->value);
	/* returns value from the front of the deque*/
}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
	assert(q != 0);
	/*confirms q is not null*/

	assert(q->size > 0);
	/*confirms q is not empty*/

	return(q->Sentinel->prev->value);
	/* returns value from the back of the deque*/
}

/* Remove a link from the deque

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{
	assert(q != 0);
	/*confirms q is not null*/

	assert(q->size > 0);
	/*confirms q is not empty*/

	lnk->prev->next = lnk->next;
	/* sets the removed link's previous link's next, to the removed link's next*/

	lnk->next->prev = lnk->prev;
	/* sets the removed link's next link's prev, to the removed link's prev*/

	free(lnk);
	/*frees the memory by deleting lnk*/

	q->size--;
	/*decrements the size of the deque*/
}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q) {
	
	assert(q != 0);
	/*confirms q is not null*/

	assert(q->size > 0);
	/*confirms q is not empty*/

	_removeLink(q, q->Sentinel->next);
	/*removes the front from the deque*/
}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{
	assert(q != 0);
	/*confirms q is not null*/

	assert(q->size > 0);
	/*confirms q is not empty*/

	_removeLink(q, q->Sentinel->prev);
	/*removes the back from the deque*/
}

/* De-allocate all links of the deque

	param: 	q		pointer to the deque
	pre:	none
	post:	All links (including Sentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{
	while (!isEmptyCirListDeque(q))
	{
		removeBackCirListDeque(q);
		/*removes the back of the deque
		**until the sentinel is reached
		*/
	}

	assert(q->size == 0);
	/*asserts size has been adjusted to 0*/

	free(q->Sentinel);
	/*removes the sentinel*/
}

/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) {
  	
	assert(q != 0);
	/*confirms q is not null*/

	if (q->Sentinel->next == q->Sentinel->prev)
	{
		return 1;
		/*returns 1 if empty*/
	}

	return 0;
	/* returns 0 if not empty*/
}

/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
	assert(q != 0);
	/*confirms q is not null*/

	assert(q->size > 0);
	/*confirms q is not empty*/

	struct DLink *tempLink = q->Sentinel->next;
	/* creates a temporary struct starting at the front of the deque*/

	while (tempLink != q->Sentinel)
	{
		printf("%g\n", tempLink->value);
		
		/*prints the value contained in tempLink*/

		tempLink = tempLink->next;
		/*reassigns tempLink to its next*/
	}
}

/* Reverse the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the deque is reversed
*/
void reverseCirListDeque(struct cirListDeque *q)
{
	assert(q != 0);
	/*confirms q is not null*/

	assert(q->size > 0);
	/*confirms q is not empty*/

	struct DLink *lnk = q->Sentinel;
	struct DLink *temp = q->Sentinel->next;

	/* create two pointers to structs to swap around links */

	for (int i = 0; i < q->size + 1; i++)
	{
		lnk->next = lnk->prev;
		lnk->prev = temp;
		lnk = temp;
		temp = temp->next;
	}
}
