#ifndef RW
#define RW

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include <math.h>


#define SHMKEY (key_t)6799 //sm key
#define SEMKEY1 (key_t) 3456 //sem keys
#define SEMKEY2 (key_t) 9470
#define SEMKEY3 (key_t) 3446
#define PERMS 0666

class Arguments{
public:
	int processes;
	int iterations;
	int entries;
	int r_w;
};

union semun {
   int val;                  	/* value for SETVAL */
   struct semid_ds *buf;     /* buffer for IPC_STAT, IPC_SET */
   unsigned short *array;    /* array for GETALL, SETALL */

};

typedef struct{
	int reads;
	int writes;
	int readersNow;
}Entry;

int shm_db;
int sem_db,sem_mutexR;// mutexR->for reades

Entry * dbPointer;

bool argvCheck(int argc, char ** argv);
bool isNumber(char * str);

int sem_wait(int sem_id, int position); //to position einai gia na kathorisoume to sem stin thesi tou
int sem_signal(int sem_id, int position);
int sem_Init(int sem_id, int val, int position);

void Initialization();
void FreeResourses();


void Peer(int peer_id);
void Reader(float *turnAroundTime);
void Writer(float *turnAroundTime);

time_t peer_wait_time();


#endif