#include "askisi2.h"

typedef struct btNode {
	
	BTItem btItemType;
    int parent;
    int position;
    int left;
    int right;
    
} BTnode;

typedef struct btTree{
	
	struct btNode ** array;
	int nodes;
	int lenght;
	
}BTtree;


BTNode * CreateNode(int position,int parent,BTItem  item){//dimiourgei neo node
	BTNode * root=(BTNode *)malloc(sizeof(BTNode));
	root->parent=parent;
	root->position=position;
	root->right=-1;
	root->left=-1;
	root->btItemType=item;  
	return root;
}

BTTree * BTCreate(int maxelem){//dimiourgei neo tree
	BTTree * treeRoot=(BTTree *)malloc(sizeof(BTTree));
	int i,len=maxelem;
	treeRoot->lenght=len;
	treeRoot->array=(BTNode **)malloc(sizeof(BTNode*)*(len));
	for(i=0;i<len;i++){
		treeRoot->array[i]=NULL;
	}
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
	tree->array[0]=CreateNode(0,-1,item);
	tree->nodes++;
	
}

void BTInsertLeft(BTTree *tree,BTNode * node ,BTItem item){//eisagei aristero paidi sto node pou theloume
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

void BTInsertRight(BTTree* tree,BTNode * node ,BTItem item ){//eisagei desksi paidi sto node pou theloume
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
void BTRemove(BTTree * tree, BTNode *node){//kanei remove to node pou theloyme apo to dentro
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

BTNode * BTGetRoot(BTTree * tree){//epistrefei to root
	
	if(BTIsEmpty(tree)){
		printf("No root found..\n");
		return NULL;
	}
	return tree->array[0];
}

BTNode * BTGetParent(BTTree * tree,BTNode * node){//epistrefei to parent tou node pou theloume
	if(node->parent==-1){
		printf("Root has no parent..\n");
		//return tree->array->parent;
	}
	return tree->array[node->parent];
}


BTNode * BTGetChildLeft(BTTree * tree,BTNode * node){// epistrefei to aristero paidi
	if(node->left==-1){
		printf("Node has no left child..\n");
		return NULL;
	}
	return tree->array[node->left];
}

BTNode * BTGetChildRight(BTTree * tree,BTNode * node){//epistrefei to aristero paidi
	if(node->right==-1){
		printf("Node has no right child.. \n");
		return NULL;
	}
	return tree->array[node->right];
}

BTItem  BTGetItem(BTTree * tree,BTNode * node){//to item tou node poy theloume
	return tree->array[node->position]->btItemType;
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

void preOrder(BTTree * tree,BTNode * node,void(*visit)(BTNode *)){
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
void BTPreOrder(BTTree * tree,void(*visit)(BTNode *)){//h preorder ektipwsi
	
	preOrder(tree,tree->array[0],visit);
	
	
}

int inOrder(BTTree * tree,BTNode * node,void(*visit)(BTNode *)){
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

void BTInOrder(BTTree * tree,void(*visit)(BTNode *)){//h in order ektipwsh
	
	inOrder(tree,tree->array[0],visit);
}

int postOrder(BTTree * tree,BTNode * node,void(*visit)(BTNode *)){
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

void BTPostOrder(BTTree * tree,void(*visit)(BTNode *)){//h post order ektipwsi
	
	postOrder(tree,tree->array[0],visit);
}

int BTHeight(BTTree * tree){  
    return FindHeight(tree,tree->array[0]);//epistrefei to ipsos tou dentrou
    
}

int FindHeight(BTTree * tree,BTNode * node){//vriskei to ipsos tou detrou
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

void BTDestroy(BTTree * tree){//kanei free to dentro
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
