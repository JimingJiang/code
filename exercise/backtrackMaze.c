#include<stdio.h>
#define EMPTY 0
#define M 4
#define N 5

typedef struct Position{
	int x, y;
}Position;
/*检查下一个位置是否可走*/
int checkNextMove(int maze[M][N], int solution[M][N], int visited[M][N], Position *next)
{
	if(next->x >=0 && next->x < M && next->y >= 0 && next->y<N && maze[next->x][next->y] == 1 && !visited[next->x][next->y])
		return 1;
	return 0;
}

/*递归回溯 走迷宫*/
int walkMaze(int maze[M][N], int solution[M][N], int visited[M][N], Position *start, Position*end)
{
	if(start->x==end->x && start->y==end->y)
	{
		solution[start->x][start->y] = 1;
		return 1;
	}

	if(checkNextMove(maze, solution, visited, start))
	{
		visited[start->x][start->y] = 1;
		solution[start->x][start->y] = 1;
		Position next;
		int i;
		for(i=0; i<4; i++)
		{
			switch(i){
				case 0://down
					next.x = start->x + 1;
					next.y = start->y;
					break;
				case 1://right
					next.x = start->x;
					next.y = start->y + 1;
					break;
				case 2://up
					next.x = start->x - 1;
					next.y = start->y; 
					break;
				case 3://left
					next.x = start->x;
					next.y = start->y - 1;
					break;
			}
			if(walkMaze(maze, solution, visited, &next, end))
				return 1;
		} 
		solution[start->x][start->y] = 0;//回溯 
	}
	return 0;
}
/*输出 解*/
void printSolution(int solution[M][N])
{
	int i, j;
	for(i=0; i<M; i++)
	{
		for(j=0; j<N; j++)
			printf("%3d", solution[i][j]);
		printf("\n");
	}
}
/*program entry*/
int main()
{
	int maze[M][N] = {{1, 0, 1, 1, 1},
                      {1, 1, 1, 0, 1},
                      {0, 1, 0, 0, 1},
                      {1, 1, 0, 1, 1}};
    /* 1 表示走的路 */
	int solution[M][N] = {{0,0,0,0,0},
							{0,0,0,0,0},
							{0,0,0,0,0},
							{0,0,0,0,0}};
	int visited[M][N] = {{0,0,0,0,0},
							{0,0,0,0,0},
							{0,0,0,0,0},
							{0,0,0,0,0}};							
	Position start, end;
	start={0,0};
	end={M-1, N-1};

	if(walkMaze(maze, solution, visited, &start, &end))
		printSolution(solution);
	return 0;
}
