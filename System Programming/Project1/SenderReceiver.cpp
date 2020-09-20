#include "SenderReceiver.h"
class TransHashBase;
class TransactionNode;

TransactionNode::TransactionNode(char * transId,Date *date,BitcoinAddressNodeList * transList):date(date),next(NULL),transList(transList){
	this->transId=new char[strlen(transId)+1];
	strcpy(this->transId,transId);
	BitcoinAddressNode * temp=this->transList->head;
	while(temp){
		
		temp=temp->next;
	}
}

TransactionNode::~TransactionNode(){
	delete [] transId;
}


TransactionList::~TransactionList(){
	TransactionNode * temp;
	while(head){
		temp=head;
		head=head->next;
		delete temp;
	}
	
}

/*void TransactionList::insertTransNode(Date date, char* transId,BitcoinTreeNode * bitNode){
	TransactionNode * temp=tail;
	if (head==NULL){
		head= new TransactionNode(transId,date,bitNode);
		counter++;
		tail=head;
		return ;
	}
	temp->next=new TransactionNode(transId,date,bitNode);
	tail=temp->next;
	counter++;
	
}*/


void TransactionList::insertTransNodes(Date * date, char* transId,BitcoinAddressNodeList * bitsList){
	//BitcoinAddressNode * temp=bitsList->head;
	//while(temp){
	//	insertTransNode(date, transId,temp->treePtr);
	//	temp=temp->next;
	//}	
	
	//delete bitsList;
	TransactionNode * temp=tail;
	if(head==NULL){
		head=new TransactionNode(transId,date,bitsList);
		counter++;
		tail=head;
		return;
	}
	temp->next=new TransactionNode(transId,date,bitsList);
	tail=temp->next;
	counter++;
	}
	
	
void TransactionList::findEarnings(Date imer,Date imer2,TransHashBase &transBase){ //we get the amount of user and print the transactions
	
	
	TransactionNode * temp=head;
	
	int sum=0;
	while(temp){
		//cout<<"imer "<<imer.cmpTime<<" imer2 "<<imer2.cmpTime<<" temp "<<temp->date->cmpTime<<endl;
		if((temp->date->cmpTime>=imer.cmpTime && temp->date->cmpTime<=imer2.cmpTime)){
			
			sum+=temp->transList->bringMoney();
			
		}
		else if(imer.cmpTime<0){
			
			sum+=temp->transList->bringMoney();
		}
		
		temp=temp->next;
	}
	
	cout<<"Amount is :"<<sum<<endl;
	
	TransactionNode * temp2=head;
	while(temp2){
		if((temp2->date->cmpTime>=imer.cmpTime && temp2->date->cmpTime<=imer2.cmpTime)  || imer.cmpTime<0 ){
			transBase.printTrans(temp2->transId);
			
		}
		temp2=temp2->next;
	}
	
}	


//----------------------------


void SenderInfo::setSenderInfo(char * walletId){
	this->walletId=new char[strlen(walletId)+1];
	strcpy(this->walletId,walletId);
}

SenderInfo::~SenderInfo(){
	delete [] walletId;
}
	
SenderBucket::SenderBucket(int bucketSize):bucketSize(bucketSize),curPosition(0),next(NULL){
	userTransactions=new SenderInfo[bucketSize];
	
}

SenderBucket::~SenderBucket(){
	//delete userTransactions;
}

SenderBucket* SenderBucket::insertUser(char* walletId){
	if(curPosition<bucketSize-1){
		userTransactions[curPosition++].setSenderInfo(walletId);
		
	}
	if(curPosition==bucketSize){
		this->next=new SenderBucket(bucketSize);
		
	}
	return next;
}


SenderHashTableCell::~SenderHashTableCell(){
	SenderBucket * temp;
	while(head){
		temp=head;
		head=head->next;
		delete temp;
	}
}

bool SenderHashTableCell::isEmpty(){
	
	return bucketCounter==0;
}

void SenderHashTableCell::insertUser(char*walletId,int bucketSize){
	SenderBucket * temp;
	
	if (isEmpty()){
		head=new SenderBucket(bucketSize);
		tail=head;
		bucketCounter++;
		temp=head->insertUser(walletId);
		if(temp){
			tail=temp;
			bucketCounter++;
		}
		return;
	}
	temp=tail->insertUser(walletId);
	if(temp){
		tail=temp;
		bucketCounter++;
	}
	
	return;
	
	
	
}

