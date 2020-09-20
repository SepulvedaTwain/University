#include "Database.h"
using namespace std;

int universalHashingString( int M, char *str)
{
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

UserBitcoinList::~UserBitcoinList(){
	BitcoinNode * temp;
	while(head){
		temp=head;
		head=head->next;
		delete temp;
	}
	
}


int UserBitcoinList::sumOfMoney(){
	BitcoinNode * temp=head;
	int sum;
	
	while(temp){
		cout<<temp->bitcoinId<<"...";
		//sum+=temp->bitcoinBalance;
		temp=temp->next;
	}

	return sum;
}

void UserBitcoinList::updateUserBitcoinBalance(int bitcoinId,char* walletId, BitcoinDataBase * bitcoinBase){
	BitcoinNode* temp=head;
	
	while(temp){
		if(temp->bitcoinId==bitcoinId){
			
			//temp->bitcoinBalance=bitcoinBase->userBitcoinBalance(walletId,bitcoinId);
		}
			
	}
	
}

void UserBitcoinList::insertUserBitcoin(int bitcoinId){
	BitcoinNode * temp=tail;
	if (head==NULL){
		head= new BitcoinNode(bitcoinId);
		counter++;
		tail=head;
		return ;
	}
	temp->next=new BitcoinNode(bitcoinId);
	tail=temp->next;
	counter++;
	
	
}

void WalletInfo::setWalletInfo(char * walletId){
	this->walletId=new char[strlen(walletId)+1];
	strcpy(this->walletId,walletId);
	
}


WalletInfo::~WalletInfo(){
	
	delete [] walletId;
}

void WalletInfo::insertUserBitcoin(int bitcoinId,int bitcoinValue){
	if(this->isBitcoinExist(bitcoinId)) //if bitcoin allready exists no need to put it again
		return;
	BitcoinNode * temp=userBitcoins.tail;
	totalAmount+=bitcoinValue;
	if (userBitcoins.head==NULL){
		userBitcoins.head= new BitcoinNode(bitcoinId);
		userBitcoins.counter++;
		userBitcoins.tail=userBitcoins.head;
		return ;
	}
	temp->next=new BitcoinNode(bitcoinId);
	userBitcoins.tail=temp->next;
	userBitcoins.counter++;
	
}

bool WalletInfo::isBitcoinExist(int bitcoinId){
	if(userBitcoins.head==NULL){
		return false;
	}
	BitcoinNode * temp=userBitcoins.head;
	while(temp){
		if(temp->bitcoinId==bitcoinId){
			return true;
		}
		temp=temp->next;
	}
	return false;
}




MainDataBucket::MainDataBucket(int bucketSize):bucketSize(bucketSize),curPosition(0),next(NULL){
	userWallets=new WalletInfo[bucketSize];
	
}
MainDataBucket::~MainDataBucket(){
	//delete userWallets;
}

MainDataBucket * MainDataBucket::insertUser(char*walletId){
	if(curPosition<bucketSize-1){
		userWallets[curPosition++].setWalletInfo(walletId);
		
	}
	if(curPosition==bucketSize){
		this->next=new MainDataBucket(bucketSize);
		
	}
	return next;
}

bool MainDataBucket::isUserExist(char* walletId){
	
	int i;
	
	for(i=0; i<curPosition;i++){
		if(!strcmp(walletId,userWallets[i].walletId)){
			
			return true;
		}
	}
	
	return false;
}

void MainDataBucket::insertUserBitcoin(char* walletId, int bitcoinId, int bitcoinValue){
	int i;
	
	for (i=0;i<curPosition;i++){
		if(!strcmp(walletId,userWallets[i].walletId)){
			userWallets[i].insertUserBitcoin(bitcoinId, bitcoinValue);
			
			return;
		}
	}
	
}

bool MainDataBucket::isBitcoinExist(int bitcoinId){
	int i;
	
	for(i=0;i<curPosition;i++){
		if(userWallets[i].isBitcoinExist(bitcoinId)){
			return true;
		}
	}
	return false;
}

HashTableCell::~HashTableCell(){
	MainDataBucket * temp;
	while(head){
		temp=head;
		head=head->next;
		delete temp;
	}
}
bool HashTableCell::isEmpty(){
	return bucketCounter==0;
}

void HashTableCell::insertUser(char*walletId,int bucketSize){
	MainDataBucket * temp;
	if (isEmpty()){
		head=new MainDataBucket(bucketSize);
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
bool HashTableCell::isUserExist(char * walletId){
	
	if(isEmpty()){
		return false;
	}

	MainDataBucket * temp=head;
	
	while(temp){
		
		if(temp->isUserExist(walletId)){
			
			return true;
		}
		temp=temp->next;
		
	}
	
	return false;
}


MainDataBucket * HashTableCell::findWalletId(char * walletId){
	MainDataBucket * temp=head;
	
	while(temp!=NULL){
		
		if (temp->isUserExist(walletId)){
			return temp;
		}
		temp=temp->next;
	}
	return NULL;
}

WalletInfo * HashTableCell::findWalletId_vol2(char * walletId){
	MainDataBucket * temp=head;
	int i;
	while(temp){
		for(i=0;i<temp->curPosition;i++){
			if(!strcmp(walletId,temp->userWallets[i].walletId)){
				return &(temp->userWallets[i]);
			}
		}
		temp=temp->next;
	}
	return NULL;	
}

void HashTableCell::insertUserBitcoin(char* walletId,int bitcoinId, int bitcoinValue){
	MainDataBucket * temp=findWalletId(walletId);
	temp->insertUserBitcoin(walletId,bitcoinId,bitcoinValue);
	
	
	
}
bool HashTableCell::isBitcoinExist(int bitcoinId){
	if(isEmpty()){
		return false;
	}
	MainDataBucket *temp=head;
	
	while(temp){
		if(temp->isBitcoinExist(bitcoinId)){
			return true;
		}
		temp=temp->next;
	}
	return false;
}

DataBase::DataBase(int bucketSize, int hashTableSize):bucketSize(bucketSize),hashTableSize(hashTableSize){
	hashTable= new HashTableCell[hashTableSize];
	
}

DataBase::~DataBase(){
	//delete hashTable;
}

bool DataBase::insertUser(char * walletId){
	if(isUserExist(walletId)){
		return false; //false because this function is about whether or not we insert the userId
	}
	int position=universalHashingString( hashTableSize, walletId);
	hashTable[position].insertUser(walletId,this->bucketSize);
	return true;
	
	
}
bool DataBase::isUserExist(char* walletId){
	int i;
	
	for(i=0;i<hashTableSize;i++){	
		if(hashTable[i].isUserExist(walletId)){
			return true;
		}
	}
	return false;
}

bool DataBase::insertUserBitcoin(char* walletId, int bitcoinId,int bitcoinValue){
	
	if(isUserExist(walletId)==false){
		return false;//if user is not in the database we cannot insert the bitcoin
	}
	//if(isBitcoinExist(bitcoinId)){
	//	return false;
	//}
	int position=universalHashingString(hashTableSize,walletId);
	hashTable[position].insertUserBitcoin(walletId,bitcoinId,bitcoinValue);
	return true;
}

bool DataBase::isBitcoinExist(int bitcoinId){
	int i;
	for(i=0;i<hashTableSize;i++){
		if(hashTable[i].isBitcoinExist(bitcoinId)){
			return true;
		}
	}
	return false;
}

int DataBase::userMoneyAmount(char* walletId){
	
	if(isUserExist(walletId)==false){
		return false;//giati an den yparxei o xristis den mporoume na isagoume to bitcoin.
	}
	int position=universalHashingString( hashTableSize, walletId);
	WalletInfo * temp=hashTable[position].findWalletId_vol2(walletId);
	//temp->userBitcoins.sumOfMoney();
	return (temp->totalAmount);
	
}


bool DataBase::updateUserBitcoinBalance(int bitcoinId,char* walletId, BitcoinDataBase * bitcoinBase){
	if(isUserExist(walletId)==false){
		return false;
	}
	int position=universalHashingString(hashTableSize, walletId);
	WalletInfo * temp=hashTable[position].findWalletId_vol2(walletId);
	temp->userBitcoins.updateUserBitcoinBalance(bitcoinId,walletId,bitcoinBase);
	
	return true;
}

bool DataBase::transaction(char * transId, char *senderId,char* receiverId, int amount, BitcoinAddressNodeList * SenderReceiverTransNodeList, UsedBitcoinList * bitcoinUsedForTrans, BitcoinDataBase * bitcoinBase){
	int receiverAmount=amount;
	cout<<senderId<<"  "<<userMoneyAmount(senderId)<<"  "<<receiverId<<"   "<<userMoneyAmount(receiverId)<<endl;
	if((isUserExist(senderId)==false) || (isUserExist(receiverId)==false)) {
		
		return false;
	}
	
	if(!strcmp(senderId,receiverId))
		return false;
	
	if(amount>userMoneyAmount(senderId)){
		return false;
	}
	
	//here we find the sender check to see if he has the money for the transaction
	//then check the value of his bitcoins (if value==0 then we go to the next bitcoin)
	//and then we insert the bitcoins to the receiver(if he does not have them)
	//and update the walletBalance and bitCoin balance of each user and bitcoin
	
	int position=universalHashingString(hashTableSize, senderId);
	WalletInfo * temp=hashTable[position].findWalletId_vol2(senderId);
	
	temp->totalAmount-=amount;
	BitcoinNode * bitTemp=temp->userBitcoins.head;
	int remain=0;
	while(bitTemp){
		remain=bitcoinBase->transaction(senderId,receiverId, amount,bitTemp->bitcoinId,SenderReceiverTransNodeList);
		if (!(remain==amount))
			bitcoinUsedForTrans->insertUsedBitcoin(bitTemp->bitcoinId);
		if(remain<amount){
			
			insertUserBitcoin(receiverId,bitTemp->bitcoinId,0);// na bgalw to value
			
		}
		if(remain==0){
			break;
		}
		amount=remain;
		
		bitTemp=bitTemp->next;
		
	}
	
	position=universalHashingString(hashTableSize, receiverId);
	WalletInfo * rTemp=hashTable[position].findWalletId_vol2(receiverId);
	rTemp->totalAmount+=receiverAmount;
	cout<<senderId<<"  "<<userMoneyAmount(senderId)<<"  "<<receiverId<<"   "<<userMoneyAmount(receiverId)<<endl;
	
	return true;
	
}









