#include<stdio.h>
#include<stdlib.h>
#include<math.h>
static int total_num;
/*
* 检查第k行的皇后能不能放在第x[k]列 
*/
int place(int *x, int k)
{
	int i;
	for(i=0; i<k; i++)
	{
		if(x[i]==x[k] || abs(x[i]-x[k])==abs(i-k))
			return 0;
	}
	return 1;
}
/*
* 求n queens的一个可行解 
*/ 
void nQueens(int n)
{
	int *x = (int*)malloc(sizeof(int)*n);
	int i, k;
	for(i=0;i<n;i++)
		x[i]=0;
	k=0;
	while(k>-1)
	{	//n queens
		for(x[k]; k<n && x[k]<n && !place(x,k); x[k]++);
		if(x[k]<n)
		{
			k++;//下一个，下一行
			x[k] = 0;
			if(k==n)
			{	//输出一个可行解 
				for(i=0; i<n; i++)
					printf("%5d", x[i]);
				printf("\n");
				total_num++;
				//break;
				k--;
				x[k]++;
			}
		}
		else
		{
			k--;//回溯 
			x[k]++;
		}
	}
}
/*program entry*/ 
int main()
{
	int n = 8;
	nQueens(n);//解8皇后问题 
	printf("\n%d皇后问题解的个数为%d\n",n, total_num);
	return 0;
}
