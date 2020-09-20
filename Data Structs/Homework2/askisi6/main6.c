#include "askisi6.h"



int main(){
	
	BTTree * tree=BSTCreate();
	
	int i;
	BSTInsert(tree,(int)0,compare);
	for(i=1;i<10;i++){
		BSTInsert(tree,(int)i*3,compare);
		BSTInsert(tree,(int)-i*3,compare);
	}
	printf("New Tree..\n");
	BTPreOrder(tree,visit);
	printf("Deleting root..\n");
	BSTDelete(tree,(int)0);
	BTPreOrder(tree,visit);
	printf("Destroy tree..\n");
	BSTDestroy(tree);
	printf("+++++++++\n10 comparisons: \n");
	tree=BSTCreate();
	for(i=1;i<10;i++){
		BSTInsert(tree,(int)i*3,compare);
	}
	BTPreOrder(tree,visit);
	
	
	
}
