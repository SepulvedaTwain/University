#ifndef FIFO
#define FIFO

#include "types.h"
#include "quicksort.h"
#include "radixsort.h"
#include "sortMergeJoin.h"
#include "read_files.h"
#include "read_queries.h"
#include "execute_query.h"
#include "sums.h"
#include "updates.h"

typedef struct {
	relation *rel1;
	relation *rel2;
	int start;
	int end;
	int numByte;
	int currentArray;
	bool quick;
	resultBucket* Res;

}JobInfo;

typedef struct n{
	JobInfo jobInfo;
	struct n * next;
}FifoNode;

typedef struct{
	FifoNode * head;
	FifoNode * last;
	int count;
	int beforeMerge;
}Fifo;

void fifoInit(Fifo * fifo);

bool isEmpty(Fifo * fifo);

JobInfo getJob(Fifo * fifo);

void insertJob(Fifo * fifo, JobInfo jobInfo);

void printFifo(Fifo * fifo);






#endif