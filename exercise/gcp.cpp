#include<stdio.h>
#define EMPTY 0
#define N 4
static int total_num;
/*从头寻找一个空格子*/
int findEmptyVertex(int *x, int *vertex)
{
	for(*vertex=0; *vertex<N; (*vertex)++)
		if(x[*vertex] == EMPTY)
			return 1;
	return 0;
}
/*检查顶点vertex能否着色color*/
int isValid(int graph[N][N], int *x, int vertex, int color)
{
	int i;
	for(i=0; i<N; i++)
		if(graph[vertex][i]==1 && x[i]==color)
			return 0;
	return 1;		
}
void printSolution(int*x)
{
	int i;
	for(i=0;i<N;i++)
		printf("%3d",x[i]);
	printf("\n");
}
/*递归回溯recursive backtracking*/
void graphColoring(int graph[N][N], int*x, int m)
{
	int vertex;
	if(!findEmptyVertex(x, &vertex))
	{
		total_num ++;
		printSolution(x);
		return;
	}

	int k;
	for(k=1; k<=m; k++)
	{
		if(isValid(graph, x, vertex, k))
		{
			x[vertex] = k;
			graphColoring(graph, x, m);
			x[vertex] = EMPTY;
		}
	}
}

/*program entry*/
int main()
{
	int graph[N][N] = {{0,1,0,1},
                      {1, 0, 1, 0},
                      {0, 1, 0, 1},
                      {1, 0, 1, 0},};
    int m=3;
	int x[N];
    int i;
    for(i=0; i<N; i++)
    	x[i] = EMPTY;
    
	graphColoring(graph, x, m);
	printf("着色方案个数：%d\n",total_num);
	return 0;
}
