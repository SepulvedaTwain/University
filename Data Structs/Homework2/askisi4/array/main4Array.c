#include "askisi4Array.h"

int main(){
	
	
	CBTTree * tree=CBTCreate(7);
	CBTInsertLast(tree,(char*)"Root");
	CBTInsertLast(tree,(char*)"Left");
	CBTInsertLast(tree,(char*)"Right");
	CBTInsertLast(tree,(char*)"Left1");
	CBTInsertLast(tree,(char*)"Left2");
	CBTInsertLast(tree,(char*)"Right1");
	CBTInsertLast(tree,(char*)"Right2");
	CBTPreOrder(tree,visit);
	printf("=======\n");
	CBTRemoveLast(tree);
	CBTRemoveLast(tree);
	CBTInsertLast(tree,(char*)"NewRight1");
	printf("=======\n");
	CBTPreOrder(tree,visit);
	printf("=======\n");
	CBTDestroy(tree);


	
}
