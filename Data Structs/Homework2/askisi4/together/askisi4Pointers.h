#ifndef ASKISI4P_H
#define ASKISI4P_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ItemType4Pointers.h"
#include <math.h>

typedef struct cbtNode  CBTNode;

typedef struct cbtTree CBTTree;                
                



CBTTree * CBTCreate(int );

CBTNode * CreateNode(CBTNode *,CBTItem );

int CBTSize(CBTTree *);

int FindHeight(CBTNode * );

int CBTHeight(CBTTree * );

int CBTIsEmpty(CBTTree*);

int returnNodes(CBTTree*);

//void CBTInsertRoot(CBTTree*,CBTItem );

//void CBTInsertLeft(CBTTree*,CBTNode * ,CBTItem );

//void CBTInsertRight(CBTTree*,CBTNode * ,CBTItem );

//void CBTRemove(CBTTree * , CBTNode *);

CBTNode * CBTGetRoot(CBTTree *);

CBTNode* CBTGetParent(CBTTree *,CBTNode *);

CBTNode * CBTGetChildLeft(CBTTree*,CBTNode*);

CBTNode * CBTGetChildRight(CBTTree *,CBTNode*);

CBTItem  CBTGetItem(CBTTree *,CBTNode*);

void CBTChange(CBTTree*,CBTNode *,CBTItem );

void CBTPreOrder(CBTTree *,void(*visit)(CBTNode *));

void preOrder(CBTNode * node,void(*visit)(CBTNode *));

void CBTInOrder(CBTTree *,void(*visit)(CBTNode *));

void inOrder(CBTNode * node,void(*visit)(CBTNode *));

void CBTPostOrder(CBTTree *,void(*visit)(CBTNode *));

void postOrder(CBTNode * node,void(*visit)(CBTNode *));

void DestroyTree(CBTNode *);

void CBTDestroy(CBTTree *);

void visit(CBTNode * node);

//=========

void FindLast(CBTNode *, int , int * , CBTNode  ** );

CBTNode * CBTGetLast(CBTTree *);

CBTNode * FindParentNode(CBTNode *, int ,int );

void CBTInsertLast(CBTTree *,CBTItem );

void CBTRemoveLast(CBTTree *);

#endif
