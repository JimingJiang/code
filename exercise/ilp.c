/*integral linear programming*/
#include<stdio.h>
#include<stdlib.h>

/*整数线性规划*/
void ILP(int *p, int *w, int n, int c, int *x)
{
	//定义一个数组max[i][j]表示前 i 个元素，在c=j的前提下的最大值
	int i, j; 
	int **max = (int**)malloc(sizeof(int*)*(n+2));
	for(i=0; i<=n; i++)
	{
		max[i] = (int *) malloc(sizeof(int)*(c+2));
	} 
	for(i=0; i<=n; i++)
		max[i][0] = 0;
	for(i=0; i<=c; i++)
		max[0][i] = 0;
	
	for(i=1; i<=n; i++)
	{
		for(j=1; j<=c; j++)
		{
			max[i][j] = max[i-1][j];
			if(j>=w[i] && max[i][j] < p[i] + max[i-1][j-w[i]])
				max[i][j] = p[i] + max[i-1][j-w[i]];
			if(j>=2*w[i] && max[i][j] < 2*p[i] + max[i-1][j-2*w[i]])
				max[i][j] = 2*p[i] + max[i-1][j-2*w[i]];
		}
	}
	
	int cleft= c;
	for(i=n; i>0; i--)
	{
		if(max[i][cleft] == max[i-1][cleft])
			x[i] = 0;
		else if(max[i][cleft] == max[i-1][cleft - w[i]] + p[i])
			x[i] = 1, cleft -= w[i];
		else if(max[i][cleft] == max[i-1][cleft- 2*w[i]] + 2*p[i])
			x[i] = 2, cleft -= 2*w[i];
	}
	printf("max value :%d\n", max[n][c]);
}
/*program entry*/
int main()
{
	int c =22;
	int p[] = {0,10,15,6,4};
	int w[] = {0,4,6,3,2};
	int n = sizeof(p)/sizeof(p[0]) -1;
	int *x = (int*)malloc(sizeof(int)*(n+2));
	ILP(p, w, n, c, x);
	int i;
	for(i=1; i<=n; i++)
		printf("x%d=%d\n",i, x[i]);
	return 0;
} 
