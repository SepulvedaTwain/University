#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct listNode 
{ 
    int data; 
    struct listNode* next; 
}ListNode; 

ListNode * SortedMerge(ListNode *, ListNode * ); 
void Split(ListNode *, ListNode **, ListNode **); 
void MergeSort(ListNode ** );
void printList(ListNode *);
void InsertFront(ListNode ** , int);

