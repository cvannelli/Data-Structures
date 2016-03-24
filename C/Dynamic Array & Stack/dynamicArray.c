/*Author: Christiano Vannelli
**Date: 01-22-16
**Description: contains functions for dynamicArray
*/


/*	dynamicArray.c: Dynamic Array implementation. */
#include <assert.h>
#include <stdlib.h>
#include "dynArray.h"

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};


/* ************************************************************************
	Dynamic Array Functions
************************************************************************ */

/* Initialize (including allocation of data array) dynamic array.

	param: 	v		pointer to the dynamic array
	param:	cap 	capacity of the dynamic array
	pre:	v is not null
	post:	internal data array can hold cap elements
	post:	v->data is not null
*/
void initDynArr(DynArr *v, int capacity)
{
	assert(capacity > 0);
	assert(v!= 0);
	v->data = (TYPE *) malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);
	v->size = 0;
	v->capacity = capacity;	
}

/* Allocate and initialize dynamic array.

	param:	cap 	desired capacity for the dyn array
	pre:	none
	post:	none
	ret:	a non-null pointer to a dynArr of cap capacity
			and 0 elements in it.		
*/
DynArr* newDynArr(int cap)
{
	assert(cap > 0);
	DynArr *r = (DynArr *)malloc(sizeof( DynArr));
	assert(r != 0);
	initDynArr(r,cap);
	return r;
}

