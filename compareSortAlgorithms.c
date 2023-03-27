#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if (r > l)
  {
	 int mid_pt = ((l+r)/2);
    mergeSort(pData, l, mid_pt);
    mergeSort(pData, (mid_pt+1), r);
   
    //merge:
    int a, b, c;
    int tmp_size = mid_pt - l + 1;
    int tmp_size2 = r - mid_pt;
  
    int *tmp1 = (int*) malloc(tmp_size * sizeof(int));
	extraMemoryAllocated += tmp_size * sizeof(int);
    int *tmp2 = (int*) malloc(tmp_size2 * sizeof(int));
	extraMemoryAllocated += tmp_size2 * sizeof(int);
  
    for (a = 0; a < tmp_size; a++)
      {
        tmp1[a] = pData[l + a];
      }
    
    for (b = 0; b < tmp_size2; b++)
      {
        tmp2[b] = pData[(mid_pt + 1) + b];
      }
    
    a = 0; 
    b = 0; 
    c = l; 
    while (a < tmp_size && b < tmp_size2)
    {
      if (tmp1[a] <= tmp2[b])
        {
          pData[c] = tmp1[a];
          a++;
        }
      else
        {
          pData[c] = tmp2[b];
          b++;
        }
      c++;
    }
    
    while (a < tmp_size)
    {
      pData[c] = tmp1[a];
      a++;
      c++;
    }
    
    while (b < tmp_size2)
    { 
      pData[c] = tmp2[b];
      b++;
      c++;
    }
    free(tmp1);
    free(tmp2);
  }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	if (n > 1)
	{
		int key, j;
		key = 0;
		for (int i = 0; i < n; i++)
		{
			key = pData[i];
			for (j = i-1; j >= 0; j--)
			{
				if (pData[j] > key)
				{
					pData[j+1] = pData[j];
				}
				else
				{
					break;
				}
			}
			pData[j+1] = key;
		}
	}
	
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
 int tmp, counter, j;
 int * p = pData;
  if (n > 1 && p != NULL)
  {
    counter = 0;
	tmp = 0;
    for (int i = 0; i < n-1; i++)
      {
		for (j = 0; j < (n-i-1); j++)
        {
			if (pData[j] > pData[j+1])
        	{
          		tmp = pData[j];
          		pData[j] = pData[j+1];
          		pData[j+1] = tmp;
		  
        	}
		}	
      }
    
	
  }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int tmp, counter, minimum;
	if (n > 1)
	{
		for (int i = 0; i < (n-1); i++)
      {
      minimum = i;
      for (int j = i+1; j < n; j++)
        {
          if (pData[j] <pData[minimum])
          {
            minimum = j;
          }
        }
        tmp =pData[i];
       pData[i] =pData[minimum];
       pData[minimum] = tmp; 
	    }
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		for (int i = 0; i < dataSz; i++)
		{
			fscanf(inFile,"%d",&((*ppData)[i]));
		}
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}