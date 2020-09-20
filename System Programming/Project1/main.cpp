#include "main.h"
#include <cstdlib>
using namespace std;

Date tempDate;
char tempId[400];






bool argvCheck(int argc, char ** argv,UserArguments &userArguments){ //a function to check if the parameters are correct
	
	int i;
	int counter=0;
	if(argc!=13)
		return false;
	
	for(i=1;i<argc;i+=2){
		if(!strcmp(argv[i],"-a")){
			strcpy(userArguments.bitCoinBalancesFile,argv[i+1]);
			counter++;
		}
		else if(!strcmp(argv[i],"-t")){
			strcpy(userArguments.transactionsFile,argv[i+1]);
			counter++;
		}
		else if(!strcmp(argv[i],"-v")){
			if(!(isNumber(argv[i+1])))
				return false; // na valw cout
			
			userArguments.bitCoinValue=atoi(argv[i+1]);
			
			counter++;
		}
		else if(!strcmp(argv[i],"-h1")){
			if(!(isNumber(argv[i+1])))
				return false; // na valw cout
			
			userArguments.senderHashtableNumOfEntries=atoi(argv[i+1]);
			
			counter++;
		}
		else if(!strcmp(argv[i],"-h2")){
			if(!(isNumber(argv[i+1])))
				return false; // na valw cout
			
			userArguments.receiverHashtableNumOfEntries=atoi(argv[i+1]);
			
			counter++;
		}
		else if(!strcmp(argv[i],"-b")){
			if(!(isNumber(argv[i+1])))
				return false; // na valw cout
			
			userArguments.bucketSize=atoi(argv[i+1]);
			
			counter++;
		}

	}
	
	if(counter!=6)
		return false;
	
	
	return true;
}

bool isNumber(char * str){
	
	int len=strlen(str);
	int i;
	for (i=0;i<len;i++)
		if(!isdigit(str[i]))
			return false;
	
	
	return true;
}

bool readTxt(char * fileName,DataBase &dataBase,BitcoinDataBase &bitBase,UserArguments &userArguments){ //a fucntion to read the bitCoinBalances.txt
	ifstream input(fileName);
	if(!input) {
		cout << "File Not Found"<<endl;
		return false;
	}

	char line[500];
	int counter=0;
	char * p;
	char walletId[200];
	int bitcoinId;
	while(input.peek()!=EOF) {
    	input.getline(line, 500); 
    	p=strtok(line," \n");
    	strcpy(walletId,p);
    	if(!dataBase.insertUser(walletId))
    		return false;
    		
    	//extract the info from line then call the insertfunctions to put users and bitcoins in the database
    	
    	p=strtok(NULL," \n");
		while(p){
			
			bitcoinId=atoi(p);
			if(!dataBase.insertUserBitcoin(walletId,bitcoinId,userArguments.bitCoinValue)){
				return false;
			}
			if(!bitBase.insertBitcoin(bitcoinId,walletId,userArguments.bitCoinValue)){
				return false;
			}
			
			p=strtok(NULL," \n");
		}
		
		cout<<walletId<<" has "<<dataBase.userMoneyAmount(walletId)<<" US dollars in bitCoins"<<endl;
		
	}
	
	input.close();

	return true;
	
}

