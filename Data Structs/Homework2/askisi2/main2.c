#include "askisi2.h"



int main(){
	
	BTTree * aR=BTCreate(7);
	
	BTInsertRoot(aR,(char*)"Root");
	BTInsertRoot(aR,(char*)"PLEASE");
	BTInsertLeft(aR,BTGetRoot(aR),(char*)"Left");
	BTInsertLeft(aR,BTGetRoot(aR),(char*)"PLEASE");
	BTInsertLeft(aR,BTGetChildLeft(aR,BTGetRoot(aR)),(char*)"Left1");
	BTInsertRight(aR,BTGetChildLeft(aR,BTGetRoot(aR)),(char*)"Left2");
	BTPreOrder(aR,visit);
	BTRemove(aR,BTGetRoot(aR));
	BTInsertRight(aR,BTGetRoot(aR),(char*)"Right");
	BTInsertRight(aR,BTGetRoot(aR),(char*)"PLEASE");
	BTInsertLeft(aR,BTGetChildRight(aR,BTGetRoot(aR)),(char*)"Right1");
	BTInsertRight(aR,BTGetChildRight(aR,BTGetRoot(aR)),(char*)"Right2");
	BTPreOrder(aR,visit);
	
	BTInsertRight(aR,BTGetChildRight(aR,BTGetChildRight(aR,BTGetRoot(aR))),(char*)"Right2");
	
	printf("========\nGetItemTest: %s GetParent(printthesame): %s  HeightTEST: %d   SizeTEST: %d\n========\n",
	(char*)BTGetItem(aR,BTGetRoot(aR)),(char*)BTGetItem(aR,BTGetParent(aR,BTGetChildRight(aR,BTGetRoot(aR)))),BTHeight(aR),BTSize(aR));
	BTRemove(aR,BTGetChildRight(aR,BTGetRoot(aR)));
	BTChange(aR,BTGetChildLeft(aR,BTGetRoot(aR)),(char*)"LeftNew");
	BTPreOrder(aR,visit);
	BTDestroy(aR);
	
	
	
}
