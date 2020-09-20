#ifndef HT_HASH
#define HT_HASH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef char KEY[50];

typedef struct hln{
	KEY key;
	void * item;
	size_t sizeItem;
	struct hln * next;

}HTListNode;


typedef struct {
	HTListNode * head;
	HTListNode * tail;
	int count;


}HTList;


typedef struct{
	double load_factor;
	size_t size;
	HTList * hashTable;
	int totalNodes;
}HTHash;


int universalHashingString( int M, char *str);

HTListNode * CreateNode(char * key,void * item,size_t itemSize);

void initList(HTList * list);

int isEmpty(HTList * list);

int isNodeReplaced(HTList * list,char * key,void *item,size_t itemSize);

int insertNode(HTList * list,char * key, void * item, size_t itemSize);

void deleteNode(HTList * list, char * key);

void freeNode(HTListNode ** node);

int htGetList(HTList * list, char * key , void * pitem,size_t itemSize);

void deleteList(HTList* list);

HTHash * doubleHashTable(HTHash * hash);


HTHash * HTCreate(size_t size);

int HTSize(HTHash * hash);

int HTGet(HTHash * hash,char * key,void ** pitem,size_t sizeItem);

HTHash * HTInsert(HTHash * hash,char * key,void * item,size_t sizeItem);

void HTRemove(HTHash *hash,char * key);

void HTVisit(HTHash *hash, void (*visit)(char * ,void *));

void HTDelete(HTHash * hash);


#endif
