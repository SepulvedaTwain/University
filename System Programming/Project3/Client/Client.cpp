#include "Client.h"


using namespace std;

pthread_mutex_t mtxClient, mtxBuffer;/*,mtxLast; /* mutex */
pthread_cond_t cv_prod, cv_consume; /* the condition variable */
pthread_t * threads;
CycleBuffer * cBuffer;
UserArguments userArguments;

ClientList clients;
InputList inputList;


int main(int argc,char* argv[]){
	/*prwta kanoyme elenxo ton argv, 
	meta dimiourgoume tin lista me ta pathnames apo to client dir
	meta kanoume ton kikliko buffer 
	meta kanoume ta threads 
	fitaxnoume to passive endpoint tou client
	meta kanoyme logon ston server 
	meta pernoume tin list tws client apo ton server kai tin bazoyme stin client list
	episis bazoume olous toys clients stoon kikliko buffer xwris alles plirofories
	klinoume to socket tou logon 
	katopin arxizoume na kanoume accept apo allous client h ton server mesa se ena atermon while
	ilopoioume to ctrl + c gia logoff
	*/
	/*char buf[100],b[10];
	convert_to_binary(portNum,b);
	sprintf(buf,"LOG_ON %s %s ","192.10.78.15",b);
	



	



	write(sock,buf,100);
	sleep(20);
	*/

	if(!argvCheck(argc,argv)){
		cout<<"Wrong Arguments"<<endl;
		return 1;
	}
	//cout<<userArguments.bufferSize<<" "<<userArguments.serverPort<<" "<<userArguments.dirName<<" "<<userArguments.serverIP<<endl;
	signal(SIGINT, termination);

	int sock;
	unsigned short serving_port=9050,net_port;
	unsigned short portNum=9000; // apo to argv to pernoume.
	char hostname[100];
	strcpy(hostname,userArguments.serverIP);
	struct sockaddr_in server;
	//socklen_t clientlen;
	struct sockaddr *serverptr = (struct sockaddr*)&server;
   	struct hostent *rem;

   	recDirContent(userArguments.dirName,&inputList);//diavazei to dirName
   	//inputList.Print(inputList.head);
   	/*char tempList[1000];

   	prepareListToSent(tempList);
   	cout<<tempList<<endl;
	*/
   	initializer();

	makeconnection_serving(&serverptr,&rem,hostname,&server,&sock,userArguments.serverPort); printf("ip: %s\n",rem->h_name);
	char buf[1000],b[10];
	convert_to_binary(userArguments.clientPort,b);

	sprintf(buf,"LOG_ON %s %s ",rem->h_name,b);
	
	write(sock,buf,1000);

	write(sock,"GET_CLIENTS ",1000);

	read(sock,buf,1000);

	close(sock);
	cout<<"BUFFER: "<<buf<<endl;
	if(strcmp(buf,"nothing "))
		insertClientsToClientList(buf);//bazoume tous client stin lista	


	int newsock;
	struct sockaddr_in clientServer, otherClient;
	socklen_t otherClientlen;
	struct sockaddr *clientServerptr;
	struct sockaddr *otherClientptr;

	d_connection(&clientServerptr,&otherClientptr,&clientServer,& otherClient,&sock,userArguments.clientPort,&otherClientlen);

	while (1) {
	        /* accept connection */
	    	if ((newsock = accept(sock, otherClientptr, &otherClientlen)) < 0) perror_exit((char*)"accept");
	    	
	    	printf("CLient Accepted connection\n");

	    	read(newsock,buf,1000);
	    	cout<<"BUFFER META TIN LOGON KAI GET CLEINTS: "<<buf<<endl;
	    	char tempBuf[1000];
	    	strcpy(tempBuf,buf);
	    	char * token=strtok(buf," ");
	    	if(!strcmp(token,"GET_FILE_LIST")){
	    		sleep(2);
	    		getFileList(newsock);
	    	}
	    	else if(!strcmp(token,"GET_FILE")){
	    		getFile(newsock,tempBuf);
	    	}
	    	else if(!strcmp(token,"USER_ON")){
	    		sleep(5);
	    		userOn(tempBuf);
	    	}
	    	else if(!strcmp(token,"USER_OFF")){
	    		sleep(2);
	    		userOff(tempBuf);
	    	}

	    	close(newsock);
	    	cout<<"ekleise to newsock"<<endl;
   	 }



	

	
	return 0;

}

