#include "askisi3.h"




ListNode * Create(){ //create list
	ListNode * dummy=(ListNode *)malloc(sizeof(ListNode));
	dummy->next=NULL;
	return dummy;
	
}

void Print (ListNode * head){ //print list
	ListNode* temp=head->next;
	while(temp){
		printf("%d\t",temp->nodeId);
		temp=temp->next;
	}
	printf("\n");
	
}

void InsertLast(ListNode * head, int nodeId){ //insert node into list
	ListNode* temp=head;
	while(temp->next){
		temp=temp->next;	
	}
	ListNode * newNode=(ListNode *)malloc(sizeof(ListNode));
	newNode->nodeId=nodeId;
	newNode->next=NULL;
	temp->next=newNode;
	
	
	
}

 ListNode * Merge(ListNode * list1,ListNode* list2){ //merge sorted lists with the help of a third pointer that always shows 
 													 //what to compare and where the ptr should point
	 
	ListNode * temp1=list1->next;
	ListNode * temp2=list2->next;
	ListNode * hold;
	ListNode * begin;
	if(temp1==NULL){
		
		return list2;
	}
	if(temp2==NULL){
		return list1;
	}
	if(temp1 && temp2){
		if(temp1->nodeId <= temp2->nodeId){
			hold=list1;
			temp1=hold->next;
		}
		else{
			hold=list2;
			temp2=hold->next;
		}
	}
	begin=hold;
	while(temp1 && temp2){
		if(temp1->nodeId <= temp2->nodeId){
			hold->next=temp1;
			hold=temp1;
			temp1=hold->next;
			
		}
		else{
			hold->next=temp2;
			hold=temp2;
			temp2=hold->next;
			
		}
	}
	if(temp1==NULL)
		hold->next=temp2;
	if(temp2==NULL)
		hold->next=temp1;
		
	return begin;
 		
	
    
}


int main(){
	ListNode * list1=Create();
	InsertLast(list1,2);
	InsertLast(list1,10);
	InsertLast(list1,15);
	InsertLast(list1,456);
	printf("List1: \n");
	Print(list1);
	ListNode * list2=Create();
	InsertLast(list2,5);
	InsertLast(list2,8);
	InsertLast(list2,500);
	InsertLast(list2,678);
	printf("List2: \n");
	Print(list2);
	ListNode * mergedList=Merge(list1,list2);
	printf("Merged list: \n");
	Print(mergedList);
	
	
	
	
		
}
