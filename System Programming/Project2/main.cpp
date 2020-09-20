#include "main.h"

using namespace std;

bool argvCheck(int argc, char ** argv,UserArguments &userArguments){ // check to see if arguments are correct..

	int i;
	int counter=0;
	if(argc!=13)
		return false;
	for(i=1;i<argc;i+=2){
		if(!strcmp(argv[i],"-n")){
			userArguments.id=new char[strlen(argv[i+1]+1)];
			strcpy(userArguments.id,argv[i+1]);
			counter++;
			
		}
		else if(!strcmp(argv[i],"-c")){
			userArguments.common_dir=new char[strlen(argv[i+1]+1)];
			strcpy(userArguments.common_dir,argv[i+1]);
			counter++;
		}
		else if(!strcmp(argv[i],"-i")){
			userArguments.input_dir=new char[strlen(argv[i+1]+1)];
			strcpy(userArguments.input_dir,argv[i+1]);
			counter++;
		}
		else if(!strcmp(argv[i],"-m")){
			userArguments.mirror_dir=new char[strlen(argv[i+1]+1)];
			strcpy(userArguments.mirror_dir,argv[i+1]);
			counter++;
		}
		else if(!strcmp(argv[i],"-b")){
			if(!(isNumber(argv[i+1])))
				return false;
			userArguments.bufferSize=atoi(argv[i+1]);
			counter++;
		}
		else if(!strcmp(argv[i],"-l")){
			userArguments.log_file=new char[strlen(argv[i+1]+1)];
			strcpy(userArguments.log_file,argv[i+1]);
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
            inputList->InsertNode(path);
            recDirContent(path,inputList);
        } else {
	    	sprintf(path, "%s%s", name, entry->d_name);
	    	inputList->InsertNode(path);
            //printf("%s\n", path);
        }
    }
    closedir(dir);
}


void UpdatedMirrorList(UserArguments &userArguments,MirrorList &mirrorList){ // read the common file and see
	//if there are any new clients and insert them inside the list

	char fileName[100];
	strcpy(fileName,userArguments.id);
	strcat(fileName,".id");
	DIR * dir;
	struct dirent *dent;
	char buffer[userArguments.bufferSize];
	dir=opendir(userArguments.common_dir);
	if(dir!=NULL){
		
		while((dent=readdir(dir))!=NULL){
			//cout<<dent->d_name<<endl;
			if (strcmp(dent->d_name, ".") != 0 && strcmp(dent->d_name, "..") != 0 && strcmp(dent->d_name,fileName)){
				if(dent->d_name[strlen(dent->d_name)-1]=='o'){
					continue;
				}
				if(mirrorList.isNodeExist(dent->d_name)){

					continue;
				}
				
                mirrorList.InsertNode(dent->d_name);
			}

				

		}

	}
	closedir(dir);
}

void sendFile(UserArguments &userArguments,InputNode * inputNode, int fd){ 
	//the function the sender child calls to send the inputFile to the receiver

	char buffFile[inputNode->size+1];

	FILE *fp = fopen(inputNode->path, "r");
  	int count=0;
  	int ch = getc(fp); 
  	while (ch != EOF){ 
 
    	buffFile[count++]=ch;  
		ch = getc(fp); 
	} 
	buffFile[count]='\0';
	fclose(fp);

	write(fd,inputNode->strPathLen,2);

	write(fd,inputNode->path,strlen(inputNode->path));
	if(inputNode->path[strlen(inputNode->path)-1]=='/'){ //if it's a file no need to send the size and the file 
		return;
	}
	
	write(fd,inputNode->strSize,4);
	
	char * pBuff=buffFile;
	int size=inputNode->size;
	while(size>0){
		write(fd,pBuff,userArguments.bufferSize);
		pBuff+=userArguments.bufferSize;
		size-=userArguments.bufferSize;
	
		//cout<<buffFile<<endl;
	}
	
	
	 

}

