#include "read_files.h"
#include "limits.h"
#include <errno.h>

#define MAX_SPARSE_SIZE 50000000;  //Max size of the sparse table in case the (max-min+1) is very large


int read_files( fileNode **files, FILE *fp)
{
	*files = NULL;
	int filesSize = 0;

	char *input = NULL;
	size_t len = 0;

	int fd;

	uint64_t temp;
	int returnValue;
	uint64_t i,j,max = -1,min = INT_MAX;
	uint64_t current1,current2;

	// each loop goes for every line at stdin
	while ( 1 )
	{
		if ( getline( &input, &len, fp) == -1)
			break;

		input[strlen(input)-1] = '\0';

		// open file
		fd = open( input, O_RDONLY, 666);
		if ( fd < 0)
		{
			// display error message
			printf("Error with filename given fd: %d\n",fd);
		}
		else
		{
			// allocate memory for new table
			*files = (fileNode *) realloc( *files, (filesSize+1)*sizeof(fileNode) );
			if ( *files == NULL) { printf("Error with realloc()\n"); exit(1); }
			filesSize++;

			// rows
			returnValue = read( fd, &temp, sizeof(uint64_t));
			if ( returnValue < 0) { printf("Error with read()\n"); exit(1); }
			(*files)[filesSize-1].numRows = temp;

			//columns
			returnValue = read( fd, &temp, sizeof(uint64_t));
			if ( returnValue < 0) { printf("Error with read()\n"); exit(1); }
			(*files)[filesSize-1].numColumns = temp;
			(*files)[filesSize-1].Stats = malloc((int)temp*sizeof(StatisticsData)); //Allocate data for the statistics



			// data
			(*files)[filesSize-1].array = (uint64_t *) malloc( (*files)[filesSize-1].numColumns * (*files)[filesSize-1].numRows * sizeof(uint64_t)  );
			if ( (*files)[filesSize-1].array == NULL) { printf("Error with malloc()\n"); exit(1); }

			i=0;
			j=0;		
			int max_size = MAX_SPARSE_SIZE;
			int rows = (*files)[filesSize-1].numRows;

			while ( (returnValue = read( fd, &temp, sizeof(uint64_t)) > 0) )
			{
				(*files)[filesSize-1].array[i] = temp;
				if ((int)temp >= (int)max)
				{
					max = temp;
				}
				if ((int)temp <= (int)min)
				{
					min = temp;
				}				
				i++;
				if (i % rows == 0) //Read a column
				{
					(*files)[filesSize-1].Stats[j].Max = (int)max;
					(*files)[filesSize-1].Stats[j].Min = (int)min;
					(*files)[filesSize-1].Stats[j].Quantity = (uint64_t)(*files)[filesSize-1].numRows;
					(*files)[filesSize-1].Stats[j].Differ = 0;

					if (max_size <= (int)((int)max-(int)min+1))
					{
						//printf("Size capped!\n");
						(*files)[filesSize-1].Stats[j].Unique = malloc(max_size*sizeof(bool));
						if ((*files)[filesSize-1].Stats[j].Unique == NULL){printf("Error with malloc()\n");exit(1);}
						(*files)[filesSize-1].Stats[j].UniqueSize = max_size;
					}
					else
					{
						//printf("Size not capped.\n");
						(*files)[filesSize-1].Stats[j].Unique = malloc(((int)((int)max-(int)min+1))*sizeof(bool));
						if ((*files)[filesSize-1].Stats[j].Unique == NULL){printf("Error with malloc()\n");exit(1);}
						(*files)[filesSize-1].Stats[j].UniqueSize = (int)((int)max-(int)min+1);
					}

					for (int u = j*rows; u < j*rows+rows;u++) // Execute the algorithm for the Unique array
					{
						int CurrData = (int)(*files)[filesSize-1].array[u];
						if ((*files)[filesSize-1].Stats[j].Unique[((int)(CurrData-min)%max_size)]  == false)
						{
							(*files)[filesSize-1].Stats[j].Differ++;
						}
						(*files)[filesSize-1].Stats[j].Unique[((int)(CurrData-min)%max_size)] = true;
					}

					max = -1;
					min = INT_MAX;
					j++;	
				}		
			}
			if ( returnValue < 0) { printf("Error with read()\n"); exit(1); }

			// close file
			close(fd);
		}
		free(input);
		input=NULL; len=0;
	}
	free(input);

	return filesSize;
}
