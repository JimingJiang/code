#include<stdio.h>

#define PARENT(i) ((i-1)/2)
#define LEFT(i)	(2*i+1)
#define RIGHT(i)	(2*(i+1))

typedef struct Heap{
	int size;
	int *arr;
}Heap;

void initHeap(Heap *h, int *a, int n)
{
	h->size = n;
	h->arr = a;
}

void swap(int *a, int *b)
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

void maxHeapify(Heap *h, int i)
{
	int l, r, max;
	l = LEFT(i);
	r = RIGHT(i);
	max = i;
	if(l < h->size && h->arr[l] > h->arr[i])
		max = l;
	if(r < h->size && h->arr[r] > h->arr[max])
		max = r;
	if(max != i)
	{
		swap(&(h->arr[max]), &(h->arr[i]));
		maxHeapify(h, max);
	}
}

void buildMaxHeap(Heap *h)
{
	int i;
	for(i=(h->size-1)/2; i>-1; i--)
		maxHeapify(h, i); 
}

void heapSort(int*a, int n)
{
	int i;
	Heap h;
	initHeap(&h, a, n);
	buildMaxHeap(&h);
	
	for(i=h.size-1; i>0; i--)
	{
		swap(&(h.arr[0]), &(h.arr[i]));
		h.size --;
		maxHeapify(&h, 0);
	}
}

int main()
{
	int A[] ={16,14,10,8,7,9,3,2,4,1};
	int i, n;
	n = 10;
	heapSort(A, n);
	for(i=0; i<n; i++)
		printf("%d ", A[i]);
	printf("\n");
	return 0;
} 