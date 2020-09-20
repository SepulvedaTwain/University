#include "jobscheduler.h"



void initializer(){

	pthread_mutex_init (& mtxClient , NULL ); 
	pthread_mutex_init (& mtxFifo , NULL ); 
	pthread_cond_init (&cv_prod , NULL ); 
	pthread_cond_init (&cv_consume , NULL );

	int i, err;
	threads = (pthread_t*)malloc( sizeof(pthread_t) * (THREADSNUM));
	
	for (i=0 ; i <THREADSNUM; i++)
		if ( err = pthread_create (& threads [i], NULL , consumerThread ,( void *) &i)) { 
			perror_exit ((char*)" pthread_create " ); 
		}

	

	
}

void threadsWait(){

	int i;
	JobInfo jobInfo;

	jobInfo.rel1=NULL;
	jobInfo.rel2=NULL;
	jobInfo.start=-1;
	jobInfo.end=-1;
	jobInfo.numByte=-1;
	jobInfo.currentArray=-1;
	jobInfo.quick=false;

	pthread_mutex_lock(&mtxFifo);

	for(i=0;i<THREADSNUM;i++)
		insertJob(fifo, jobInfo);
	
	pthread_mutex_unlock(&mtxFifo);
	pthread_cond_signal(&cv_consume);

	
		


}

void terminate(){

	int i;
	/*JobInfo jobInfo;

	jobInfo.rel1=NULL;
	jobInfo.rel2=NULL;
	jobInfo.start=-1;
	jobInfo.end=-1;
	jobInfo.numByte=-1;
	jobInfo.currentArray=-1;
	jobInfo.quick=false;

	pthread_mutex_lock(&mtxFifo);
	for(i=0;i<THREADSNUM;i++){
		insertJob(fifo, jobInfo);
	}
	
	pthread_mutex_unlock(&mtxFifo);
	pthread_cond_signal(&cv_consume);

	//printf("%d \n",fifo->count);
	*/
	printf("%d ",fifo->beforeMerge);

	for(i=0;i<THREADSNUM;i++){
		printf("fff\n");
		pthread_join(threads[i],NULL);
		//printf("hi!\n");
		//printf("%d \n",fifo->count);
	}
	

	pthread_mutex_destroy(& mtxClient);
	pthread_mutex_destroy(& mtxFifo);

	pthread_cond_destroy(&cv_prod);
	pthread_cond_destroy(&cv_consume);

	FifoNode * temp=fifo->head;
	while(fifo->head){
		free(temp);
		temp=fifo->head->next;
		fifo->head=temp;
		
	}

	fifo=NULL;


}

//      prepei na kanw ston jobscheduler tin quicksort kai episis na kanw to join twn threads meta tis radix sort prin to merge
//      dld na stelnei ena bool(h o,ti) gia na termatizei ayto to sesion 

void jobscheduler( relation *rel1, relation *rel2, int start, int end, int numByte, int currentArray, bool quick){
	
	if(fifo==NULL){
		fifo=malloc(sizeof(Fifo));
		fifoInit(fifo);
		initializer();
	}


	JobInfo jobInfo;

	jobInfo.rel1=rel1;
	jobInfo.rel2=rel2;
	jobInfo.start=start;
	jobInfo.end=end;
	jobInfo.numByte=numByte;
	jobInfo.currentArray=currentArray;
	jobInfo.quick=quick;

	pthread_mutex_lock(&mtxFifo);

	//edw tha stelnw tin douleia stin lista 

	insertJob(fifo, jobInfo);
	
	pthread_mutex_unlock(&mtxFifo);
	pthread_cond_signal(&cv_consume);



}


void perror_exit(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}

void *consumerThread(void * ptr){
	
	while(1){

		pthread_mutex_lock(&mtxFifo);
		
		while(isEmpty(fifo) || fifo == NULL){	//an einai adeia h lista
			pthread_cond_wait(&cv_consume, &mtxFifo);
		}

			
		//edw tha kalesti h getjob na doume ta info kai poia sinartisi prepei na kalesoume stin sortMerge join 

		JobInfo jb=getJob( fifo);//h get job na kanei kai remove to node

		//radixSort(jb.rel1, jb.rel2, jb.start, jb.end, jb.numByte ,jb.currentArray);
		if(jb.rel1==NULL && jb.rel2==NULL && jb.start==-1 && jb.end==-1 && jb.numByte==-1 && jb.currentArray==-1 && jb.quick==false){
        	fifo->beforeMerge++;
        	//printf("%d\n",fifo->beforeMerge );
        	if(fifo->beforeMerge==THREADSNUM){
        		pthread_cond_wait(&cv_consume,&mtxFifo);
        		fifo->beforeMerge=0;
        	}
        	//

        	pthread_mutex_unlock(&mtxFifo);

        	continue;




		}


		pthread_mutex_unlock(&mtxFifo);
		//pthread_cond_signal(&cv_prod);
		
		//kaleite h sinatrisi gia na eksipiretithei h aitisi
		
		if(jb.quick==false){
			radixSort(jb.rel1, jb.rel2, jb.start, jb.end, jb.numByte ,jb.currentArray);
			
		}
		else if(jb.quick==true){
			//printf("ep\n");
			quickSort(jb.rel1,jb.start,jb.end);

		}

		

		

	}
	pthread_exit(NULL);


}

bool isEmptyFifo(){
	return isEmpty(fifo);
}

bool beforeMergeCount(){
	if(fifo->beforeMerge==THREADSNUM){
		
		//pthread_cond_signal(&cv_prod);

		fifo->beforeMerge=0;
		return true;
	}
	else false;
}