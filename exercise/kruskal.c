#include<stdio.h>
#define N 6
#define MAX 65536
int graph[N][N]={{0,10,-1,30,45,-1},
			{10,0,50,-1,40,25},
			{-1,50,0,-1,35,15},
			{30,-1,-1,0,-1,20},
			{45,40,35,-1,0,55},
			{-1,25,15,20,55,0}};
int parent[N];
int root(int p)
{
	while(p!=parent[p])
	{
		parent[p] = parent[parent[p]];//路径压缩 
		p = parent[p];
	}
	return p;
}
int sameSet(int p,int q)
{
	return root(p)==root(q);
}
//合并 
void myunion(int p, int q)
{
	int proot = root(p);
	int qroot = root(q);
	parent[qroot] = proot; 
}
void findMinEdge(int *x, int *y)
{
	int i, j, min=MAX;
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			if(graph[i][j]>0 && (!sameSet(i,j)) && min>graph[i][j])
			{
				*x = i;
				*y = j;
				min = graph[i][j];
			}
		}
	}//时间复杂度差 
}
// kruskal algorithm
void kruskalMST()
{
	int i;
	for(i=0; i<N; i++)
		parent[i] = i;
	
	int u, v;
	for(i=0; i<N-1; i++)
	{
		findMinEdge(&u, &v);
		myunion(u,v);
		printf("%d--%d\t%d\n",u,v,graph[u][v]);
	}
	
}
/*program entry*/
int main()
{
	kruskalMST();
	return 0;
} 
