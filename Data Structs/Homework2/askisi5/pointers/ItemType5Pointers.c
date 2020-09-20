#include "ItemType5Pointers.h"

void Print(BHItem item){
	char* p=(char*)(item);
	printf("Item: %s \n",p);
}
