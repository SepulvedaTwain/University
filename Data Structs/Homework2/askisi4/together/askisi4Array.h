#ifndef ASKISI4A_H
#define ASKISI4A_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ItemType4Array.h"

typedef struct cbtNode  CBTNode;

typedef struct cbtTree CBTTree;                
                



CBTTree * CBTCreate(int );

CBTNode * CreateNode(int , int ,CBTItem );

int CBTSize(CBTTree *);

int CBTHeight(CBTTree * );

int FindHeight(CBTTree *,CBTNode * );

int CBTIsEmpty(CBTTree*);

int returnNodes(CBTTree*);

void CBTBInsertRoot(CBTTree*,CBTItem );

void CBTInsertLeft(CBTTree*,CBTNode * ,CBTItem );

void CBTInsertRight(CBTTree*,CBTNode * ,CBTItem );

void CBTRemove(CBTTree * , CBTNode *);

CBTNode * CBTGetRoot(CBTTree *);

CBTNode* CBTGetParent(CBTTree *,CBTNode *);

CBTNode * CBTGetChildLeft(CBTTree*,CBTNode*);

CBTNode * CBTGetChildRight(CBTTree *,CBTNode*);

CBTItem  CBTGetItem(CBTTree *,CBTNode*);

void CBTChange(CBTTree*,CBTNode *,CBTItem );

void CBTPreOrder(CBTTree *,void(*visit)(CBTNode *));

void preOrder(CBTTree * tree,CBTNode * node,void(*visit)(CBTNode *));

void CBTInOrder(CBTTree *,void(*visit)(CBTNode *));

int inOrder(CBTTree *,CBTNode * node,void(*visit)(CBTNode *));

void CBTPostOrder(CBTTree *,void(*visit)(CBTNode *));

int postOrder(CBTTree *,CBTNode * node,void(*visit)(CBTNode *));

void CBTDestroy(CBTTree *);

void visit(CBTNode * node);

//=========================

CBTNode * CBTGetLast(CBTTree *);

void CBTInsertLast(CBTTree *,CBTItem);

void CBTRemoveLast(CBTTree *);

#endif
