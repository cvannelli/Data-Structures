/*Author: Christiano Vannelli
**Date: 03/03/16
**Description: contains the hashMap functions
** for storing and counting the occurance of words in .txt files.
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "hashMap.h"



/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashMap * ht)
{  
	assert(ht != 0);
	/*confirms ht is not null*/

	struct hashLink *cur;
	/*create a pointer to a hash link*/

	struct hashLink *temp;


	for (int i = 0; i < capacity(ht); i++)
	{
		if (ht->table[i] != 0)
		{
			cur = ht->table[i];
			/*set cur to table at index i*/

			do
			{
				temp = cur->next;
				cur->key = 0;
				free(cur);
				/*frees up memory from hashlink*/

				ht->count--;
				/*decrements the count*/

				cur = temp;
				/*increments cur to its next*/
			} while (temp != 0);
		}
	}
	free(ht->table);
	/*frees the entire table*/
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/* 
Resizes the hash table to be the size newTableSize 
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
	assert(ht != 0);
	/*confirms ht is not null*/

	assert(newTableSize > 0);
	/*confirms the new size is greater than 0*/

	struct hashMap *newTable = createMap(newTableSize);
	/*create a pointer to a new hashMap*/

	assert(newTable->table != 0);
	/*confirms creation of a new table*/

	struct hashLink *cur;
	/*create a pointer to a new hashLink*/

	for (int i = 0; i < capacity(ht); i++)
	{
		cur = ht->table[i];
		/*sets current to list at the index*/

		while (cur != 0)
		{
			insertMap(newTable, cur->key, cur->value);
			/*copies over keys and values at current table index*/

			cur = cur->next;
			/*increments cur to its next*/
		}
	}

	_freeMap(ht);
	/*frees the hash table
	*/

	ht->table = newTable->table;
	ht->tableSize = newTable-> tableSize;
	ht->count = newTable->count;
	/*changes the hash table's variables to the new hash table*/
}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".
 
 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.
 
 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap(struct hashMap * ht, KeyType k, ValueType v)
{
	int hashIndex;
	/*create an int for the Hash Index*/

	struct hashLink *newLink;
	/*pointer to a new hashlink*/

	struct hashLink *cur;
	/*pointer to the current hashlink*/


	if (tableLoad(ht) >= LOAD_FACTOR_THRESHOLD)
	{
		_setTableSize(ht, (2 * capacity(ht)));
		/*doubles the table size if greater than or equal to threshold*/
	}


	if (HASHING_FUNCTION == 1)
	{
		hashIndex = stringHash1(k) % ht->tableSize;
		/*use the first hashing function*/
	}
	else
	{
		hashIndex = stringHash2(k) % ht->tableSize;
		/*use the second hashing function*/
	}

	if (hashIndex < 0)
	{
		hashIndex += ht->tableSize;
	}
	/* changes hashIndex in case negative index is generated*/


	if (containsKey(ht, k))
	{
		removeKey(ht, k);
		/*removes they key if it already exists*/
	}
	
	newLink = (hashLink *)malloc(sizeof(hashLink));
	/*allocates space for newLink*/

	assert(newLink != 0);
	/*confirms allocation*/

	newLink->key = k;
	newLink->next = 0;
	newLink->value = v;
	/*sets up key, next and value variables within the struct*/


	cur = ht->table[hashIndex];
	/*sets up cur to be the link at the hashIndex*/


	if (ht->table[hashIndex] == 0) 
	{
		ht->table[hashIndex] = newLink;
		/*adds newly created link at hashIndex*/
	}

	else
	{
		while (cur->next != 0)
		{
			cur = cur->next;
			/*increments cur to the next link*/
		}

		cur->next = newLink;
		/*sets the next link to the newLink*/
	}

	ht->count++;
	/*increments the count*/

	return;
}
	

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.
 
 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.
 
 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{ 
	assert(ht != 0);
	/*confirms ht is not null*/

	int hashIndex;
	/*create an int for the Hash Index*/

	if (HASHING_FUNCTION == 1)
	{
		hashIndex = stringHash1(k) % ht->tableSize;
		/*use the first hashing function*/
	}
	else
	{
		hashIndex = stringHash2(k) % ht->tableSize;
		/*use the second hashing function*/
	}

	if (hashIndex < 0) hashIndex += ht->tableSize;
	/* changes hashIndex in case negative index is generated*/


	hashLink *cur = ht->table[hashIndex];
	/*create a pointer to the hashLink at the
	**specific Hash Index in the table
	*/

	while (cur != 0)
	{
		if (strcmp(cur->key, k) == 0)
			return &(cur->value);
		/*returns value at key*/

		else
			cur = cur->next;
		/*increments cur to its next*/
	}

	return 0;
	/*returns 0 if key was not in hash table*/
}