bool readTransTxt(char *fileName,DataBase &dataBase,BitcoinDataBase &bitBase,SenderBase &senderBase,
ReceiverBase &receiverBase,TransHashBase &transBase,UserArguments &userArguments){//a fucntion to read the transactionsfile.txt
	ifstream input(fileName);
	if(!input) {
		cout << "File Not Found"<<endl;
		return false;
	}

	int counter=0;
	
	char line[500];
	char * p;
	char transId[200];
	char fullTranstr[200];
	char senderId[200];
	char receiverId[200];
	int amount;
	int day,year,mounth,hour,min;
	
	// we extract the info and call the functions for trasnaction and insert info to sender and receiver base and transaction base
	
	while(input.peek()!=EOF){
		input.getline(line, 500);
		strcpy(fullTranstr,line);
		p=strtok(line," ");
		strcpy(transId,p);
		p=strtok(NULL," ");
		strcpy(senderId,p);
		p=strtok(NULL," ");
		strcpy(receiverId,p);
		p=strtok(NULL," ");
		amount=atoi(p);
		p=strtok(NULL,"-");
		day=atoi(p);
		p=strtok(NULL,"-");
		mounth=atoi(p);
		p=strtok(NULL," ");
		year=atoi(p);
		p=strtok(NULL,":");
		hour=atoi(p);
		p=strtok(NULL," \n");
		min=atoi(p);
		
		Date imer(year,mounth,day,hour,min,0);
		
		if(!transBase.insertTransId(transId))
			return false;
		
		BitcoinAddressNodeList * bitcoinAddressNodeList = new BitcoinAddressNodeList();
		UsedBitcoinList * bitcoinUsedForTrans=new UsedBitcoinList();
		cout<<fullTranstr<<endl;	
		if(!dataBase.transaction(transId,senderId,receiverId,amount,bitcoinAddressNodeList,bitcoinUsedForTrans,&bitBase)){
			
			return false;
		}
		
		if(!senderBase.insertTransNodes(senderId,&imer,transId,bitcoinAddressNodeList))
			return false;
		
		if(!receiverBase.insertTransNodes(receiverId,&imer,transId,bitcoinAddressNodeList))
			return false;
		
		if(!transBase.insertUsedBitcoinListAndTransString(transId,fullTranstr,bitcoinUsedForTrans))
			return false;
		
		
		tempDate=imer;
		strcpy(tempId,transId);
	}
	
	input.close();

	return true;
	
}

bool readInput(char * command,int &number){ //function to read the command
	char * p;
	char temp[200];
	strcpy(temp,command);
	p=(strtok(temp," \n"));
	if(!strcmp(p,"requestTransaction")){
		number=1;
		return true;
	}
	else if(!strcmp(p,"requestTransactions")){
		number=2;
		return true;
	}
	else if(!strcmp(p,"findEarnings")){
		number=3;
		return true;
	}
	else if(!strcmp(p,"findPayments")){
		number=4;
		return true;
	}
	else if(!strcmp(p,"walletStatus")){
		number=5;
		return true;
	}
	else if(!strcmp(p,"bitCoinStatus")){
		number=6;
		return true;
	}
	else if(!strcmp(p,"traceCoin")){
		number=7;
		return true;
	}
	else if(!strcmp(p,"exit")){
		number=8;
		return true;
	}
	else
		return false;
}

bool requestTransaction(char * command,char * transId,DataBase &dataBase,BitcoinDataBase &bitBase,SenderBase &senderBase,
ReceiverBase &receiverBase,TransHashBase &transBase){ //take user input and make the transaction with or with not date
	
	char * p;
	char temp[200];
	char fullTranstr[200];
	char senderId[200];
	char receiverId[200];
	int amount;
	int day,year,mounth,hour,min;
	
	strcpy(fullTranstr,transId);
	strcat(fullTranstr," ");
	
	
	p = strchr(command, ' ');
	strcat(fullTranstr,p);
	strcat(fullTranstr," ");
	strcpy(temp,p);
	p=strtok(temp," ");
	strcpy(senderId,p);
	p=strtok(NULL," ");
	strcpy(receiverId,p);
	p=strtok(NULL," ");
	amount=atoi(p);
	
	p=strtok(NULL,"-");
	day=atoi(p);
	p=strtok(NULL,"-");
	mounth=atoi(p);
	p=strtok(NULL," ");
	year=atoi(p);
	p=strtok(NULL,":");
	hour=atoi(p);
	p=strtok(NULL," \n");
	min=atoi(p);
			
	
	
	
	Date imer2(year,mounth,day,hour,min,0);
	
	BitcoinAddressNodeList * bitcoinAddressNodeList = new BitcoinAddressNodeList();
	UsedBitcoinList * bitcoinUsedForTrans=new UsedBitcoinList();
	
	
	if(!transBase.insertTransId(transId))
		return false;
	
	if(imer2.cmpTime>0){
		if(imer2.cmpTime<=tempDate.cmpTime){
			cout<<"Transaction not done due to date"<<endl;
			return false;
		}
		tempDate=imer2;
		cout<<fullTranstr<<endl;
		if(!dataBase.transaction(transId,senderId,receiverId,amount,bitcoinAddressNodeList,bitcoinUsedForTrans,&bitBase)){
		
		return false;
		}
		
		if(!senderBase.insertTransNodes(senderId,&imer2,transId,bitcoinAddressNodeList))
			return false;
		
		if(!receiverBase.insertTransNodes(receiverId,&imer2,transId,bitcoinAddressNodeList))
			return false;
		
		if(!transBase.insertUsedBitcoinListAndTransString(transId,fullTranstr,bitcoinUsedForTrans))
			return false;
		
		return true;
		
	}
	
	Date * imer=new Date();
	char str[50];
	sprintf(str, "%d", imer->day);
	strcat(fullTranstr,str);
	strcat(fullTranstr,"-");
	sprintf(str, "%d", imer->month);
	strcat(fullTranstr,str);
	strcat(fullTranstr,"-");
	sprintf(str, "%d", imer->year);
	strcat(fullTranstr,str);
	strcat(fullTranstr," ");
	sprintf(str, "%d", imer->myTime.hours);
	strcat(fullTranstr,str);
	strcat(fullTranstr,":");
	sprintf(str, "%d", imer->myTime.mins);
	strcat(fullTranstr,str);
	
	if(imer->cmpTime<=tempDate.cmpTime){
		cout<<"Transaction not done due to date"<<endl;
		return false;
	}
	
	tempDate=imer;
	cout<<fullTranstr<<endl;
	if(!dataBase.transaction(transId,senderId,receiverId,amount,bitcoinAddressNodeList,bitcoinUsedForTrans,&bitBase)){
	
		return false;
	}
	
	if(!senderBase.insertTransNodes(senderId,imer,transId,bitcoinAddressNodeList))
		return false;
	
	if(!receiverBase.insertTransNodes(receiverId,imer,transId,bitcoinAddressNodeList))
		return false;
	
	if(!transBase.insertUsedBitcoinListAndTransString(transId,fullTranstr,bitcoinUsedForTrans))
		return false;
	delete imer;
	return true;
}

