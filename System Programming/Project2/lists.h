#ifndef LISTS_H
#define LISTS_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <cstring>


class MirrorNode{
	public:
		char  id[1000];
		char  fileId[1000];
		int pId;
		bool transfered;
		bool isRemoved;
		bool visited;
		MirrorNode * next;
		MirrorNode(char * id);

};

class MirrorList{
	public:
		MirrorNode * head;
		MirrorNode * tail;
		int counter;
		//con
		MirrorList():head(NULL),tail(NULL),counter(0){}
		//destr
		~MirrorList(){
			MirrorNode * temp;
			while(head){
				temp=head;
				head=head->next;
				delete temp;
			}
		}


		void InsertNode(char * fileName);
		void Print(MirrorNode * head);
		bool isListChanged();
		bool isNodeExist(char * fileName);
		void visitedFalse();
		//na kanw ton destr
};

class InputNode{
	public:
		char path[100];
		unsigned short pathLen;
		size_t size;
		char strPathLen[3];
		char strSize[5];
		InputNode * next;
		InputNode(char * path);
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

		void InsertNode(char * fileName);
		void Print(InputNode * head);

};


#endif