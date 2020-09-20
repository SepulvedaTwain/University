#include "BitcoinTreeBase.h"
using namespace std;
Date glob(0,0,0,0,0,0);

int universalHashingInt( int M, int x) //here is the hashfunction for int
{
	// parameters a,b
	int a = 6;
	int b = 8;

	// 1000th prime number
	int p = 7919;

	// universal hashing for integers
	return (((a*x + b) % p ) % M)+1;
}




BitcoinTreeNode::BitcoinTreeNode(char * walletId, int moneyAmount,Date date=glob):moneyAmount(moneyAmount),date(date),left(NULL),right(NULL),changedOrginalWalletId(false){
	
	this->walletId=new char[strlen(walletId)+1];
	strcpy(this->walletId,walletId);
	
	
}

BitcoinTreeNode::~BitcoinTreeNode(){
	delete [] walletId;
	
}

BitcoinAddressNodeList::~BitcoinAddressNodeList(){
	BitcoinAddressNode * temp;
	while(head){
		temp=head;
		head=head->next;
		delete temp;
	}
	
}

void BitcoinAddressNodeList::insertBitcoinNode(BitcoinTreeNode * bitcoinTreeNode){
	
	BitcoinAddressNode * temp=tail;
	
	if (head==NULL){
		head= new BitcoinAddressNode(bitcoinTreeNode);
		
		counter++;
		
		tail=head;
		return ;
	}
	temp->next=new BitcoinAddressNode(bitcoinTreeNode);
	tail=temp->next;
	counter++;
}

int BitcoinAddressNodeList::bringMoney(){
	int sum=0;
	BitcoinAddressNode * temp=head;
	while(temp){
		sum+=temp->treePtr->moneyAmount;
		temp=temp->next;
	}
	return sum;
}

BitcoinTree::BitcoinTree(int bitcoinId,char* walletId,int moneyAmount):bitcoinId(bitcoinId),transactionCounter(0){

	Date lol(0,0,0,0,0,0);
	root=new BitcoinTreeNode(walletId,moneyAmount,lol);
	
}

void BitcoinTree::deleteTree(BitcoinTreeNode * root){
	if(root==NULL){
		return;
	}
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}

BitcoinTree::~BitcoinTree(){
	deleteTree(root);
	
}
int BitcoinTree::transRec(char* senderId, char* receiverId,int amount,BitcoinTreeNode * root,  BitcoinAddressNodeList * SenderReceiverTransNodeList){//twra kanw to transaction gia ta split ktl
	
	int remain;
	
	
	if (root==NULL){ 
		return amount;
	}
	
	
	
	
	if(root->left==NULL && root->right==NULL){ //if leaf
		if(!strcmp(senderId,root->walletId)){   //if is the leaf we want
			if(root->moneyAmount>amount){ //if leaf has more money
				
				root->left=new BitcoinTreeNode(receiverId,amount,glob); //Create two nodes right sender left receiver
				root->right=new BitcoinTreeNode(senderId,root->moneyAmount-amount,glob);
				
				SenderReceiverTransNodeList->insertBitcoinNode(root->left);
				
				return 0;
			}
			else{  //if leaf has less money
				
				delete[] root->walletId; //We insert the receiverId to this node without creating a new node 
				root->walletId=new char[strlen(receiverId)+1];
				strcpy(root->walletId,receiverId);
				root->changedOrginalWalletId=true;
				SenderReceiverTransNodeList->insertBitcoinNode(root);
				return amount-root->moneyAmount;
			}
		}
		else{
			return amount;
		}
		
	}
	
	remain=transRec(senderId,receiverId,amount,root->left,SenderReceiverTransNodeList); //go left
	if(remain==0){
		return remain;
	}	
	remain=transRec(senderId,receiverId,remain,root->right,SenderReceiverTransNodeList); //go right
	return remain;
	
}

int BitcoinTree::transaction(char*senderId,char*receiverId,int amount,  BitcoinAddressNodeList * SenderReceiverTransNodeList){//h elenxoi tou transaction tha ginoun apo prin !!!!!!!! gia na ektelesti auth h senatrisi tha pei oti mporei na ginei
	
	//for checking if the amount is not 0 and counter

	if(userBitcoinBalance(senderId,this->root)<=0)
		return amount;
	transactionCounter++;
	return transRec(senderId,receiverId,amount,root,SenderReceiverTransNodeList);
	
}

int BitcoinTree::userBitcoinBalance(char * walletId,BitcoinTreeNode * root){
	int sum=0;
	if(root->left==NULL && root->right==NULL){
		if(!strcmp(walletId,root->walletId)){
			return sum+=root->moneyAmount;
		}
	}	
	if(root->left!=NULL){
		sum+=userBitcoinBalance(walletId,root->left);
	}
	if(root->right!=NULL){
		sum+=userBitcoinBalance(walletId,root->right);
	}
	return sum;
	
}

void BitcoinTree::bitCoinStatus(int bitcoinId){
	cout<<root->moneyAmount<<" "<<transactionCounter<<" "<<bitcoinUnspentMoney(this->root->walletId,this->root)<<endl;;
}

int BitcoinTree::bitcoinUnspentMoney(char * walletId,BitcoinTreeNode * root){ //take only right nodes to find unspent money
	int sum=0;
	if(root->left==NULL && root->right==NULL){
		if(!strcmp(walletId,root->walletId) && root->changedOrginalWalletId==false ){
			return sum+=root->moneyAmount;
		}
	}
	if(root->right!=NULL){
		sum+=userBitcoinBalance(walletId,root->right);
	}
    return sum;

}

