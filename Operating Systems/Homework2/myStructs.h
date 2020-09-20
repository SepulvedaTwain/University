#ifndef	STRUCTS
#define STRUCTS

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "main.h"


using namespace std;

class InvertedPageTable;

class ListNode{
	public:
		int position;
		char r_w;
		ListNode * next;
		ListNode * prv;
		ListNode(int position,char * rw):position(position),r_w(rw[0]),next(NULL),prv(NULL){}

};

class List{				//ta writes ta grafoume mono mia fora otan prosthetoume mia selida me W dioti otan tha bgei apo tin lista tote mono tha grapsoume ston disko enw
						// ta reads ta metrame kathe fora pou emfanizontai
	public:
		ListNode * head;
		ListNode * tail;
		InvertedPageTable * ipt;
		int pid;
		int counter; 
		int readCounter;
		int writeCounter;
		int referenceCounter;
		int pfCounter;//pagefault
		List(int pid, InvertedPageTable * ipt):pid(pid),ipt(ipt),head(NULL),tail(NULL),counter(0),readCounter(0),writeCounter(0),pfCounter(0),referenceCounter(0){}
		~List();
		bool isEmpty(){
			return counter==0;
		}
		void insertNewPage(int position,char * rw);
		int RemoveLastNode();
		ListNode * FindPage(char* page,char * rw); //ap eksw kaloume tin find kai an yparxei o kombos tote kaloume tin move atfront
		void MoveAtFront(ListNode * page); //

		void LRU(char * page,char * rw);


};

//___________________________________________________________WORKING SET__________________________________


class WsNode{
	public:
		int position;
		char r_w;
		clock_t time;
		bool referenceBit;
		WsNode * next;
		WsNode * prv;
		WsNode(int position,char * rw, clock_t time):position(position),r_w(rw[0]),time(time),referenceBit(false),next(NULL),prv(NULL){}

};


class WsList{	
	public:
		WsNode * head;
		WsNode * tail;
		InvertedPageTable * ipt;
		int pid;
		int counter; 
		int readCounter;
		int writeCounter;
		int referenceCounter;
		int pfCounter;//pagefault
		clock_t tick;
		clock_t start_time;
		WsList(int pid, InvertedPageTable * ipt, clock_t tick):pid(pid),ipt(ipt),head(NULL),tail(NULL),counter(0),readCounter(0),writeCounter(0),pfCounter(0),referenceCounter(0),tick(tick),start_time(clock()){}
		~WsList();
		bool isEmpty(){
			return counter==0;
		}



		int RemoveNode(WsNode * node);
		
		bool FindPage(char* page,char * rw);

		void insertNewPage(int position,char * rw,clock_t time);

		void WsTickUpdate(clock_t currentTime);

		void Ws(char * page,char * rw);


};





#endif