/* Deallocate data array in dynamic array. 

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	d.data points to null
	post:	size and capacity are 0
	post:	the memory used by v->data is freed
*/
void freeDynArr(DynArr *v)
{
	if(v->data != 0)
	{
		free(v->data); 	/* free the space on the heap */
		v->data = 0;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}

/* Deallocate data array and the dynamic array ure. 

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	the memory used by v->data is freed
	post:	the memory used by d is freed
*/
void deleteDynArr(DynArr *v)
{
	freeDynArr(v);
	free(v);
}

/* Resizes the underlying array to be the size cap 

	param: 	v		pointer to the dynamic array
	param:	cap		the new desired capacity
	pre:	v is not null
	post:	v has capacity newCap
*/
void _dynArrSetCapacity(DynArr *v, int newCap)
{	
	struct DynArr newDynArr;
	/*create a new DynArr struct*/

	initDynArr(&newDynArr, newCap);
	/* allocate memory for the new struct and set up variables*/

	for (int i = 0; i < v->capacity; i++)
	{
		newDynArr.data[i] = v->data[i];
		newDynArr.size++;
		/*copy data to the new struct*/
	}

	freeDynArr(v);
	/* free the old struct from memory*/

	*v = newDynArr;
	/* assign the pointer to the new struct*/
}

/* Get the size of the dynamic array

	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	none
	ret:	the size of the dynamic array
*/
int sizeDynArr(DynArr *v)
{
	assert(v != 0);

	return v->size;
}

/* 	Adds an element to the end of the dynamic array

	param: 	v		pointer to the dynamic array
	param:	val		the value to add to the end of the dynamic array
	pre:	the dynArry is not null
	post:	size increases by 1
	post:	if reached capacity, capacity is doubled
	post:	val is in the last utilized position in the array
*/
void addDynArr(DynArr *v, TYPE val)
{
	assert(v != 0);

	if (v->size >= v->capacity)
	{
		_dynArrSetCapacity(v, 2 * v->capacity);
	}

	v->data[v->size] = val;
	v->size++;

}

/*	Get an element from the dynamic array from a specified position
	
	param: 	v		pointer to the dynamic array
	param:	pos		integer index to get the element from
	pre:	v is not null
	pre:	v is not empty
	pre:	pos < size of the dyn array and >= 0
	post:	no changes to the dyn Array
	ret:	value stored at index pos
*/

TYPE getDynArr(DynArr *v, int pos)
{
	assert(v != 0);
	assert(pos < v->size && pos >= 0);
	assert(v->size > 0);


	return v->data[pos]; 
}

/*	Put an item into the dynamic array at the specified location,
	overwriting the element that was there

	param: 	v		pointer to the dynamic array
	param:	pos		the index to put the value into
	param:	val		the value to insert 
	pre:	v is not null
	pre:	v is not empty
	pre:	pos >= 0 and pos < size of the array
	post:	index pos contains new value, val
*/
void putDynArr(DynArr *v, int pos, TYPE val)
{
	
	assert(v != 0);
	assert(v->size > 0);
	assert(pos < v->size && pos >= 0);

	v->data[pos] = val;
}

/*	Swap two specified elements in the dynamic array

	param: 	v		pointer to the dynamic array
	param:	i,j		the elements to be swapped
	pre:	v is not null
	pre:	v is not empty
	pre:	i, j >= 0 and i,j < size of the dynamic array
	post:	index i now holds the value at j and index j now holds the value at i
*/
void swapDynArr(DynArr *v, int i, int  j)
{
	assert(v != 0);
	assert(i < v->size && i >= 0);
	assert(j < v->size && j >= 0);

	/* asserts that spots i and j arent bigger than
	**  the array size and that they're greater than
	** or equal to 0
	*/

	TYPE temp = v->data[i];
	v->data[i] = v->data[j];
	v->data[j] = temp;

	/*swaps the positions using the int variable temp*/
}

/*	Remove the element at the specified location from the array,
	shifts other elements back one to fill the gap

	param: 	v		pointer to the dynamic array
	param:	idx		location of element to remove
	pre:	v is not null
	pre:	v is not empty
	pre:	idx < size and idx >= 0
	post:	the element at idx is removed
	post:	the elements past idx are moved back one
*/
void removeAtDynArr(DynArr *v, int idx)
{
	assert(v != 0);
	assert(v->size > 0);
	assert(idx < v->size && idx >= 0);

	for (int i = idx; i < v->size - 1; i++)
	{
		v->data[i] = v->data[i + 1];

		/* replaces the chosen index with the next
		** element until the end of the array is hit
		*/
	}

	v->data[v->size - 1] = 0;
	/* changes the final element in the array to a NULL value*/

	v->size--;
	/* decreases the size of the array by 1*/
}



/* ************************************************************************
	Stack Interface Functions
************************************************************************ */

/*	Returns boolean (encoded in an int) demonstrating whether or not the 
	dynamic array stack has an item on it.

	param:	v		pointer to the dynamic array
	pre:	the dynArr is not null
	post:	none
	ret:	1 if empty, otherwise 0
*/
int isEmptyDynArr(DynArr *v)
{
	assert(v != 0);

	if (v->size == 0)
	{
		return 1;
		/* returns 1 if the size is 0*/
	}

	return 0;
}

/* 	Push an element onto the top of the stack

	param:	v		pointer to the dynamic array
	param:	val		the value to push onto the stack
	pre:	v is not null
	post:	size increases by 1
			if reached capacity, capacity is doubled
			val is on the top of the stack
*/
void pushDynArr(DynArr *v, TYPE val)
{
	assert(v != 0);

	addDynArr(v, val);
	/*utilizes addDynArr function to push value e to
	** the top of the stack
	*/
}

/*	Returns the element at the top of the stack 

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the stack
*/
TYPE topDynArr(DynArr *v)
{
	assert(v != 0);
	assert(v->size > 0);

	return (getDynArr(v, v->size - 1));
	/* returns the to value of the stack*/
}

/* Removes the element on top of the stack 

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	size is decremented by 1
			the top has been removed
*/
void popDynArr(DynArr *v)
{
	assert(v != 0);
	assert(v->size > 0);
	/* asserts that the array is not empty*/

	removeAtDynArr(v, v->size - 1);
	/* removes the top element of the stack*/
}

/* ************************************************************************
	Bag Interface Functions
************************************************************************ */

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	v		pointer to the dynamic array
	param:	val		the value to look for in the bag
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the bag
*/
int containsDynArr(DynArr *v, TYPE val)
{
	assert(v != 0);
	assert(v->size > 0);
	/* asserts v isn't pointing to NULL and size is greater than 0*/

	for (int i = 0; i < v->size; i++)
	{
		if (val == v->data[i])
		{
			return 1;
			/* returns 1 if the value is contained in the array*/
		}
	}

	return 0;
	/*returns 0 if the array does not contain the val*/
}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	v		pointer to the dynamic array
	param:	val		the value to remove from the array
	pre:	v is not null
	pre:	v is not empty
	post:	val has been removed
	post:	size of the bag is reduced by 1
*/
void removeDynArr(DynArr *v, TYPE val)
{
	assert(v != 0);
	assert(v->size > 0);
	assert(containsDynArr(v, val));
	/* asserts array does not point to NULL, array is not empty
	** and the array contains the value being removed
	*/

	for (int i = 0; i < (v->size); i++)
	{
		if (v->data[i] == val)
		{
			for (int j = i; j < (v->size - 1); j++)
			{
				v->data[j] = v->data[j + 1];
				/*swaps values from point of removal*/

			}
			v->size -= 1;
			/*decreases array size*/

			return;
		}
	}
}