void getFile(int sock,char * buf){
	char * token=strtok(buf," ");
	token=strtok(NULL," ");
	char bufPath[128];
	strcpy(bufPath,userArguments.dirName);
	strcat(bufPath,"/");
	strcat(bufPath,token);
	token=strtok(NULL,"\n");
	char bufVersion[100];
	strcpy(bufVersion,token);
	strcat(bufVersion,"\n");
	
	int i;
	InputNode * temp=inputList.head;
	for(i=0;i<inputList.counter;i++){
		if(!strcmp(temp->path,bufPath)){
			if(!strcmp(temp->version,bufVersion)){
				write(sock,"FILE_UP_TO_DATE ",1000);
				return;
			}
			else{
				//strcpy(bufVersion,temp->version);
				//sendFile(bufPath,bufVersion,temp->size,sock);
				//return;

			}

			
		}
		temp=temp->next;
	}
	

}

void sendFile(char * filePath,char * version,size_t size1, int sock){ 
	//the function the sender child calls to send the inputFile to the receiver

	char buffFile[1000];

	FILE *fp = fopen(filePath, "r");
  	int count=0;
  	int ch = getc(fp); 
  	while (ch != EOF){ 
 
    	buffFile[count++]=ch;  
		ch = getc(fp); 
	} 
	buffFile[count]='\0';
	fclose(fp);

	char array[100];
	sprintf(array,"FILE_SIZE %s%ld ",version,size1);
	
	write(sock,array,1000);
	
	char * pBuff=buffFile;
	int size=size1;
	while(size>0){
		write(sock,pBuff,1000);
		pBuff+=userArguments.bufferSize;
		size-=userArguments.bufferSize;
	
		//cout<<buffFile<<endl;
	}
	
	
	 

}


void getFileList(int socket){
	char list[1000];
	prepareListToSent(list);
	//cout<<list<<endl;
	write(socket,list,1000);

}
void prepareListToSent(char * list){
	char list2[1000];
	char list4[1000];
	

	if(inputList.head==NULL){
		sprintf(list,"FILE_LIST %d",0);
		return;
	}
	int counter=0;
	InputNode * temp=inputList.head;
	//inputList.Print(temp);
	char list3[1000];
	for(counter=0;counter<inputList.counter;counter++){
		sprintf(list3,"%s %s ",temp->path,temp->version);
		if(counter==0)
			strcpy(list2,list3);
		else
			strcat(list2,list3);
		temp=temp->next;
	}
	sprintf(list4,"FILE_LIST %d %s ",inputList.counter,list2);
	strcpy(list,list4);
}

void insertClientsToClientList(char * buf){
	char * token=strtok(buf," ");
	if(!strcmp(token,"CLIENT_LIST")){
		token=strtok(NULL," ");
		int i=atoi(token);
		while(i!=0){
			token=strtok(NULL," ");
			char bufIp[100];
			strcpy(bufIp,token);
			token=strtok(NULL," ");
			unsigned short * portPtr=((unsigned short *)token);
			unsigned short port=*portPtr;
			port=ntohs(port);

			pthread_mutex_lock(&mtxClient);
			clients.insertNode(bufIp,port);
			pthread_mutex_unlock(&mtxClient);

			BufferElement element;
			element.setBufferElement(bufIp,port);

			insertElementToBuffer(&element);


			i--;
		}
	}
	else{
		cout<<"Something went wrong with get Clients  bufffer: "<< buf<<endl;
	}
}


void termination (int sig) {
	int err,i;

	int sock;
	unsigned short serving_port=userArguments.serverPort,net_port;
	unsigned short portNum=userArguments.clientPort; // apo to argv to pernoume.
	char hostname[100];
	strcpy(hostname,userArguments.serverIP);
	struct sockaddr_in server;
	//socklen_t clientlen;
	struct sockaddr *serverptr = (struct sockaddr*)&server;
   	struct hostent *rem;


	makeconnection_serving(&serverptr,&rem,hostname,&server,&sock,serving_port);

	char buf[1000],b[10];
	convert_to_binary(portNum,b);
	sprintf(buf,"USER_OFF %s %s ",rem->h_name,b);
	cout<<buf<<endl;
	write(sock,buf,1000);
	read(sock,buf,1000);
	cout<<buf<<endl;
	close(sock);



	

	BufferElement lastElement;
	lastElement.setBufferElement((char*)"end",100,(char*)"end",(char*)"end");
	for(i=0;i<userArguments.workerThreads;i++){
		insertElementToBuffer(&lastElement);
	}
	

	for(i=0;i<userArguments.workerThreads;i++){
		if ( err = pthread_join ( threads[i], NULL )) {
			perror_exit ((char*)" pthread_join " ); 
		}

	}
	free(threads);
	if ( err = pthread_mutex_destroy (& mtxBuffer )) {
		perror_exit ((char*)" pthread_mutex_destroy "); 
	}
	if ( err = pthread_mutex_destroy (& mtxClient )) {
		perror_exit ((char*)" pthread_mutex_destroy "); 
	}/*
	if ( err = pthread_mutex_destroy (& mtxLast )) {
		perror_exit ((char*)" pthread_mutex_destroy "); 
	}*/
	if ( err = pthread_cond_destroy (& cv_prod )) {
		perror_exit ((char*)" pthread_cond_destroy "); 
	}
	if ( err = pthread_cond_destroy (& cv_consume )) {
		perror_exit ((char*)" pthread_cond_destroy "); 
	}
	
	free(cBuffer);
	cout<<"Client terminated"<<endl;
	pthread_exit(NULL);

	
}