SenderInfo * SenderHashTableCell::findUser(char* walletId){
	SenderBucket* temp=head;
	int i;
	while(temp){
		for(i=0;i<temp->curPosition;i++)
			if(!strcmp(walletId,temp->userTransactions[i].walletId)){
				return &(temp->userTransactions[i]);
			}
		temp=temp->next;
	}
	return NULL;
	
	
}


void SenderHashTableCell::insertTransNodes(char* walletId,Date * date, char* transId,BitcoinAddressNodeList * bitsList,int bucketSize){
	
	SenderInfo* temp=findUser(walletId);
	
	if(temp==NULL){
		
		this->insertUser(walletId,bucketSize);
		
		temp=findUser(walletId);
		
	}
	temp->transactionList.insertTransNodes(date,transId,bitsList);
	
}

SenderBase::SenderBase(int bucketSize, int hashTableSize):bucketSize(bucketSize),hashTableSize(hashTableSize){
	hashTable= new SenderHashTableCell[hashTableSize];
	
}

SenderBase::~SenderBase(){
	//delete hashTable;
}

bool SenderBase::insertTransNodes(char* walletId, Date* imer, char* transId,BitcoinAddressNodeList * bitsList){
	int position=universalHashingString(hashTableSize,walletId);
	
		
	//cout<<imer->day<<" "<<imer->month<<" "<<imer->year<<"  "<<imer->cmpTime<<endl;

	hashTable[position].insertTransNodes(walletId, imer, transId, bitsList, bucketSize);
	return true;
}

bool SenderBase::findPayments(char* walletId, Date imer, Date imer2,TransHashBase &transBase){
	if(isUserExist(walletId)==false)
		return false;
	int position=universalHashingString(hashTableSize,walletId);
	SenderInfo * temp=hashTable[position].findUser(walletId);
	
	temp->transactionList.findEarnings(imer,imer2,transBase); //findPayments and findEarnings work the same way but for differnt Base so no need to make two functions we make one in the transactionlistnode class
	return true;
}

bool SenderBase::isUserExist(char * walletId){
	int position=universalHashingString(hashTableSize,walletId);
	SenderInfo * temp=hashTable[position].findUser(walletId);
	if(temp==NULL)
		return false;
	return true;
	
}



//____________________________________----------------------------------_____________________

void ReceiverInfo::setReceiverInfo(char * walletId){
	this->walletId=new char[strlen(walletId)+1];
	strcpy(this->walletId,walletId);
}

ReceiverInfo::~ReceiverInfo(){
	delete [] walletId;
}

ReceiverBucket::ReceiverBucket(int bucketSize):bucketSize(bucketSize),curPosition(0),next(NULL){
	userTransactions=new ReceiverInfo[bucketSize];
	
}

ReceiverBucket::~ReceiverBucket(){
	//delete userTransactions;
}

ReceiverBucket* ReceiverBucket::insertUser(char* walletId){
	if(curPosition<bucketSize-1){
		userTransactions[curPosition++].setReceiverInfo(walletId);
		
	}
	if(curPosition==bucketSize){
		this->next=new ReceiverBucket(bucketSize);
		
	}
	return next;
}

ReceiverHashTableCell::~ReceiverHashTableCell(){
	ReceiverBucket * temp;
	while(head){
		temp=head;
		head=head->next;
		delete temp;
	}
}

bool ReceiverHashTableCell::isEmpty(){
	return bucketCounter==0;
}

void ReceiverHashTableCell::insertUser(char*walletId,int bucketSize){
	ReceiverBucket * temp;
	if (isEmpty()){
		head=new ReceiverBucket(bucketSize);
		tail=head;
		bucketCounter++;
		temp=head->insertUser(walletId);
		if(temp){
			tail=temp;
			bucketCounter++;
		}
		return;
	}
	temp=head->insertUser(walletId);
	if(temp){
		tail=temp;
		bucketCounter++;
	}
	return;
	
	
	
}

