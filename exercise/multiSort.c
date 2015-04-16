#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Node{
	int a[3];
}Node;
void printNodeArr(Node *node, int n)
{
	int i,j;
	for(i=0; i<n; i++)
	{
		for(j=0; j<sizeof(Node)/sizeof(int); j++)
			printf("\t%d",node[i].a[j]);
		printf("\n");
	}
	printf("\n---------------------------\n");
}
int cmpNode(const void *a, const void *b)
{
	Node x,y;
	x = *(Node*)a;
	y = *(Node*)b;
	int i;
	for(i=0; i<sizeof(Node)/sizeof(int) &&x.a[i]==y.a[i]; i++);
	return x.a[i] - y.a[i];
}
//用qsort实现对多个字段的数据字典序排序 
void testSort()
{
	int i, j, n;
	n = 20;
	Node node[20];
	for(i=0; i<n; i++)
		for(j=0; j<sizeof(Node)/sizeof(int); j++)
			node[i].a[j] = rand()%10;
	
	printNodeArr(node,n);
	qsort(node, n, sizeof(Node), cmpNode);
	printNodeArr(node,n);	
}
int cmpStr(const void*a, const void*b)
{
	return -strcmp((char*)a, (char*)b);
}
//实现字符串排序 
void strSort()
{
	int maxLen = 10;
	int n = 5;
	char s[][10]={"bcdf","abcd","abcde","bcde","bbbbbbb"};
	qsort(s, n, sizeof(char)*maxLen,cmpStr);
	
	for(n=n-1; n>-1; n--)
		printf("%s\n",s[n]);
} 
int main()
{
	testSort();
	strSort();
	return 0;
} 
