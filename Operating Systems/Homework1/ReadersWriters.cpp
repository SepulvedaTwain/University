#include "ReadersWriters.h"


Arguments arguments;

bool argvCheck(int argc, char ** argv){ // check to see if arguments are correct..

	int i;
	int counter=0;
	if(argc!=9)
		return false;
	for(i=1;i<argc;i+=2){
		

		if(!strcmp(argv[i],"-p")){
			if(!(isNumber(argv[i+1])))
				return false;
			arguments.processes=atoi(argv[i+1]);
			counter++;
			
		}
		else if(!strcmp(argv[i],"-i")){
			if(!(isNumber(argv[i+1])))
				return false;
			arguments.iterations=atoi(argv[i+1]);
			counter++;
		}
		else if(!strcmp(argv[i],"-e")){
			if(!(isNumber(argv[i+1])))
				return false;
			arguments.entries=atoi(argv[i+1]);
			counter++;
		}
		else if(!strcmp(argv[i],"-r")){
			if(!(isNumber(argv[i+1])))
				return false;
			arguments.r_w=atoi(argv[i+1]);
			counter++;
		}
	}
	if (counter!=4)
		return false;

	return true;

}


bool isNumber(char * str){	//find if it's a num using isdigit()
	int len=strlen(str);
	int i;
	for(i=0,i<len;i++;)
		if(!isdigit(str[i]))
				return false;

	return true;

}

/* Semaphore down operation, using semop */
int sem_wait(int sem_id, int position) {
   struct sembuf sem_d;
   
   sem_d.sem_num = position;
   sem_d.sem_op = -1;
   sem_d.sem_flg = 0;
   if (semop(sem_id,&sem_d,1) == -1) {
       perror("# Semaphore down operation ");
       return -1;
   }
   return 0;
}

/* Semaphore up operation, using semop */
int sem_signal(int sem_id, int position) {
   struct sembuf sem_d;
   
   sem_d.sem_num = position;
   sem_d.sem_op = 1;
   sem_d.sem_flg = 0;
   if (semop(sem_id,&sem_d,1) == -1) {
       perror("# Semaphore up operation ");
       return -1;
   }
   return 0;
}

/* Semaphore Init - set a semaphore's value to val */
int sem_Init(int sem_id, int val, int position) {

   union semun arg;
   
   arg.val = val;
   if (semctl(sem_id,position,SETVAL,arg) == -1) {
       perror("# Semaphore setting value ");
       return -1;
   }
   return 0;

}

void Initialization(){
	//Creating shm 
	shm_db = shmget (SHMKEY, sizeof(Entry)*arguments.entries, PERMS | IPC_CREAT);
	if ( shm_db < 0 ) {
    	perror("Creating Shared Memory Failed..\n");
    	exit(1);
    }

    //Initializating shm

    dbPointer = (Entry*)shmat(shm_db, (char *) 0, 0);
	if ( dbPointer == NULL ) {
		perror("Initializating Shared Memory Failed..\n");
    	exit(1);      
    }

    //Creating sems
	sem_db = semget(SEMKEY1,arguments.entries,IPC_CREAT | PERMS);
   	if (sem_db == -1) {
       	perror("Creating Sem_db Failed..\n");
       	exit(2);
   	}

   	sem_mutexR = semget(SEMKEY2,arguments.entries,IPC_CREAT | PERMS);
   	if (sem_mutexR == -1) {
       	perror("Creating Sem_mutexR Failed..\n");
       	exit(2);
   	}

   	//Initializating sems
   	int i;
   	for (i = 0; i < arguments.entries; ++i)
   	{
   		//gia ta cell
   		dbPointer[i].reads=0;
   		dbPointer[i].writes=0;
   		dbPointer[i].readersNow=0;
   		//gia ta cell
  
	   	if (sem_Init(sem_db, 1, i) == -1) { 
	       	perror("Initializating Sem_db Failed..\n");
	       	exit(3);
	   	}

	   	if (sem_Init(sem_mutexR, 1, i) == -1) { 
	       	perror("Initializating Sem_mutexR Failed..\n");
	       	exit(3);
	   	}
	}


}

void FreeResourses(){
	//free shm
	if (shmctl(shm_db,IPC_RMID,(struct shmid_ds *)NULL) < 0){
			perror(" Free shm_db.. \n");
			exit(4);
	}
	//free sems
	if (semctl(sem_db, 0, IPC_RMID, 0) < 0){
			perror("Free sem_db.. \n");
			exit(5);
	}	

	if (semctl(sem_mutexR, 0, IPC_RMID, 0) < 0){
			perror("Free sem_mutexR.. \n");
			exit(5);
	}

	std::cout<<"Rescourses are Free"<<std::endl;
}

