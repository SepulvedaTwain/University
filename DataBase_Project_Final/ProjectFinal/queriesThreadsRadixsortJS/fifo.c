#include "fifo.h"

bool isEmpty(Fifo * fifo){
	if(fifo->count==0){
		return true;
	}
	else 
		return false;
}

JobInfo getJob(Fifo * fifo){

	JobInfo temp;

	//copy jobInfo
	temp.rel1=fifo->head->jobInfo.rel1;
	temp.rel2=fifo->head->jobInfo.rel2;
	temp.start=fifo->head->jobInfo.start;
	temp.end=fifo->head->jobInfo.end;
	temp.numByte=fifo->head->jobInfo.numByte;
	temp.currentArray=fifo->head->jobInfo.currentArray;
	temp.quick=fifo->head->jobInfo.quick;

	//remove job from fifo
	FifoNode * node=malloc(sizeof(FifoNode));
	node=fifo->head;
	fifo->head=fifo->head->next;
	fifo->count--;

	free(node);

	return temp;
		



}//h get job na kanei kai remove to node

void insertJob(Fifo * fifo, JobInfo jobInfo){
	FifoNode * temp=malloc(sizeof(FifoNode));

	//copy jobinfo
	temp->next=NULL;
	temp->jobInfo.rel1=jobInfo.rel1;
	temp->jobInfo.rel2=jobInfo.rel2;
	temp->jobInfo.start=jobInfo.start;
	temp->jobInfo.end=jobInfo.end;
	temp->jobInfo.numByte=jobInfo.numByte;
	temp->jobInfo.currentArray=jobInfo.currentArray;
	temp->jobInfo.quick=jobInfo.quick;

	//insert if fifo is empty
	if(isEmpty(fifo)){

		fifo->count++;
		fifo->head=temp;
		fifo->last=temp;	
		return;	
	}
	//normal insert to fifo

	fifo->count++;
	fifo->last->next=temp;
	fifo->last=temp;
	return;


}

void fifoInit(Fifo * fifo){
	fifo->head=NULL;
	fifo->last=NULL;
	fifo->count=0;
	fifo->beforeMerge=0;
}

void printFifo(Fifo * fifo){
	if(isEmpty(fifo)){
		printf("FIFO is empty\n");
		return;
	}
	printf("%d count\n",fifo->count );
}