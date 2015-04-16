#include<stdio.h>
#define EMPTY 0
#define N 9
/*从头寻找一个空格子*/
int findEmptyGrid(int grid[N][N], int *row, int *col)
{
	for(*row=0; *row<N; (*row)++)
		for(*col=0; *col<N; (*col)++)
			if(grid[*row][*col] == EMPTY)
				return 1;
	return 0;
}
/*检查(row, col)位置能否放置num*/
int isValid(int grid[N][N], int row ,int col, int num)
{
	int i;
	//row
	for(i=0; i<N; i++)
		if(grid[row][i]==num)
			return 0;
	//col
	for(i=0; i<N; i++)
		if(grid[i][col]==num)
			return 0;
	//3*3box
	int j, rowoffset, coloffset;
	rowoffset = row - row%3;
	coloffset = col - col%3;
	for(i=0; i<3; i++)
		for(j=0; j<3; j++)
			if(grid[rowoffset+i][coloffset+j]==num)
				return 0;
	return 1;		
}
/*递归回溯recursive backtracking*/
int solveSudoku(int grid[N][N])
{
	int row, col;
	if(!findEmptyGrid(grid, &row, &col))
		return 1;
	int k;
	for(k=1; k<=9; k++)
	{
		if(isValid(grid, row, col, k))
		{
			grid[row][col] = k;
			if(solveSudoku(grid))
				return 1;
			grid[row][col] = EMPTY;
		}
	}
	return 0;
}
/*输出grid*/ 
void printGrid(int grid[N][N])
{
	int i, j;
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
			printf("%3d",grid[i][j]);
		printf("\n");
	}
	printf("\n");
}
/*program entry*/
int main()
{
	int grid[N][N] = {{5, 3, 0, 0, 7, 0, 0, 0, 0},
                      {6, 0, 0, 1, 9, 5, 0, 0, 0},
                      {0, 9, 8, 0, 0, 0, 0, 6, 0},
                      {8, 0, 0, 0, 6, 0, 0, 0, 3},
                      {4, 0, 0, 8, 0, 3, 0, 0, 1},
                      {7, 0, 0, 0, 2, 0, 0, 0, 6},
                      {0, 6, 0, 0, 0, 0, 2, 8, 0},
                      {0, 0, 0, 4, 1, 9, 0, 0, 5},
                      {0, 0, 0, 0, 8, 0, 0, 7, 9}};
    if(solveSudoku(grid))
		printGrid(grid);
    else
		printf("No solution exists\n");
	return 0;
}
