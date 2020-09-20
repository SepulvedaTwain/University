#include "read_queries.h"

sem_t semPass;
pthread_mutex_t mutexSumsList;

void *queriesThread(void *argp)
{
	queriesThreadStruct *qTS_temp = (queriesThreadStruct *) argp;

	queriesThreadStruct *qTS = malloc(sizeof(queriesThreadStruct));
	if ( qTS == NULL) { printf("Error with malloc()\n"); exit(1); }

	qTS->files = qTS_temp->files;
	qTS->filesSize = qTS_temp->filesSize;
	qTS->input = malloc( strlen( qTS_temp->input)*sizeof(char) + sizeof(char));
	if ( qTS->input == NULL) { printf("Error with malloc()\n"); exit(1); }
	strcpy( qTS->input, qTS_temp->input);
	qTS->head = qTS_temp->head;

	sem_post( &semPass);

	// take info from query
	int i;

	char **parts;	int partsSize;

	char **partA;	int partASize;
	char **partB;	int partBSize;
	char **partC;	int partCSize;

	partsSize = split( qTS->input, '|', &parts);

	partASize = split( parts[0], ' ', &partA);
	partBSize = split( parts[1], '&', &partB);
	partCSize = split( parts[2], ' ', &partC);

	// swap the position of predicates in partB
	// putting filters in the beginning will speed up the predicates execution
	int firstJoin = swap_predicates( &partB, partBSize);

	/****** Create a function to swap the order of the partB array (Statistics) ******/
	BestTree(partB, partBSize, partA, partASize,firstJoin,qTS->files);

	// execute query and write results in sums list
	uint64_t *current;
	current = execute_query( qTS->files, qTS->filesSize, partA, partASize, partB, partBSize, partC, partCSize);

	// write sums in sums list
	pthread_mutex_lock( &mutexSumsList);

	insertSums( qTS->head, &current, partCSize);

	pthread_mutex_unlock( &mutexSumsList);

	// free memory
	for ( i=0; i < partsSize; i++)
		free(parts[i]);
	free(parts);

	for ( i=0; i < partASize; i++)
		free(partA[i]);
	free(partA);

	for ( i=0; i < partBSize; i++)
		free(partB[i]);
	free(partB);

	for ( i=0; i < partCSize; i++)
		free(partC[i]);
	free(partC);

	free(qTS->input);
	free(qTS);

	// return nothing
	pthread_exit(NULL);
}

void read_queries( fileNode *files, int filesSize, FILE *fp)
{
	char *input=NULL;
	size_t len=0;

	pthread_t *thr;
	int thrLength=0;
	queriesThreadStruct *qTS;

	uint64_t *current;
	sumsNode *head=NULL;

	int i;

	pthread_mutex_init( &mutexSumsList, NULL);

	// each loop goes for every query
	while( 1 )
	{
		if ( getline( &input, &len, fp) == -1)
			break;

		input[strlen(input)-1] = '\0';

		if ( !strcmp(input,"F") )
		{
			for ( i=0; i < thrLength; i++)
				pthread_join( thr[i], NULL);

			free(thr);
			thrLength = 0;

			printSumsList( head);

			freeSumsList( &head);
			head=NULL;
		}
		else
		{
			sem_init(&semPass,0,0);

			qTS = malloc(sizeof(queriesThreadStruct));
			if (qTS == NULL) { printf("Error with malloc()\n"); exit(1); }

			qTS->files = files;
			qTS->filesSize = filesSize;
			qTS->input = input;
			qTS->head = &head;

			if ( thrLength == 0)
			{
				thrLength++;
				thr = malloc(sizeof(pthread_t)*thrLength);
				if (thr == NULL) { printf("Error with malloc()\n"); exit(1); }
			}
			else
			{
				thrLength++;
				thr = realloc( thr, sizeof(pthread_t)*thrLength);
				if (thr == NULL) { printf("Error with realloc()\n"); exit(1); }
			}

			pthread_create( &thr[thrLength-1], NULL, queriesThread, (void *) qTS);

			sem_wait(&semPass);

			sem_destroy(&semPass);

			free(qTS);
		}
		free(input);
		input = NULL; len = 0;
	}
	free(input);

	pthread_mutex_destroy( &mutexSumsList);

	return;
}

