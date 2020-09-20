#include "askisi2.h"


int compare(ItemType a,ItemType b){ //compare function
	return strcmp((char *)a,(char *)b);	
	
}

AirportNode * Create(){ //create list
	AirportNode * head=(AirportNode *)malloc(sizeof(AirportNode));
	AirportNode * tail=(AirportNode *)malloc(sizeof(AirportNode));
	head->next=tail;
	head->prv=NULL;
	tail->next=NULL;
	tail->prv=head;
	
	return head;
	
}

void Print (AirportNode * head,char * format){ //print list
	AirportNode* temp=head->next;
	
	while(temp->next){
		if(!strcmp(format,"%s"))
			printf("%s\t",(char *)temp->itemtype);
		temp=temp->next;
		//diaforetika an ypirxan alloi typoi tha kaname else gia tin kathe periptwsi
	}
	printf("\n");
	
}

AirportNode * Search(AirportNode * head, ItemType itemtype,CompareType cmp){  //search for node in list
	AirportNode* temp=head->next;
	
	while(temp->next){
		if(!cmp(itemtype,temp->itemtype))
			return temp;
		temp=temp->next;
	}
	//o last dummy an den brei kati
	return temp->next; //opote stelnoume to ->next gia na paroume null an den to brei
	
}


void InsertLast(AirportNode* head,ItemType  itemtype){ //insert node into the list
	AirportNode* temp=head->next;
	while(temp->next){
		temp=temp->next;
	}
	AirportNode * newNode=(AirportNode *)malloc(sizeof(AirportNode));
	newNode->itemtype=(char*)malloc(sizeof(char*)*strlen((char*)itemtype)+1);
	strcpy((char *)newNode->itemtype,(char *)itemtype);
	temp->prv->next=newNode;
	newNode->prv=temp->prv;
	temp->prv=newNode;
	newNode->next=temp;

}

void InsertAfter (AirportNode *head , ItemType itemtype, AirportNode * node ){ //insert node after a node
	if(node==NULL){
		InsertLast(head,itemtype);
	}
	AirportNode* newNode=(AirportNode *)malloc(sizeof(AirportNode));
	newNode->itemtype=(char*)malloc(sizeof(char*)*strlen((char*)itemtype)+1);
	strcpy((char*)newNode->itemtype,(char*)itemtype);
	//AirportNode * temp=node;
	node->next->prv=newNode;
	newNode->next=node->next;
	node->next=newNode;
	newNode->prv=node;

	
}

void InsertBefore(AirportNode * head, ItemType itemtype,AirportNode *node){ //insert node before a node
	if(node==NULL){
		InsertLast(head,itemtype);
	}
	AirportNode* newNode=(AirportNode *)malloc(sizeof(AirportNode));
	newNode->itemtype=(char*)malloc(sizeof(char*)*strlen((char*)itemtype)+1);
	strcpy((char*)newNode->itemtype,(char*)itemtype);
	node->prv->next=newNode;
	newNode->prv=node->prv;
	node->prv=newNode;
	newNode->next=node;
}

void DeleteLast(AirportNode * head){ //delete last node
	AirportNode* temp=head->next;
	while(temp->next->next){
		temp=temp->next;
	}
	if(temp->prv->prv==NULL){
		
		return;
	}
	temp->prv->next=temp->next;
	temp->next->prv=temp->prv;
	free(temp);

}

void Delete (AirportNode *head , AirportNode *node){ //delete the given node
	if(node==NULL){
		DeleteLast(head);
		return;
	}
	AirportNode * temp=head->next;
	
	while(temp->next){
		//printf("ga");
		if(!strcmp((char*)temp->itemtype,(char*)node->itemtype)){
			
			break;
		}
		temp=temp->next;
	}
	if(!strcmp((char*)temp->itemtype,(char*)node->itemtype)){
		temp->prv->next=temp->next;
		temp->next->prv=temp->prv;
		free(temp);
	}
	
}




//Search( x , x , compare);


int main(){
	//printf("%d\n",compare("ASD","AsD"));
	AirportNode* list=Create();
	char format[]="%s";
	
	InsertLast(list,(char *)"ASD");
	Print(list,format);
	InsertLast(list,(char *)"DFD");
	Print(list,format);
	InsertLast(list,(char *)"LSD");
	Print(list,format);
	InsertLast(list,(char *)"RTM");
	Print(list,format);
	InsertAfter(list,(char*)"EDW",list->next->next->next);
	Print(list,format);
	InsertBefore(list,(char*)"EDW",list->next->next);
	Print(list,format);
	printf("%s\n",(char*)Search(list,(char*)"LSD",compare)->itemtype);
	DeleteLast(list);
	Print(list,format);
	DeleteLast(list);
	Print(list,format);
	Delete(list,list->next->next);
	Print(list,format);

	

	
	
}
