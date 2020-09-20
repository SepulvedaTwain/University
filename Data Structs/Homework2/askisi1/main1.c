#include "askisi1.h"



int main(){
	
	BTTree * aR=BTCreate(6);
	
	BTInsertRoot(aR,(char*)"Root");
	BTInsertRoot(aR,(char*)"PLEASE");
	BTInsertLeft(aR,BTGetRoot(aR),(char*)"Left");
	BTInsertLeft(aR,BTGetRoot(aR),(char*)"PLEASE");
	BTInsertLeft(aR,BTGetChildLeft(aR,BTGetRoot(aR)),(char*)"Left2");
	BTPreOrder(aR,visit);
	BTRemove(aR,BTGetRoot(aR));
	BTInsertRight(aR,BTGetRoot(aR),(char*)"Right");
	BTInsertRight(aR,BTGetRoot(aR),(char*)"PLEASE");
	BTInsertRight(aR,BTGetChildRight(aR,BTGetRoot(aR)),(char*)"Right2");
	BTPreOrder(aR,visit);
	
	
	printf("========\nGetItemTest: %s GetParent(printthesame): %s  HeightTEST: %d   SizeTEST: %d\n========\n",
	(char*)BTGetItem(aR,BTGetRoot(aR)),(char*)BTGetItem(aR,BTGetParent(aR,BTGetChildRight(aR,BTGetRoot(aR)))),BTHeight(aR),BTSize(aR));
	BTRemove(aR,BTGetChildRight(aR,BTGetRoot(aR)));
	BTChange(aR,BTGetChildLeft(aR,BTGetRoot(aR)),(char*)"LeftNew");
	BTPostOrder(aR,visit);
	BTDestroy(aR);
	
	
	
}
