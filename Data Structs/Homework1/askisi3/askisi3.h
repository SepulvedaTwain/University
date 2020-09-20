#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct listNode {
                        int nodeId;
                        struct listNode *next;
} ListNode;


ListNode * Create();
void Print(ListNode *);
void InsertLast (ListNode *, int );
ListNode * Merge(ListNode *,ListNode*);
ListNode * Sort(ListNode * );
void Insert(ListNode*,ListNode*);
ListNode * Split(ListNode *);
ListNode * MergeSort(ListNode * );


ListNode * MergeSort2(ListNode *);
void Split2(ListNode* source, ListNode ** fastList, ListNode** slowList);
