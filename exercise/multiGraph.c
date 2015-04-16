#include<stdio.h>
#define N 5 //段个数 
#define M 4 //每个段最大顶点数 
#define NUM 12 //多段图总共的顶点个数 
//多段图的顶点, 0表示空 
int graphVertex[N][M]={{1,0,0,0},{2,3,4,5},{6,7,8,0},{9,10,11,0},{12,0,0,0}};

int graphEdge[NUM][NUM]={{0,9,7,3,2,0,0,0,0,0,0,0},
						{0,0,0,0,0,4,2,1,0,0,0,0},
						{0,0,0,0,0,2,7,0,0,0,0,0},
						{0,0,0,0,0,0,0,11,0,0,0,0},
						{0,0,0,0,0,0,11,8,0,0,0,0},
						{0,0,0,0,0,0,0,0,6,5,0,0},
						{0,0,0,0,0,0,0,0,4,3,0,0},
						{0,0,0,0,0,0,0,0,0,5,6,0},
						{0,0,0,0,0,0,0,0,0,0,0,4},
						{0,0,0,0,0,0,0,0,0,0,0,2},
						{0,0,0,0,0,0,0,0,0,0,0,5},
						{0,0,0,0,0,0,0,0,0,0,0,0}};
int minDist[NUM];//存储源点到各顶点的最小距离
/*
*输出最小路径
* vi是段号
* vno是顶点号
* dist是源点到vno的最小距离 
*/ 
void printRoute(int vi, int vno, int dist)
{
	int i,ei;
	for(i=0; i<M; i++)
	{
		if((ei = graphVertex[vi-1][i]-1)>=0 && graphEdge[ei][vno]+minDist[ei]==dist)
		{
			printRoute(vi-1, ei, minDist[ei]);			
			break;//去掉break会发现有两条最小路径 
		}	
	}
	printf("->%d",vno+1); 
}

//dp
void multiGraph()
{
	int i, j, k, ei, ej;
	for(i=0; i<NUM; i++)
		minDist[i] = -1;
	minDist[0] = 0;
	for(i=1; i<N; i++)
	{
		for(j=0; j<M; j++)
		{
			if((ei = graphVertex[i][j] -1)>=0)
			{
				for(k=0; k<M; k++)
				{
					if((ej=graphVertex[i-1][k] -1)>=0 && graphEdge[ej][ei])
					{
						 if(minDist[ei]<0 || minDist[ei]>minDist[ej]+graphEdge[ej][ei])
						 	minDist[ei] = minDist[ej]+graphEdge[ej][ei];
					}
												
				}
			}
		}
	}
	printf("Min Distance between(0,11) is: %d\n",minDist[NUM-1]);
}
/*program entry*/
int main()
{
	multiGraph();
	printRoute(N-1, NUM-1, minDist[NUM-1]);
	return 0;
} 
