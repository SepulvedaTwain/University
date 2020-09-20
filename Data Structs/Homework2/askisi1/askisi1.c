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


BTNode * CreateNode(BTNode* parent,BTItem  item){//dimiourgei neo node
	BTNode * root=(BTNode *)malloc(sizeof(BTNode));
	root->parent=parent;
	root->right=NULL;
	root->left=NULL;
	root->btItemType=item;  
	return root;
}

BTTree * BTCreate(int maxelem){//dimiourgei neo tree
	BTTree * treeRoot=(BTTree *)malloc(sizeof(BTTree));
	treeRoot->root=NULL;
	treeRoot->nodes=0;
	return treeRoot;
}

int BTSize(BTTree * tree){//epistrefeiposa nodes exei
	return tree->nodes;	
}
int BTIsEmpty(BTTree* tree){//epistrefei an einai adio h oxi
	if(tree->nodes==0){
		return 1;
	}
	else
		return 0;
}

int returnNodes(BTTree*tree){
	return tree->nodes;
}

void BTInsertRoot(BTTree*tree,BTItem item){//eisagei to root
	if(BTIsEmpty(tree)==0){
		printf("Tree already has a root..\n");
		return;
	}
	tree->root=CreateNode(NULL,item);
	tree->nodes++;
	
}

void BTInsertLeft(BTTree *tree,BTNode * node ,BTItem item){//eisagei aristero paidi sto node pou theloume
	if(node->left!=NULL){
		printf("Node has already a left node..\n");
		return;
	}
	node->left=CreateNode(node,item);
	tree->nodes++;
}

void BTInsertRight(BTTree* tree,BTNode * node ,BTItem item ){//eisagei desksi paidi sto node pou theloume
	if(node->right!=NULL){
		printf("Node has already a right node..\n");
		return;
	}
	node->right=CreateNode(node,item);
	tree->nodes++;
	
}
void BTRemove(BTTree * tree, BTNode *node){//kanei remove to node pou theloyme apo to dentro
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

BTNode * BTGetRoot(BTTree * tree){//epistrefei to root
	
	if(BTIsEmpty(tree)){
		printf("No root found..\n");
		return NULL;
	}
	return tree->root;
}

BTNode * BTGetParent(BTTree * tree,BTNode * node){//epistrefei to parent tou node pou theloume
	if(node->parent==NULL){
		printf("Root has no parent..\n");
		return tree->root->parent;
	}
	return node->parent;
}


BTNode * BTGetChildLeft(BTTree * tree,BTNode * node){// epistrefei to aristero paidi
	if(node->left==NULL){
		printf("Node has no left child..\n");
		return NULL;
	}
	return node->left;
}

BTNode * BTGetChildRight(BTTree * tree,BTNode * node){//epistrefei to aristero paidi
	if(node->right==NULL){
		printf("Node has no right child.. \n");
		return NULL;
	}
	return node->right;
}

BTItem  BTGetItem(BTTree * tree,BTNode * node){//to item tou node poy theloume
	return node->btItemType;
}

void BTChange(BTTree * tree,BTNode * node,BTItem item ){//allazei to item tou node me to item pou pairnei
	if(node==NULL){
		printf("Node is empty..\n");
		return;
	}
	node->btItemType=item;
	
}


void visit(BTNode * node){//kanei print to item
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
void BTPreOrder(BTTree * tree,void(*visit)(BTNode *)){//h preorder ektipwsh
	
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

void BTInOrder(BTTree * tree,void(*visit)(BTNode *)){//h inorder ektipwsh
	
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

void BTPostOrder(BTTree * tree,void(*visit)(BTNode *)){//h postorder ektipwsi
	
	postOrder(tree->root,visit);
}

int BTHeight(BTTree * tree){  //epistrefei to ipsos tou dentrou
    return FindHeight(tree->root);
    
}

int FindHeight(BTNode * node){//vriskei to ipsos tou dentrou
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

void BTDestroy(BTTree *tree){//kalei tin sinartisi pou kanei free to dentro
	DestroyTree(tree->root);
}
void DestroyTree(BTNode * node){//kkanei free to dentro
	if (node==NULL)
        return;
    DestroyTree(node->left);
    DestroyTree(node->right);
	printf("Node : %s is destroyed\n",(char*)node->btItemType);
    free(node);
	
	
}

