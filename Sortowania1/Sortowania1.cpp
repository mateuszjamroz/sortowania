// Sortowania1.cpp : Defines the entry point for the console application.
//
#include "sort.h"

void Update(int l, int p, int* t);
void Merge(int* Tab, int* temp, int l, int m, int p);
bool Copy(int* pTab, int* temp, int nSize, int* i, int* ix);
void CopySerie(int* pTab, int* temp, int nSize, int*i, int*ix);


void SelectionSort(int * pTab, int nSize)
{
	for (int i = 0; i < nSize - 1; i++)
	{
		int k = i;
		int min = pTab[i];
		for (int j = i + 1; j < nSize; j++)
		{
			if (pTab[j] < min)
			{
				k = j;
				min = pTab[j];
			}
		}
		pTab[k] = pTab[i];
		pTab[i] = min;
	}
}

void InsertionSort(int* pTab, int nSize)
{
	for (int i = 1; i < nSize; i++)
	{
		int j;
		int temp = pTab[i];
		for (j = i - 1; j > 0 && pTab[j] > temp; j--)
		{
			pTab[j + 1] = pTab[j];
		}
		pTab[j + 1] = temp;
	}
}

void HalfSort(int * pTab, int nSize)
{
	for (int i = 1; i < nSize; i++)
	{
		int temp = pTab[i];
		int l = 1;
		int p = i - 1;
		while (l <= p)
		{
			int m = (l + p) / 2;
			if (temp < pTab[m])
				p = m - 1;
			else
				l = m + 1;
		}
		for (int j = i - 1; j > l; j--)
		{
			pTab[j + 1] = pTab[j];
			pTab[l] = temp;
		}
	}
}

void ShakeSort(int* pTab, int nSize) 
{
	int l = 1;
	int p = nSize-1;
	int k = nSize-1;
	do
	{
		for (int j = p; j >= l; j--)
		{
			if (pTab[j - 1] > pTab[j])
			{
				int temp = pTab[j - 1];
				pTab[j - 1] = pTab[j];
				pTab[j] = temp;
				k = j;
			}
		}
		l = k + 1;
		for (int j = l; j <= p; j++)
		{
			if (pTab[j - 1] > pTab[j])
			{
				int temp = pTab[j - 1];
				pTab[j - 1] = pTab[j];
				pTab[j] = temp;
				k = j;
			}
		}
		p = k - 1;
	} while (l < p);
}

void QuickSort(int* pTab, int l, int p)
{
	int i=l;
	int j=p;
	int temp;
	int wart= pTab[(l + p) / 2]; //srodek
	while(i<=j)
	{
		while (pTab[i] < wart)	i++;
		while (pTab[j]>wart)	j--;
		if (i <= j)
		{
			if (i != j)
			{
				temp = pTab[i];
				pTab[i] = pTab[j];
				pTab[j] = temp;
			}
			i++;
			j--;
		}
	}
	if (l < j)
		QuickSort(pTab, l, j);
	if (i < p)
		QuickSort(pTab, i, p);
}

void Update(int l, int p, int* t)
{
	if (l == p) return;
	int i = l;
	int j = 2 * (i+1)-1;
	int temp=t[i];
	while (j <= p)
	{
		if (j < p)
			if (t[j] < t[j + 1])	j++;

		if (temp >= t[j])
		{
			break;
		}
		t[i] = t[j];
		i = j;
		j = 2 * i+1;
	}
	t[i] = temp;
}

void HeapSort(int* t, int nSize)
{
	int temp;
	for(int l = (nSize / 2) + 1;l>=0;l--)
	{
		Update(l, nSize-1, t);
	}
	int p = nSize-1;
	for (; p > 0; p--)
	{
		temp = t[0];
		t[0] = t[p];
		t[p] = temp;
		Update(0, p-1, t);
	}
}

void MergeSort(int* Tab, int* temp, int l, int p)
{
	int m;
	if (l < p)
	{
		m = (l + p) / 2;
		MergeSort(Tab, temp, l, m);
		MergeSort(Tab, temp, m + 1, p);
		Merge(Tab, temp, l, m, p);
	}
}

void Merge(int* Tab, int* temp,  int l, int m, int p)
{
	memcpy(temp + 1, Tab + 1, (p - l + 1) * sizeof(*Tab)); 
	int i=l;
	int j=m+1;
	int q=l;
	while (i <= m && j <= p)
	{
		if (temp[i] < temp[j])
		{
			Tab[q++] = temp[i++];
		}
		else
		{
			Tab[q++] = temp[j++];
		}
	}
	while (i <= m)
	{
		Tab[q++] = temp[i++];
	}
}

void NaturalSort(int* pTab, int nSize)
{
	int* temp1 = (int*)calloc(nSize, sizeof(int));
	int* temp2 = (int*)calloc(nSize, sizeof(int));
	int nSerie;
	do
	{
		int i = 0;
		int j = 0;
		int k = 0;
		while (i < nSize)
		{
			while ((i < nSize - 1) && (pTab[i] <= pTab[i + 1]))
			{
				temp1[j++] = pTab[i++];
			}
			if (i < nSize)
			{
				temp1[j++] = pTab[i++];
			}
			while ((i < nSize - 1) && (pTab[i] < pTab[i + 1]))
			{
				temp2[k++] = pTab[i++];
			}
			if (i < nSize)
			{
				temp2[k++] = pTab[i++];
			}
		}
		int end1 = j;
		int end2 = k;
		nSerie = 0;
		i = j = k = 0;
		while ((j < end1) && (k < end2))
		{
			bool end = false;
			while (!end)
			{
				if (temp1[j] <= temp2[k])
				{
					end = Copy(pTab, temp1, end1, &i, &j);
					if (end)
					{
						CopySerie(pTab, temp2, end2, &i, &k);
					}
				}
				else
				{
					end = Copy(pTab, temp2, end2, &i, &j);
					if (end)
					{
						CopySerie(pTab, temp1, end1, &i, &k);
					}
				}
			}
			nSerie++;
		}
		while (j < end1)
		{
			CopySerie(pTab, temp1, end1, &i, &j);
			nSerie++;
		}
		while (k < end2)
		{
			CopySerie(pTab, temp2, end2, &i, &k);
			nSerie++;
		}
	} while (nSerie > 1);
	free(temp1);
	free(temp2);
}

void CopySerie(int* pTab, int* temp, int nSize, int*i, int*ix)
{
	bool end = false;
	do
	{
		end = Copy(pTab, temp, nSize, i, ix);
	} while (!end);
}

bool Copy(int* pTab, int* temp, int nSize, int* i, int* ix)
{
	pTab[(*i)++] = temp[(*ix)++];
	if (*ix == nSize)
	{
		return true;
	}
	return (temp[*ix - 1] > temp[*ix]);
}