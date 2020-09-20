#include "main.h"

Arguments arguments;

bool argvCheck(int argc, char ** argv){ // check to see if arguments are correct..

	int i;
	int counter=0;
	if(argc==9 || argc==7){
		
	
		for(i=1;i<argc;i+=2){
			

			if(!strcmp(argv[i],"-a")){
				strcpy(arguments.alg,argv[i+1]);
				counter++;
				
			}
			else if(!strcmp(argv[i],"-f")){
				if(!(isNumber(argv[i+1])))
					return false;
				arguments.frames=atoi(argv[i+1]);
				counter++;
			}
			else if(!strcmp(argv[i],"-q")){
				if(!(isNumber(argv[i+1])))
					return false;
				arguments.q=atoi(argv[i+1]);
				counter++;
			}
			else if(!strcmp(argv[i],"-t")){
				if(!(isNumber(argv[i+1])))
					return false;
				arguments.secs=atoi(argv[i+1]);
				counter++;
			}
		}
	}
	if (counter==4 || counter==3)
		return true;

	return false;

}


bool isNumber(char * str){	//find if it's a num using isdigit()
	int len=strlen(str);
	int i;
	for(i=0,i<len;i++;)
		if(!isdigit(str[i]))
				return false;

	return true;

}

int InvertedPageTable::insertPage(int pid,char * page){ //ayto tha kaleite afou exoume dei an einai full h oxi
	int i;

	for(i=0;i<length;i++){
		if(ipt[i].pid==-1){
			ipt[i].pid=pid;
			strcpy(ipt[i].page,page);
			count++;
			return i;
		}
	}
	return -1;
}

void LRU(int frames,int q){

	InvertedPageTable ipt(frames);

	List list1(7895,&ipt);
	List list2(9080,&ipt);

	FILE *fp1=fopen("bzip.trace","r");
	FILE *fp2=fopen("gcc.trace","r");

	int i;
	char address[10];
	char rw[2];
	for(i=0;i<q;i++){
		fscanf(fp1,"%s",address);
		fscanf(fp1,"%s",rw);
		list1.LRU(address,rw);
		fscanf(fp2,"%s",address);
		fscanf(fp2,"%s",rw);
		list2.LRU(address,rw);


	}




	fclose(fp1);
	fclose(fp2);

	cout<<"Counter : "<<list1.counter<<" pfCounter : "<<list1.pfCounter<<" readCounter : "<<list1.readCounter<<" writeCounter : "<<list1.writeCounter<<" referenceCounter : "<<list1.referenceCounter<<endl;
	cout<<"Counter : "<<list2.counter<<" pfCounter : "<<list2.pfCounter<<" readCounter : "<<list2.readCounter<<" writeCounter : "<<list2.writeCounter<<" referenceCounter : "<<list2.referenceCounter<<endl;

}


void WS(int frames,int q,int secs){

	clock_t tick=secs*CLOCKS_PER_SEC;
	//clock_t tick=5000;
	InvertedPageTable ipt(frames);

	WsList list1(7895,&ipt,tick);
	WsList list2(9080,&ipt,tick);

	FILE *fp1=fopen("bzip.trace","r");
	FILE *fp2=fopen("gcc.trace","r");

	int i;
	char address[10];
	char rw[2];
	for(i=0;i<q;i++){
		fscanf(fp1,"%s",address);
		fscanf(fp1,"%s",rw);
		list1.Ws(address,rw);
		fscanf(fp2,"%s",address);
		fscanf(fp2,"%s",rw);
		list2.Ws(address,rw);


	}


	

	fclose(fp1);
	fclose(fp2);
	
	cout<<"Counter : "<<list1.counter<<" pfCounter : "<<list1.pfCounter<<" readCounter : "<<list1.readCounter<<" writeCounter : "<<list1.writeCounter<<" referenceCounter : "<<list1.referenceCounter<<endl;
	cout<<"Counter : "<<list2.counter<<" pfCounter : "<<list2.pfCounter<<" readCounter : "<<list2.readCounter<<" writeCounter : "<<list2.writeCounter<<" referenceCounter : "<<list2.referenceCounter<<endl;
}

int main(int argc, char ** argv){

	if(!argvCheck(argc,argv)){
		cout<<"Invalid Arguments.."<<endl;
		return 1;
	}
	if(arguments.frames<=0){
		cout<<"Invalid Arguments.."<<endl;
		return 1;
	}
	
	if(!strcmp(arguments.alg,"WS\0")){
		if(arguments.secs<=0){
		cout<<"Invalid Arguments.."<<endl;
		return 1;
		}

		WS(arguments.frames,arguments.q,arguments.secs);
		return 0;
	}
	if(!strcmp(arguments.alg,"LRU\0")){
		LRU(arguments.frames,arguments.q);
		return 0;
	}

	cout<<"Invalid Arguments.."<<endl;
	return 1;

}