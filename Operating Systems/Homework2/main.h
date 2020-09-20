#ifndef	MAIN
#define MAIN

#include <stdio.h>
#include "myStructs.h"



class Arguments{
	public:
		char alg[5];
		int frames;
		int q;
		int secs;
};

class PageTableCell{
	public:
		int pid;
		char page[10];

		PageTableCell(){
			pid=-1;
		}
};

class InvertedPageTable{
	public:
		PageTableCell * ipt;
		int length;
		int count;
		InvertedPageTable(int length):length(length),count(0),ipt(new PageTableCell[length]){}
		~InvertedPageTable(){
			delete [] ipt;
		}

		bool isFull(){
			return length==count;
		}
		int insertPage(int pid,char * page);

};

bool argvCheck(int argc, char ** argv);

bool isNumber(char * str);

void LRU(int frames,int q);

void WS(int frames,int q,int secs);

#endif