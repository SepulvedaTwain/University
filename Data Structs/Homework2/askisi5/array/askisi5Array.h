#ifndef ASKISI5A_H
#define ASKISI5A_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ItemType5Array.h"

typedef struct bhNode  BHNode;

typedef struct bhHeap BHHeap;                
                



BHHeap * CBTCreate(int );

BHNode * CreateNode(int , int ,BHItem ,int );

int CBTSize(BHHeap *);

int CBTHeight(BHHeap * );

int FindHeight(BHHeap *,BHNode * );

int CBTIsEmpty(BHHeap*);

int returnNodes(BHHeap*);

void CBTBInsertRoot(BHHeap*,BHItem );

void CBTInsertLeft(BHHeap*,BHNode * ,BHItem );

void CBTInsertRight(BHHeap*,BHNode * ,BHItem );

void CBTRemove(BHHeap * , BHNode *);

BHNode * CBTGetRoot(BHHeap *);

BHNode* CBTGetParent(BHHeap *,BHNode *);

BHNode * CBTGetChildLeft(BHHeap*,BHNode*);

BHNode * CBTGetChildRight(BHHeap *,BHNode*);

BHItem  CBTGetItem(BHHeap *,BHNode*);

void CBTChange(BHHeap*,BHNode *,BHItem );

void CBTPreOrder(BHHeap *,void(*visit)(BHNode *));

void preOrder(BHHeap * tree,BHNode * node,void(*visit)(BHNode *));

void CBTInOrder(BHHeap *,void(*visit)(BHNode *));

int inOrder(BHHeap *,BHNode * node,void(*visit)(BHNode *));

void CBTPostOrder(BHHeap *,void(*visit)(BHNode *));

int postOrder(BHHeap *,BHNode * node,void(*visit)(BHNode *));

void CBTDestroy(BHHeap *);

void visit(BHNode * node);

//=========================

BHNode * CBTGetLast(BHHeap *);

void CBTInsertLast(BHHeap *,BHItem, int );

void CBTRemoveLast(BHHeap *);

//=========================


BHHeap * BHCreate(int );

int BHIsEmpty(BHHeap *);

int BHGetMaxPriority(BHHeap *);

BHItem BHGetMaxItem(BHHeap *);

void BHInsert(BHHeap *,int ,BHItem );

void BHRemove(BHHeap * );

void Heapify(BHHeap * ,int );

BHHeap * BHHeapify(int , int * , BHItem *);

void BHDestroy(BHHeap *);



#endif
