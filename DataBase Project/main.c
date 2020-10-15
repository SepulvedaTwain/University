#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HT.h"

int main( int argc, char *argv[])
{
	char *fileName;
	fileName = malloc( sizeof(char)*7 );
	strcpy(fileName,"myFile1");

	char attrType = 'i';

	char *attrName;
	attrName = malloc( sizeof(char)*3);
	strcpy(attrName,"id");

	int attrLength = sizeof(int);

	int buckets = 1;

	// create
	HT_CreateIndex( fileName, attrType, attrName, attrLength, buckets);

	// open
	HT_info *header_info;
	header_info = HT_OpenIndex( fileName);

	// insert
	Record one;
	one.id=1; strcpy(one.name, "name_1"); strcpy(one.surname, "surname_1"); strcpy(one.address, "address_1");
	HT_InsertEntry( header_info, one);
	one.id=2; strcpy(one.name, "name_2"); strcpy(one.surname, "surname_2"); strcpy(one.address, "address_2");
	HT_InsertEntry( header_info, one);
	one.id=3; strcpy(one.name, "name_3"); strcpy(one.surname, "surname_3"); strcpy(one.address, "address_3");
	HT_InsertEntry( header_info, one);
	one.id=4; strcpy(one.name, "name_4"); strcpy(one.surname, "surname_4"); strcpy(one.address, "address_4");
	HT_InsertEntry( header_info, one);
	one.id=5; strcpy(one.name, "name_5"); strcpy(one.surname, "surname_5"); strcpy(one.address, "address_5");
	HT_InsertEntry( header_info, one);
	one.id=6; strcpy(one.name, "name_6"); strcpy(one.surname, "surname_6"); strcpy(one.address, "address_6");
	HT_InsertEntry( header_info, one);
	one.id=7; strcpy(one.name, "name_7"); strcpy(one.surname, "surname_7"); strcpy(one.address, "address_7");
	HT_InsertEntry( header_info, one);

	// get all entries
	int value;
	value = 1;
	HT_GetAllEntries( header_info, &value);
	value = 2;
	HT_GetAllEntries( header_info, &value);
	value = 3;
	HT_GetAllEntries( header_info, &value);
	value = 4;
	HT_GetAllEntries( header_info, &value);
	value = 5;
	HT_GetAllEntries( header_info, &value);
	value = 6;
	HT_GetAllEntries( header_info, &value);
	value = 7;
	HT_GetAllEntries( header_info, &value);

	puts("\n\n-------------------------------------------------------\n\n");

	// delete
	value = 1;
	HT_DeleteEntry( header_info, (void *) &value);
	value = 2;
	HT_DeleteEntry( header_info, (void *) &value);
	value = 3;
	HT_DeleteEntry( header_info, (void *) &value);
	value = 4;
	HT_DeleteEntry( header_info, (void *) &value);
	value = 5;
	HT_DeleteEntry( header_info, (void *) &value);
	value = 6;
	HT_DeleteEntry( header_info, (void *) &value);
	value = 7;
	HT_DeleteEntry( header_info, (void *) &value);

	puts("\n\n-------------------------------------------------------\n\n");

	// get all entries
	value = 1;
	HT_GetAllEntries( header_info, &value);
	value = 2;
	HT_GetAllEntries( header_info, &value);
	value = 3;
	HT_GetAllEntries( header_info, &value);
	value = 4;
	HT_GetAllEntries( header_info, &value);
	value = 5;
	HT_GetAllEntries( header_info, &value);
	value = 6;
	HT_GetAllEntries( header_info, &value);
	value = 7;
	HT_GetAllEntries( header_info, &value);

	// close
	HT_CloseIndex( header_info);

	free(fileName);
	free(attrName);

	return 0;
}
