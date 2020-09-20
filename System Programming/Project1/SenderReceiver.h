#ifndef SENDERRECEIVER_H
#define SENDERRECEIVER_H
#include "BitcoinTreeBase.h"
#include "Database.h"
#include <iostream>
#include <string.h>
class TransHashBase;

class TransactionNode{
	public:
		Date * date;
		char * transId;
		BitcoinAddressNodeList * transList;
		TransactionNode * next;
		TransactionNode(char * transId,Date * date,BitcoinAddressNodeList * transList);
		~TransactionNode();
		
		
};

class TransactionList{
	public:
		TransactionNode * head;
		TransactionNode * tail;
		int counter;
		TransactionList():head(NULL),tail(NULL),counter(0){}
		~TransactionList();
		void insertTransNodes(Date * date, char* transId,BitcoinAddressNodeList * bitsList);
		void findEarnings(Date imer,Date imer2,TransHashBase &transBase);
		//void insertTransNode(Date date, char* transId,BitcoinTreeNode * bitNode);
};

class SenderInfo{
	public:
		char * walletId;
		TransactionList  transactionList;
		SenderInfo(){}
		~SenderInfo();
		void setSenderInfo(char * walletId);
		
		
		
};

class SenderBucket{
	public:
		SenderInfo * userTransactions;
		SenderBucket * next;
		int bucketSize;
		int curPosition;
		SenderBucket(int bucketSize);
		~SenderBucket();
		SenderBucket* insertUser(char* walletId);
};

class SenderHashTableCell{
	public:
		SenderBucket * head;
		SenderBucket * tail;
		int bucketCounter;
		SenderHashTableCell():head(NULL),tail(NULL),bucketCounter(0){}
		~SenderHashTableCell();
		bool isEmpty();
		void insertUser(char*walletId,int bucketSize);
		SenderInfo* findUser(char*walletId);
		void insertTransNodes(char* walletId,Date * date, char* transId,BitcoinAddressNodeList * bitsList,int bucketSize);
		
};

class SenderBase{
	public:
		int bucketSize;
		int hashTableSize;
		SenderHashTableCell * hashTable;
		SenderBase(int bucketSize, int hashTableSize);
		~SenderBase();
		bool insertTransNodes(char* walletId,Date * date, char* transId,BitcoinAddressNodeList * bitsList);
		bool findPayments(char * walletId,Date imer,Date imer2,TransHashBase &transBase);
		bool isUserExist(char * walletId);
		
};


//ousiastika edw to BitcoinAddressNodelist tha to pernoume apo to bitcoin tree kai tha mas dinei dio listes mia gia ton sender kai mia gia ton re
//receiver opote apla edw kanw ton kwdika idio giati tha pernw apo to pio panw epidedo to BitcoinAddressNodeList epeidi tha exoun allous pointer
// to ena apo to allo

class ReceiverInfo{
	public:
		char * walletId;
		TransactionList  transactionList;
		ReceiverInfo(){}
		~ReceiverInfo();
		void setReceiverInfo(char * walletId);
		
};

class ReceiverBucket{
	public:
		ReceiverInfo * userTransactions;
		ReceiverBucket * next;
		int bucketSize;
		int curPosition;
		ReceiverBucket(int bucketSize);
		~ReceiverBucket();
		ReceiverBucket* insertUser(char* walletId);
};

class ReceiverHashTableCell{
	public:
		ReceiverBucket * head;
		ReceiverBucket * tail;
		int bucketCounter;
		ReceiverHashTableCell():head(NULL),tail(NULL),bucketCounter(0){}
		~ReceiverHashTableCell();
		bool isEmpty();
		void insertUser(char*walletId,int bucketSize);
		ReceiverInfo* findUser(char*walletId);
		void insertTransNodes(char* walletId,Date * date, char* transId,BitcoinAddressNodeList * bitsList,int bucketSize);
		
};

class ReceiverBase{
	public:
		int bucketSize;
		int hashTableSize;
		ReceiverHashTableCell * hashTable;
		ReceiverBase(int bucketSize, int hashTableSize);
		~ReceiverBase();
		bool insertTransNodes(char* walletId,Date * date, char* transId,BitcoinAddressNodeList * bitsList);
		bool findEarnings(char * walletId,Date imer,Date imer2,TransHashBase &transBase);
		bool isUserExist(char* walletId);
};

//_______________________--------------------------------------_______________________________


class UsedBitcoinNode{
	public:
		int bitcoinId;
		
		UsedBitcoinNode * next;
		UsedBitcoinNode(int bitcoinId):bitcoinId(bitcoinId),next(NULL){}
		~UsedBitcoinNode(){}
		
		
		
	
};

class UsedBitcoinList{
	public:
		UsedBitcoinNode * head;
		UsedBitcoinNode * tail;
		int counter;//autos o counter einai ta lefta poy exei h posa? bitcoin..... prepei na kanw mia sinartisi pou na mou dinei posa lefta exei.
		UsedBitcoinList():head(NULL),tail(NULL),counter(0){}
		~UsedBitcoinList();
		
		void  insertUsedBitcoin(int bitcoinId);
		
		
		
};





class TransHashInfo{
	public:
		char * transId;
		
		char* fullTransString;
		
		UsedBitcoinList * bitcoinUsedForTrans;
		
		TransHashInfo(){};
		~TransHashInfo();
		void setTransHashInfo(char * transId);
		void insertUsedBitcoinListAndTransString(char * fullTransString, UsedBitcoinList * bitcoinUsedForTrans);
		void traceCoin(int bitcoinId);
		void printTrans(char * walletId);
};


class TransHashBucket{
	public:
		TransHashInfo * transIds;
		TransHashBucket * next;
		int bucketSize;
		int curPosition;
		TransHashBucket(int bucketSize);
		~TransHashBucket();
		TransHashBucket * insertTransId(char*transId);
		bool isTransIdExist(char* transId);
		void traceCoin(int bitcoinId);
		void printTrans(char * walletId);

		
};

class TransHashHashTableCell{
	public:
		TransHashBucket * head;
		TransHashBucket * tail;
		int bucketCounter;
		TransHashHashTableCell():head(NULL),tail(NULL),bucketCounter(0){}
		~TransHashHashTableCell();
		bool isEmpty();
		void insertTransId(char* transId,int bucketSize);
		bool isTransIdExist(char * transId);
		TransHashInfo * findTransId(char* transId);
		void traceCoin(int bitcoinId);
		void printTrans(char * walletId);
};

class TransHashBase{
	public:
		int bucketSize;
		int hashTableSize;
		TransHashHashTableCell * hashTable;
		TransHashBase(int bucketSize, int hashTableSize);
		~TransHashBase();
		bool insertTransId(char* transId);
		bool isTransIdExist(char* transId);
		bool insertUsedBitcoinListAndTransString(char * transId,char * fullTransString, UsedBitcoinList * bitcoinUsedForTrans);
		void traceCoin(int bitcoinId);
		void printTrans(char * walletId);
};


#endif 