void Peer(int peer_id){
	srand(getpid());
	int reads=0;
	int writes=0;
	float turnAroundTimeR=0.0;
	float turnAroundTimeW=0.0;

	int i;
	for(i=0;i<arguments.iterations;i++){
		if((rand())> RAND_MAX/arguments.r_w){

			Reader(&turnAroundTimeR);
			reads++;
		}
		else{
			Writer(&turnAroundTimeW);
			writes++;
		}

		
	}

	if(writes && reads)
		printf(" %f -> WritersTime, %f -> ReadersTime, %d -> ProcessID, %d -> Reads, %d -> Writes\n",turnAroundTimeW/writes, turnAroundTimeR/reads, peer_id, reads ,writes);
	else if(writes==0){
		printf(" %f -> WritersTime, %f -> ReadersTime, %d -> ProcessID, %d -> Reads, %d -> Writes\n",0.0, turnAroundTimeR/reads, peer_id, reads ,writes);
	}
	else
		printf(" %f -> WritersTime, %f -> ReadersTime, %d -> ProcessID, %d -> Reads, %d -> Writes\n",turnAroundTimeW/writes, 0.0, peer_id, reads ,writes);


	exit(0);
}

void Reader(float *turnAroundTime){
	int cell_num=rand()%arguments.entries;

	clock_t time1,time2;
	time1 = clock();

	if(sem_wait(sem_mutexR,cell_num)){
		perror("Error with sem_wait in reader.. \n");
		FreeResourses();
		exit(6);

	}
	dbPointer[cell_num].readersNow++;
	if(dbPointer[cell_num].readersNow==1){
		if(sem_wait(sem_db,cell_num)){
			perror("Error with sem_wait in read2.. \n");
			FreeResourses();
			exit(6);
		}
	}
	if(sem_signal(sem_mutexR,cell_num)){
		perror("Error with sem_signal in read.. \n");
		FreeResourses();
		exit(7);

	}
	time2=clock();
	dbPointer[cell_num].reads++;
	usleep(peer_wait_time());

	if(sem_wait(sem_mutexR,cell_num)){
		perror("Error with sem_wait in reader.. \n");
		FreeResourses();
		exit(6);

	}

	dbPointer[cell_num].readersNow--;
	if(dbPointer[cell_num].readersNow==0){
		if(sem_signal(sem_db,cell_num)){
			perror("Error with sem_signal in read2.. \n");
			FreeResourses();
			exit(6);
		}
	}

	if(sem_signal(sem_mutexR,cell_num)){
		perror("Error with sem_signal in read.. \n");
		FreeResourses();
		exit(7);

	}

	*turnAroundTime+= ((float)time2 - time1)/CLOCKS_PER_SEC;



	

}
void Writer(float *turnAroundTime){
	int cell_num=rand()%arguments.entries;

	clock_t time1,time2;
	time1 = clock();

	if(sem_wait(sem_db,cell_num)){
		perror("Error with sem_wait in write.. \n");
		FreeResourses();
		exit(6);

	}
	time2=clock();
	dbPointer[cell_num].writes++;
	usleep(peer_wait_time());
	if(sem_signal(sem_db,cell_num)){
		perror("Error with sem_signal in write.. \n");
		FreeResourses();
		exit(7);

	}
	*turnAroundTime+= ((float)time2 - time1)/CLOCKS_PER_SEC;
}

time_t peer_wait_time(){
	double x=rand();
	return -log(x/RAND_MAX)/(arguments.processes)*10000;//*arguments.iterations;
}


int main(int argc, char ** argv){

	if(!argvCheck(argc,argv)){
		printf("Error wrong arguments\n");
		return 1;	
	}

	pid_t pid;
	int status;


	Initialization();
	int i;
	
	for(i=0;i<arguments.processes;i++){
		pid=fork();
		if(pid==0)
			Peer(i+1);

	}
	while((pid=wait(&status)) > 0 ){
		//printf("teleiwse i %u\n",pid);
	}

	int sumR=0;
	int sumW=0;
	int test=0;

	for (i = 0; i < arguments.entries; ++i)
	{
		sumR+=dbPointer[i].reads;
		sumW+=dbPointer[i].writes;
		test+=dbPointer[i].readersNow;
	}

	printf("Total -> %d, totalR_W ->  %d, Reads -> %d, Writes -> %d, ReadersNow -> %d\n",arguments.iterations*arguments.processes, sumW+sumR , sumR , sumW, test );
	



	//sto telos

	FreeResourses();


}

