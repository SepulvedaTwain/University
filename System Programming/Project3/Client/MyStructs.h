#ifndef MYSTRUCTS_H
#define MYSTRUCTS_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>



using namespace std;

class ClientNode{

	public:
		char ip_address[100];
		unsigned short port;
		bool active;
		ClientNode * next;

		ClientNode(char * ip, unsigned short port):port(port),next(NULL),active(true){
			strcpy(ip_address,ip);
		}


};

class ClientList{
	public:
		ClientNode * head;
		ClientNode * tail;
		ClientList():head(NULL),tail(NULL){}
		~ClientList();
		void insertNode(char * ip,unsigned short port);
		bool findNode(char * ip,unsigned short port);
		void deleteNode(char * ip,unsigned short port);
		void make_inactive(char * ip,unsigned short port);
		void print();

};



class BufferElement{
	public:
		char pathName[128];
		char version[100];
		char ip_address[128];
		unsigned short port;
		void setBufferElement(char * ip_address,unsigned short port,char* pathName=NULL,char * version=NULL);
		BufferElement():port(0){
			version[0]=10;
		}
};

class CycleBuffer{
	public:
		int input;
		int output;
		int size;
		BufferElement * buffer;
		CycleBuffer(int size):size(size),input(0),output(0){
			buffer=new BufferElement[size+1];
			buffer[size].version[0]=0;

		}
		~CycleBuffer(){
			
			delete [] buffer;
			//free(buffer);
		}
		void insertElement(char * ip_address,unsigned short port,char* pathName=NULL,char * version=NULL);
		void removeElement(BufferElement * element);
		bool isFull();
		bool isEmpty();

};

class InputNode{
	public:
		char path[100];
		unsigned short pathLen;
		size_t size;
		char strPathLen[3];
		char strSize[5];
		char version[100];
		InputNode * next;
		InputNode(char * path,char * version);
};

class InputList{
	public:
		InputNode * head;
		InputNode * tail;
		int counter;
		//con
		InputList():head(NULL),tail(NULL),counter(0){}
		//destr
		~InputList(){
			InputNode * temp;
			while(head){
				temp=head;
				head=head->next;
				delete temp;
			}


		}

		void InsertNode(char * fileName,char * version);
		void Print(InputNode * head);

};



#endif