int split( char *input, char toBreak, char ***array)
{
	int arraySize=0;
	int i,j,previousI=0;

	// for every character in input
	for ( i=0; i< strlen(input)+1; i++)
	{
		// if you found toBreak or '\0', add a string to the array
		// the string you add starts right after from the last toBreak you found(or input[0]) and ends at teh current toBreak(or '\0')
		if ( (input[i] == toBreak) || ( input[i] == '\0') )
		{
			if ( arraySize != 0)
			{
				*array = (char **) realloc( *array, (arraySize+1)*sizeof(char*));
				if ( *array == NULL) { printf("Error with realloc()\n"); exit(1); }
			}
			else
			{
				*array = (char **) malloc( (arraySize+1)*sizeof(char *));
				if ( *array == NULL) { printf("Error with malloc()\n"); exit(1); }
			}
			arraySize++;

			(*array)[arraySize-1] = malloc( (i-previousI+1)*sizeof(char) );
			if ( (*array)[arraySize-1] == NULL) { puts("Error with malloc()\n"); exit(1); }
			for ( j=previousI; j<i; j++)
				(*array)[arraySize-1][j-previousI] = input[j];
			(*array)[arraySize-1][j-previousI] = '\0';

			previousI = j+1;
		}
	}

	return arraySize;
}

int swap_predicates( char ***predicates, int size)
{
	int firstJoin=-1;
	int i,j,k,previousK,l;
	bool filter;
	char *tempA; char *tempB;
	char *array1; char *array2;
	int ret=-1;

	// put filters in the beginning
	for ( i=0; i<size; i++)
	{
		// extract info from predicate ( isFilter and store position if its the first join)
		for ( j=strlen((*predicates)[i]); j>0; j--)
		{
			if ( (*predicates)[i][j] == '.')
			{
				// find array1 and array2
				previousK = 0;
				for ( k=0; k < strlen( (*predicates)[i]); k++)
				{
					if ( ((*predicates)[i][k] == '.') && ( previousK == 0) )
					{
						array1 = malloc( (k-previousK+1)*sizeof(char));
						if ( array1 == NULL) { printf("Error with malloc()\n"); exit(1); }
						for ( l=0; l < (k-previousK); l++)
							array1[l] = (*predicates)[i][l+previousK];
						array1[l] = '\0';
					}
					else if ( ((*predicates)[i][k] == '.') && (previousK != 0) )
					{
						array2 = malloc( (k-previousK+1)*sizeof(char));
						if ( array2 == NULL) { printf("Error with malloc()\n"); exit(1); }
						for ( l=0; l < (k-previousK); l++)
							array2[l] = (*predicates)[i][l+previousK];
						array2[l] = '\0';
					}

					if ( (*predicates)[i][k] == '=')
						previousK = k+1;
				}

				if ( !strcmp(array1,array2))
					filter = true;
				else
				{
					filter = false;
					if (firstJoin==-1)
						firstJoin=i;
				}

				free( array1); free(array2);
				break;
			}
			else if ( ((*predicates)[i][j]=='>') || ((*predicates)[i][j]=='<') || ((*predicates)[i][j]=='=') )
			{
				filter = true;
				break;
			}
		}
		ret = firstJoin;
		// swap (*predicates)[i] and (*predicates)[firstJoin]
		if ( (filter) && (firstJoin!=-1) )
		{
			tempA = malloc( strlen( (*predicates)[firstJoin])*sizeof(char) + sizeof(char));
			if ( tempA == NULL) { printf("Error with malloc()\n"); exit(1); }
			strcpy( tempA, (*predicates)[firstJoin]);
			tempB = malloc( strlen( (*predicates)[i])*sizeof(char) + sizeof(char));
			if ( tempB == NULL) { printf("Error with malloc()\n"); exit(1); }
			strcpy( tempB, (*predicates)[i]);

			free( (*predicates)[firstJoin]);
			free( (*predicates)[i]);

			(*predicates)[firstJoin] = malloc( strlen(tempB)*sizeof(char) + sizeof(char));
			if ( (*predicates)[firstJoin] == NULL) { printf("Error with malloc()\n"); exit(1); }
			strcpy( (*predicates)[firstJoin], tempB);
			(*predicates)[i] = malloc( strlen(tempA)*sizeof(char) + sizeof(char));
			if ( (*predicates)[i] == NULL) { printf("Error with malloc()\n"); exit(1); }
			strcpy( (*predicates)[i], tempA);

			firstJoin = -1;
			i=0;

			free( tempA);
			free( tempB);
		}
	}

	return ret;
}