ReceiverInfo * ReceiverHashTableCell::findUser(char* walletId){
	ReceiverBucket* temp=head;
	int i;
	while(temp){
		for(i=0;i<temp->curPosition;i++)
			if(!strcmp(walletId,temp->userTransactions[i].walletId)){
				return &(temp->userTransactions[i]);
			}
		temp=temp->next;
	}
	return NULL;
	
	
}


void ReceiverHashTableCell::insertTransNodes(char* walletId,Date * date, char* transId,BitcoinAddressNodeList * bitsList,int bucketSize){
	ReceiverInfo* temp=findUser(walletId);
	if(temp==NULL){
		insertUser(walletId,bucketSize);
		temp=findUser(walletId);
	}
	temp->transactionList.insertTransNodes(date,transId,bitsList);
}


ReceiverBase::ReceiverBase(int bucketSize, int hashTableSize):bucketSize(bucketSize),hashTableSize(hashTableSize){
	hashTable= new ReceiverHashTableCell[hashTableSize];
	
}

ReceiverBase::~ReceiverBase(){
	//delete hashTable;
}

bool ReceiverBase::insertTransNodes(char* walletId,Date * date, char* transId,BitcoinAddressNodeList * bitsList){
	int position=universalHashingString(hashTableSize,walletId);
	//cout<<date.day<<" "<<date.month<<" "<<date.year<<" "<<date.cmpTime<<endl;
	hashTable[position].insertTransNodes(walletId,date, transId, bitsList, bucketSize);
	return true;
}


bool ReceiverBase::findEarnings(char* walletId, Date imer, Date imer2,TransHashBase &transBase){
	if(isUserExist(walletId)==false)
		return false;
	
	int position=universalHashingString(hashTableSize,walletId);
	ReceiverInfo * temp=hashTable[position].findUser(walletId);
	
	temp->transactionList.findEarnings(imer,imer2,transBase);
	return true;
}

bool ReceiverBase::isUserExist(char* walletId){
	int position=universalHashingString(hashTableSize, walletId);
	ReceiverInfo * temp=this->hashTable[position].findUser(walletId);
	if(temp==NULL)
		return false;
	return true;
}



//_____________________________----------------------------____________________

UsedBitcoinList::~UsedBitcoinList(){
	UsedBitcoinNode * temp;
	while(head){
		temp=head;
		head=head->next;
		delete temp;
	}
	
}


void UsedBitcoinList::insertUsedBitcoin(int bitcoinId){
	UsedBitcoinNode * temp=tail;
	
	if (head==NULL){
		head= new UsedBitcoinNode(bitcoinId);
		
		counter++;
		
		tail=head;
		return ;
	}
	temp->next=new UsedBitcoinNode(bitcoinId);
	tail=temp->next;
	counter++;
}





void TransHashInfo::setTransHashInfo(char * transId){
	this->transId=new char[strlen(transId)+1];
	strcpy(this->transId,transId);	
}


TransHashInfo::~TransHashInfo(){
	
	delete [] transId;
}

void TransHashInfo::insertUsedBitcoinListAndTransString(char * fullTransString, UsedBitcoinList * bitcoinUsedForTrans){ //insert the full transstr so we can print it easy
	this->fullTransString=new char[strlen(fullTransString)+1];
	strcpy(this->fullTransString,fullTransString);
	this->bitcoinUsedForTrans=bitcoinUsedForTrans;
	
}

void TransHashInfo::traceCoin(int bitcoinId){ //searchs the whole base and if the bitcoin is used in a transaction we print the fulltransstr
	
	UsedBitcoinNode * temp=bitcoinUsedForTrans->head;
	while(temp){
		if(temp->bitcoinId==bitcoinId){
			cout<<this->fullTransString<<endl;
		}
		
	temp=temp->next;
	}
	
}

void TransHashInfo::printTrans(char * walletId){
	
	if(!strcmp(walletId,this->transId)){
		cout<<this->fullTransString<<endl;
	}
	
}




TransHashBucket::TransHashBucket(int bucketSize):bucketSize(bucketSize),curPosition(0),next(NULL){
	transIds=new TransHashInfo[bucketSize];
	
}
TransHashBucket::~TransHashBucket(){
	//delete transIds;
}

TransHashBucket * TransHashBucket::insertTransId(char*transId){
	if(curPosition<bucketSize-1){
		transIds[curPosition++].setTransHashInfo(transId);
		
	}
	if(curPosition==bucketSize){
		this->next=new TransHashBucket(bucketSize);
		
	}
	return next;
}

