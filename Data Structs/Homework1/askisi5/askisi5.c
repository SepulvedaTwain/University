#include "askisi5.h"




WordNode * Create(){ //creating the list
	WordNode * dummy=(WordNode *)malloc(sizeof(WordNode));
	dummy->next=NULL;
	return dummy;
	
}



void Print (WordNode * head){ //print the list
	WordNode* temp=head->next;
	int i;
	while(temp){
		printf("%s",temp->word);
		temp=temp->next;
	}
	printf("\n");
	
}


void InsertLast(WordNode * head, char * word){ //insertnode into the list
	WordNode* temp=head;
	while(temp->next){
		temp=temp->next;	
	}
	WordNode * newNode=(WordNode *)malloc(sizeof(WordNode));
	newNode->word = (char *)malloc(sizeof(char)*(strlen(word)+1));
	strcpy(newNode->word,word);
	newNode->next=NULL;
	temp->next=newNode;
	
	
	
}



int compare(const void * a,const void * b){ //compare function
	return(strcmp((char*)a,(char*)b));
}


int readFile(FILE * fp){ //read the count of lines in the file
	char c;  
  	int count = 0; 
    
    for (c = getc(fp); c != EOF; c = getc(fp)) {
        if (c == '\n')  
            count = count + 1; 
	}
	
    
    
    return count;    
}


void putWords(FILE * fp,char** words,int count){ //put words into the array
	FILE * temp=fp;
	int i=0;
	char line[256];
	
	
	while (fgets(line, sizeof(line), fp)) {
		
		words[i] = (char *)malloc(sizeof(char)*(strlen(line)+1));
		strcpy(words[i],line);
		i++;
	}

    
	
}

WordNode * Similar(char * word,char** dic,int count){ // search for similar words
	int wordLen=strlen(word);
	int i,p,j=0;
	int sum=0;
	char temp[50];
	char word2[50];
	strcpy(temp,word);
	strcat(temp,"\n");
	strcpy(word2,word);
	strcat(word2,"\n");
	WordNode * list=Create();
	
	for(i=0;i<wordLen;i++){ //for every letter
		while((strlen(dic[j])-1)<=strlen(word)){ //no need to search the whole array
			
			for(p=97;p<=122;p++){ //from 'a' to 'z'
				temp[i]=p;
				//printf("%s\t",temp,j);
				if(!strcmp(temp,dic[j])){
					//printf("%s",temp);
					if(strcmp(word2,dic[j])) //not the given word
						InsertLast(list,temp); //insert the node
				}
				sum++;
			}
			
			
			j++;
		}
		j=0;
		strcpy(temp,word);
		strcat(temp,"\n");
	}
	//Print(list);
	//printf("%d\n",sum);
	return list;
}




int main(){
	FILE *fp; 
    int count = 0;   
    char filename[]="words.txt" ;
    int i;
  
    fp = fopen(filename, "r"); 
  
    if (fp == NULL) 
    { 
        printf("Could not open file %s", filename); 
        return 1; 
    } 
    count=readFile(fp);
    fclose(fp);
    char ** words;
    words=(char** )malloc(sizeof(char*)*(count)); //create array
    
    fp = fopen(filename, "r");
    putWords(fp,words,count);
    fclose(fp);
    
    qsort(words,sizeof(words)/sizeof(char*),sizeof(char*),*compare); //sort array
    
	printf("The word is cat. Similar words: \n");
	WordNode * wordList=Similar("cat",words,count);
	Print(wordList);
	
	
    
}
