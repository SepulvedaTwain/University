#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef char AirportCode[4];
typedef struct airportNode {
                        AirportCode airportCode;
                        struct airportNode *next;
                } AirportNode;
                

AirportNode * Create();
void Print(AirportNode *);
AirportNode * Search(AirportNode *, AirportCode );
void InsertLast (AirportNode *, AirportCode );
void InsertAfter (AirportNode *, AirportCode, AirportNode * );
void DeleteLast(AirportNode *);
void Delete (AirportNode *, AirportNode *);