void Sender(UserArguments &userArguments,InputList &inputList,MirrorList &mirrorList){ //the child sender function

	MirrorNode * temp=mirrorList.head;
	char buff[userArguments.bufferSize+1];
	while(temp){
		if(temp->transfered==false){
			char pipeName[100];
			strcpy(pipeName,userArguments.common_dir);
			strcat(pipeName,"/");
			strcat(pipeName,userArguments.id);
			strcat(pipeName,"_to_");
			strcat(pipeName,temp->id);
			strcat(pipeName,".fifo");
			mkfifo(pipeName,0666);	//creating the pipe for communication
			int fd=open(pipeName,O_WRONLY);
			InputNode * tmp=inputList.head;
			while(tmp){

				sendFile(userArguments,tmp,fd); //calls the sendFile function
				
				
				tmp=tmp->next;
			}

			char zero[3];
			unsigned short temp=0;
			zero[0]=temp;
			temp>>=8;
			zero[1]=temp;
			zero[2]='\0';
			write(fd,zero,2);	//sent "00" to end the communication
			close(fd);


		}


		temp->transfered=true;	//change the transfered value so next time it wont send it..
		temp=temp->next;
	}
	exit(0);	//call exit() so parent nows the child is done

}

unsigned short makeStrToShort(char * str){ //from str[] to unsigned short so the receiver use the number..
	unsigned short temp=0;
	temp=temp | str[1];
	temp<<=8;
	temp=temp | str[0];
	return temp;


}

unsigned int makeStrToUnint(char * str){ //from str[] to unsigned int so the receiver use the number..
	unsigned int temp=0;
	temp=temp | str[3];
	temp<<=8;
	temp=temp | str[2];
	temp<<=8;
	temp=temp | str[1];
	temp<<=8;
	temp=temp | str[0];
	return temp;
}

