#include<stdio.h>
#define EMPTY 0
#define N 4
static int total_num;
/*��ͷѰ��һ���ո���*/
int findEmptyVertex(int *x, int *vertex)
{
	for(*vertex=0; *vertex<N; (*vertex)++)
		if(x[*vertex] == EMPTY)
			return 1;
	return 0;
}
/*��鶥��vertex�ܷ���ɫcolor*/
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
/*�ݹ����recursive backtracking*/
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
	printf("��ɫ����������%d\n",total_num);
	return 0;
}
