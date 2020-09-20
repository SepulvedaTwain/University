#include "HTHash.h"
#include "ItemType.h"

void print(char * key,void * item);

int main(){
	printf("-------------\n");
	HTHash * hashTable=HTCreate(5);
	hashTable=HTInsert(hashTable,"Key",(int*)5,sizeof(5));
	hashTable=HTInsert(hashTable,"Key2",(int*)10,sizeof(10));
	hashTable=HTInsert(hashTable,"Key5",(int*)14,sizeof(14));
	HTVisit(hashTable,(*print));
	printf("-------------\n");
	hashTable=HTInsert(hashTable,"Key3",(int*)78,sizeof(78));
	hashTable=HTInsert(hashTable,"Key4",(int*)9,sizeof(9));
	hashTable=HTInsert(hashTable,"Key3",(int*)90,sizeof(90));
	HTVisit(hashTable,(*print));
	printf("-------------\n");
	printf("hashTable nodes: %d\n",hashTable->totalNodes);
	printf("-------------\n");
	HTRemove(hashTable,"Key4");
	HTVisit(hashTable,(*print));
	printf("-------------\n");
	void * pitem;
	HTGet(hashTable,"Key",&pitem,sizeof(5)); 
	printf("To HTGetItem->Item: %d\n",(int*)pitem);
	printf("-------------\n");
	HTDelete(hashTable);
}



void print(char * key,void * item){
	printf("key: %s  item : %d \n",key,((int*)item));
}
