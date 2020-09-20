#ifndef ASKISI6_H
#define ASKISI6_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ItemType6.h"

typedef struct btNode  BTNode;

typedef struct btTree BTTree;                
                



BTTree * BTCreate(int );

BTNode * CreateNode(BTNode *,BSTItem );

int BTSize(BTTree *);

int FindHeight(BTNode *);

int BTHeight(BTTree * );

int BTIsEmpty(BTTree*);

int returnNodes(BTTree*);

void BTInsertRoot(BTTree*,BSTItem );

void BTInsertLeft(BTTree*,BTNode * ,BSTItem );

void BTInsertRight(BTTree*,BTNode * ,BSTItem );

void BTRemove(BTTree * , BTNode *);

BTNode * BTGetRoot(BTTree *);

BTNode* BTGetParent(BTTree *,BTNode *);

BTNode * BTGetChildLeft(BTTree*,BTNode*);

BTNode * BTGetChildRight(BTTree *,BTNode*);

BSTItem  BTGetItem(BTTree *,BTNode*);

void BTChange(BTTree*,BTNode *,BSTItem );

void BTPreOrder(BTTree *,void(*visit)(BTNode *));

void preOrder(BTNode * node,void(*visit)(BTNode *));

void BTInOrder(BTTree *,void(*visit)(BTNode *));

void inOrder(BTNode * node,void(*visit)(BTNode *));

void BTPostOrder(BTTree *,void(*visit)(BTNode *));

void postOrder(BTNode * node,void(*visit)(BTNode *));

void DestroyTree(BTNode *);

void BTDestroy(BTTree *);

void visit(BTNode * node);


//++++++++++++++++++



BTTree * BSTCreate();

void BSTInsert(BTTree*,BSTItem ,int (*compare)(BSTItem , BSTItem));

void BSTDelete(BTTree *,BSTItem );

BTNode * BSTSearch(BTTree * , BSTItem );

void BSTDestroy(BTTree *);

#endif



