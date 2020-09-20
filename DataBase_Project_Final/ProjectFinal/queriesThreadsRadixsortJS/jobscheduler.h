#ifndef JOBSCHEDULER
#define JOBSCHEDULER

#include "types.h"
#include "quicksort.h"
#include "radixsort.h"
#include "sortMergeJoin.h"
#include "read_files.h"
#include "read_queries.h"
#include "execute_query.h"
#include "sums.h"
#include "updates.h"
#include "fifo.h"

#include <stdio.h>
#include <unistd.h>	         /* fork */		
#include <stdlib.h>	        
#include <ctype.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>


#define THREADSNUM 10

Fifo *fifo;

pthread_mutex_t mtxClient, mtxFifo; /* mutex */
pthread_cond_t cv_prod, cv_consume; /* the condition variable */
pthread_t * threads;



void jobscheduler( relation *rel1, relation *rel2, int start, int end, int numByte, int currentArray, bool quick);

void initializer();

void *consumerThread(void * ptr);

void perror_exit(char *message);

bool isEmptyFifo();

void terminate();

void threadsWait();

bool beforeMergeCount();




#endif
