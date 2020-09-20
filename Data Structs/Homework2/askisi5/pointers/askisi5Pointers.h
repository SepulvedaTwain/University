#ifndef ASKISI5P_H
#define ASKISI5P_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ItemType5Pointers.h"
#include <math.h>

typedef struct bhNode  BHNode;

typedef struct bhHeap BHHeap;                
                



BHHeap * CBTCreate(int );

BHNode * CreateNode(BHNode *,BHItem , int );

int BTSize(BHHeap *);

int FindHeight(BHNode *);

int BTHeight(BHHeap * );

int BTIsEmpty(BHHeap*);

int returnNodes(BHHeap*);

void BTInsertRoot(BHHeap*,BHItem );

void BTInsertLeft(BHHeap*,BHNode * ,BHItem );

void BTInsertRight(BHHeap*,BHNode * ,BHItem );

void BTRemove(BHHeap * , BHNode *);

BHNode * BTGetRoot(BHHeap *);

BHNode* BTGetParent(BHHeap *,BHNode *);

BHNode * BTGetChildLeft(BHHeap*,BHNode*);

BHNode * BTGetChildRight(BHHeap *,BHNode*);

BHItem  BTGetItem(BHHeap *,BHNode*);

void BTChange(BHHeap*,BHNode *,BHItem );

void CBTPreOrder(BHHeap *,void(*visit)(BHNode *));

void preOrder(BHNode * node,void(*visit)(BHNode *));

void BTInOrder(BHHeap *,void(*visit)(BHNode *));

void inOrder(BHNode * node,void(*visit)(BHNode *));

void BTPostOrder(BHHeap *,void(*visit)(BHNode *));

void postOrder(BHNode * node,void(*visit)(BHNode *));

void DestroyTree(BHNode *);

void BTDestroy(BHHeap *);

void visit(BHNode * node);

//=========

void FindLast(BHNode *, int , int * , BHNode  ** );

BHNode * CBTGetLast(BHHeap *);

BHNode * FindParentNode(BHNode *, int ,int );

void CBTInsertLast(BHHeap *,BHItem , int);

void CBTRemove(BHHeap *);

//========

BHHeap * BHCreate(int );

int BHIsEmpty(BHHeap *);

int BHGetMaxPriority(BHHeap *);

BHItem BHGetMaxItem(BHHeap *);

void BHRemove(BHHeap * );

void BHInsert(BHHeap * ,int , BHItem );

void Heapify(BHNode *,int ,int );

BHHeap * BHHeapify(int ,int *, BHItem *);

void BHDestroy(BHHeap * );	



#endif