void BestTree(char **partB,int partBsize,char **partA,int partAsize,int firstJoin,fileNode* files)
{
	if ((partBsize - firstJoin) == 1 ){/*printf("No point in rearrange\n");*/return;}

	int intermediateSize = -1;

	//Debug
	// printf("From BestTree partB: \n");
	// for (int i = 0 ;i<partBsize;i++)
	// {
	// 	printf("%s\n",partB[i]);
	// }
	// printf("From BestTree partA: \n");
	// for (int i = 0 ;i<partAsize;i++)
	// {
	// 	printf("%s\n",partA[i]);
	// }

	for (int i = 0; i < firstJoin; i++) /* Execute the filters first*/
	{
		char* inputPredicate = malloc(sizeof(char)*strlen(partB[i]));
		strcpy(inputPredicate,partB[i]);
		Stats st;
		st.Max=-1;
		st = CalculateFilterInterSize(files,inputPredicate,partA,st);
		//printf("Statistics returned : \n Max: %d\nMin: %d\nQuantity: %d\nSparse: %d\n\n",st.Max,st.Min,st.Quantity,st.Sparse);
		free(inputPredicate);
	}

	IntegerList** Rels; //A somewhat graph struct
	Rels = malloc(sizeof(IntegerList*)*partAsize);

	for(int j=0;j<partAsize;j++)
	{
		Rels[j] = malloc(sizeof(IntegerList));
		Rels[j]->next = NULL;
		Rels[j]->value = -1;
	}
	IntegerList* eachhead;
	for (int j=firstJoin;j<partBsize;j++)
	{
		char dump[1];
		dump[0]=partB[j][0];
		int A = atoi(dump);
		dump[0]=partB[j][4];
		int B = atoi(dump);

		eachhead = Rels[A];
		if (eachhead->value==-1)
		{
			eachhead->value = B;
		}
		else
		{
			while(eachhead->next != NULL)
			{
				eachhead=eachhead->next;
			}
			eachhead->next = malloc(sizeof(IntegerList));
			eachhead = eachhead->next;
			eachhead->value = B;
			eachhead->next = NULL;
		}

		eachhead = Rels[B];
		if (eachhead->value == -1)
		{
			eachhead->value = A;
		}
		else
		{
			while(eachhead->next != NULL)
			{
				eachhead=eachhead->next;
			}
			eachhead->next = malloc(sizeof(IntegerList));
			eachhead = eachhead->next;
			eachhead->value = A;
			eachhead->next = NULL;
		}

	}

	int NumofPredicates = partBsize - firstJoin; //Remaining predicates (without the filters)
	if( NumofPredicates == 1){return ;}
	int Seq[NumofPredicates][NumofPredicates];
	int SeqCost[NumofPredicates];
	for (int i =0;i<NumofPredicates;i++)
	{
		Seq[i][0]=i;
		SeqCost[i] = INT_MAX;
		for(int j=1;j<NumofPredicates;j++){Seq[i][j] = -1;} //False Value
	}

	IntegerList** Pred_Rels;
	Pred_Rels = malloc(sizeof(IntegerList*)*NumofPredicates);
	for (int i=0;i<NumofPredicates;i++)
	{
		Pred_Rels[i] = NULL;
	}


	for (int i=0; i<NumofPredicates;i++)
	{
		char val1,val2;
		val1 = partB[i+firstJoin][0];
		val2 = partB[i+firstJoin][4];
		for( int j=0;j<NumofPredicates;j++)
		{
			if (j != i && partB[j+firstJoin][0] == val1 || partB[j+firstJoin][0] == val2 || partB[j+firstJoin][4] == val1 || partB[j+firstJoin][4] == val2)
			{
				IntegerList* curr = Pred_Rels[i];
				if (curr == NULL)
				{
					Pred_Rels[i] = malloc(sizeof(IntegerList));
					Pred_Rels[i]->next = NULL;
					Pred_Rels[i]->value = j;
				}
				else
				{
					while(curr->next != NULL) {curr = curr->next;}
					curr->next = malloc(sizeof(IntegerList));
					curr = curr->next;
					curr->value = j;
					curr->next = NULL;
				}
			}
		}
	}

	//NOTE: Free the Rels struct

	for(int u=0; u<NumofPredicates-1;u++)
	{
		for (int i=0 ;i<NumofPredicates; i++)
		{
			int RecCost = INT_MAX;
			int Next_Pred = -1;
			for (int j=0 ; j<NumofPredicates; j++)
			{
				if (NotIn(Seq[i],j,NumofPredicates) == true && CanBeReached(Pred_Rels[i],j) == true)//&& CanBeReached(Pred_Rels[i],j) == true)
				{
					int CostRet = CalculateCost(partA,partB,j+firstJoin,files);
					if (CostRet < RecCost){RecCost = CostRet; Next_Pred = j;}
				}
			}
			Seq[i][u+1] = Next_Pred;
			SeqCost[i] = RecCost;
		}
	}
	int BestCost = INT_MAX;
	int BestSeq;
	for (int i=0; i<NumofPredicates;i++) //Find the Sequence with the lowest cost
	{
		if (BestCost > SeqCost[i])
		{
			BestSeq = i;
		}
	}

	char** PredicateDump;
	PredicateDump = malloc(sizeof(char*)*NumofPredicates);
	for (int i=0; i<NumofPredicates; i++)
	{
		PredicateDump[i] = malloc(sizeof(char)*8); //0.1=1.2 (8 chars)
		strcpy(PredicateDump[i],partB[(Seq[BestSeq][i])+firstJoin]);
	}

	for(int i=0; i<NumofPredicates; i++)
	{
		strcpy(partB[i+firstJoin],PredicateDump[i]);
	}

	//Debug
	//printf("The best sequence is: ");
	// for(int i=0;i<NumofPredicates;i++)
	// {
	// 	printf("%s ",partB[(Seq[BestSeq][i])+firstJoin]);
	// }

	//Free
	for (int i=0;i<partAsize;i++)
	{
		IntegerList* tempList;
		while(Rels[i] !=NULL)
		{
			tempList=Rels[i];
			Rels[i]=Rels[i]->next;
			free(tempList);
		}
	}
	free(Rels);
	for (int i=0; i<NumofPredicates; i++)
	{
		free(Pred_Rels[i]);
	}
	free(Pred_Rels);
	for(int i=0; i<NumofPredicates; i++)
	{
		free(PredicateDump[i]);
	}
	free(PredicateDump);

}