void BitcoinInfo::setBitcoinInfo(int bitcoinId,char * walletId,int moneyAmount){
	this->bitcoinId=bitcoinId;
	this->bitcoinTree=new BitcoinTree(bitcoinId,walletId,moneyAmount);
	
}

BitcoinInfo::~BitcoinInfo(){
	//delete bitcoinTree;
}


BitcoinTreeBucket::BitcoinTreeBucket(int bucketSize):bucketSize(bucketSize),curPosition(0),next(NULL){
	bitcoins=new BitcoinInfo[bucketSize];

}

BitcoinTreeBucket::~BitcoinTreeBucket(){
	//delete bitcoins;
}

BitcoinTreeBucket * BitcoinTreeBucket::insertBitcoin(int bitcoinId,char* walletId,int moneyAmount){ //insert bitcoin if bucket full create new one
	
	if(curPosition<bucketSize-1){
		bitcoins[curPosition++].setBitcoinInfo(bitcoinId,walletId,moneyAmount);
	}
	if(curPosition==bucketSize){
		this->next=new BitcoinTreeBucket(bucketSize);
	}
	return next;
}

bool BitcoinTreeBucket::isBitcoinExist(int bitcoinId){ //if bitcoin exists
	int i;
	for(i=0;i<curPosition;i++){
		if(bitcoinId==bitcoins[i].bitcoinId){
			return true;
		}
	}
	return false;
}

BitcoinHashTableCell::~BitcoinHashTableCell(){
		BitcoinTreeBucket * temp;
	while(head){
		temp=head;
		head=head->next;
		delete temp;
	}
}


bool BitcoinHashTableCell::isEmpty(){
	return this->bucketCounter == 0;
}

void BitcoinHashTableCell::insertBitcoin(int bitcoinId,char * walletId, int moneyAmount, int bucketSize){ //ifempty create new bucket else go to tail
	BitcoinTreeBucket * temp;
	if (isEmpty()){
		head=new BitcoinTreeBucket(bucketSize);
		tail=head;
		bucketCounter++;
		temp=head->insertBitcoin(bitcoinId,walletId,moneyAmount);
		if(temp){
			tail=temp;
			bucketCounter++;
		}
		return;
	}
	temp=tail->insertBitcoin(bitcoinId,walletId,moneyAmount);
	if(temp){
		tail=temp;
		bucketCounter++;
	}
	return;
}

bool BitcoinHashTableCell::isBitcoinExist(int bitcoinId){ //if bidcoin exists
	if(isEmpty()){
		return false;
	}
	BitcoinTreeBucket * temp=head;
	
	while(temp){
		if(temp->isBitcoinExist(bitcoinId)){
			return true;
		}
		temp=temp->next;
		
	}
	return false;
}

int BitcoinHashTableCell::transaction(char *senderId,char* receiverId, int amount, int bitcoinId,  BitcoinAddressNodeList * SenderReceiverTransNodeList){ //find bitcoin then go to tree
	BitcoinInfo * bInfo=findBitcoin(bitcoinId);
	
	return bInfo->bitcoinTree->transaction(senderId,receiverId,amount,SenderReceiverTransNodeList);
	
}

BitcoinInfo* BitcoinHashTableCell::findBitcoin(int bitcoinId){
	BitcoinTreeBucket * temp=head;
	int i;
	
	while(temp){
		for(i=0;i<temp->curPosition;i++){
			if(bitcoinId==temp->bitcoins[i].bitcoinId){
				
				return &(temp->bitcoins[i]);
			}
		}
		temp=temp->next;
	}
	
	return NULL;	
}


BitcoinDataBase::BitcoinDataBase(int bucketSize, int hashTableSize):bucketSize(bucketSize),hashTableSize(hashTableSize){
	hashTable= new BitcoinHashTableCell[hashTableSize];
	
}

BitcoinDataBase::~BitcoinDataBase(){
	//delete hashTable;
}

bool BitcoinDataBase::insertBitcoin(int bitcoinId,char* walletId,int moneyAmount){
	if(isBitcoinExist(bitcoinId)){
		
		return false; //edw false giati edw einai an tha mpei o user h oxi
	}
	int position=universalHashingInt( hashTableSize, bitcoinId);
	hashTable[position].insertBitcoin(bitcoinId,walletId,moneyAmount,this->bucketSize);
	return true;
	
	
}

bool BitcoinDataBase::isBitcoinExist(int bitcoinId){
	int i;
	for(i=0;i<hashTableSize;i++){
		if(hashTable[i].isBitcoinExist(bitcoinId)){
			return true;
		}
	}
	return false;
}

int BitcoinDataBase::transaction(char *senderId,char* receiverId, int amount, int bitcoinId,  BitcoinAddressNodeList * SenderReceiverTransNodeList){
	int position=universalHashingInt( hashTableSize, bitcoinId);
	
	return hashTable[position].transaction(senderId, receiverId,  amount, bitcoinId,SenderReceiverTransNodeList);
	
}

int BitcoinDataBase::userBitcoinBalance(char* walletId,int bitcoinId){
	int position=universalHashingInt(hashTableSize,bitcoinId);
	BitcoinInfo * temp=hashTable[position].findBitcoin(bitcoinId);
	return temp->bitcoinTree->userBitcoinBalance(walletId,temp->bitcoinTree->root);
	
}

void BitcoinDataBase::bitCoinStatus(int bitcoinId){ 
	int position=universalHashingInt(hashTableSize,bitcoinId);
	BitcoinInfo * temp=hashTable[position].findBitcoin(bitcoinId);
	temp->bitcoinTree->bitCoinStatus(bitcoinId);
}








