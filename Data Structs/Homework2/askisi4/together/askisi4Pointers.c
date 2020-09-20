#include "askisi4Pointers.h"

typedef struct cbtNode {
	
	CBTItem CBTItemType;
    struct cbtNode * parent;
    struct cbtNode * right;
    struct cbtNode * left;
    
} CBTnode;

typedef struct cbtTree{
	
	struct cbtNode * root;
	int nodes;
	
}CBTtree;


CBTNode * CreateNode(CBTNode* parent,CBTItem  item){
	CBTNode * root=(CBTNode *)malloc(sizeof(CBTNode));
	root->parent=parent;
	root->right=NULL;
	root->left=NULL;
	root->CBTItemType=item;  
	return root;
}

CBTTree * CBTCreate(int maxelem){
	CBTTree * treeRoot=(CBTTree *)malloc(sizeof(CBTTree));
	treeRoot->root=NULL;
	treeRoot->nodes=0;
	return treeRoot;
}

int CBTSize(CBTTree * tree){
	return tree->nodes;	
}
int CBTIsEmpty(CBTTree* tree){
	if(tree->nodes==0){
		return 1;
	}
	else
		return 0;
}

int returnNodes(CBTTree*tree){
	return tree->nodes;
}
/*
void CBTInsertRoot(CBTTree*tree,CBTItem item){
	if(BTIsEmpty(tree)==0){
		printf("Tree already has a root..\n");
		return;
	}
	tree->root=CreateNode(NULL,item);
	tree->nodes++;
	
}

void CBTInsertLeft(CBTTree *tree,CBTNode * node ,CBTItem item){
	if(node->left!=NULL){
		printf("Node has already a left node..\n");
		return;
	}
	node->left=CreateNode(node,item);
	tree->nodes++;
}

void CBTInsertRight(CBTTree* tree,CBTNode * node ,CBTItem item ){
	if(node->right!=NULL){
		printf("Node has already a right node..\n");
		return;
	}
	node->right=CreateNode(node,item);
	tree->nodes++;
	
}
void CBTRemove(CBTTree * tree, CBTNode *node){
	if(node->left!=NULL || node->right!=NULL){
		printf("Node has at least a child..\n");
		return;
	}
	if(node->parent==NULL){
		free(node);
		tree->nodes--;
		return;
	}
	if(!strcmp((char*)node->parent->left->CBTItemType,(char*)node->CBTItemType)){
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
*/
CBTNode * CBTGetRoot(CBTTree * tree){
	
	if(CBTIsEmpty(tree)){
		printf("No root found..\n");
		return NULL;
	}
	return tree->root;
}

CBTNode * CBTGetParent(CBTTree * tree,CBTNode * node){
	if(node->parent==NULL){
		printf("Root has no parent..\n");
		return tree->root->parent;
	}
	return node->parent;
}


CBTNode * CBTGetChildLeft(CBTTree * tree,CBTNode * node){
	if(node->left==NULL){
		printf("Node has no left child..\n");
		return NULL;
	}
	return node->left;
}

CBTNode * CBTGetChildRight(CBTTree * tree,CBTNode * node){
	if(node->right==NULL){
		printf("Node has no right child.. \n");
		return NULL;
	}
	return node->right;
}

CBTItem  CBTGetItem(CBTTree * tree,CBTNode * node){
	return node->CBTItemType;
}

void CBTChange(CBTTree * tree,CBTNode * node,CBTItem item ){
	if(node==NULL){
		printf("Node is empty..\n");
		return;
	}
	node->CBTItemType=item;
	
}


void visit(CBTNode * node){
	Print(node->CBTItemType);
}

void preOrder(CBTNode * node,void(*visit)(CBTNode *)){
	if(node==NULL){
		return;
	}
	
	visit(node);
	
	preOrder(node->left,visit);
	preOrder(node->right,visit);
}
void CBTPreOrder(CBTTree * tree,void(*visit)(CBTNode *)){
	
	preOrder(tree->root,visit);
	
	
}

