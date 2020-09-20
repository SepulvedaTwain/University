#include "ItemType6.h"
#include <stdio.h>


void Print(BSTItem item){
	int p=(int)(item);
	printf("Item: %d \n",p);
}

int compare(BSTItem item1 ,BSTItem item2){
	
	if( (int)item1>(int)item2){
		return 1;
	}
	else if ( (int)item1<(int)item2)
		return -1;
	else
		return 0;
}

