#include "askisi5Array.h"





typedef struct bhNode {
	
	BHItem btItemType;
	int priority;
    int parent;
    int position;
    int left;
    int right;
    
} BHnode;

typedef struct bhHeap{
	
	struct bhNode ** array;
	int nodes;
	int lenght;
	
}BHheap;

BHNode * CreateNode(int position,int parent,BHItem  item,int priority){
	BHNode * root=(BHNode *)malloc(sizeof(BHNode));
	root->parent=parent;
	root->position=position;
	root->priority=priority;
	root->right=-1;
	root->left=-1;
	root->btItemType=item;  
	return root;
}

BHHeap * CBTCreate(int maxelem){
	BHHeap * treeRoot=(BHHeap *)malloc(sizeof(BHHeap));
	int i,len=maxelem;
	treeRoot->lenght=len;
	treeRoot->array=(BHNode **)malloc(sizeof(BHNode*)*(len));
	for(i=0;i<len;i++){
		treeRoot->array[i]=NULL;
	}
	treeRoot->nodes=0;
	return treeRoot;
}

int CBTSize(BHHeap * tree){
	return tree->nodes;	
}
int CBTIsEmpty(BHHeap* tree){
	if(tree->nodes==0){
		return 1;
	}
	else
		return 0;
}

int returnNodes(BHHeap*tree){
	return tree->nodes;
}

void CBTInsertRoot(BHHeap*tree,BHItem item){
	if(CBTIsEmpty(tree)==0){
		printf("Tree already has a root..\n");
		return;
	}
	//tree->array[0]=CreateNode(0,-1,item);
	tree->nodes++;
	
}

void CBTInsertLeft(BHHeap *tree,BHNode * node ,BHItem item){
	if(node->left!=-1){
		printf("Node has already a left node..\n");
		return;
	}
	
	int temp=node->position*2+1;
	if(temp>tree->lenght-1){
		printf("Not enough space..\n");
		return;
	}
	node->left=temp;
	//tree->array[temp]=CreateNode(temp,node->position,item);
	tree->nodes++;
}

void CBTInsertRight(BHHeap* tree,BHNode * node ,BHItem item ){
	if(node->right!=-1){
		printf("Node has already a right node..\n");
		return;
	}
	int temp=node->position*2+2;
	if(temp>tree->lenght-1){
		printf("Not enough space..\n");
		return;
	}
	node->right=temp;
	//tree->array[temp]=CreateNode(temp,node->position,item);	
	tree->nodes++;
	
}
void CBTRemove(BHHeap * tree, BHNode *node){
	if(node->left!=-1 || node->right!=-1){
		printf("Node has at least a child..\n");
		return;
	}
	if(node->parent==-1){
		node=NULL;
		tree->nodes--;
		return;
	}
	if(tree->array[node->parent]->left==node->position){
		tree->array[node->parent]->left=-1;
		tree->array[node->position]=NULL;
		free(node);
		node=NULL;
		tree->nodes--;
		return;
	}
	tree->array[node->parent]->right=-1;
	tree->array[node->position]=NULL;
	free(node);
	tree->nodes--;
	return;
}

BHNode * CBTGetRoot(BHHeap * tree){
	
	if(CBTIsEmpty(tree)){
		printf("No root found..\n");
		return NULL;
	}
	return tree->array[0];
}

BHNode * CBTGetParent(BHHeap * tree,BHNode * node){
	if(node->parent==-1){
		printf("Root has no parent..\n");
		//return tree->array->parent;
	}
	return tree->array[node->parent];
}


BHNode * CBTGetChildLeft(BHHeap * tree,BHNode * node){
	if(node->left==-1){
		printf("Node has no left child..\n");
		return NULL;
	}
	return tree->array[node->left];
}

BHNode * CBTGetChildRight(BHHeap * tree,BHNode * node){
	if(node->right==-1){
		printf("Node has no right child.. \n");
		return NULL;
	}
	return tree->array[node->right];
}

BHItem  CBTGetItem(BHHeap * tree,BHNode * node){
	return tree->array[node->position]->btItemType;
}

void CBTChange(BHHeap * tree,BHNode * node,BHItem item ){
	if(node==NULL){
		printf("Node is empty..\n");
		return;
	}
	node->btItemType=item;
	
}


void visit(BHNode * node){
	Print(node->btItemType);
}

void preOrder(BHHeap * tree,BHNode * node,void(*visit)(BHNode *)){
	if(node==NULL){
		return;
	}
	printf("Position: %d\t Priority %d\t",node->position,node->priority);
	visit(node);

	int temp1=node->position*2+1;
	int temp2=node->position*2+2;
	if(temp1>tree->lenght)
		return;
	if(temp2>tree->lenght)
		return;
	preOrder(tree,tree->array[temp1],visit);
	preOrder(tree,tree->array[temp2],visit);
	
}
void CBTPreOrder(BHHeap * tree,void(*visit)(BHNode *)){
	
	preOrder(tree,tree->array[0],visit);
	
	
}