int CalculateCost(char** partA,char** partB,int at,fileNode* files)
{
	char dump1[10],dump2[10],dump3[10],dump4[10],dump5[10],dump6[10];
	dump1[0] = partB[at][0];
	int TB1 = atoi(dump1);
	strcpy(dump2,partA[TB1]);
	int table1 = atoi(dump2);
	dump3[0] = partB[at][2];
	int row1 = atoi(dump3);
	dump4[0] = partB[at][4];
	int TB2 = atoi(dump4);
	strcpy(dump5,partA[TB2]);
	int table2 = atoi(dump5);
	dump6[0] = partB[at][6];
	int row2 = atoi(dump6);

	int MinValue = GetMin(files[table1].Stats[row1].Max,files[table2].Stats[row2].Max);
	int MaxValue = GetMax(files[table1].Stats[row1].Min,files[table2].Stats[row2].Min);

	int N = (MaxValue - MinValue + 1);
	if( N == 0){N++;}
	int F = (files[table1].Stats[row1].Quantity,files[table2].Stats[row2].Quantity)/N;
	return F;
}

Stats CalculateFilterInterSize(fileNode* files,char* predicate,char** partA,Stats stats)
{
	Stats output;
	if (predicate[5] == '.') //p.e.=> 1.2=1.4
	{
		// printf("Its a same array filter\n");
		// printf("Predicate: %s\n",predicate);

		char dump[1];
		dump[0] = predicate[0];
		int num = atoi(dump);
		int tablenum = atoi(partA[num]);
		dump[0] = predicate[2];
		int rowA = (int)atoi(dump);
		dump[0] = predicate[6];
		int rowB = (int)atoi(dump);
		int quantintytmp = (int)files[tablenum].Stats[rowA].Quantity;
		int Sparcitytmp = GetSparcity(files[tablenum].Stats[rowA].Unique,files[tablenum].Stats[rowA].UniqueSize);

		int InterMax = GetMax((int)files[tablenum].Stats[rowA].Max,(int)files[tablenum].Stats[rowB].Max);
		int InterMin = GetMin((int)files[tablenum].Stats[rowA].Max,(int)files[tablenum].Stats[rowB].Max);
		int InterQuantity = quantintytmp/(InterMax-InterMin+1);
		int InterSparse;
		if (quantintytmp != 0 && Sparcitytmp !=0)
		{
			InterSparse = Sparcitytmp*(1-((1-InterQuantity/quantintytmp)^(quantintytmp/Sparcitytmp)));
		}
		else
		{
			InterSparse = 0;
		}

		output.Max= InterMax;
		output.Min=InterMin;
		output.Quantity=InterQuantity;
		output.Sparse=InterSparse;
		//Test
		files[tablenum].Stats[rowA].Max = (uint64_t)InterMax;
		files[tablenum].Stats[rowA].Min = (uint64_t)InterMin;
		files[tablenum].Stats[rowA].Differ = InterSparse;
		files[tablenum].Stats[rowA].Quantity = (uint64_t)InterQuantity;

		files[tablenum].Stats[rowB].Max = (uint64_t)InterMax;
		files[tablenum].Stats[rowB].Min = (uint64_t)InterMin;
		files[tablenum].Stats[rowB].Differ = InterSparse;
		files[tablenum].Stats[rowB].Quantity = (uint64_t)InterQuantity;
		for(int i=0;i<files[tablenum].numColumns;i++)
		{
			if (i!=rowA && i!=rowB)
			{
				if(files[tablenum].Stats[i].Differ !=0 && Sparcitytmp !=0)
				{
					files[tablenum].Stats[i].Differ = (int)files[tablenum].Stats[i].Differ*(1-(1-InterSparse/Sparcitytmp)^((int)files[tablenum].Stats[i].Quantity/files[tablenum].Stats[i].Differ));
				}
				files[tablenum].Stats[i].Quantity = (uint64_t)InterQuantity;
			}
		}
	}
	else if (predicate[3] == '=')//p.e.=> 1.3=3000
	{
		// printf("Its a simple equal filter\n");
		// printf("Predicate: %s\n",predicate);

		char dump[1];
		dump[0] = predicate[0];
		int tempa = atoi(dump);
		int tablenum = (int)atoi(partA[tempa]);
		dump[0]=predicate[2];
		int rowA = (int)atoi(dump);
		int quantintytmp = (int)files[tablenum].Stats[rowA].Quantity;
		int Sparcitytmp = GetSparcity(files[tablenum].Stats[rowA].Unique,files[tablenum].Stats[rowA].UniqueSize);
		int rowAMin = (int)files[tablenum].Stats[rowA].Min;
		int rowAUniqueSize = (int)files[tablenum].Stats[rowA].UniqueSize;

		int temp = 4;
		int filterNumberCharacters = 0;
		while(true)
		{
			if (predicate[temp] != '\0'){filterNumberCharacters++;}
			else{break;}
			temp++;
		}
		char filterNumberChar [filterNumberCharacters+1];
		for (int j=4;j<temp;j++)
		{
			filterNumberChar[j-4] = predicate[j];
		}
		filterNumberChar[filterNumberCharacters] = '\0';
		int filterNumber = atoi(filterNumberChar);


		int InterMax = filterNumber;
		int InterMin = filterNumber;
		int InterQuantity;
		int InterSparse;
		if(files[tablenum].Stats[rowA].Unique[(int)(filterNumber-rowAMin)%(rowAUniqueSize)] == true)
		{
			InterQuantity = 1;
			InterSparse = quantintytmp/Sparcitytmp;
		}
		else
		{
			InterQuantity = 0;
			InterSparse = 0;
		}

		output.Max= InterMax;
		output.Min=InterMin;
		output.Quantity=InterQuantity;
		output.Sparse=InterSparse;

		//Test
		files[tablenum].Stats[rowA].Max = (uint64_t)InterMax;
		files[tablenum].Stats[rowA].Min = (uint64_t)InterMin;
		files[tablenum].Stats[rowA].Quantity = (uint64_t)InterQuantity;
		files[tablenum].Stats[rowA].Differ = InterSparse;

		for (int i=0;i<files[tablenum].numColumns;i++)
		{
			if (i!=rowA)
			{
				if(files[tablenum].Stats[i].Differ != 0 && files[tablenum].Stats[i].Quantity!=0)
				{
					files[tablenum].Stats[i].Differ = files[tablenum].Stats[i].Differ*(1-(1-InterQuantity/quantintytmp)^((int)files[tablenum].Stats[i].Quantity/files[tablenum].Stats[i].Differ));
				}
				files[tablenum].Stats[i].Quantity = (uint64_t)InterQuantity;
			}
		}
	}
	else //p.e.=> 1.2>30000
	{
		// printf("Its a simple filter\n");
		// printf("Predicate: %s\n",predicate);

		char dump[1];
		dump[0] = predicate[0];
		int tempa = atoi(dump);
		int tablenum = (int)atoi(partA[tempa]);
		dump[0]=predicate[2];
		int rowA = (int)atoi(dump);
		int quantintytmp = (int)files[tablenum].Stats[rowA].Quantity;
		int Sparcitytmp = GetSparcity(files[tablenum].Stats[rowA].Unique,files[tablenum].Stats[rowA].UniqueSize);
		int rowAMin = (int)files[tablenum].Stats[rowA].Min;
		int rowAMax = (int)files[tablenum].Stats[rowA].Max;
		int rowAUniqueSize = (int)files[tablenum].Stats[rowA].UniqueSize;
		// printf("Min is %d\n",rowAMin);
		// printf("Max is %d\n",rowAMax);

		int temp = 4;
		int filterNumberCharacters = 0;
		while(true)
		{
			if (predicate[temp] != '\0'){filterNumberCharacters++;}
			else{break;}
			temp++;
		}
		char filterNumberChar [filterNumberCharacters+1];
		for (int j=4;j<temp;j++)
		{
			filterNumberChar[j-4] = predicate[j];
		}
		filterNumberChar[filterNumberCharacters] = '\0';
		int filterNumber = atoi(filterNumberChar);
		//printf("Filter number: %d\n",filterNumber);

		int InterMax,InterMin,InterSparse,InterQuantity;

		if (predicate[3] == '<')
		{
			//printf("Smaller\n");
			InterMax = (int)filterNumber;
			InterMin = (int)rowAMin;
			if (rowAMin > filterNumber)
			{
				InterQuantity = 0;
				InterSparse = 0;
			}
			else
			{
				InterSparse = GetLowerLimitSparcity(files[tablenum].Stats[rowA].Unique,files[tablenum].Stats[rowA].UniqueSize,filterNumber);
				if(InterSparse == 0)
				{
					InterQuantity = (InterMax-InterMin+1);
				}
				else
				{
					InterQuantity = (InterMax-InterMin+1)/InterSparse;
				}
			}

		}
		else
		{
			//printf("Bigger\n");
			InterMax = rowAMax;
			InterMin = filterNumber;
			if (rowAMax < filterNumber)
			{
				InterQuantity = 0;
				InterSparse = 0;
			}
			else
			{
				InterSparse = GetUpperLimitSparcity(files[tablenum].Stats[rowA].Unique,files[tablenum].Stats[rowA].UniqueSize,filterNumber);
				if(InterSparse == 0)
				{
					InterQuantity = (InterMax-InterMin+1);
				}
				else
				{
					InterQuantity = (InterMax-InterMin+1)/InterSparse;
				}

			}
		}
		output.Max= InterMax;
		output.Min=InterMin;
		output.Quantity=InterQuantity;
		output.Sparse=InterSparse;

		files[tablenum].Stats[rowA].Max = (uint64_t)InterMax;
		files[tablenum].Stats[rowA].Min = (uint64_t)InterMin;
		files[tablenum].Stats[rowA].Differ = InterSparse;
		files[tablenum].Stats[rowA].Quantity = (uint64_t)InterQuantity;

		for (int i=0;i<files[tablenum].numColumns;i++)
		{
			if (i!=rowA)
			{
				if(files[tablenum].Stats[i].Differ != 0 && files[tablenum].Stats[i].Quantity!=0)
				{
					files[tablenum].Stats[i].Differ = files[tablenum].Stats[i].Differ*(1-(1-InterQuantity/quantintytmp)^((int)files[tablenum].Stats[i].Quantity/files[tablenum].Stats[i].Differ));
				}
				files[tablenum].Stats[i].Quantity = (uint64_t)InterQuantity;
			}
		}
	}
	return output;
}

