#ifndef ASKISI1_H
#define ASKISI1_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ItemType1.h"

typedef struct btNode  BTNode;

typedef struct btTree BTTree;                
                



BTTree * BTCreate(int );

BTNode * CreateNode(BTNode *,BTItem );

int BTSize(BTTree *);

int FindHeight(BTNode * );

int BTHeight(BTTree * );

int BTIsEmpty(BTTree*);

int returnNodes(BTTree*);

void BTInsertRoot(BTTree*,BTItem );

void BTInsertLeft(BTTree*,BTNode * ,BTItem );

void BTInsertRight(BTTree*,BTNode * ,BTItem );

void BTRemove(BTTree * , BTNode *);

BTNode * BTGetRoot(BTTree *);

BTNode* BTGetParent(BTTree *,BTNode *);

BTNode * BTGetChildLeft(BTTree*,BTNode*);

BTNode * BTGetChildRight(BTTree *,BTNode*);

BTItem  BTGetItem(BTTree *,BTNode*);

void BTChange(BTTree*,BTNode *,BTItem );

void BTPreOrder(BTTree *,void(*visit)(BTNode *));

void preOrder(BTNode * node,void(*visit)(BTNode *));

void BTInOrder(BTTree *,void(*visit)(BTNode *));

void inOrder(BTNode * node,void(*visit)(BTNode *));

void BTPostOrder(BTTree *,void(*visit)(BTNode *));

void postOrder(BTNode * node,void(*visit)(BTNode *));

void DestroyTree(BTNode *);

void BTDestroy(BTTree *);

void visit(BTNode * node);

#endif



