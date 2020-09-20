#include "askisi6.h"


typedef struct btNode {
	
	BSTItem BSTItemType;
    struct btNode * parent;
    struct btNode * right;
    struct btNode * left;
    
} BTnode;

typedef struct btTree{
	
	struct btNode * root;
	int nodes;
	
}BTtree;


BTNode * CreateNode(BTNode* parent,BSTItem  item){
	BTNode * root=(BTNode *)malloc(sizeof(BTNode));
	root->parent=parent;
	root->right=NULL;
	root->left=NULL;
	root->BSTItemType=item;
	return root;
}

BTTree * BTCreate(int maxelem){
	BTTree * treeRoot=(BTTree *)malloc(sizeof(BTTree));
	treeRoot->root=NULL;
	treeRoot->nodes=0;
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

void BTInsertRoot(BTTree*tree,BSTItem item){
	if(BTIsEmpty(tree)==0){
		printf("Tree already has a root..\n");
		return;
	}
	tree->root=CreateNode(NULL,item);
	tree->nodes++;
	
}

void BTInsertLeft(BTTree *tree,BTNode * node ,BSTItem item){
	if(node->left!=NULL){
		printf("Node has already a left node..\n");
		return;
	}
	node->left=CreateNode(node,item);
	tree->nodes++;
}

void BTInsertRight(BTTree* tree,BTNode * node ,BSTItem item ){
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
	/*if(!strcmp((int)node->parent->left->BSTItemType,(int)node->BSTItemType)){
		node->parent->left=NULL;
		free(node);
		tree->nodes--;
		return;
	}*/
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

BSTItem  BTGetItem(BTTree * tree,BTNode * node){
	return node->BSTItemType;
}

void BTChange(BTTree * tree,BTNode * node,BSTItem item ){
	if(node==NULL){
		printf("Node is empty..\n");
		return;
	}
	node->BSTItemType=item;
	
}


void visit(BTNode * node){
	Print(node->BSTItemType);
	
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
	printf("Node : %d is destroyed\n",(int)node->BSTItemType);
    free(node);
	
	
}

//=======================

BTTree * BSTCreate(){
	return BTCreate(0);
}

void BSTInsert(BTTree* tree,BSTItem item,int (*compare)(BSTItem , BSTItem)){
	//krateme ptr, kai kouname deksi h aristera sto ta node gia na doume pou tha mpei to neo node kai to bazoume
	if(tree->nodes==0){
		BTInsertRoot(tree,item);
		return;
	}
	BTNode * temp=tree->root;
	BTNode * prv;
	while(temp!=NULL){
		prv=temp;
		if(compare(temp->BSTItemType,item)==1){
			temp=temp->left;
			
		}
		else 
			temp=temp->right;
		
	}
	if(compare(prv->BSTItemType,item)==1){
		prv->left=CreateNode(prv,item);
		tree->nodes++;
	}
	else{
		prv->right=CreateNode(prv,item);
		tree->nodes++;
	}
	
}

BTNode * BSTSearch(BTTree * tree, BSTItem item){
	//koitame an to data einai megalitero h mikrotero tou node gia na kounithoume analoga wste na vroume to node
	BTNode * temp=tree->root;
	while((int)temp->BSTItemType != (int)item){
		if(temp != NULL){
				
			if((int)temp->BSTItemType > (int)item){
				temp=temp->left;
			}
			else
				temp=temp->right;
			if(temp==NULL)
				return NULL;
				
		}
	}
	
	return temp;
	
}

void BSTDelete(BTTree * tree,BSTItem item){
	//stin delete diagrafoume to node kai koitame oles tis periptwseis pou mporei na yparxoyn
	if(tree->nodes==0){
		printf("Empty tree..\n");
		return;
	}
	if(tree->nodes==1){
		free(tree->root);
		tree->root=NULL;
		return;
	}
	BTNode * temp=BSTSearch(tree,item);
	if(temp==NULL){//kanena node
		printf("This item does not exist in this tree..\n");
		return;
	}
	if(temp->left==NULL && temp->right==NULL){//to node den exei kanena paidi
		if(temp->parent->left->BSTItemType==item){
			temp->parent->left=NULL;
		}
		else
			temp->parent->right=NULL;
		free(temp);
		return;
	}
	if( temp->left==NULL && temp->right!=NULL){//na exei mono ena
		if(temp->parent->left!=NULL){
			if(temp->parent->left->BSTItemType==item){
				temp->parent->left=temp->right;
				temp->right->parent=temp->parent;
			}
		}
		else{
			temp->parent->right=temp->right;
			temp->right->parent=temp->parent;
		}
			
		
		free(temp);
		return;
	}

	if( temp->left!=NULL && temp->right==NULL ){//na exei mono ena
		if(temp->parent->left->BSTItemType==item){
			temp->parent->left=temp->left;
			temp->left->parent=temp->parent;
		}
		else{
			temp->parent->right=temp->left;
			temp->left->parent=temp->parent;
		}
			
			
		free(temp);
		return;
	}
	
	if(temp->left!=NULL && temp->right!=NULL){//na exei 2
		BTNode * transf=temp->right;
		if(transf->left==NULL && transf->right==NULL){//to deksi pedi tou na min exei paidia
			temp->BSTItemType=transf->BSTItemType;
			free(transf);
			temp->right=NULL;
			return;
		}
		if(transf->left==NULL && transf->right!=NULL){//to deksi pedi na exei mono deksi paidi
			temp->BSTItemType=transf->BSTItemType;
			temp->right=transf->right;
			transf->right->parent=temp;
			free(transf);
			return;
		}
		BTNode * transf2=transf;
		if(transf2->left!=NULL){
			transf2=transf2->left;
		}
		
		if(transf2->right==NULL){//to n aristero paidi tou paidiou tou node na mhn exei deksi paidi
			temp->BSTItemType=transf2->BSTItemType;
			transf2->parent->left=NULL;
			free(transf2);
			return;
		}
		if(transf2->right!=NULL){//to n aristero paidi tou paidiou tou node na exei deksi paidi
			transf2->parent->left=transf2->right;
			transf2->right->parent=transf2->parent;
			temp->BSTItemType=transf2->BSTItemType;
			free(transf2);
			return;
		}
		
	}
}

void BSTDestroy(BTTree * tree){
	BTDestroy(tree);
}







