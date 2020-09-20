#ifndef READ_QUERIES
#define READ_QUERIES

#include "types.h"
#include "execute_query.h"
#include "sums.h"

// A simple struct used for the Statistics
typedef struct Stats
{
	int Min;
	int Max;
	int Quantity;
	int Sparse;
}Stats;

/* read queries the users gives */
void read_queries( fileNode*, int, FILE*);

/* changes the order of the predicates as inputed in partB */
void BestTree(char**,int,char**,int,int,fileNode*);

/* takes a string input and splits it into parts based on toBreak char. Results are written in array */
int split( char*, char, char***);

/* takes an array of predicates and puts the filters in the first places of the array */
int swap_predicates( char***, int);

/* Computes the size of the intermediateResult for the predicate inputed */
Stats CalculateFilterInterSize(fileNode*,char*,char**,Stats);

//Get the max value from 2 integers
int GetMax(int,int);
//Get the min value from 2 integers
int GetMin(int,int);
//Get the sparcity of a bool table(how many cells are true)
int GetSparcity(bool*,int);
//Get the sparcity with upper bound
int GetUpperLimitSparcity(bool*,int,int);
//Get the sparcity with lower bound
int GetLowerLimitSparcity(bool*,int,int);
//Returns true if the predicate can be reached through the graph
bool CanBeReached (IntegerList*,int);
//Returns true if the j integer is in the table
bool NotIn(int*,int,int);
//Calculates the cost of a certain predicate
int CalculateCost(char**,char**,int,fileNode*); 

#endif
