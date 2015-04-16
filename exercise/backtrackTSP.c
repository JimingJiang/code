/*
* 旅行商问题，travelling saleman problem
* 简称 TSP 
*/
#include<stdio.h>
#include<stdlib.h>

/*使用邻接矩阵存储这个图*/
int w[4][4]={
	{0,30,6,5},
	{30,0,4,10},
	{6,4,0,20},
	{5,10,20,0}}; 
int n = sizeof(w)/sizeof(w[0]);
/*判断 城市k有没有遍历过*/
int nextCity(int*x, int k)
{
	int i;
	for(i=0; i<k; i++)
	{
		if(x[k]==x[i])
			return 0;
	}
	return 1;
}
/*TSP using backtracking*/
void backtrackTSP(int *x)
{	
	int i, j, k, cur_len, best_len;

	x[0]=0; 
	cur_len = 0;
	best_len = 1000000;
	k = 1;
	while(k>0)
	{
		x[k] = (x[k]+1)%n;
		for(j=0; j<n; j++)
		{//循环n次，找一个合适的k, 和j并无关系 
			if(nextCity(x, k))
			{
				//cur_len += w[x[k-1]][x[k]];
				for(i=0, cur_len=0; i<k; i++)
					cur_len += w[x[i]][x[i+1]];
				break;
			}
			x[k] = (x[k]+1)%n;
		}
		if(cur_len >= best_len || (k==n-1 && best_len < cur_len+w[x[k]][0]))
		{
			cur_len -= w[x[k-1]][x[k]];
			k--;
		}
		else if(k==n-1 && best_len >= cur_len + w[x[k]][0])
		{
			best_len = cur_len + w[x[k]][0];
			cur_len -= w[x[k-1]][x[k]];
			k--;
		}
		else
		{
			k++;
		}
	}
	printf("best route length:%d\n",best_len);
} 

/*program entry*/
int main()
{
	int i;
	int *x =(int*)malloc(sizeof(int)*(n+1));
	for(i=0; i<n; i++)
		x[i] = -1;
	backtrackTSP(x);
	
	for(i=0; i<n; i++)
		printf("%5d",x[i]);
	printf("\n");
	return 0;
}