#include "askisi1.h"


AirportNode * Create(){ // create list
	AirportNode * dummy=(AirportNode *)malloc(sizeof(AirportNode));
	dummy->next=NULL;
	return dummy;
	
}

void Print (AirportNode * head){ //print list
	AirportNode* temp=head->next;
	while(temp){
		printf("%s\t",temp->airportCode);
		temp=temp->next;
	}
	printf("\n");
	
}

AirportNode * Search(AirportNode * head , AirportCode airportCode ){ // search list
	AirportNode* temp=head->next;
	while(temp){
		if(!strcmp(temp->airportCode,airportCode))
			return temp;
		temp=temp->next;
	}
	return temp;
	
}


void InsertLast(AirportNode * head, AirportCode airportCode){ //insert node
	AirportNode* temp=head;
	while(temp->next){
		temp=temp->next;	
	}
	AirportNode * newNode=(AirportNode *)malloc(sizeof(AirportNode));
	strcpy(newNode->airportCode,airportCode);
	newNode->next=NULL;
	temp->next=newNode;
	
	
	
}


void InsertAfter(AirportNode * head, AirportCode airportCode, AirportNode * node ){ //insert node after a node
	if(node==NULL){ //ara tha mpei sto telos
		InsertLast(head,airportCode);
		return;
		
	}
	AirportNode* newNode=(AirportNode *)malloc(sizeof(AirportNode));
	strcpy(newNode->airportCode,airportCode);
	newNode->next=NULL;
	if(node->next==NULL){
		node->next=newNode;
		return;
	}
	AirportNode*temp=node->next;
	node->next=newNode;
	newNode->next=temp;
	
	
}

void DeleteLast(AirportNode * head){ //delete last node
	if(head->next==NULL){
		return;
	}
	AirportNode* temp=head;
	while(temp->next->next){
		temp=temp->next;	
	}
	
	free(temp->next);
	temp->next=NULL;
}


void Delete (AirportNode *head , AirportNode * node){ //delete the given node
	if(node==NULL){ //ara tha diagrapsei to last
		DeleteLast(head);
		return;	
	}
	AirportNode* temp=head;
	while(temp->next){
		if(!strcmp(temp->next->airportCode,node->airportCode))
			break;
		temp=temp->next;	
	}
	if(!strcmp(temp->next->airportCode,node->airportCode)){
		AirportNode * nextNode=temp->next->next;
		free(temp->next);
		temp->next=nextNode;
	}
	
}

int main(){
	
	AirportNode* list=Create();
	InsertLast(list,"ASD");
	Delete(list,list->next);
	Print(list);
	InsertLast(list,"XVD");
	InsertLast(list,"IOP");
	Print(list);
	InsertAfter(list,"LAL",NULL);
	Print(list);
	InsertAfter(list,"HRO",list->next->next);
	Print(list);
	printf("%s\n",(Search(list,"HRO"))->airportCode);
	DeleteLast(list);
	Print(list);
	Delete(list,list->next->next);
	Print(list);
	

}
