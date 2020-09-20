#include "askisi1.h"


typedef struct btNode {
	
	BTItem btItemType;
    struct btNode * parent;
    struct btNode * right;
    struct btNode * left;
    
} BTnode;

typedef struct btTree{
	
	struct btNode * root;
	int nodes;
	
}BTtree;


BTNode * CreateNode(BTNode* parent,BTItem  item){
	BTNode * root=(BTNode *)malloc(sizeof(BTNode));
	root->parent=parent;
	root->right=NULL;
	root->left=NULL;
	root->btItemType=item;  /*(char*)malloc(sizeof(char)*strlen((char *)item)+1);
	strcpy((char *)root->btItemType,(char *)item);*/
	return root;
}

BTTree * BTCreate(int maxelem){
	BTTree * treeRoot=(BTTree *)malloc(sizeof(BTTree));
	treeRoot->root=NULL;
	treeRoot->nodes=0;
	return treeRoot;
}

int BTSize(BTTree * tree){
	return tree->nodes;	
}
int BTIsEmpty(BTTree* tree){
	if(tree->nodes==0){
		return 1;
	}
	else
		return 0;
}

int returnNodes(BTTree*tree){
	return tree->nodes;
}

void BTInsertRoot(BTTree*tree,BTItem item){
	if(BTIsEmpty(tree)==0){
		printf("Tree already has a root..\n");
		return;
	}
	tree->root=CreateNode(NULL,item);
	tree->nodes++;
	
}

void BTInsertLeft(BTTree *tree,BTNode * node ,BTItem item){
	if(node->left!=NULL){
		printf("Node has already a left node..\n");
		return;
	}
	node->left=CreateNode(node,item);
	tree->nodes++;
}

void BTInsertRight(BTTree* tree,BTNode * node ,BTItem item ){
	if(node->right!=NULL){
		printf("Node has already a right node..\n");
		return;
	}
	node->right=CreateNode(node,item);
	tree->nodes++;
	
}
void BTRemove(BTTree * tree, BTNode *node){
	if(node->left!=NULL || node->right!=NULL){
		printf("Node has at least a child..\n");
		return;
	}
	if(node->parent==NULL){
		free(node);
		tree->nodes--;
		return;
	}
	if(!strcmp((char*)node->parent->left->btItemType,(char*)node->btItemType)){
		node->parent->left=NULL;
		free(node);
		tree->nodes--;
		return;
	}
	node->parent->right=NULL;
	free(node);
	tree->nodes--;
	return;
}

BTNode * BTGetRoot(BTTree * tree){
	
	if(BTIsEmpty(tree)){
		printf("No root found..\n");
		return NULL;
	}
	return tree->root;
}

BTNode * BTGetParent(BTTree * tree,BTNode * node){
	if(node->parent==NULL){
		printf("Root has no parent..\n");
		return tree->root->parent;
	}
	return node->parent;
}


BTNode * BTGetChildLeft(BTTree * tree,BTNode * node){
	if(node->left==NULL){
		printf("Node has no left child..\n");
		return NULL;
	}
	return node->left;
}

BTNode * BTGetChildRight(BTTree * tree,BTNode * node){
	if(node->right==NULL){
		printf("Node has no right child.. \n");
		return NULL;
	}
	return node->right;
}

BTItem  BTGetItem(BTTree * tree,BTNode * node){
	return node->btItemType;
}

void BTChange(BTTree * tree,BTNode * node,BTItem item ){
	if(node==NULL){
		printf("Node is empty..\n");
		return;
	}
	node->btItemType=item;/*(char*)malloc(sizeof(char)*strlen((char *)item)+1);
	strcpy((char*)node->btItemType,(char*)item);*/
	
}


void visit(BTNode * node){
	Print(node->btItemType);
}

void preOrder(BTNode * node,void(*visit)(BTNode *)){
	if(node==NULL){
		return;
	}
	
	visit(node);
	
	preOrder(node->left,visit);
	preOrder(node->right,visit);
}
void BTPreOrder(BTTree * tree,void(*visit)(BTNode *)){
	
	preOrder(tree->root,visit);
	
	
}

void inOrder(BTNode * node,void(*visit)(BTNode *)){
	if(node==NULL){
		return;
	}
	inOrder(node->left,visit);
	visit(node);
	inOrder(node->right,visit);
}

void BTInOrder(BTTree * tree,void(*visit)(BTNode *)){
	
	inOrder(tree->root,visit);
}

void postOrder(BTNode * node,void(*visit)(BTNode *)){
	if(node==NULL){
		return;
	}
	postOrder(node->left,visit);
	postOrder(node->right,visit);
	visit(node);
}

void BTPostOrder(BTTree * tree,void(*visit)(BTNode *)){
	
	postOrder(tree->root,visit);
}

int BTHeight(BTTree * tree){  
    return FindHeight(tree->root);
    
}

int FindHeight(BTNode * node){
	if (node == NULL)  
        return 0;  
    else{ 
        int leftLen = FindHeight(node->left);  
        int rightLen = FindHeight(node->right);  
      
        /* use the larger one */
        if (leftLen > rightLen)  
            return(leftLen + 1);  
        else return(rightLen + 1);  
    }  
}

void BTDestroy(BTTree *tree){
	DestroyTree(tree->root);
}
void DestroyTree(BTNode * node){
	if (node==NULL)
        return;
    DestroyTree(node->left);
    DestroyTree(node->right);
	printf("Node : %s is destroyed\n",(char*)node->btItemType);
    free(node);
	
	
}

