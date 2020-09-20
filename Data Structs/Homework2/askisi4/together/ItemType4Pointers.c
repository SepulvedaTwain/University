#include "ItemType4Pointers.h"

void Print(CBTItem item){
	char* p=(char*)(item);
	printf("Item: %s \n",p);
}
