#ifndef BITCOINTREE_H
#define BITCOINTREE_H
#include <iostream>
#include <string.h>
#include <time.h>
int universalHashingInt( int M, int x);


//compare date

class Time{
	public:
		int hours;
		int mins;
		int secs;
		Time(int hours,int mins,int secs=0):hours(hours),mins(mins),secs(secs){}
		Time(){}
		
};

class Date{
	public:
		int year;
		int month;
		int day;
		Time myTime;
		time_t cmpTime;
		Date(int year,int month,int day, int hours,int mins,int secs ):year(year),month(month),day(day),myTime(hours,mins,secs){
			
			struct tm * timeinfo= new struct tm;
			timeinfo->tm_year = year - 1900;
			timeinfo->tm_mon = month - 1;
			timeinfo->tm_mday = day;
			timeinfo->tm_hour = hours;
			timeinfo->tm_min = mins;
			timeinfo->tm_sec = secs;
			  
			
			cmpTime = mktime ( timeinfo );
			//delete timeinfo;
			
		}	
		Date(){
			struct tm * timeinfo= new struct tm;
			time ( &cmpTime );
			timeinfo = localtime ( &cmpTime );
			year=timeinfo->tm_year  + 1900;
			month=timeinfo->tm_mon  + 1;
			day=timeinfo->tm_mday ;
			int hours=timeinfo->tm_hour;
			int mins=timeinfo->tm_min;
			int secs=timeinfo->tm_sec;
			myTime.hours=hours;
			myTime.mins=mins;
			myTime.secs=secs;
			//delete timeinfo;
			
		}
		Date(Date * date){}
		~Date(){}
		void setDateZero(){
			year=0;
			month=0;
			day=0;
			myTime.hours=0;
			myTime.mins=0;
			myTime.secs=0;
		}
};


class BitcoinTreeNode{
	public:
		char * walletId;
		int moneyAmount;
		Date date;
		bool changedOrginalWalletId;
		BitcoinTreeNode * left;
		BitcoinTreeNode * right;
		BitcoinTreeNode(char* walletId,int moneyAmount,Date date);
		BitcoinTreeNode(char* walletId,int moneyAmount);
		~BitcoinTreeNode();
};

class BitcoinAddressNode{
	public:
		BitcoinTreeNode * treePtr;
		
		BitcoinAddressNode * next;
		BitcoinAddressNode(BitcoinTreeNode * treePtr):treePtr(treePtr),next(NULL){}
		~BitcoinAddressNode(){}	
	
};

class BitcoinAddressNodeList{
	public:
		BitcoinAddressNode * head;
		BitcoinAddressNode * tail;
		int counter;
		BitcoinAddressNodeList():head(NULL),tail(NULL),counter(0){}
		~BitcoinAddressNodeList();
		void insertBitcoinNode(BitcoinTreeNode * bitcoinTreeNode);
		int bringMoney();
};

class BitcoinTree{
	public:
		int bitcoinId;
		int transactionCounter;
		BitcoinTreeNode * root;
		BitcoinTree(int bitcoinId,char * walletId,int moneyAmount);
		~BitcoinTree();
		void deleteTree(BitcoinTreeNode* root);
		int transaction(char* senderId, char* receiverId,int amount,  BitcoinAddressNodeList * SenderReceiverTransNodeList);
		int transRec(char* senderId, char* receiverId,int amount, BitcoinTreeNode * root, BitcoinAddressNodeList * SenderReceiverTransNodeList);
		int userBitcoinBalance(char * walletId,BitcoinTreeNode* root);
		//h bitCoinStatus tha einai void?
		void bitCoinStatus(int bitcoinId);
		int bitcoinUnspentMoney(char * walletId,BitcoinTreeNode * root);
};

class BitcoinInfo{
	public:
		int bitcoinId;
		BitcoinTree * bitcoinTree;
		BitcoinInfo(){};
		~BitcoinInfo();
		void setBitcoinInfo(int bitcoinId,char * walletId,int moneyAmount);
};


class BitcoinTreeBucket{
	public:
		BitcoinInfo * bitcoins;
		BitcoinTreeBucket * next;
		int bucketSize;
		int curPosition;
		BitcoinTreeBucket(int bucketSize);
		~BitcoinTreeBucket();
		BitcoinTreeBucket * insertBitcoin(int bitcoinId,char* walletId,int moneyAmount);
		bool isBitcoinExist(int bitcoinId);
		
};


class BitcoinHashTableCell{
	public:
		BitcoinTreeBucket * head;
		BitcoinTreeBucket * tail;
		int bucketCounter;
		BitcoinHashTableCell():head(NULL),tail(NULL),bucketCounter(0){}
		~BitcoinHashTableCell();
		bool isEmpty();
		void insertBitcoin(int bitcoinId,char* walletId,int moneyAmount, int bucketSize);
		bool isBitcoinExist(int bitcoinId);
		int transaction(char *senderId,char* receiverId, int amount, int bitcoinId, BitcoinAddressNodeList * SenderReceiverTransNodeList);
		BitcoinInfo * findBitcoin(int bitcoinId);
};

class BitcoinDataBase{
	public:
		int bucketSize;
		int hashTableSize;
		BitcoinHashTableCell * hashTable;
		BitcoinDataBase(int bucketSize, int hashTableSize);
		~BitcoinDataBase();
		bool insertBitcoin(int bitcoinId,char* walletId,int moneyAmount);
		bool isBitcoinExist(int bitcoinId); 
		int transaction(char *senderId,char* receiverId, int amount, int bitcoinId, BitcoinAddressNodeList * SenderReceiverTransNodeList);
		int userBitcoinBalance(char* walletId,int bitcoinId);
		//h bitcoinstatus void tha einai?
		void bitCoinStatus(int bitcoinId);
};













#endif
