
#include<stdio.h>
#define N 6
#define MAX 65536
int graph[N][N]={{0,10,-1,30,45,-1},
			{10,0,50,-1,40,25},
			{-1,50,0,-1,35,15},
			{30,-1,-1,0,-1,20},
			{45,40,35,-1,0,55},
			{-1,25,15,20,55,0}};

int findMinKey(int *key, int *mstSet)
{
	int i, min_index, min=MAX;
	for(i=0; i<N; i++)
		if(!mstSet[i] && key[i] < min) 
			min = key[i], min_index = i;
	return min_index;
}
/*print the result*/
void printMST(int *father)
{
	printf("Edge\tWeight\n");
	int i;
	for(i=1; i<N; i++)
		printf("%d--%d\t%d\n",i, father[i], graph[i][father[i]]);
}
//prim algorithm 
void primMST()
{
	int father[N];
	int mstSet[N];
	int key[N];
	
	int i, v;
	for(i=0; i<N; i++)
		mstSet[i]=0, key[i] = MAX;
	
	father[0] = -1;
	key[0] = 0;
	
	for(i=0; i<N; i++)
	{
		int u = findMinKey(key, mstSet);
		mstSet[u] = 1;
		
		for(v=0; v<N; v++)
		{
			if(graph[u][v]>0 && !mstSet[v] && key[v]>graph[u][v])
				father[v] = u, key[v] = graph[u][v];
		}
	}
	printMST(father);
}
/*start from here*/
int main()
{
	primMST();
	return 0;
} 
