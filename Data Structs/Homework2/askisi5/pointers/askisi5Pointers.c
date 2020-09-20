#include "askisi5Pointers.h"


typedef struct bhNode {
	
	BHItem BHItemType;
	int priority;
    struct bhNode * parent;
    struct bhNode * right;
    struct bhNode * left;
    
} BHnode;

typedef struct bhHeap{
	
	struct bhNode * root;
	int nodes;
	
}BHheap;


BHNode * CreateNode(BHNode* parent,BHItem  item , int priority){
	BHNode * root=(BHNode *)malloc(sizeof(BHNode));
	root->parent=parent;
	root->right=NULL;
	root->left=NULL;
	root->priority=priority;
	root->BHItemType=item; 
	return root;
}

BHHeap * CBTCreate(int maxelem){
	BHHeap * treeRoot=(BHHeap *)malloc(sizeof(BHHeap));
	treeRoot->root=NULL;
	treeRoot->nodes=0;
}

int BTSize(BHHeap * tree){
	return tree->nodes;	
}
int BTIsEmpty(BHHeap* tree){
	if(tree->nodes==0){
		return 1;
	}
	else
		return 0;
}

int returnNodes(BHHeap*tree){
	return tree->nodes;
}

void BTInsertRoot(BHHeap*tree,BHItem item){
	if(BTIsEmpty(tree)==0){
		printf("Tree already has a root..\n");
		return;
	}
	//tree->root=CreateNode(NULL,item);
	tree->nodes++;
	
}

void BTInsertLeft(BHHeap *tree,BHNode * node ,BHItem item){
	if(node->left!=NULL){
		printf("Node has already a left node..\n");
		return;
	}
	//node->left=CreateNode(node,item);
	tree->nodes++;
}