/*
 a simple yes/no if the key is in the hashtable. 
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{  
	assert(ht != 0);
	/*confirms ht is not null*/

	int hashIndex;
	/*create an int for the Hash Index*/
	
	if (HASHING_FUNCTION == 1)
	{
		hashIndex = stringHash1(k) % ht->tableSize;
		/*use the first hashing function*/
	}
	else
	{
		hashIndex = stringHash2(k) % ht->tableSize;
		/*use the second hashing function*/
	}
	
	if (hashIndex < 0) hashIndex += ht->tableSize;
	/* changes hashIndex in case negative index is generated*/


	hashLink *cur = ht->table[hashIndex];
	/*create a pointer to the hashLink at the
	**specific Hash Index in the table
	*/

	while (cur != 0)
	{
		if (strcmp(cur->key, k) == 0)
			return 1;
			/*key is within hash table*/
		else
			cur = cur->next;
			/*increments cur to its next*/
	}

	return 0;
	/*returns 0 if key was not in hash table*/
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{  
	struct hashLink *cur;
	/*create a pointer to a hashLink*/

	struct hashLink *temp;
	/*create a temporary pointer*/

	assert(ht != 0);
	/*confirms ht is not null*/

	if (containsKey(ht, k))
	{
		int hashIndex;
		/*create an int for the Hash Index*/

		if (HASHING_FUNCTION == 1)
		{
			hashIndex = stringHash1(k) % ht->tableSize;
			/*use the first hashing function*/
		}
		else
		{
			hashIndex = stringHash2(k) % ht->tableSize;
			/*use the second hashing function*/
		}

		if (hashIndex < 0) hashIndex += ht->tableSize;
		/* changes hashIndex in case negative index is generated*/


		cur = ht->table[hashIndex];
		/*set cur to the link at the hashIndex*/


		if (strcmp(cur->key, k) == 0)
		{
			temp = cur->next;
			free(cur->key);
			free(cur);
			ht->table[hashIndex] = temp;
			/*free cur and  give next its spot*/

			ht->count--;
			/*decrease the count*/
			
			return;
		}

	
		while (cur->next != 0)
		{
			if (strcmp(cur->next->key, k) == 0)
			{
				temp = cur->next->next;
				free(cur->next->key);
				free(cur->next);
				cur->next = temp;
				/*free next and give its next its spot*/

				ht->count--;
				/*decrement the count*/

				return;
			}
			cur = cur->next;
			/*increment cur to its next*/
		}
	}
}

/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{  
	assert(ht != 0);
	/*confirms ht is not null*/

	return (ht->count);
	/*returns the number of hashLinks in the table*/
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{  
	assert(ht != 0);
	/*confirms ht is not null*/

	return (ht->tableSize);
	/*returns the number of buckets in the table*/
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{  
	assert(ht != 0);
	/*confirms ht is not null*/

	int numEmpty = 0;

	for (int i = 0; i < capacity(ht); i++)
	{
		if (ht->table[i] == 0)
		{
			numEmpty++;
			/*increments number of empty buckets*/
		}
	}

	return numEmpty;
	/* returns number of empty buckets*/
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)
 
 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{  
	assert(ht != 0);
	/*confirms ht is not null*/

	float load = ((float)size(ht) / (float)capacity(ht));
	/* load is the ratio of: (number of hashlinks) / (number of buckets)*/

	return load;
}


void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;	
	for(i = 0; i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {		
			printf("\nBucket Index %d -> ", i);		
		}
		while(temp != 0){			
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;			
		}		
	}
}


