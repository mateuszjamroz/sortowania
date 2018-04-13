#ifndef _SORT_
#define _SORT_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <tchar.h>


int CreateTab(int** pTab, int nSize);
void InitTab(int *pTab, int nSize);
void PrintTab(int *pTab, int nSize);


void SelectionSort(int * pTab, int nSize);
void InsertionSort(int* pTab, int nSize);
void HalfSort(int * pTab, int nSize);
void ShakeSort(int* pTab, int nSize);
void QuickSort(int* pTab, int l, int p);
void HeapSort(int* t, int nSize);
void MergeSort(int* Tab, int* temp, int l, int p);
void NaturalSort(int *t, int nSize);



#endif
