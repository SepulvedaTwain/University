#include <stdio.h>
#include <sys/wait.h>	     /* sockets */
#include <sys/types.h>	     
#include <sys/socket.h>	     
#include <netinet/in.h>	     /* internet sockets */
#include <netdb.h>	         /* gethostbyaddr */
#include <unistd.h>	         /* fork */		
#include <stdlib.h>	        
#include <ctype.h>	         
#include <signal.h>          /* signal */
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <iostream>
#include <arpa/inet.h>
#include "MyStructs.h"


typedef struct{
	int bufferSize;
	int workerThreads;
	char dirName[100];
	char serverIP[100];
	unsigned short serverPort;
	unsigned short clientPort;
}UserArguments;

bool isNumber(char * str);
bool argvCheck(int argc, char ** argv);

void recDirContent(const char *name,InputList * inputList);



void perror_exit(char *message);
void termination (int sig);

void makeconnection_serving(struct sockaddr **serverptr,struct hostent **rem,char* sname,struct sockaddr_in *server,
	int *sock,short port);

void d_connection(struct sockaddr**sptr,struct sockaddr**cptr,
	struct sockaddr_in *server, struct sockaddr_in *client,int *sock,int port,socklen_t *clientlen);

void *consumerThread(void * ptr);

void insertClientsToClientList(char * buf);

void getFileList(int socket);
void prepareListToSent(char * list);

void userOn(char * buf);
void userOff(char *buf);

void askGetFileList(BufferElement * temp);
void askGetFile(BufferElement * temp);

void getFile(int sock,char * buf);
void sendFile(char * filePath,char * version,size_t size1, int sock);


void insertElementToBuffer(BufferElement * element);

void putFileToBuffer(char * buf,char * ip_address,unsigned short);


void convert_to_binary(unsigned short port,char * b);

void initializer();


void makeDirs(char * path,char *tempPath,char * ip_address,unsigned short port);
void receiveFile(unsigned int size, int sock,BufferElement * temp);
