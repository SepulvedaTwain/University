#include "askisi5Pointers.h"



int main(){
	/*
	BHHeap * heap=BHCreate(40);
	
	BHInsert(heap,50,(char*)"1");
	BHInsert(heap,60,(char*)"2");
	BHInsert(heap,40,(char*)"3");
	BHInsert(heap,6000,(char*)"4");
	BHInsert(heap,0,(char*)"5");
	printf("Nodes: %d \n",BTSize(heap));
	CBTPreOrder(heap,visit);
	BHRemove(heap);
	printf("++++++\n");
	printf("Nodes: %d \n",BTSize(heap));
	CBTPreOrder(heap,visit);
	BHDestroy(heap);
	
	printf("+++++\nNew CBTTree!..\n");
	int i,size=7;
	int priorities[size];
	BHItem items[size];
	
	for(i=0;i<size;i++){
		priorities[i]=i*2;
		items[i]=(char*)"TEST";
	}
	
	BHHeap * eleos=BHHeapify(size,priorities,items);
	printf("++++++\n");
	CBTPreOrder(eleos,visit);
	*/
	
	BHHeap * heap=BHCreate(7);
	BHInsert(heap,3,(char*)"Root");
	BHInsert(heap,6,(char*)"Left");
	BHInsert(heap,9,(char*)"Right");
	BHInsert(heap,5,(char*)"Left1");
	BHInsert(heap,3,(char*)"Left2");
	BHInsert(heap,1,(char*)"Right1");
	BHInsert(heap,89,(char*)"Right2");
	BHInsert(heap,3434,(char*)"PE");
	CBTPreOrder(heap,visit);
	printf("=======\n");
	BHRemove(heap);
	CBTPreOrder(heap,visit);
	printf("=======\n");
	BHRemove(heap);
	CBTPreOrder(heap,visit);
	BHInsert(heap,44555,(char*)"NewRight1");
	printf("=======\n");
	CBTPreOrder(heap,visit);
	printf("=======\n");
	BHDestroy(heap);
	
	printf("++++++++++\n+++++++++++\n");
	
	int i,size=5;
	int prior[size];
	for(i=0;i<size;i++){
		prior[i]=i*3;
	}
	BHItem items[size];
	for(i=0;i<size;i++){
		items[i]=(char*)"TEST";
	}
	
	BHHeap * heap2=BHHeapify(size, prior , items);
	printf("===============\n");
	CBTPreOrder(heap2,visit);
	
}