void BTInsertRight(BHHeap* tree,BHNode * node ,BHItem item ){
	if(node->right!=NULL){
		printf("Node has already a right node..\n");
		return;
	}
	//node->right=CreateNode(node,item);
	tree->nodes++;
	
}
void BTRemove(BHHeap * tree, BHNode *node){
	if(node->left!=NULL || node->right!=NULL){
		printf("Node has at least a child..\n");
		return;
	}
	if(node->parent==NULL){
		free(node);
		tree->nodes--;
		return;
	}
	if(!strcmp((char*)node->parent->left->BHItemType,(char*)node->BHItemType)){
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

BHNode * BTGetRoot(BHHeap * tree){
	
	if(BTIsEmpty(tree)){
		printf("No root found..\n");
		return NULL;
	}
	return tree->root;
}

BHNode * BTGetParent(BHHeap * tree,BHNode * node){
	if(node->parent==NULL){
		printf("Root has no parent..\n");
		return tree->root->parent;
	}
	return node->parent;
}


BHNode * BTGetChildLeft(BHHeap * tree,BHNode * node){
	if(node->left==NULL){
		printf("Node has no left child..\n");
		return NULL;
	}
	return node->left;
}

BHNode * BTGetChildRight(BHHeap * tree,BHNode * node){
	if(node->right==NULL){
		printf("Node has no right child.. \n");
		return NULL;
	}
	return node->right;
}

BHItem  BTGetItem(BHHeap * tree,BHNode * node){
	return node->BHItemType;
}

void BTChange(BHHeap * tree,BHNode * node,BHItem item ){
	if(node==NULL){
		printf("Node is empty..\n");
		return;
	}
	node->BHItemType=item;
	
}


void visit(BHNode * node){
	Print(node->BHItemType);
}

void preOrder(BHNode * node,void(*visit)(BHNode *)){
	if(node==NULL){
		return;
	}
	
	printf("Nodes priority: %d\t",node->priority);
	visit(node);
	
	preOrder(node->left,visit);
	preOrder(node->right,visit);
}
void CBTPreOrder(BHHeap * tree,void(*visit)(BHNode *)){
	
	preOrder(tree->root,visit);
	
	
}

void inOrder(BHNode * node,void(*visit)(BHNode *)){
	if(node==NULL){
		return;
	}
	inOrder(node->left,visit);
	visit(node);
	inOrder(node->right,visit);
}

void BTInOrder(BHHeap * tree,void(*visit)(BHNode *)){
	
	inOrder(tree->root,visit);
}

void postOrder(BHNode * node,void(*visit)(BHNode *)){
	if(node==NULL){
		return;
	}
	postOrder(node->left,visit);
	postOrder(node->right,visit);
	visit(node);
}

void BTPostOrder(BHHeap * tree,void(*visit)(BHNode *)){
	
	postOrder(tree->root,visit);
}

int BTHeight(BHHeap * tree){  
    return FindHeight(tree->root);
    
}

int FindHeight(BHNode * node){
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

void BTDestroy(BHHeap *tree){
	DestroyTree(tree->root);
}
void DestroyTree(BHNode * node){
	if (node==NULL)
        return;
    DestroyTree(node->left);
    DestroyTree(node->right);
	printf("Node : %s is destroyed\n",(char*)node->BHItemType);
    free(node);
	
	
}

//==================

void FindLast(BHNode *root, int lvl, int * maxLvl, BHNode  ** node){ 
    if (root != NULL){ 
        FindLast(root->right, ++lvl, maxLvl, node); 
        if (lvl > *maxLvl) { 
            *node = root; 
            *maxLvl = lvl; 
        } 
  
        FindLast(root->left, lvl, maxLvl, node); 
    } 
} 

BHNode * CBTGetLast(BHHeap *tree){ 
    int maxLvl = -1; 
  	BHNode * temp; 
    FindLast(tree->root, 0, &maxLvl, &temp); 
    return temp; 
} 

BHNode * FindParentNode(BHNode * root, int maxlvl,int lvl ){
	BHNode * temp=NULL;
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

void CBTInsertLast(BHHeap * tree, BHItem item,int priority){
	int maxlvl,i;
	if(tree->nodes==0){
		tree->root=CreateNode(NULL,item,priority);
		tree->nodes++;
		return;
	}
	for(i=1;1;i++){
		if(tree->nodes < (pow(2,i)-1)){
			maxlvl=i-1;
			break;
		}
	}
	BHNode * temp=FindParentNode(tree->root,maxlvl,1);
	
	if(temp->left==NULL){
		temp->left=CreateNode(temp,item , priority);
		tree->nodes++;
		return;
	}
	else{
		temp->right=CreateNode(temp,item,priority);
		tree->nodes++;
		return;
	}
}

void CBTRemove(BHHeap * tree){
	BHNode * temp=CBTGetLast(tree);
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

//========

BHHeap * BHCreate(int maxelem){
	BHHeap * heap=(BHHeap *)malloc(sizeof(BHHeap));
	heap->root=NULL;
	heap->nodes=0;
	
}


int BHIsEmpty(BHHeap *heap){
	if(heap->nodes==0){
		return 1;
	}
	else
		return 0;
}

int GetMaxPriority(BHHeap * heap){
	if(BHIsEmpty(heap)){
		printf("No root found..");
		return -1;
	}
	return heap->root->priority;
}

BHItem GetMaxItem(BHHeap * heap){
	if(BHIsEmpty(heap)){
		printf("No root found..");
		return (char*)"\0";
	}
	return heap->root->BHItemType;
}
void BHRemove(BHHeap * heap){
	if(heap->nodes==0){
		free(heap->root);
		return;
	}
	
	BHNode * temp=CBTGetLast(heap);
	heap->root->BHItemType=temp->BHItemType;
	heap->root->priority=temp->priority;
	
	if(temp->parent->left==temp)
		temp->parent->left=NULL;
	else
		temp->parent->right=NULL;
	
	free(temp);
	
	heap->nodes--;
	
	temp=heap->root;
	while(1){
		
		if(temp->left!=NULL && temp->left->priority > temp->priority ){
			
			
				//printf("ep");
				BHItem tempItem=temp->BHItemType;
				int tempPriority=temp->priority;
				
				temp->BHItemType=temp->left->BHItemType;
				temp->priority=temp->left->priority;
				
				temp->left->BHItemType=tempItem;
				temp->left->priority=tempPriority;
				
				temp=temp->left;
				
			
		}
		
		else if(temp->right!=NULL && temp->right->priority > temp->priority){
			
			
				BHItem tempItem=temp->BHItemType;
				int tempPriority=temp->priority;
				
				temp->BHItemType=temp->right->BHItemType;
				temp->priority=temp->right->priority;
				
				temp->right->BHItemType=tempItem;
				temp->right->priority=tempPriority;
				
				temp=temp->right;
				
			
		}
		
		else
			break;
		
	}
	
	
}

void BHInsert(BHHeap * heap ,int priority ,BHItem item){
	if(heap->nodes==0){
		heap->root=CreateNode(NULL,item,priority);
		heap->nodes++;
		return;
	}
	
	CBTInsertLast(heap,item,priority);
	BHNode * temp=CBTGetLast(heap);
	while(temp->parent){
		if(temp->priority > temp->parent->priority){
			BHItem tempItem=temp->BHItemType;
			int tempPriority=temp->priority;
			
			temp->BHItemType=temp->parent->BHItemType;
			temp->priority=temp->parent->priority;
			
			temp->parent->BHItemType=tempItem;
			temp->parent->priority=tempPriority;
		}
		temp=temp->parent;
	}
	
	
}

void Heapify2Nodes(BHNode * parent,BHNode * child){
	if(parent->priority < child->priority){
		BHItem tempItem=parent->BHItemType;
		int tempPriority=parent->priority;
		
		parent->BHItemType=child->BHItemType;
		parent->priority=child->priority;
		
		child->BHItemType=tempItem;
		child->priority=tempPriority;
	}
}

void Heapify(BHNode * root, int level, int counter){
	if(level>counter){
		Heapify(root->right,level,counter+1);
		Heapify(root->left,level,counter+1);
		return;
	}
	if(root->left==NULL && root->right==NULL){
		return;
	}
	
	if(root->right==NULL){
		Heapify2Nodes(root,root->left);
		return;
	}
	if(root->left==NULL){
		return;
	}
	if(root->right->priority > root->priority || root->left->priority > root->priority){
		BHNode * temp=root;
		
		if(root->right->priority > temp->priority){
			
			temp=root->right;
		}
		if(root->left->priority > temp->priority){
			temp=root->left;
		}
		
		Heapify2Nodes(root,temp);
		printf("ep");
	}
	
	
}

BHHeap * BHHeapify(int size, int * priorities, BHItem * items){
	
	BHHeap * heap=CBTCreate(40);
	int i,j;
	for(i=0;i<size;i++){
		CBTInsertLast(heap,items[i],priorities[i]);
	}
	CBTPreOrder(heap,visit);
	
	for(i=BTHeight(heap)-1;i>0;i--){
		Heapify(heap->root,i,1);
		printf("f");
	}
	return heap;
	
}

void BHDestroy(BHHeap * heap ){
	DestroyTree(heap->root);
}