int inOrder(BHHeap * tree,BHNode * node,void(*visit)(BHNode *)){
	if(node==NULL){
		return 0;
	}
	int temp1=node->position*2+1;
	int temp2=node->position*2+2;
	if(temp1>tree->lenght){
		printf("%d\t%d ",node->position,node->right);
		visit(node);
		return 1;
	}
	if(temp2>tree->lenght){
		printf("%d\t%d ",node->position,node->right);
		visit(node);
		return 1;
	}
	int flag=inOrder(tree,tree->array[temp1],visit);
	if(flag!=1){
	
	printf("%d\t%d ",node->position,node->right);
	visit(node);
	}
	inOrder(tree,tree->array[temp2],visit);
	
}

void CBTInOrder(BHHeap * tree,void(*visit)(BHNode *)){
	
	inOrder(tree,tree->array[0],visit);
}

int postOrder(BHHeap * tree,BHNode * node,void(*visit)(BHNode *)){
	if(node==NULL){
		return 0;
	}
	int temp1=node->position*2+1;
	int temp2=node->position*2+2;
	if(temp1>tree->lenght){
		printf("%d\t%d ",node->position,node->right);
		visit(node);
		return 1;
	}
		
	if(temp2>tree->lenght){
		printf("%d\t%d ",node->position,node->right);
		visit(node);
		return 1;
	}
	int flag1=postOrder(tree,tree->array[temp1],visit);
	int flag2=postOrder(tree,tree->array[temp2],visit);
	if(flag1!=1 || flag2!=1){
	
	printf("%d\t%d ",node->position,node->right);
	visit(node);
	}
}

void CBTPostOrder(BHHeap * tree,void(*visit)(BHNode *)){
	
	postOrder(tree,tree->array[0],visit);
}

int CBTHeight(BHHeap * tree){  
    return FindHeight(tree,tree->array[0]);
    
}

int FindHeight(BHHeap * tree,BHNode * node){
	if (node == NULL)  
        return 0;  
    else{ 
	    int temp1=node->position*2+1;
		int temp2=node->position*2+2;
		if(temp1>=tree->lenght)
			return 1;
		if(temp2>=tree->lenght)
			return 1;
        int leftLen = FindHeight(tree,tree->array[temp1]);  
        int rightLen = FindHeight(tree,tree->array[temp2]);  
        if (leftLen > rightLen)  
            return(leftLen + 1);  
        else 
			return(rightLen + 1);  
    }  
} 

void CBTDestroy(BHHeap * tree){
	if (tree==NULL)
        return;
   	int i;
   	printf("Destroy!..\n");
   	for(i=0;i<tree->lenght;i++){
   		if(tree->array[i]!=NULL)
   			printf("Node : %s is destroyed\n",(char*)tree->array[i]->btItemType);
   		free(tree->array[i]);
	}
    free(tree->array);
    free(tree);
	
	
}



//======================

BHNode * CBTGetLast(BHHeap * tree){
	int i;
	if(CBTIsEmpty(tree)==1){
		printf("Empty tree..");
		return NULL;
	}
	return tree->array[tree->nodes-1];
	
}

void CBTInsertLast(BHHeap *tree,BHItem item,int priority){
	if(tree->nodes==tree->lenght){
		printf("Tree Already Completed..\n");
		return;
	}
	tree->array[tree->nodes]=CreateNode(tree->nodes,(tree->nodes-1)/2,item,priority);
	if(tree->array[(tree->nodes-1)/2]->left==-1)
		tree->array[(tree->nodes-1)/2]->left=tree->nodes;
	else
		tree->array[(tree->nodes-1)/2]->right=tree->nodes;
	tree->nodes++;
		
}

void CBTRemoveLast(BHHeap * tree){
	BHNode * temp=CBTGetLast(tree);
	if(tree->array[temp->parent]->left==temp->position){
		tree->array[temp->parent]->left=-1;
		tree->array[temp->position]=NULL;
		free(temp);
		temp=NULL;
		tree->nodes--;
		return;
	}
	tree->array[temp->parent]->right=-1;
	tree->array[temp->position]=NULL;
	free(temp);
	tree->nodes--;
	return;
}

//==================


BHHeap * BHCreate(int maxelem){
	BHHeap * treeRoot=(BHHeap *)malloc(sizeof(BHHeap));
	int i,len=maxelem;
	treeRoot->lenght=len;
	treeRoot->array=(BHNode **)malloc(sizeof(BHNode*)*(len));
	for(i=0;i<len;i++){
		treeRoot->array[i]=NULL;
	}
	treeRoot->nodes=0;
	return treeRoot;
	
}


int BHIsEmpty(BHHeap * heap){
	
	if(heap->nodes==0){
		return 1;
	}
	else
		return 0;
}

int BHGetMaxPriority(BHHeap * heap){
	//to priority tou root
	if(BHIsEmpty(heap)){
		printf("No root found..\n");
		return -1;
	}
	
	return heap->array[0]->priority;
	
}

BHItem BHGetMaxItem(BHHeap * heap){
	//to item tou root
	if(BHIsEmpty(heap)){
		printf("No root found..\n");
		return NULL;
	}
	return heap->array[0]->btItemType;
}

