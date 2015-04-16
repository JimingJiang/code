#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define PARENT(i) ((i-1)/2)
#define LEFT(i)	(2*i+1)
#define RIGHT(i)	(2*(i+1))

#define N 8
typedef struct Node{
	char value;
	int f;
	struct Node* left;
	struct Node* right;
}Node;

#define MaxLen 8
typedef struct Code{
	char s[MaxLen];
	int end;
}Code;

/*
* 堆数据结构实现最小优先级队列
*/
typedef struct Heap{
	int size;
	Node *arr;
}Heap;

Heap *initHeap( Node *a, int n)
{
	Heap *h = (Heap*)malloc(sizeof(Heap));
	h->size = n;
	h->arr = a;
	return h;
}

void swap(Node*a, Node *b)
{
	Node t = *a;	*a = *b;	*b = t;
}

void minHeapify(Heap *h, int i)
{
	int l, r, min;
	l = LEFT(i);
	r = RIGHT(i);
	min = i;
	if(l < h->size && h->arr[l].f < h->arr[i].f)
		min = l;
	if(r < h->size && h->arr[r].f < h->arr[min].f)
		min = r;
	if(min != i)
	{
		swap(&(h->arr[min]), &(h->arr[i]));
		minHeapify(h, min);
	}
}

void buildMinHeap(Heap *h)
{
	int i;
	for(i=(h->size-1)/2; i>-1; i--)
		minHeapify(h, i); 
}

Node heapExtractMin(Heap*h)
{
	if(h->size < 1)
		return;
	Node min;
	min = h->arr[0];
	h->arr[0] = h->arr[h->size-1];
	h->size --;
	minHeapify(h,0);
	return min;
}

void minHeapInsert(Heap *h, Node *node)
{
	h->size ++;
	h->arr[h->size - 1] = *node;
	int i;
	i = h->size - 1;
	while(i>0 && h->arr[PARENT(i)].f > h->arr[i].f)
	{
		swap(&(h->arr[PARENT(i)]), &(h->arr[i]));
		i = PARENT(i);
	}
}
/*
* 利用最小优先级队列构造huffman树 
*/
Node* huffmanTree(Node*arr, int n)
{
	Heap *h;
	h = initHeap(arr, n);
	buildMinHeap(h);
	
	int i;
	Node *node, *left, *right; 
	for(i=0; i<n-1; i++)
	{
		left = (Node*)malloc(sizeof(Node));
		right = (Node*)malloc(sizeof(Node));
		node = (Node*)malloc(sizeof(Node));

		*left = heapExtractMin(h);
		*right = heapExtractMin(h);

		node->left = left;
		node->right = right;
		node->f = right->f + left->f;
		
		minHeapInsert(h, node);
		//printf("%d, %d\n", left->f, right->f);
	}
	//return heapExtractMin(h);
	return &(h->arr[0]);
}

void huffmanCode(Node* root, Code *c)
{
	if(root && !(root->left || root->right))
	{
		c->s[++c->end] = '\0';
		printf("[%c, %d]: %s\n",root->value, root->f, c->s);
		return;
	}else{
		int t = c->end;
		c->s[++c->end] = '0';
		huffmanCode(root->left, c);
		c->end = t;
		c->s[++c->end] = '1';
		huffmanCode(root->right, c);
	}
}

int main()
{
	int i, n;
	char c[] = {'a','b','c','d','e','f','g','h'};
	int f[] = {1,1,2,3,5,8,13,21};
	Node node[N];
	for(i=0; i<N; i++)
	{
		node[i].value = c[i];
		node[i].f = f[i];
		node[i].left = NULL;
		node[i].right = NULL;
	}
	Node *root;
	root = huffmanTree(node,N);	
	Code code;
	code.end = -1;
	huffmanCode(root, &code);
	return 0;
} 
