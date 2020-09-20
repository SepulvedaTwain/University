#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef void * ItemType;
typedef int (*CompareType)(ItemType a, ItemType b);

int compare(ItemType , ItemType);
typedef struct airportNode {
    ItemType itemtype;
    struct airportNode *next;
    struct airportNode *prv;
} AirportNode;



AirportNode * Create();
void Print(AirportNode *,char *);
AirportNode * Search(AirportNode *, ItemType ,CompareType );
void InsertLast (AirportNode *, ItemType );
void InsertAfter (AirportNode *, ItemType, AirportNode * );
void InsertBefore(AirportNode*, ItemType, AirportNode *);
void DeleteLast(AirportNode *);
void Delete (AirportNode *, AirportNode *);
