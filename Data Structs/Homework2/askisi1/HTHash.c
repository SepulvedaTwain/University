#include "HTHash.h"



int universalHashingString( int M, char *str){
	int h =0;

	// parameter a
	int a =6;

	// 1000th prime number
	int p = 7919;

	// universal hashing for strings
	int i =0;
	while ( str[i] != '\0')
	{
		h = (h*a + str[i]) % p;
		i++;
	}

	return (h % M)+1;
}

HTListNode * CreateNode(char * key, void * item, size_t itemSize){
	HTListNode * temp=(HTListNode*)malloc(sizeof(HTListNode));
	
	strcpy(temp->key,key);
	
	temp->item=malloc(itemSize);
	
	temp->sizeItem=itemSize;
	
	//memcpy(temp->item,item,itemSize);
	temp->item=item;
	
	temp->next=NULL;
	return temp;
}

void initList(HTList * list){
	list->head=NULL;
	list->tail=NULL;
	list->count=0;
}


int isEmpty(HTList * list){
	return list->count==0;
}

int isNodeReplaced(HTList * list,char * key,void *item,size_t itemSize){
	
	HTListNode * temp=list->head;
	while(temp){
		
		if(!strcmp(temp->key,key)){
			
			//free(temp->item);
			//temp->item=malloc(itemSize);
			temp->item=item;
			return 1;
		}
		temp=temp->next;
	}
	
	return 0;
}

int insertNode(HTList * list,char * key, void * item, size_t itemSize){
	
	HTListNode * temp=CreateNode(key,item,itemSize);
	
	
	
	if(isEmpty(list)){
		
		list->head=temp;
		list->tail=temp;
		list->count++;
		return 1;
	}

	
	if(isNodeReplaced(list,key,item,itemSize))
		return 0;
	list->count++;
	list->tail->next=temp;
	list->tail=list->tail->next;
	return 1;
	
}

void deleteNode(HTList * list, char * key){
	if(isEmpty(list)){
		printf("Empty list(deletenode)");
		return;
	}
	HTListNode * temp=list->head;
	HTListNode * prv=NULL;
	
	while(temp->next){
		if(!strcmp(temp->key,key)){
			break;
		}
		prv=temp;
		temp=temp->next;
	}
	
	if(temp==NULL){
		printf("No key found(deletenode");
		return;
	}

	if(prv==NULL){
		
		if(list->count==1){
			
			list->head=NULL;
			list->tail=NULL;
			freeNode(&temp);
			list->count--;
			
			return;
		}
		list->head=list->head->next;
		freeNode(&temp);
		list->count--;
		return;
	}
	else if(temp==list->tail){
		list->tail=prv;
		list->tail->next=NULL;
		freeNode(&temp);
		list->count--;
		return;
	}
	else{
		prv->next=temp->next;
		freeNode(&temp);
		list->count--;
		return;
	}

}

void freeNode(HTListNode ** node){
	//printf("ERROR\n");
	//free((*(node))->item);
	//printf("ERROR\n");
	free(*node);
	return;
}

int htListGet(HTList * list, char * key , void ** pitem,size_t itemSize){
	if(isEmpty(list)){
		printf("Empty list(htlistget)");
		return 0;
	}
	HTListNode * temp=list->head;
	while(temp){
		if(!strcmp(temp->key,key)){
			
			//memcpy(pitem,temp->item,itemSize);
			
			*pitem=temp->item;
			return 1;
		}
		temp=temp->next;
	}
	
	return 0;

}

void deleteList(HTList* list){
	if(isEmpty(list)){
		return;
	}
	HTListNode * temp;
	while(list->head){
		printf("Node %s Deleted..\n",list->head->key);
		temp=list->head;
		list->head=list->head->next;
		free(temp);

	}
}


HTHash * HTCreate(size_t size){
	HTHash * temp=(HTHash*)malloc(sizeof(HTHash));
	temp->load_factor=0;
	temp->size=size;
	temp->totalNodes=0;
	temp->hashTable=(HTList*)malloc(sizeof(HTList)*size);
	int i;
	for(i=0;i<size;i++){
		initList(&(temp->hashTable[i]));
	}
	return temp;
}

int HTSize(HTHash * hash){

	return hash->totalNodes;

}


int HTGet(HTHash * hash,char * key,void ** pitem,size_t sizeItem){
	 int position=universalHashingString( hash->size , key);
	 return htListGet(&(hash->hashTable[position-1]),key,pitem,sizeItem);

}

HTHash * doubleHashTable(HTHash * hash){
	
	HTHash * temp=HTCreate(hash->size*2);
	int i;
	for(i=0;i<hash->size;i++){
		HTListNode * tempNode=hash->hashTable[i].head;
		while(tempNode){
			HTInsert(temp,tempNode->key,tempNode->item,tempNode->sizeItem);
			
			tempNode=tempNode->next;
		}
	}
	HTHash * temp2=hash;
	//hash=temp;
	HTDelete(temp2);
	return temp;
	
}

HTHash * HTInsert(HTHash * hash,char * key,void * item,size_t sizeItem){
	if(hash->load_factor> 0.75)
		hash=doubleHashTable(hash);
	int position=universalHashingString( hash->size , key);
	
	
	if(insertNode(&(hash->hashTable[position-1]),key,item,sizeItem));
		hash->totalNodes++;
	
	hash->load_factor=((double)hash->totalNodes/(double)hash->size);
	
	return hash;
}

void HTRemove(HTHash *hash,char * key){
	int position=universalHashingString( hash->size , key);
	
	deleteNode(&(hash->hashTable[position-1]),key);
	
	hash->totalNodes--;
}

void HTVisit(HTHash *hash, void (*visit)(char * ,void *)){
	int i;
	for(i=0;i<hash->size;i++){
		HTListNode * temp=hash->hashTable[i].head;
		while(temp){
			
			(*visit)(temp->key,temp->item);
			temp=temp->next;
		}
	}

}

void HTDelete(HTHash * hash){
	int i;
	for(i=0;i<hash->size;i++){
		printf("List %d Deleted..\n",i);
		deleteList(&(hash->hashTable[i]));
		
	}
	free(hash);
	
}
