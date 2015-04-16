#include<stdio.h>
int x, y;
x=7;
y=6;
void printLCS(char *X, int *traceback, int i, int j)
{
	if(i==0 || j==0)
		return;
	if(*(traceback + i*(y+1)+j)==1)
	{
		printLCS(X, traceback,i-1, j-1);
		printf("->%c", X[i-1]);
	}
	else if(*(traceback + i*(y+1) +j)==2)
		printLCS(X, traceback, i-1, j);
	else
		printLCS(X, traceback, i, j-1);
}

int main()
{
	char X[]={'A','B','C','B','D','A','B'};
	char Y[]={'B','D','C','A','B','A'};

	int flen[x+1][y+1];
	/*
	 *《算法导论》traceback
	 * 0表示向左的箭头，1表示向左上方的箭头, 2表示向上的箭头 
	*/ 
	int traceback[x+1][y+1];
	int i, j;
	for(i=0;i<y;i++)
		flen[0][i] = 0;
	for(i=0;i<x;i++)
		flen[i][0] = 0;
		
	for(i=1; i<=x; i++)
	{
		for(j=1; j<=y; j++)
		{
			if(X[i-1] == Y[j-1])
			{
				flen[i][j] = flen[i-1][j-1] + 1;
				traceback[i][j] = 1;
			}	
			else if(flen[i-1][j] >= flen[i][j-1])
			{
				flen[i][j] =  flen[i-1][j];
				traceback[i][j] = 2;
			}	
			else
			{
				flen[i][j] = flen[i][j-1];
				traceback[i][j] = 0;
			}	
		}
	}

	printf("公共子序列的长度:%d\n", flen[x][y]);
	printLCS(X, traceback[0], x, y);
	return 0;
}
/*
void printFromHead(int *arr, int*pre, int index)
{
	if(pre[index] >0)
	{
		printFromHead(arr,pre, pre[index]);
		printf("->%d",arr[index]);
	}	
	else
		printf("%d",arr[index]);
}

void longest_increasing_subsequences(int *arr, int n)
{
	int *len = (int)malloc(sizeof(int)*n);
	int *pre= (int)malloc(sizeof(int)*n);
	
	int i,j;
	for(i=0;i<n; i++)
	{
		len[i]=1;
		pre[i]=-1;
		for(j=0; j<i; j++)
		{
			if(arr[i] > arr[j] &&len[i] <= len[j])
			{
				len[i] = len[j]+1;
				pre[i] = j;
			}
		}
	}
	
	int maxLen = 0;
	for(i=0;i<n;i++)
		if(len[i]>maxLen)
			maxLen = len[i];
	printf("最大长度为:%d, 序列如下:\n",maxLen);		
	for(i=0;i<n;i++)
	{
		if(len[i]==maxLen)	
		{
			printFromHead(arr, pre, i);
			printf("\n");
		}
	}		
}

int main(){
	int arr[]={5,2,8,6,3,6,9,7};
	int n=8;
	longest_increasing_subsequences(arr,n);
	return 0;
}*/