int GetMax(int a, int b)
{
	if (a>b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int GetMin(int a, int b)
{
	if (a>b)
	{
		return b;
	}
	else
	{
		return a;
	}
}

int GetSparcity(bool* table,int tableSize)
{
	int output = 0;
	for(int i=0;i<tableSize;i++)
	{
		if (table[i] == true){output++;}
	}
	return output;
}

int GetUpperLimitSparcity(bool* table,int tableSize,int limit)
{
	int output = 0;
	for (int i =limit;i<tableSize;i++)
	{
		if (table[i] == true){output++;}
	}
	return output;
}

int GetLowerLimitSparcity(bool* table,int tableSize,int limit)
{
	int output = 0;
	if(limit>tableSize){/*printf("Error\n")*/;return output;}
	for(int i=0;i<limit;i++)
	{
		if (table[i] == true){output++;}
	}
	return output;
}

bool NotIn(int* table,int j,int size)
{
	for(int i =0; i<size;i++)
	{
		if (table[i] == j)
		{
			//printf("Already IN\n");
			return false;
		}
	}
	return true;
}

bool CanBeReached (IntegerList* PredRel,int value)
{
	if (PredRel == NULL){printf("NUll value !\n");}
	IntegerList* curr = PredRel;
	while(curr->next != NULL)
	{
		if (curr->value == value)
		{
			return true;
		}
		curr = curr->next;
	}
	if (curr->value == value)
	{
		return true;
	}
	//printf("Cannot be reached\n");
	//printf("OUT\n");
	return false;
}