void userOff(char*buf){
	char * token=strtok(buf," ");
	token=strtok(NULL," ");
	char bufIp[100];
	strcpy(bufIp,token);
	token=strtok(NULL," ");
	unsigned short * portPtr=((unsigned short *)token);
	unsigned short port=*portPtr;
	port=ntohs(port);

	pthread_mutex_lock(&mtxClient);
	clients.deleteNode(bufIp,port);
	pthread_mutex_unlock(&mtxClient);

	
}


void userOn(char * buf){

	char * token=strtok(buf," ");
	token=strtok(NULL," ");
	char bufIp[100];
	strcpy(bufIp,token);
	token=strtok(NULL," ");
	unsigned short * portPtr=((unsigned short *)token);
	unsigned short port=*portPtr;
	port=ntohs(port);
	
	pthread_mutex_lock(&mtxClient);
	clients.insertNode(bufIp,port);
	pthread_mutex_unlock(&mtxClient);
	
	BufferElement element;
	element.setBufferElement(bufIp,port);

	insertElementToBuffer(&element);
	cout<<bufIp<<" kai to port "<<port<<endl;
}

void d_connection(struct sockaddr**sptr,struct sockaddr**cptr, struct sockaddr_in *server, struct sockaddr_in *client,int *sock,int port,socklen_t *clientlen){

	*sptr = (struct sockaddr *)server;
	*cptr = (struct sockaddr *)client;
	if ((*sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
        	perror_exit((char *)"socket");
    	server->sin_family = AF_INET;       /* Internet domain */
    	server->sin_addr.s_addr = htonl(INADDR_ANY);
    	server->sin_port = htons(port);    //printf("eimai edw bind\n");  /* The given port */
    	if (bind(*sock, *sptr, sizeof(*server)) < 0)
        	perror_exit((char*)"bind");
    	/* Listen for connections */
    	if (listen(*sock, 5) < 0) perror_exit((char*)"listen");
    	//printf("Listening for connections to port %d\n", port);
    	//if ((*sock = accept(*sock, *cptr, clientlen)) < 0) perror_exit("accept");
    	//printf("Create passive connection\n");
}

void insertElementToBuffer(BufferElement * element){
	pthread_mutex_lock(&mtxBuffer);
	while(cBuffer->isFull()){		//edw h oura einai gemath kai peftei gia "upno"
		pthread_cond_wait(&cv_prod, &mtxBuffer);	
	}
	cBuffer->insertElement(element->ip_address,element->port,element->pathName,element->version);

	pthread_mutex_unlock(&mtxBuffer);	//printf("SERVER THREAD enqueue---------------------------\n");
	pthread_cond_signal(&cv_consume);
}

void initializer(){
	pthread_mutex_init (& mtxClient , NULL ); 
	pthread_mutex_init (& mtxBuffer , NULL ); 
	//pthread_mutex_init (& mtxLast , NULL ); 
	pthread_cond_init (&cv_prod , NULL ); 
	pthread_cond_init (&cv_consume , NULL );
	cBuffer=new CycleBuffer(userArguments.bufferSize);


	int i, err;
	threads = (pthread_t*)malloc( sizeof(pthread_t) * (userArguments.workerThreads));
	for (i=0 ; i <userArguments.workerThreads ; i++)
		if ( err = pthread_create (& threads [i], NULL , consumerThread ,( void *) &i)) { 
			perror_exit ((char*)" pthread_create " ); 
		}
}

void *consumerThread(void * ptr){
	BufferElement temp;
	while(1){	

		pthread_mutex_lock(&mtxBuffer);

		while(cBuffer->isEmpty()){	//an einai adeia h lista
			pthread_cond_wait(&cv_consume, &mtxBuffer);
		}
		/*pthread_mutex_lock(&mtxLast);
		if(cBuffer->buffer[userArguments.bufferSize].version[0]){
			pthread_mutex_unlock(&mtxLast);
			break;
		}  //idopoiei to main thread gia termatismo
			
		pthread_mutex_unlock(&mtxLast);*/
		cBuffer->removeElement(&temp);

		pthread_mutex_unlock(&mtxBuffer);
		pthread_cond_signal(&cv_prod);
		if(temp.port==100){
			break;
		}
		//kaleite h sinatrisi gia na eksipiretithei h aitisi

		if(temp.version[0]==10){
			askGetFileList(&temp);
		}
		else{
			char kati[128];
			makeDirs(temp.pathName,kati,temp.ip_address,temp.port);
			strcpy(temp.pathName,kati);
			askGetFile(&temp);
		}


		
	}
	
	pthread_exit(NULL);

}

void askGetFile(BufferElement * temp){
	int sock;
	struct sockaddr_in server;
	struct sockaddr *serverptr = (struct sockaddr*)&server;
   	struct hostent *rem;
   	char ip_address[100];
   	strcpy(ip_address,temp->ip_address);
   	unsigned short port=temp->port;
   	cout<<"consumerThread "<<ip_address<<"  "<<port<<endl;
	makeconnection_serving(&serverptr,&rem,ip_address,&server,&sock,port);
	
	char buf[1000];
	sprintf(buf,"GET_FILE %s %s ",temp->pathName,temp->version);
	write(sock,buf,1000);
	sleep(3);
	read(sock,buf,1000);

	cout<<"STIN ASKGETFILE : "<<buf<<endl;
	char * token=strtok(buf," ");
	if(!(strcmp(token,"FILE_UP_TO_DATE"))){ //edw ksanabazoume to temp ston buffer wste na min xathei to arxeio.
		//insertElementToBuffer(temp);
		return;
	}
	cout<<"ep"<<endl;
	//char version[100];
	token=strtok(NULL,"\n");
	strcpy(temp->version,token);
	int size;
	token=strtok(NULL," ");
	size=atoi(token);

	receiveFile(size,sock,temp);
	close(sock);
	insertElementToBuffer(temp);



}

void askGetFileList(BufferElement * temp){

	int sock;
	struct sockaddr_in server;
	struct sockaddr *serverptr = (struct sockaddr*)&server;
   	struct hostent *rem;
   	char ip_address[100];
   	strcpy(ip_address,temp->ip_address);
   	unsigned short port=temp->port;
   	cout<<"consumerThread "<<ip_address<<"  "<<port<<endl;
	makeconnection_serving(&serverptr,&rem,ip_address,&server,&sock,port);
	
	char buf[1000];
	strcpy(buf,"GET_FILE_LIST ");
	write(sock,buf,1000);
	sleep(3);
	read(sock,buf,1000);

	cout<<"STIN ASKGETFILELIST : "<<buf<<endl;

	close(sock);
	//na balw to pathfile dld to path tou arxiou mono ayta na ta bazei ston buffer

	putFileToBuffer(buf,ip_address,port);



}

void putFileToBuffer(char * buf,char * ip_address,unsigned short port){
	char *token=strtok(buf," ");
	token=strtok(NULL," ");
	int count=atoi(token);
	int i;
	char filePath[128];
	char version[100];
	for(i=0;i<count;i++){
		token=strtok(NULL," ");
		if(token[strlen(token)-1]=='/'){
			token=strtok(NULL," ");
			continue;
		}
		strcpy(filePath,token);
		token=strtok(NULL,"\n");
		strcpy(version,token);
		strcat(version,"\n");
		BufferElement element;
		element.setBufferElement(ip_address,port,filePath,version);
		insertElementToBuffer(&element);

	}


}

void makeDirs(char * path,char *tempPath,char * ip_address,unsigned short port){
	//this function gets the path of the file and it creates all the dirs and sub dir the file path has..
	struct stat statbuf;
	char temp[100],temp2[1000];
	char tempPort[10];
	sprintf(tempPort,"%d",port);
	strcpy(temp,tempPort);
	strcat(temp,"_");
	strcat(temp,ip_address);

	if(stat(temp,&statbuf)==-1){
		
		mkdir(temp,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}
	int i,counter=0;
	strcpy(temp2,path);
	char * token;

	if(temp2[0]=='.'){	//checking if file starts with ./
		token=strtok(temp2,"/");
		token=strtok(NULL,"\0");
		strcpy(temp2,token);

		
	}
	token=strtok(temp2,"/");
	token=strtok(NULL,"\0");
	strcpy(tempPath,token);
	
	for(i=0;i<strlen(tempPath);i++){
		if(tempPath[i]=='/')
			counter++;
	}

	
	if(counter==0)
		return;
	strcpy(temp2,tempPath);
	strcat(temp,"/");
	token=strtok(temp2,"/");
	for(i=0;i<counter;i++){
		strcat(temp,token);
		
		if(stat(temp,&statbuf)==-1){
			//cout<<temp<<endl;
			cout<<mkdir(temp,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)<<endl;
		}
		strcat(temp,"/");
		token=strtok(NULL,"/");

	}
}

void receiveFile(unsigned int size, int sock,BufferElement * temp){
	char file[1000];
	sprintf(file,"%d",temp->port);		//this is the function the receiver calls to receiver
	strcat(file,"_");							//the file and to create the dirs in the mirrorDir
	strcat(file,temp->ip_address); 				//and also to create the file
	strcat(file,"/");
	strcat(file,temp->pathName);
	char buffer[size+1];
	char * ptr=buffer;
	int bytes=0;
	int len=size;
	int len2=size;
	int forc=size;
	int i;
	

	while(len2>0){

		bytes=read(sock,ptr,1000);
		
		ptr+=bytes;
		len2-=bytes;
	}

	FILE * fp=fopen(file,"w"); //create file
	
	for( i=0;i<forc;i++){
		
		fputc(buffer[i],fp);

	}
	fclose(fp);
	


}


//connection me ton server
void makeconnection_serving(struct sockaddr **serverptr,struct hostent **rem,char* sname,struct sockaddr_in *server, int *sock,short port){
	*serverptr = (struct sockaddr*)server;
    	if ((*sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    		perror_exit((char*)"socket");	
    	if ((*rem = gethostbyname(sname)) == NULL) {	
	   		herror((char*)"gethostbyname"); exit(1);
    	}
        server->sin_family = AF_INET;       /* Internet domain */
    	memcpy(&server->sin_addr, (*rem)->h_addr, (*rem)->h_length);
    	server->sin_port = htons(port);         /* Server port */
    	/* Initiate connection */
    	if (connect(*sock, *serverptr, sizeof(*server)) < 0)
	   		perror_exit((char*)"connect");
    	printf("Connecting to %s port %d\n", sname, port);
}


void convert_to_binary(unsigned short port, char * b){
	unsigned short net_port;
	net_port=htons(port);
	char * ptr=(char*)&net_port;
	b[0]=*ptr;
	b[1]=*(ptr+1);
	b[2]='\0';


}

void perror_exit(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}

bool argvCheck(int argc, char ** argv){ // check to see if arguments are correct..

	int i;
	int counter=0;
	if(argc!=13)
		return false;
	
	for(i=1;i<argc;i+=2){
		if(!strcmp(argv[i],"-d")){
			strcpy(userArguments.dirName,argv[i+1]);
			counter++;
			
		}
		else if(!strcmp(argv[i],"-p")){
			if(!(isNumber(argv[i+1])))
				return false;
			userArguments.clientPort=atoi(argv[i+1]);
			counter++;
		}
		else if(!strcmp(argv[i],"-w")){
			if(!(isNumber(argv[i+1])))
				return false;
			userArguments.workerThreads=atoi(argv[i+1]);
			counter++;
		}
		else if(!strcmp(argv[i],"-b")){
			if(!(isNumber(argv[i+1])))
				return false;
			userArguments.bufferSize=atoi(argv[i+1]);
			counter++;
		}
		else if(!strcmp(argv[i],"-sp")){
			if(!(isNumber(argv[i+1])))
				return false;
			userArguments.serverPort=atoi(argv[i+1]);
			counter++;
		}
		else if(!strcmp(argv[i],"-sip")){
			strcpy(userArguments.serverIP,argv[i+1]);
			counter++;
		}
		

	}
	if (counter!=6)
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

void recDirContent(const char *name,InputList * inputList){ //Read clients InputFile and pass it inside an input list
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;
    char path[1024];
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            if(name[strlen(name)-1]=='/'){
            	sprintf(path, "%s%s/", name, entry->d_name);
            }
            else
            	sprintf(path, "%s/%s/", name, entry->d_name);
            //printf("%s\n", path);
            inputList->InsertNode(path,(char*)"File");
            recDirContent(path,inputList);
        } else {
        	struct stat attr;
	    	sprintf(path, "%s%s", name, entry->d_name);
	    	stat(path, &attr);
	    	char version[100];
		    strcpy(version,ctime(&attr.st_mtime));
	    	inputList->InsertNode(path,version);
            //printf("%s\n", path);
        }
    }
    closedir(dir);
}