void makeDirs(UserArguments &userArguments,char * path,char *tempPath,MirrorNode * mirrorNode){
	//this function gets the path of the file and it creates all the dirs and sub dir the file path has..
	struct stat statbuf;
	char temp[100],temp2[1000];
	strcpy(temp,userArguments.mirror_dir);
	strcat(temp,"/");
	strcat(temp,mirrorNode->id);

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
//===================
//===================

//Autos pou diavazei to pipe asxetos me to posous xaraktires zitaei na diavasei telika diavazei
//osous pragmatika egrapse o Sender kai episis an o read exei zitithei na diavasei < apo ton sender diavazei
//ta zitoumena

void receiveFile(UserArguments &userArguments,unsigned int size,char * pathFileName, int fd,MirrorNode * mirrorNode){
	char tempPath[1000];
	char file[1000];
	makeDirs(userArguments,pathFileName,tempPath,mirrorNode);

	strcpy(file,userArguments.mirror_dir);		//this is the function the receiver calls to receiver
	strcat(file,"/");							//the file and to create the dirs in the mirrorDir
	strcat(file,mirrorNode->id); 				//and also to create the file
	strcat(file,"/");
	strcat(file,tempPath);
	char buffer[size+1];
	char * ptr=buffer;
	int bytes=0;
	int len=size;
	int len2=size;
	int forc=size;
	int i;
	

	while(len2>0){

		bytes=read(fd,ptr,userArguments.bufferSize);
		
		ptr+=bytes;
		len2-=bytes;
	}

	FILE * fp=fopen(file,"w"); //create file
	
	for( i=0;i<forc;i++){
		
		fputc(buffer[i],fp);

	}
	fclose(fp);
	


}

void Receiver(UserArguments &userArguments,MirrorList &mirrorList){ //function receiver child calls
	int fd,rd,count=0;
	MirrorNode * temp=mirrorList.head;
	char buff[1000];
	char filePath[1000];
	while(temp){
		if(temp->transfered==false){
			//kanoume ton id fakelo
			char pipeName[100];
			strcpy(pipeName,userArguments.common_dir);
			strcat(pipeName,"/");
			strcat(pipeName,temp->id);
			strcat(pipeName,"_to_");
			strcat(pipeName,userArguments.id);
			strcat(pipeName,".fifo");
			mkfifo(pipeName,0666);	//create the pipe for communication
			fd=open(pipeName,O_RDONLY);


			while(1){


				rd=read(fd,buff,2);
				buff[2]='\0';
				unsigned short nameLen=makeStrToShort(buff); //read the name Len
				//cout<<"nameLen   "<<int(nameLen)<<endl;
				if(nameLen==0){
					
					break;
				}

				
				rd=read(fd,filePath,nameLen);
				filePath[nameLen]='\0';	//read  file path
				//cout<<"Name   "<<filePath<<"\t id  "<<temp->id<<endl;

				if(filePath[nameLen-1]=='/'){
					
					continue;	//if folder continue
				}
				

				rd=read(fd,buff,4);
				buff[4]='\0';
				unsigned int fileSize=makeStrToUnint(buff);	//read file size
				//cout<<fileSize<<endl;


				receiveFile(userArguments,fileSize,filePath,fd,temp); //create the dirs of the path and then the file

				FILE * log=fopen(userArguments.log_file,"w");
				fprintf(log,"Size of file : %d  Name of File : %s it came from : %s \n",fileSize,filePath,temp->fileId);
				fclose(log);

			}

			close(fd);


			
		}
		temp->transfered=true;
		temp=temp->next;
	}


	exit(0);
}

bool isRemoved(UserArguments &userArguments,MirrorNode * head){ //function delete child call *incomplete*
	if(head==NULL)
		return false;
	MirrorNode * temp=head;
	int child,status;
	while(temp){
		if(temp->isRemoved==true){
			child=fork();
			if(child==0){
				//cout<<"PLEASE"<<endl;
				
				exit(0);
			}
			child=wait(&status);

		}
		temp=temp->next;
	}

}

int main(int argc,char ** argv){
	UserArguments userArguments;
	if(!argvCheck(argc,argv,userArguments)){ //check args
		cout<<"Wrong Arguments"<<endl;
		return 1;
	}
	struct stat statbuf;
	if(stat(userArguments.input_dir,&statbuf)==-1){ //if input does not exist exit
		cout<<"Input dir file does not exits"<<endl;
		return 1;
	}

	if(mkdir(userArguments.mirror_dir,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)!=0){ //if mirror dir exist end
		cout<<"Mirror dir file already exists"<<endl;
		return 1;
	}
	
	if(mkdir(userArguments.common_dir,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)==0){ //if common is does not exist make one
		cout<<"new common_dir was created"<<endl;
	}
	FILE * log;
	log=fopen(userArguments.log_file,"w"); //create log file
	fclose(log);



	//create lists
	MirrorList mirrorList;
	InputList inputList;
	//---------

	char fileName[100];
	strcpy(fileName,userArguments.id);
	strcat(fileName,".id");
	DIR * dir;
	struct dirent *dent;
	char buffer[userArguments.bufferSize];
	dir=opendir(userArguments.common_dir);
	if(dir!=NULL){	//read common dir to update mirrorList
		
		while((dent=readdir(dir))!=NULL){

			if(!strcmp(dent->d_name,fileName)){
				rmdir(userArguments.mirror_dir);
				cout<<"Another client is running with the same Id"<<endl;
				return 1;
			}
			if(dent->d_name[strlen(dent->d_name)-1]=='o'){
					continue;
			}
			if (strcmp(dent->d_name, ".") != 0 && strcmp(dent->d_name, "..") != 0){
				//cout<<dent->d_name<<"\t"<<userArguments.id<<endl;
                mirrorList.InsertNode(dent->d_name);
			}
				

		}
		char temp1[100];
		strcpy(temp1,userArguments.common_dir);
		strcat(temp1,"/");
		strcat(temp1,fileName);

		ofstream write (temp1);
		if(write.is_open()){
			write<<getpid()<<endl;
			write.close();	

		}
		else{
			cout<<"Unable to open file";
			return 1;
		}

	}

	closedir(dir);


	//cout<<"================="<<endl;
	recDirContent(userArguments.input_dir,&inputList);
	cout<<"================="<<endl;
	mirrorList.Print(mirrorList.head);
	cout<<"================="<<endl;
	inputList.Print(inputList.head);
	cout<<"================="<<endl;
	

	pid_t child;
	int status;
	//makeDirs(userArguments,char * path,char *tempPath,MirrorNode * mirrorNode)
	while(1){	// if node in mirrorlist is not transfered then transfer it then update the mirror list delete id nessesary and repeat
		if(mirrorList.isListChanged()){
			
			child=fork();
			if(child==0){
				Sender(userArguments,inputList,mirrorList);
			}
			child=fork();
			if(child==0){
				//kalw sinatrisi gia child2;
				Receiver(userArguments,mirrorList);
			}
			child=wait(&status);
			child=wait(&status);
		
			
		}
		else{
			sleep(5);

		}
		mirrorList.visitedFalse();
		UpdatedMirrorList(userArguments,mirrorList);
		isRemoved(userArguments,mirrorList.head);

	}
	

}