bool requestTransactions(char * command, char*transId,DataBase &dataBase,BitcoinDataBase &bitBase,SenderBase &senderBase,
ReceiverBase &receiverBase,TransHashBase &transBase){ //not done :/
	
	char * p;
	char temp[200];
	char fullTranstr[200];
	char fileName[200];
	char senderId[200];
	char receiverId[200];
	int amount;
	int day,year,mounth,hour,min;
	
	
	
	p = strchr(command, ' ');
	strcpy(fullTranstr,p);
	strcpy(temp,p);
	while(temp){
		p=strtok(temp," ");
		strcpy(senderId,p);
		p=strtok(NULL," ");
		strcpy(receiverId,p);
		p=strtok(NULL," ;");
		amount=atoi(p);
		
		p=strtok(NULL,"-");
		day=atoi(p);
		p=strtok(NULL,"-");
		mounth=atoi(p);
		p=strtok(NULL," ");
		year=atoi(p);
		p=strtok(NULL,":");
		hour=atoi(p);
		p=strtok(NULL,";");
		min=atoi(p);
		
		Date imer2(year,mounth,day,hour,min,0);
		
		BitcoinAddressNodeList * bitcoinAddressNodeList = new BitcoinAddressNodeList();
		UsedBitcoinList * bitcoinUsedForTrans=new UsedBitcoinList();
		
	
		if(!transBase.insertTransId(transId))
			return false;
		
		if(imer2.cmpTime>0){
			if(imer2.cmpTime<=tempDate.cmpTime){
				cout<<"Transaction not done due to date"<<endl;
				return false;
			}
			tempDate=imer2;
			cout<<fullTranstr<<endl;
			if(!dataBase.transaction(transId,senderId,receiverId,amount,bitcoinAddressNodeList,bitcoinUsedForTrans,&bitBase)){
			
			return false;
			}
			
			if(!senderBase.insertTransNodes(senderId,&imer2,transId,bitcoinAddressNodeList))
				return false;
			
			if(!receiverBase.insertTransNodes(receiverId,&imer2,transId,bitcoinAddressNodeList))
				return false;
			
			if(!transBase.insertUsedBitcoinListAndTransString(transId,fullTranstr,bitcoinUsedForTrans))
				return false;
			
			return true;
			
		}
		Date imer;
		if(imer.cmpTime<=tempDate.cmpTime){
			cout<<"Transaction not done due to date"<<endl;
			return false;
		}
		
		tempDate=imer;
		cout<<fullTranstr<<" "<<imer.day<<" "<<imer.month<<" "<<imer.year<<" "<<imer.myTime.hours<<":"<<imer.myTime.mins<<endl;
		if(!dataBase.transaction(transId,senderId,receiverId,amount,bitcoinAddressNodeList,bitcoinUsedForTrans,&bitBase)){
		
			return false;
		}
		
		if(!senderBase.insertTransNodes(senderId,&imer,transId,bitcoinAddressNodeList))
			return false;
		
		if(!receiverBase.insertTransNodes(receiverId,&imer,transId,bitcoinAddressNodeList))
			return false;
		
		if(!transBase.insertUsedBitcoinListAndTransString(transId,fullTranstr,bitcoinUsedForTrans))
			return false;
		
		return true;
		
		}
	
	return true;
	
	
}



