/*
* Sort Algorithm
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define random(x) (rand()%x)
#define INFINITE 2147483647

void merge(int *a, int low, int mid, int high)
{
	int i, j, k;
	int n1, n2;
	n1 = mid - low + 1;
	n2 = high - mid + 1;
	int *larray = (int*)malloc(sizeof(int)*(n1 + 1));
	int *rarray = (int*)malloc(sizeof(int)*(n2 + 1));
	
	for(i=0; i<n1; i++)
		larray[i] = a[low + i];
	for(i=0; i<n2; i++)
		rarray[i] = a[mid + 1 + i];
		
	larray[n1+1] = INFINITE;
	rarray[n2+1] = INFINITE;
	
	for(i = 0, j = 0, k = low; k<high; k++)
	{
		if(larray[i]<rarray[j])
		{
			a[k] = larray[i];
			i++;
		}
		else
		{
			a[k] = rarray[j];
			j++;
		}
	}
}
void mergeSort(int *a, int low, int high)
{
	if(low < high)
	{
		int mid = (low+high)/2;
		mergeSort(a, low, mid);
		mergeSort(mid+1, high);
		merge(a, low, mid, high);
	}
}
/*插入排序*/
void insertSort(int *a, int low, int high)
{
	int i, j;
	int target;
	for(i=low+1; i< =high; i++)
	{
		target = a[i];
		for(j=i-1; j>-1;j--)
		{
			if(a[j]<target)
			{
				a[j+1]=a[j];
			}
		}
		a[j+1] = target;
	}
}
/*使用链接法实现归并排序*/
void insertSortL(int *a, int *link, int low, int high, int *p)
{
	int i, j,k;
	int target;
	for(i=low+1; i< =high; i++)
	{
		for(j=i-1; j>-1 && a[j]<target;j--);
		k = link[j+1];
		link[j+1] = i;
		link[i] =k;
	}
	*p = low;
}

void mergeL(int *a, int *link, int q, int r, int *p)
{
	int i, j, k;
	i=q;
	j=r;
	k = 0;
	while(i!=0 && j!=0)
	{
		if(a[i]<=a[j])
		{
			link[k]=i;
			k=i;
			i=link[i];
		}
		else
		{
			link[k]=j;
			k=j;
			j=link[j];
		}
	}
	if(0==i)
		link[k]=j;
	else
		link[k]=i;
	
	*p = link[0];
}
void mergeSortL(int *a, int *link, int low, int high, int *p)
{
	if(high -low +1 <16)
		insertSort(a, link, low, high, p);
	else
	{
		int q, r ;
		int mid = (high +low)/2;
		mergeSortL(a, link, low, mid, &q);
		mergeSortL(a, link, mid+1, high, &r);
		mergeL(a, link, q, r , p);
	}
}


void quickSort()
{}


void produceRandomNumber(int *a, int len)
{
     srand((int)time(0));
	 int i;
     for(i=0; i<len; i++)
           a[i] = random(1000);
}
int main()
{
	int len = 10000;
	int *a = (int *)malloc(sizeof(int)*(len+1));
	produceRandomNumber(a, len);
	mergeSort(a, 0, len);
	return 0;
}