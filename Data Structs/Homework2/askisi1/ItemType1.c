#include "ItemType1.h"
#include <stdio.h>
void Print(BTItem item){
	char* p=(char*)(item);
	printf("Item: %s \n",p);
}