bool findEarnings(char * command,DataBase &dataBase,BitcoinDataBase &bitBase,SenderBase &senderBase,
ReceiverBase &receiverBase,TransHashBase &transBase){ //find user earnings throuth receiverbase and print them
	char * p;
	char temp[200];
	char walletId[200];
	p = strchr(command, ' ');
	strcpy(temp,p);
	Date oti1(0000,00,00,00,00,0);
	
	int day,year,mounth,hour,min;
	
	p=strtok(temp," ");
	strcpy(walletId,p);
	p=strtok(NULL,"-\n");

	day=atoi(p);
	p=strtok(NULL,"-");
	mounth=atoi(p);
	p=strtok(NULL," ");
	year=atoi(p);
	p=strtok(NULL,":");
	hour=atoi(p);
	p=strtok(NULL," ");
	min=atoi(p);
	
	Date imer(year,mounth,day,hour,min,0);
	
	
	p=strtok(NULL,"-");
	day=atoi(p);
	p=strtok(NULL,"-");
	mounth=atoi(p);
	p=strtok(NULL," ");
	year=atoi(p);
	p=strtok(NULL,":");
	hour=atoi(p);
	p=strtok(NULL," ");
	min=atoi(p);
	
	Date imer2(year,mounth,day,hour,min,0);
	if(imer.cmpTime<0){
		receiverBase.findEarnings(walletId,oti1,oti1,transBase);
		return true;
	}
	
	
	receiverBase.findEarnings(walletId,imer,imer2,transBase);
	return true;
	}
	
bool findPayments(char * command,DataBase &dataBase,BitcoinDataBase &bitBase,SenderBase &senderBase,
ReceiverBase &receiverBase,TransHashBase &transBase){//find user payments throuth receiverbase and print them
	char * p;
	char temp[200];
	char walletId[200];
	p = strchr(command, ' ');
	strcpy(temp,p);
	Date oti1(0000,00,00,00,00,0);
	
	int day,year,mounth,hour,min;
	
	p=strtok(temp," ");
	strcpy(walletId,p);
	p=strtok(NULL,"-");

	day=atoi(p);
	p=strtok(NULL,"-");
	mounth=atoi(p);
	p=strtok(NULL," ");
	year=atoi(p);
	p=strtok(NULL,":");
	hour=atoi(p);
	p=strtok(NULL," ");
	min=atoi(p);
	
	Date imer(year,mounth,day,hour,min,0);
	
	
	p=strtok(NULL,"-");
	day=atoi(p);
	p=strtok(NULL,"-");
	mounth=atoi(p);
	p=strtok(NULL," ");
	year=atoi(p);
	p=strtok(NULL,":");
	hour=atoi(p);
	p=strtok(NULL," ");
	min=atoi(p);
	
	Date imer2(year,mounth,day,hour,min,0);
	if(imer.cmpTime<0){
		senderBase.findPayments(walletId,oti1,oti1,transBase);
		return true;
	}
	
	cout<<imer.day<<" "<<imer2.day<<endl;
	senderBase.findPayments(walletId,imer,imer2,transBase);
	return true;
	}
	
		
bool walletStatus(char * command,DataBase &dataBase,BitcoinDataBase &bitBase,SenderBase &senderBase,
ReceiverBase &receiverBase,TransHashBase &transBase){ //print current money amount of user
	char * p;
	char temp[200];
	char walletId[200];
	p = strchr(command, ' ');
	strcpy(temp,p);
	p=strtok(temp," \n");
	strcpy(walletId,p);
	
	cout<<"Current amount is:  "<<dataBase.userMoneyAmount(walletId)<<endl;
	return true;
}

