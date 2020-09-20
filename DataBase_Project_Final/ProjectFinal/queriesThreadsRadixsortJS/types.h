#ifndef TYPES
#define TYPES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <limits.h>

static const int  BucketSize = 1024*1024; /*The bucket size will be 1MB.*/

/////////////////////////////////////////////////////
/////////////////// data types //////////////////////

/** Type definition for a tuple */
typedef struct tuple
{
	uint64_t key;
	uint64_t payload;
	uint64_t intermediatePayload;
}tuple;

/** Type definition for a relation */
typedef struct relation
{
	tuple *tuples;
	uint64_t numtuples;
}relation;

typedef struct resultBucket
{
	uint64_t data[65536][2]; /*Since the bucket size is 1MB every bucket can hold 65536 * 2 uint64_t numbers*/
	struct resultBucket *next; /* SET next = NULL*/
	int numOfEntries; /* SET numOfEntries = 0;*/
	uint64_t data2[65536][2]; /*Holds the intermediate payloads */
}resultBucket;

typedef struct StatisticsData
{
	uint64_t Min;
	uint64_t Max;
	uint64_t Quantity;
	bool *Unique; //Array for the unique values
	int UniqueSize; //Could be removed (Contains the size of the Unique array)
	int Differ; //Number of different values
}StatisticsData;

typedef struct fileNode
{
	uint64_t numRows;
	uint64_t numColumns;
	uint64_t *array;
	StatisticsData *Stats; //Array of StatisticsData for every row of the relation
}fileNode;

typedef struct intermediateNode
{
	uint64_t numRows;
	uint64_t *relations;
	uint64_t relationsSize;
	int *sorted;
	uint64_t **info;
	struct intermediateNode *next;
}iNode;

typedef struct sumsNode
{
	uint64_t *array;
	uint64_t arraySize;
	bool isNull;
	struct sumsNode *next;
}sumsNode;

typedef struct queriesThreadStruct
{
	fileNode *files;
	int filesSize;
	char *input;
	sumsNode **head;
}queriesThreadStruct;

typedef struct IntegerList
{
	int value;
	struct IntegerList* next;
}IntegerList;

#endif