void BHInsert(BHHeap * heap, int priority , BHItem item){
	if(heap->nodes==heap->lenght){
		printf("Tree is already full..\n");
		return;
	}
	heap->array[heap->nodes]=CreateNode(heap->nodes,(heap->nodes-1)/2,item,priority);
	if(heap->array[(heap->nodes-1)/2]->left==-1)
		heap->array[(heap->nodes-1)/2]->left=heap->nodes;
	else
		heap->array[(heap->nodes-1)/2]->right=heap->nodes;
	int i=heap->nodes;
	while(i != 0 ){
		if(heap->array[i]->priority > heap->array[(i-1)/2]->priority){
			BHItem tempItem=heap->array[i]->btItemType;
			int tempPriority=heap->array[i]->priority;
			heap->array[i]->btItemType=heap->array[(i-1)/2]->btItemType;
			heap->array[i]->priority=heap->array[(i-1)/2]->priority;
			heap->array[(i-1)/2]->btItemType=tempItem;
			heap->array[(i-1)/2]->priority=tempPriority;
			
			
		}
		else
			break;
		i=(i-1)/2;
	}
	heap->nodes++;
}

void BHRemove(BHHeap * heap){
	//kanoume remove to root
	if(BHIsEmpty(heap)){
		printf("Empty Tree..");
		return;
	}
	if(heap->nodes==1){
		free(heap->array[0]);
		return;
	}
	BHNode * temp=heap->array[heap->nodes-1];//vazoume to last node san prwto
	if(heap->array[temp->parent]->left==temp->position){
		heap->array[temp->parent]->left=-1;
	}
	else
		heap->array[temp->parent]->right=-1;
	
	heap->array[0]->btItemType=temp->btItemType;
	heap->array[0]->priority=temp->priority;
	
	
	
	
	
	
	int i=0;
	
	while(i<heap->nodes ){ //kai to pame oso katw xriazete 
		if(i*2+1 > heap->lenght || i*2+2 > heap->lenght)
			break;
		if(heap->array[i]->priority < heap->array[(i*2)+1]->priority){
			BHItem tempItem=heap->array[i]->btItemType;
			int tempPriority=heap->array[i]->priority;
			heap->array[i]->btItemType=heap->array[(i*2)+1]->btItemType;
			heap->array[i]->priority=heap->array[(i*2)+1]->priority;
			heap->array[(i*2)+1]->btItemType=tempItem;
			heap->array[(i*2)+1]->priority=tempPriority;
			i=(i*2)+1;
			
		}
		else if(heap->array[i]->priority < heap->array[(i*2)+2]->priority){
			BHItem tempItem=heap->array[i]->btItemType;
			int tempPriority=heap->array[i]->priority;
			heap->array[i]->btItemType=heap->array[(i*2)+2]->btItemType;
			heap->array[i]->priority=heap->array[(i*2)+2]->priority;
			heap->array[(i*2)+2]->btItemType=tempItem;
			heap->array[(i*2)+2]->priority=tempPriority;
			i=(i*2)+2;
		
		}
		else 
			break;
		
		
	}
	
	heap->array[heap->nodes-1]=NULL;
	free(temp);
	temp=NULL;
	heap->nodes--;
	
	
	
}

void Heapify(BHHeap * heap, int position ){
	//to heapify kanei anadiataksi twn node kai o megaliteros paei panw.
	int temp=position;
	int tempL=position*2 +1;
	int tempR=position*2 +2;
	if(tempL>heap->nodes || tempR > heap->nodes)
		return;
	if(heap->array[temp]->priority < heap->array[tempL]->priority){
		temp=tempL;
	}
	if(heap->array[temp]->priority < heap->array[tempR]->priority){
		temp=tempR;
	}
	if(temp != position){
		BHItem tempItem=heap->array[position]->btItemType;
		int tempPriority=heap->array[position]->priority;
		heap->array[position]->btItemType=heap->array[temp]->btItemType;
		heap->array[position]->priority=heap->array[temp]->priority;
		heap->array[temp]->btItemType=tempItem;
		heap->array[temp]->priority=tempPriority;
		
		Heapify(heap,temp);
	}
	
	
}

BHHeap * BHHeapify(int size , int * priorities, BHItem * items){
	//fitaxnoume to dentro kai kaloume tin heapify me ena loop mesa se loop
	int i,j;
	BHHeap * heap=CBTCreate(size);
	for(i=0;i<size;i++){
		CBTInsertLast(heap,items[i],priorities[i]);
	}
	printf("New CBT Tree...\n");
	CBTPreOrder(heap,visit);
	
	for(i=0;i<=size;i++)
		for(j=0;j<=size;j++)
			Heapify(heap,j);
	return heap;
	
	
}

void BHDestroy(BHHeap * heap){
	if (heap==NULL)
        return;
   	int i;
   	printf("Destroy!..\n");
   	for(i=0;i<heap->lenght;i++){
   		if(heap->array[i]!=NULL)
   			printf("Node : %s is destroyed\n",(char*)heap->array[i]->btItemType);
   		free(heap->array[i]);
	}
    free(heap->array);
    free(heap);
}