bool bitCoinStatus(char * command,DataBase &dataBase,BitcoinDataBase &bitBase,SenderBase &senderBase,
ReceiverBase &receiverBase,TransHashBase &transBase){ //print bitcoin status
	char * p;
	char temp[200];
	int bitcoinId;
	p = strchr(command, ' ');
	strcpy(temp,p);
	p=strtok(temp," \n");
	bitcoinId=atoi(p);
	
	bitBase.bitCoinStatus(bitcoinId);
	
	return true;
	
	
}

bool traceCoin(char * command,DataBase &dataBase,BitcoinDataBase &bitBase,SenderBase &senderBase,
ReceiverBase &receiverBase,TransHashBase &transBase){ //print transactions which this bitcoin was in
	char * p;
	char temp[200];
	int bitcoinId;
	p = strchr(command, ' ');
	strcpy(temp,p);
	p=strtok(temp," \n");
	bitcoinId=atoi(p);
	
	transBase.traceCoin(bitcoinId);
	
	return true;
}


int main(int argc,char ** argv){
	
	UserArguments userArguments;
	if (!argvCheck(argc,argv,userArguments)){
		cout<<"Wrong Arguments"<<endl;
		return 1;
	}
	//initialize bases with given values
	
	DataBase baseData(userArguments.bucketSize/sizeof(WalletInfo),userArguments.receiverHashtableNumOfEntries+userArguments.senderHashtableNumOfEntries);
	BitcoinDataBase bitBase(userArguments.bucketSize/sizeof(BitcoinInfo),userArguments.receiverHashtableNumOfEntries+userArguments.senderHashtableNumOfEntries);
	SenderBase senderBase(userArguments.bucketSize/sizeof(SenderInfo),userArguments.senderHashtableNumOfEntries);
	ReceiverBase receiverBase(userArguments.bucketSize/sizeof(ReceiverInfo),userArguments.receiverHashtableNumOfEntries);
	TransHashBase transBase(userArguments.bucketSize/sizeof(TransHashInfo),userArguments.receiverHashtableNumOfEntries+userArguments.senderHashtableNumOfEntries);
	//read files
	cout<<"Reading bitCoinBalancesFile..."<<endl;
	if(!readTxt(userArguments.bitCoinBalancesFile,baseData,bitBase,userArguments)){
		cout<<"error in balancefile"<<endl;
		return 1;
	}
	cout<<"__________________________________________"<<endl<<"Reading trasanactionsFile..."<<endl;
	
	if(!readTransTxt(userArguments.transactionsFile,baseData,bitBase,senderBase,receiverBase,transBase,userArguments)){
		cout<<"error in trans file"<<endl;
		return 1;
	}	
	
	
	cout<<"__________________________________________"<<endl;
	
	
	//start the interface
	
	bool t=true;
	int number;
	char temp[200];
	char senderId[200];
	char receiverId[200];
	char amount[200];
	int numAmount=0;
	
	while(t){
		cout<<"Write command... "<<endl;
		char command[200];
		fgets(command,200,stdin);
		
		
		if(!readInput(command,number))
			cout<<"Try again..."<<endl;
		if(number==8)
			return 1;
		if(number==1){
			strcat(tempId,"~");
			if(!requestTransaction(command,tempId,baseData,bitBase,senderBase,receiverBase,transBase))
				cout<<"Transaction not done!"<<endl;
			
		}
		else if(number==2){
			strcat(tempId,"+");
			if(!requestTransactions(command,tempId,baseData,bitBase,senderBase,receiverBase,transBase))
				cout<<"Transactions not done!"<<endl;
			
		}
		else if(number==3){
			
			if(!findEarnings(command,baseData,bitBase,senderBase,receiverBase,transBase)){
				cout<<"Find Earnings not done!"<<endl;
			}
			
		}
		else if (number==4){
			if(!findPayments(command,baseData,bitBase,senderBase,receiverBase,transBase)){
				cout<<"Find Payments not done!"<<endl;
			}
		}
		else if(number ==5){
			if(!walletStatus(command,baseData,bitBase,senderBase,receiverBase,transBase)){
				cout<<"Wallet Status not done!"<<endl;
			}
		}
		else if(number==6){
			if(!bitCoinStatus(command,baseData,bitBase,senderBase,receiverBase,transBase)){
				cout<<"bitCoinStatus not done!"<<endl;
			}
		}
		else if(number==7){
			if(!traceCoin(command,baseData,bitBase,senderBase,receiverBase,transBase)){
				cout<<"TraceCoin not done!"<<endl;
			}
		}
			
			
	}
	
}
