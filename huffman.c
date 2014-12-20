#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode{
	char ch;
	int key;
	struct TreeNode *lchild;
	struct TreeNode *rchild;
}TreeNode;

#define DataType TreeNode

/*用最小堆实现优先级队列*/
#define PARENT(i) ((i-1)/2)
#define LEFT(i) (2*i + 1)
#define RIGHT(i) (2*(i+1))
/* swap two element */
void swap(DataType *a, int i, int j)
{
	DataType t = *(a+i);
	*(a+i) = *(a+j);
	*(a+j) = t;
}
/* keep the attribute of min heap*/
void min_heapify(DataType *a, int n, int k)
{
	int l, r, min;
	l = LEFT(k);
	r = RIGHT(k);
	min = k;
	if(l<n)
	{
		if((*(a+l)).key < (*(a+k)).key)
			min = l;
		else
			min = k;
	}

	if(r<n && (*(a+r)).key < (*(a+min)).key)
	{
		min = r;
	}
	if(min != k)
	{
		swap(a, min, k);
		min_heapify(a, n, min);
	}
}
/* build a min heap*/
void build_min_heap(DataType *a, int n)
{	
	int i;
	for(i= n/2 -1; i>-1; i--)
	{
		min_heapify(a, n, i);
	}
}

/*extract min of heap*/
DataType heap_extract_min(DataType  *a, int n)
{
	DataType min;
	if(n<1)
	{
		printf("heap underflow\n");
		exit(1);
	}
	min = *(a+0);
	a[0] = *(a+n-1);
	min_heapify(a, n-1, 0);
	
	return min;
}

/*insert into min_heap*/
void min_heap_insert(DataType *a, int n, int value)
{
	int i, k;
	i = n;
	k = PARENT(i);
	
	TreeNode *p;
	p->key = value;
	p->lchild = p->rchild = NULL;
	*(a+n) = *P;
	while(i>=0 &&  (*(a+k)).key > (*(a+i)).key)
	{
		swap(a, k, i);
		i = k;
		k = PARENT(i);
	}
}



/*build huffman tree*/
void build_huffman_tree(TreeNode *root, int *a, int n)
{
	build_min_heap(a, n);

}

int n = 8;
int test[]= {1,5,8,13,21,1,2,3};

int main()
{
	build_min_heap(test, n);
	heap_extract_min(test, n);
	min_heap_insert(test, n, 2);
	return 0;
}