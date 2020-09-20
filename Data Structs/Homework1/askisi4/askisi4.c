#include "askisi4.h"
  

void MergeSort(ListNode ** head) {  //split the lists until they have two nodes and then merge them etc..
	ListNode * temp = *head; 
	ListNode * list1; 
	ListNode * list2; 
	if ((temp == NULL) || (temp->next == NULL)) { 
	    return; 
	} 
	  
	
	Split(temp, &list1, &list2);  
	  
	
	MergeSort(&list1); 
	MergeSort(&list2); 
	  
	*head = SortedMerge(list1, list2); 
} 
  

ListNode * SortedMerge(ListNode * a, ListNode * b) { //merge the nodes
	ListNode * result = NULL; 
	  
	
	if (a == NULL) 
	    return(b); 
	else if (b==NULL) 
	    return(a); 
	  
	
	if (a->data <= b->data){ 
	    result = a; 
	    result->next = SortedMerge(a->next, b); 
	} 
	else{ 
	    result = b; 
	    result->next = SortedMerge(a, b->next); 
	} 
	return(result); 
} 
  

void Split(ListNode * list, ListNode ** list1, ListNode ** list2){ //split the list with one slow and one fast pointer
    ListNode * temp; 
    ListNode * tempSlow; 
    tempSlow = list; 
    temp = list->next; 
  
    while (temp != NULL){ 
	    temp = temp->next; 
	    if (temp != NULL){ 
	        tempSlow = tempSlow->next; 
	        temp = temp->next; 
	    } 
    } 
  
    
    *list1 = list; 
    *list2 = tempSlow->next; 
    tempSlow->next = NULL; 
} 
  

void printList(ListNode *head) { //print list
	ListNode * temp=head;
	while(temp){ 
		printf("%d\t", temp->data); 
		temp = temp->next; 
	} 
	printf("\n");
} 
  

void InsertFront(ListNode ** head, int data) { //insert node into the list

	ListNode * newNode =(ListNode *) malloc(sizeof(ListNode)); 
	  
	newNode->data = data; 
	newNode->next = (*head);  
	  
	(*head) = newNode; 
}  
  

int main() { 
	ListNode * list = NULL; 
	  
	InsertFront(&list, 46); 
	InsertFront(&list, 2546); 
	InsertFront(&list, 565);  
	InsertFront(&list, 5); 
	InsertFront(&list, 34); 
	InsertFront(&list, 9); 
	 
	printf("List: \n");
	printList(list);
	MergeSort(&list); 
	  
	printf("MergeSort list: \n"); 
	printList(list);          
  
} 
