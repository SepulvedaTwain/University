#include "MyStructs.h"

ClientList::~ClientList(){
	ClientNode * temp;
	while(head){
		temp=head;
		head=head->next;
		delete temp;
	}
}


void ClientList::insertNode(char * ip, unsigned short port){
	if(findNode(ip,port)){
		cout<<"Node Exists"<<endl;
		return;
	}
	ClientNode * temp=new ClientNode(ip,port);

	if(head==NULL){
		head=temp;
		tail=temp;
		return;

	}
	tail->next=temp;
	tail=temp;

}
bool ClientList::findNode(char * ip,unsigned short port){
	ClientNode * temp=head;
	while(temp){
		if(  (!strcmp(temp->ip_address,ip)) && temp->port==port ){
			temp->active=true;
			return true;
		}
		temp=temp->next;
	}
	return false;

}
void ClientList::deleteNode(char * ip, unsigned short port){
	if(!findNode(ip,port)){
		return;
	}
	ClientNode * temp=head;
	while(temp){
		if(  (!strcmp(temp->ip_address,ip)) && temp->port==port ){
			temp->active=false;
			return;
		}
		temp=temp->next;
	}

}

void ClientList::make_inactive(char * ip,unsigned short port){
	ClientNode * temp=head;
	while(temp){
		if(  (!strcmp(temp->ip_address,ip)) && temp->port==port ){
			temp->active=false;
			return;
		}
		temp=temp->next;
	}


}

ThreadList::~ThreadList(){
	ThreadNode * temp;
	while(head){
		temp=head;
		head=head->next;
		delete temp;
	}

}

void ThreadList::insertTheard(pthread_t t_id){
	ThreadNode * temp=new ThreadNode(t_id);

	if(head==NULL){
		head=temp;
		tail=temp;
		return;

	}
	tail->next=temp;
	tail=temp;

}