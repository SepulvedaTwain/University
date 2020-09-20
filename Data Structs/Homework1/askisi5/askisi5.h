#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef struct wordNode {
    char * word;
    struct wordNode *next;
    
} WordNode;




WordNode * Create();
void Print(WordNode *);
void InsertLast (WordNode *, char * );

int compare(const void * ,const void *);

int readFile(FILE *);
void putWords(FILE *,char**,int);


WordNode * Similar(char *,char**,int);