void inOrder(CBTNode * node,void(*visit)(CBTNode *)){
	if(node==NULL){
		return;
	}
	inOrder(node->left,visit);
	visit(node);
	inOrder(node->right,visit);
}

void CBTInOrder(CBTTree * tree,void(*visit)(CBTNode *)){
	
	inOrder(tree->root,visit);
}

void postOrder(CBTNode * node,void(*visit)(CBTNode *)){
	if(node==NULL){
		return;
	}
	postOrder(node->left,visit);
	postOrder(node->right,visit);
	visit(node);
}

void CBTPostOrder(CBTTree * tree,void(*visit)(CBTNode *)){
	
	postOrder(tree->root,visit);
}

int BTHeight(CBTTree * tree){  
    return FindHeight(tree->root);
    
}

int FindHeight(CBTNode * node){
	if (node == NULL)  
        return 0;  
    else{ 
        int leftLen = FindHeight(node->left);  
        int rightLen = FindHeight(node->right);  
      
        
        if (leftLen > rightLen)  
            return(leftLen + 1);  
        else return(rightLen + 1);  
    }  
}

void CBTDestroy(CBTTree *tree){
	DestroyTree(tree->root);
}
void DestroyTree(CBTNode * node){
	if (node==NULL)
        return;
    DestroyTree(node->left);
    DestroyTree(node->right);
	printf("Node : %s is destroyed\n",(char*)node->CBTItemType);
    free(node);
	
	
}

//==================

void FindLast(CBTNode *root, int lvl, int * maxLvl, CBTNode  ** node){ 
    if (root != NULL){ 
        FindLast(root->right, ++lvl, maxLvl, node); 
        if (lvl > *maxLvl){ 
            *node = root; 
            *maxLvl = lvl; 
        } 
  
        FindLast(root->left, lvl, maxLvl, node); 
    } 
} 

CBTNode * CBTGetLast(CBTTree *tree){ 
    int maxLvl = -1; 
  	CBTNode * temp; 
    FindLast(tree->root, 0, &maxLvl, &temp); //epistrefei to teleutaio node
    return temp; 
} 

CBTNode * FindParentNode(CBTNode * root, int maxlvl,int lvl ){
	//vriskei ton patera pou tha mpei to node
	CBTNode * temp=NULL;
	if(lvl>maxlvl)
		return NULL;
	else if(maxlvl==lvl && (root->left==NULL || root->right==NULL)){
		return root;
	}
	

	temp=FindParentNode(root->left,maxlvl,lvl+1);
	if(temp==NULL){
		temp=FindParentNode(root->right,maxlvl,lvl+1);
	}
	return temp;
}

void CBTInsertLast(CBTTree * tree, CBTItem item){
	//bazei ena node sto telos tou dentrou
	int maxlvl,i;
	if(tree->nodes==0){
		tree->root=CreateNode(NULL,item);
		tree->nodes++;
		return;
	}
	for(i=1;1;i++){
		if(tree->nodes < (pow(2,i)-1)){
			maxlvl=i-1;
			break;
		}
	}
	CBTNode * temp=FindParentNode(tree->root,maxlvl,1);//vriskei ton patera tou node pou tha eisagoume
	
	if(temp->left==NULL){ //kai to topothetei analoga
		temp->left=CreateNode(temp,item);
		tree->nodes++;
		return;
	}
	else{
		temp->right=CreateNode(temp,item);
		tree->nodes++;
		return;
	}
}

void CBTRemoveLast(CBTTree * tree){
	//pernei to last node kai to bgazei analoga..
	CBTNode * temp=CBTGetLast(tree);
	if(temp->parent==NULL){
		free(temp);
		tree->nodes--;
		return;
	}
	if(temp->parent->left==temp){
		temp->parent->left=NULL;
		free(temp);
		tree->nodes--;
		return;
		
	}
	temp->parent->right=NULL;
	free(temp);
	tree->nodes--;
	
}

