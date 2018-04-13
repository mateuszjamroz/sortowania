#include "stdafx.h"
#include "sort.h"


typedef void(*pF)(int*, int);

void Copy(void* first, void* second, int nSize);
void Testujsort(pF  pTabf[],const char* pFun[], int nSize,int*pMain, int* pTab, int tSize);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Bład wywołania! Brakuje parametru rozmiaru tablicy");
		return 1;
	}
	int nSize = atoi(argv[1]);
	pF pTabf[] = { SelectionSort,InsertionSort,HalfSort,ShakeSort,HeapSort };
	const char* pFun[] = { "SelectionSort", "InsertionSort", "HalfSort", "ShakeSort", "HeapSort" };
	int tSize = sizeof(pTabf) / sizeof(pF);

	int* pTab = NULL;
	int* pMain = NULL;
	int* tempTab = NULL;
	CreateTab(&pTab, nSize);
	CreateTab(&pMain, nSize);
	if (!pTab || !pMain)
	{
		printf("\nBrak pamięci!!\n");
		return 1;
	}
	printf("\nSortowanie dla %d elementow.\n", nSize);
	Testujsort(pTabf, pFun, nSize, pMain, pTab, tSize);
	
	//MergeSort------------------------------------------
	printf("\nTyp Sortowania: MergeSort\n");
	CreateTab(&tempTab, nSize);
	InitTab(tempTab, nSize);
	Copy(pTab, pMain, nSize * sizeof(int));
	double t = clock();
	MergeSort(pTab, tempTab, 0, nSize);
	t = clock() - t;
	double time = (double)t / CLOCKS_PER_SEC;
#ifdef _DEBUG_
	printf("\n");
	PrintTab(pTab,nSize);
#endif
	printf("Czas sortowania wyniosl: %lf sekund\n", time);
	memset(pTab, 0, nSize * sizeof(int));
	
	//QuickSort-----------------------------------------
	printf("\nTyp Sortowania: QuickSort\n");
	Copy(pTab, pMain, nSize * sizeof(int));
	t = clock();
	QuickSort(pTab, 0, nSize);
	t = clock() - t;
	time = (double)t / CLOCKS_PER_SEC; 
#ifdef _DEBUG_
	printf("\n");
	PrintTab(pTab, nSize);
#endif
	printf("Czas sortowania wyniosl: %lf sekund\n", time);
	memset(pTab, 0, nSize * sizeof(int));


	//Natural Sort-------------------------------------
	printf("\nTyp Sortowania: Natural Sort\n");
	Copy(pTab, pMain, nSize * sizeof(int));
	t = clock();
	NaturalSort(pTab, nSize);
	t = clock() - t;
	time = (double)t / CLOCKS_PER_SEC; 
#ifdef _DEBUG_
	printf("\n");
	PrintTab(pTab, nSize);
#endif
	printf("Czas sortowania wyniosl: %lf sekund\n", time);

	free(pMain);
	free(pTab);
	free(tempTab);
	return 0;
}

void Testujsort(pF  pTabf[], const char* pFun[], int nSize, int*pMain, int* pTab, int tSize)
{
	InitTab(pMain, nSize);

#ifdef _DEBUG_
	printf("\nWydruk: \n");
	PrintTab(pMain, nSize);
	printf("\n\n");
#endif

	for (int i = 0; i < tSize; i++)
	{
		Copy(pTab, pMain, nSize * sizeof(int));
		printf("\nTyp sortowania: %s", pFun[i]);

		clock_t t = clock();
		pTabf[i](pTab, nSize);
		t = clock() - t;
		double time = ((double)t) / CLOCKS_PER_SEC;

#ifdef  _DEBUG_
		printf("\n");
		PrintTab(pTab, nSize);
#endif
		printf("\nCzas sortowania wyniosl: %lf sekund\n", time);

		memset(pTab, 0, nSize * sizeof(int));
	}
}

void Copy(void* first, void* second, int nSize)
{
	memcpy(first, second, nSize);
}

int CreateTab(int** pTab, int nSize)
{
	int * t = *pTab = (int*)calloc(nSize, sizeof(int));
	return 1;
}

void InitTab(int *pTab, int nSize)
{
	int * t = pTab;
	for (int i = 0; i < nSize; i++)
	{
		*t++ = rand() % 100;
	}
}

void PrintTab(int *pTab, int nSize)
{
	int * t = pTab;
	for (int i = 0; i < 50; i++)
	{
		printf("%d ", *t++);
		if ((i % 10) == 0)
			printf("\n");
	}
	printf("\n");
}
