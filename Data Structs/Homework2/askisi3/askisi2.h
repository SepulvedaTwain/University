#ifndef ASKISI2_H
#define ASKISI2_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ItemType2.h"

typedef struct btNode  BTNode;

typedef struct btTree BTTree;                
                



BTTree * BTCreate(int );

BTNode * CreateNode(int , int ,BTItem );

int BTSize(BTTree *);

int BTHeight(BTTree * );

int FindHeight(BTTree *,BTNode * );

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

void preOrder(BTTree * tree,BTNode * node,void(*visit)(BTNode *));

void BTInOrder(BTTree *,void(*visit)(BTNode *));

int inOrder(BTTree *,BTNode * node,void(*visit)(BTNode *));

void BTPostOrder(BTTree *,void(*visit)(BTNode *));

int postOrder(BTTree *,BTNode * node,void(*visit)(BTNode *));

void BTDestroy(BTTree *);

void visit(BTNode * node);

#endif
