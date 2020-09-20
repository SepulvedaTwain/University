#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "Database.h"
#include "BitcoinTreeBase.h"
#include "SenderReceiver.h"




class UserArguments{
	public:
		char bitCoinBalancesFile[100];
		char transactionsFile[100];
		int bitCoinValue;
		int senderHashtableNumOfEntries;
		int receiverHashtableNumOfEntries;
		int bucketSize;
};

bool argvCheck(int argc, char ** argv,UserArguments &userArguments);

bool isNumber(char * str);

bool readTxt(char * fileName,DataBase &dataBase,BitcoinDataBase &bitBase,UserArguments &userArguments);

bool readTransTxt(char *fileName,DataBase &dataBase,BitcoinDataBase &bitBase,SenderBase &senderBase,ReceiverBase &receiverBase,TransHashBase &transBase,UserArguments &userArguments);

bool readInput(char * command,int &number);

bool requestTransaction(char * command, char*transId,DataBase &dataBase,BitcoinDataBase &bitBase,SenderBase &senderBase,
ReceiverBase &receiverBase,TransHashBase &transBase);

bool requestTransactions(char * command, char*transId,DataBase &dataBase,BitcoinDataBase &bitBase,SenderBase &senderBase,
ReceiverBase &receiverBase,TransHashBase &transBase);

bool findEarnings(char * command,DataBase &dataBase,BitcoinDataBase &bitBase,SenderBase &senderBase,
ReceiverBase &receiverBase,TransHashBase &transBase);

bool findPayments(char * command,DataBase &dataBase,BitcoinDataBase &bitBase,SenderBase &senderBase,
ReceiverBase &receiverBase,TransHashBase &transBase);

bool walletStatus(char * command,DataBase &dataBase,BitcoinDataBase &bitBase,SenderBase &senderBase,
ReceiverBase &receiverBase,TransHashBase &transBase);

bool bitCoinStatus(char * command,DataBase &dataBase,BitcoinDataBase &bitBase,SenderBase &senderBase,
ReceiverBase &receiverBase,TransHashBase &transBase);

bool traceCoin(char * command,DataBase &dataBase,BitcoinDataBase &bitBase,SenderBase &senderBase,
ReceiverBase &receiverBase,TransHashBase &transBase);
#endif
