#include "myStructs.h"

void List::insertNewPage(int position,char * rw){
	ListNode* temp=new ListNode(position,rw);

	if(temp->r_w=='R')
		readCounter++;
	else
		writeCounter++;

	if(isEmpty()){
		head=temp;
		tail=temp;
		counter++;
		return;
	}

	head->prv=temp;
	temp->next=head;
	head=temp;
	counter++;
	return;

}

int List::RemoveLastNode(){
	if(isEmpty())
		return -1;

	tail->prv->next=NULL;
	ListNode *temp=tail;
	tail=tail->prv;
	int position=temp->position;
	delete temp;
	counter--;

	return position;



}

ListNode * List::FindPage(char* page,char * rw){
	if(isEmpty()){
		pfCounter++;
		return NULL;
	}

	char tempstr[10];
	strcpy(tempstr,page);
	


	ListNode * temp=head;
	while(temp){
		if(!strcmp(ipt->ipt[temp->position].page,tempstr)){	//edw tin kanoyme write an htan read kai ginei write
			
			referenceCounter++;
			if(temp->r_w=='R' && rw[0]=='W'){
				writeCounter++;
				temp->r_w='W';
			}
			return temp;

		}
		temp=temp->next;
	}
	pfCounter++;
	return NULL;

}
void List::MoveAtFront(ListNode * page){
	
	if(page==head)
		return;
	if(page==tail){
		tail=tail->prv;
		tail->next=NULL;
	}

	page->prv->next=page->next;
	if(page->next!=NULL)
		page->next->prv=page->prv;
	head->prv=page;
	page->next=head;
	head=page;


}

List::~List(){
	ListNode *temp;
	while(head){
		temp=head;
		head=head->next;
		delete temp;
	}

}


void List::LRU(char * page,char * rw){


	page[strlen(page)-3]='\0';
	int position;

	ListNode * temp=FindPage(page,rw);
	
	if(temp==NULL){

		if(ipt->isFull()){
			position=RemoveLastNode();
			ipt->ipt[position].pid=pid;
			strcpy(ipt->ipt[position].page,page);
			insertNewPage(position,rw);
			return;
		}
		else{

			position=ipt->insertPage(pid,page);
			insertNewPage(position,rw);
			return;
		}

	}
	MoveAtFront(temp);
	return;


}


//_______________________________________WORKIGN SET____________________________-


WsList::~WsList(){
	WsNode *temp;
	if(isEmpty())
		return;
	
	while(head){
		temp=head;
		head=head->next;
		delete temp;
	}
}


void WsList::WsTickUpdate(clock_t currentTime){


	WsNode *temp=head;
	WsNode *deleteNode;

	int position;

	while(temp){

		if(temp->referenceBit){
			temp->time=currentTime;
			temp->referenceBit=false;
		}
		else{
			if((temp->time + tick)>currentTime){
				deleteNode=temp;
				temp=temp->next;
				position=RemoveNode(deleteNode);
				ipt->ipt[position].pid=-1;

				continue;

			}

		}

		temp=temp->next;
	}
}

int WsList::RemoveNode(WsNode * node){
	
	if(isEmpty())
		return -1;

	int position;

	if(counter==1){
		head=NULL;
		tail=NULL;
		counter--;
		position=node->position;
		delete node;
		return position;
	}

	if(node==head){
		head=head->next;
		head->prv=NULL;
		counter--;
		position=node->position;
		delete node;
		return position;
	}

	if(node==tail){
		tail->prv->next=NULL;
		tail=tail->prv;
		counter--;
		position=node->position;
		delete node;
		return position;
	}

	node->prv->next=node->next;
	node->next->prv=node->prv;
	counter--;
	position=node->position;
	delete node;
	return position;



}

bool  WsList::FindPage(char* page,char * rw){
	if(isEmpty()){
		pfCounter++;
		return false;
	}

	char tempstr[10];
	strcpy(tempstr,page);
	


	WsNode * temp=head;
	while(temp){
		if(!strcmp(ipt->ipt[temp->position].page,tempstr)){	//edw tin kanoyme write an htan read kai ginei write
			temp->referenceBit=true;
			referenceCounter++;
			if(temp->r_w=='R' && rw[0]=='W'){
				writeCounter++;
				temp->r_w='W';
			}
			return true;

		}
		temp=temp->next;
	}
	pfCounter++;
	return false;

}



void WsList::Ws(char * page,char * rw){

	page[strlen(page)-3]='\0';
	int position;

	clock_t currentTime=clock();

	if((currentTime-tick)>start_time){
		WsTickUpdate(currentTime);
		start_time=currentTime;
	}
	
	if(FindPage(page,rw)){
		return;
	}

	if(ipt->isFull()){
		WsNode * temp=tail;
		position=RemoveNode(temp);
		ipt->ipt[position].pid=pid;
		strcpy(ipt->ipt[position].page,page);
		insertNewPage(position,rw,currentTime);
		return;

	}

	position=ipt->insertPage(pid,page);
	insertNewPage(position,rw,currentTime);

}





void WsList::insertNewPage(int position,char * rw,clock_t time){



	WsNode* temp=new WsNode(position,rw,time);

	if(temp->r_w=='R')
		readCounter++;
	else
		writeCounter++;

	if(isEmpty()){
		head=temp;
		tail=temp;
		counter++;
		return;
	}

	head->prv=temp;
	temp->next=head;
	head=temp;
	counter++;
	return;

}

