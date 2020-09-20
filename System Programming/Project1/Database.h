#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <string.h>
#include "BitcoinTreeBase.h"
#include "SenderReceiver.h"
using namespace std;

class UsedBitcoinList;

int universalHashingString( int M, char *str);

class BitcoinNode{
	public:
		int bitcoinId;
		
		BitcoinNode * next;
		BitcoinNode(int bitcoinId):bitcoinId(bitcoinId),next(NULL){}
		~BitcoinNode(){}
		
		//prepei na kanw mia sinartisi pou tha mou kanei update to bitcoin balance swsta?
		
	
};

class UserBitcoinList{
	public:
		BitcoinNode * head;
		BitcoinNode * tail;
		int counter;//autos o counter einai ta lefta poy exei h posa? bitcoin..... prepei na kanw mia sinartisi pou na mou dinei posa lefta exei.
		int sumOfMoney();
		UserBitcoinList():head(NULL),tail(NULL),counter(0){}
		~UserBitcoinList();
		
		void  insertUserBitcoin(int bitcoinId);
		
		void updateUserBitcoinBalance(int bitcoinId,char* walletId, BitcoinDataBase * bitcoinBase);
		
};

class WalletInfo{
	public:
		char * walletId;
		int totalAmount;
		UserBitcoinList userBitcoins;
		WalletInfo():totalAmount(0){}
		~WalletInfo();
		void setWalletInfo(char * walletId);
		void insertUserBitcoin(int bitcoinId,int bitcoinValue);
		bool isBitcoinExist(int bitcoinId);
		
};

class MainDataBucket{
	public:
		WalletInfo * userWallets;
		MainDataBucket * next;
		int bucketSize;
		int curPosition;
		MainDataBucket(int bucketSize);
		~MainDataBucket();
		MainDataBucket * insertUser(char* walletId);
		bool isUserExist(char* walletId);
		void insertUserBitcoin(char* walletId, int bitcoinId, int bitcoinValue);
		bool isBitcoinExist(int bitcoinId);
};

class HashTableCell{
	public:
		MainDataBucket * head;
		MainDataBucket * tail;
		int bucketCounter;
		HashTableCell():head(NULL),tail(NULL),bucketCounter(0){}
		~HashTableCell();
		bool isEmpty();
		void insertUser(char* walletId,int bucketSize);
		bool isUserExist(char * walletId);
		MainDataBucket * findWalletId(char* walletId);
		WalletInfo * findWalletId_vol2(char* walletId);
		void insertUserBitcoin(char* walletId,int bitcoinId,int bitcoinValue);
		bool isBitcoinExist(int bitcoinId);
};

class DataBase{
	public:
		int bucketSize;
		int hashTableSize;
		HashTableCell * hashTable;
		DataBase(int bucketSize, int hashTableSize);
		~DataBase();
		bool insertUser(char * walletId);
		bool isUserExist(char* walletId);// twra prepei na baloume to bitcoin 
		bool insertUserBitcoin(char * walletId,int bitcoinId,int bitcoinValue);
		bool isBitcoinExist(int bitcoinId);
		int userMoneyAmount(char* walletId);
		bool updateUserBitcoinBalance(int bitcoinId,char* walletId,BitcoinDataBase * bitcoinBase);
		bool transaction(char * transId, char *senderId,char* receiverId, int amount, BitcoinAddressNodeList * SenderReceiverTransNodeList, UsedBitcoinList * bitcoinUsedForTrans,BitcoinDataBase * bitcoinBase);
};




















#endif
