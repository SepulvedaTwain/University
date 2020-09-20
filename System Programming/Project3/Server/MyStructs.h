#ifndef MYSTRUCTS_H
#define MYSTRUCTS_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

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

class ThreadNode{

	public:
		pthread_t t_id;
		ThreadNode * next;

		ThreadNode(pthread_t t_id):t_id(t_id),next(NULL){}



};

class ThreadList{
	public:
		ThreadNode * head;
		ThreadNode * tail;
		ThreadList():head(NULL),tail(NULL){}
		~ThreadList();
		void insertTheard(pthread_t t_id);

};



#endif
