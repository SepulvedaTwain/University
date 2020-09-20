#include "askisi4Array.h"




typedef struct cbtNode {
	
	CBTItem btItemType;
    int parent;
    int position;
    int left;
    int right;
    
} CBTnode;

typedef struct cbtTree{
	
	struct cbtNode ** array;
	int nodes;
	int lenght;
	
}CBTtree;

CBTNode * CreateNode(int position,int parent,CBTItem  item){
	CBTNode * root=(CBTNode *)malloc(sizeof(CBTNode));
	root->parent=parent;
	root->position=position;
	root->right=-1;
	root->left=-1;
	root->btItemType=item;  
	return root;
}

CBTTree * CBTCreate(int maxelem){
	CBTTree * treeRoot=(CBTTree *)malloc(sizeof(CBTTree));
	int i,len=maxelem;
	treeRoot->lenght=len;
	treeRoot->array=(CBTNode **)malloc(sizeof(CBTNode*)*(len));
	for(i=0;i<len;i++){
		treeRoot->array[i]=NULL;
	}
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

void CBTInsertRoot(CBTTree*tree,CBTItem item){
	if(CBTIsEmpty(tree)==0){
		printf("Tree already has a root..\n");
		return;
	}
	tree->array[0]=CreateNode(0,-1,item);
	tree->nodes++;
	
}

void CBTInsertLeft(CBTTree *tree,CBTNode * node ,CBTItem item){
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
	tree->array[temp]=CreateNode(temp,node->position,item);
	tree->nodes++;
}

void CBTInsertRight(CBTTree* tree,CBTNode * node ,CBTItem item ){
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
	tree->array[temp]=CreateNode(temp,node->position,item);	
	tree->nodes++;
	
}
void CBTRemove(CBTTree * tree, CBTNode *node){
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

CBTNode * CBTGetRoot(CBTTree * tree){
	
	if(CBTIsEmpty(tree)){
		printf("No root found..\n");
		return NULL;
	}
	return tree->array[0];
}

CBTNode * CBTGetParent(CBTTree * tree,CBTNode * node){
	if(node->parent==-1){
		printf("Root has no parent..\n");
		//return tree->array->parent;
	}
	return tree->array[node->parent];
}


CBTNode * CBTGetChildLeft(CBTTree * tree,CBTNode * node){
	if(node->left==-1){
		printf("Node has no left child..\n");
		return NULL;
	}
	return tree->array[node->left];
}

CBTNode * CBTGetChildRight(CBTTree * tree,CBTNode * node){
	if(node->right==-1){
		printf("Node has no right child.. \n");
		return NULL;
	}
	return tree->array[node->right];
}

CBTItem  CBTGetItem(CBTTree * tree,CBTNode * node){
	return tree->array[node->position]->btItemType;
}

void CBTChange(CBTTree * tree,CBTNode * node,CBTItem item ){
	if(node==NULL){
		printf("Node is empty..\n");
		return;
	}
	node->btItemType=item;
	
}


void visit(CBTNode * node){
	Print(node->btItemType);
}

void preOrder(CBTTree * tree,CBTNode * node,void(*visit)(CBTNode *)){
	if(node==NULL){
		return;
	}
	//printf("%d\t%d ",node->position,node->right);
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
void CBTPreOrder(CBTTree * tree,void(*visit)(CBTNode *)){
	
	preOrder(tree,tree->array[0],visit);
	
	
}

int inOrder(CBTTree * tree,CBTNode * node,void(*visit)(CBTNode *)){
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

void CBTInOrder(CBTTree * tree,void(*visit)(CBTNode *)){
	
	inOrder(tree,tree->array[0],visit);
}

int postOrder(CBTTree * tree,CBTNode * node,void(*visit)(CBTNode *)){
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

void CBTPostOrder(CBTTree * tree,void(*visit)(CBTNode *)){
	
	postOrder(tree,tree->array[0],visit);
}

int CBTHeight(CBTTree * tree){  
    return FindHeight(tree,tree->array[0]);
    
}

int FindHeight(CBTTree * tree,CBTNode * node){
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

void CBTDestroy(CBTTree * tree){
	if (tree==NULL)
        return;
   	int i;
   	printf("Destroy!..\n");
   	for(i=0;i<tree->lenght;i++){
   		if(tree->array[i]!=NULL)
   			printf("Node : %s is destroyed\n",(char*)tree->array[i]->btItemType);
   		free(tree->array[i]);
	}
    free(tree);
	
	
}



//======================

CBTNode * CBTGetLast(CBTTree * tree){
	//epistrefei ton teleuteo
	int i;
	if(CBTIsEmpty(tree)==1){
		printf("Empty tree..");
		return NULL;
	}
	return tree->array[tree->nodes-1];
	
}

void CBTInsertLast(CBTTree *tree,CBTItem item){
	//kanei insert sto telos tou dentrou ena node
	if(tree->nodes==tree->lenght){
		printf("Tree Already Completed..\n");
		return;
	}
	tree->array[tree->nodes]=CreateNode(tree->nodes,(tree->nodes-1)/2,item);
	if(tree->array[(tree->nodes-1)/2]->left==-1)
		tree->array[(tree->nodes-1)/2]->left=tree->nodes;
	else
		tree->array[(tree->nodes-1)/2]->right=tree->nodes;
	tree->nodes++;
		
}

void CBTRemoveLast(CBTTree * tree){
	//vriski ton last node kai ton bgazei
	CBTNode * temp=CBTGetLast(tree);
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