bool TransHashBucket::isTransIdExist(char* transId){
	
	int i;
	
	for(i=0; i<curPosition;i++){
		if(!strcmp(transId,transIds[i].transId)){
			return true;
		}
	}
	return false;
}


void TransHashBucket::traceCoin(int bitcoinId){
	int i;
	for(i=0;i<curPosition;i++)
		transIds[i].traceCoin(bitcoinId);
		
}

void TransHashBucket::printTrans(char * walletId){
	int i;
	for(i=0;i<curPosition;i++)
		transIds[i].printTrans(walletId);
		
}


TransHashHashTableCell::~TransHashHashTableCell(){
	TransHashBucket * temp;
	while(head){
		temp=head;
		head=head->next;
		delete temp;
	}
}

bool TransHashHashTableCell::isEmpty(){
	return this->bucketCounter==0;
}

void TransHashHashTableCell::insertTransId(char*transId,int bucketSize){
	TransHashBucket * temp;
	if (isEmpty()){
		head=new TransHashBucket(bucketSize);
		tail=head;
		bucketCounter++;
		temp=head->insertTransId(transId);
		if(temp){
			tail=temp;
			bucketCounter++;
		}
		return;
	}
	temp=head->insertTransId(transId);
	if(temp){
		tail=temp;
		bucketCounter++;
	}
	return;
	
	
	
}
bool TransHashHashTableCell::isTransIdExist(char * transId){
	if(isEmpty()){
		return false;
	}
	TransHashBucket * temp=head;
	
	while(temp){
		if(temp->isTransIdExist(transId)){
			return true;
		}
		temp=temp->next;
		
	}
	return false;
}

TransHashInfo* TransHashHashTableCell::findTransId(char * transId){
	TransHashBucket * temp=head;
	int i;
	
	while(temp){
		for(i=0;i<temp->curPosition;i++){
			if(!strcmp(transId,temp->transIds[i].transId)){
				
				return &(temp->transIds[i]);
			}
		}
		temp=temp->next;
	}
	
	return NULL;	
}

void TransHashHashTableCell::traceCoin(int bitcoinId){
	if(isEmpty())
		return;
	
	TransHashBucket * temp =head;
	
	while(temp){
		temp->traceCoin(bitcoinId);
		
		temp=temp->next;
		
	}
	
}

void TransHashHashTableCell::printTrans(char * walletId){
	if(isEmpty())
		return;
	
	TransHashBucket * temp =head;
	
	while(temp){
		temp->printTrans(walletId);
		
		temp=temp->next;
		
	}
	
}



TransHashBase::TransHashBase(int bucketSize, int hashTableSize):bucketSize(bucketSize),hashTableSize(hashTableSize){
	hashTable= new TransHashHashTableCell[hashTableSize];
	
}

TransHashBase::~TransHashBase(){
	//delete hashTable;
}


bool TransHashBase::insertTransId(char * transId){
	if(isTransIdExist(transId)){
		return false; //edw false giati edw einai an tha mpei o user h oxi
	}
	int position=universalHashingString( hashTableSize, transId);
	hashTable[position].insertTransId(transId,this->bucketSize);
	return true;
	
	
}

bool TransHashBase::isTransIdExist(char* transId){
	int i;
	for(i=0;i<hashTableSize;i++){	
		if(hashTable[i].isTransIdExist(transId)){
			return true;
		}
	}
	return false;
}

bool TransHashBase::insertUsedBitcoinListAndTransString(char * transId,char * fullTransString, UsedBitcoinList * bitcoinUsedForTrans){
	int position=universalHashingString( hashTableSize, transId);
	TransHashInfo *  temp=hashTable[position].findTransId(transId);
	temp->insertUsedBitcoinListAndTransString(fullTransString,bitcoinUsedForTrans);
	return true;
}

void TransHashBase::traceCoin(int bitcoinId){
	int i;
	for(i=0;i<hashTableSize;i++){
		hashTable[i].traceCoin(bitcoinId);
		
	}
	
	
}

void TransHashBase::printTrans(char * walletId){
	int i;
	for(i=0;i<hashTableSize;i++){
		hashTable[i].printTrans(walletId);
		
	}
}




