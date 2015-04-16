#include<stdio.h>
#include<stdlib.h>
#define BAD_NUM 2
int bad[BAD_NUM][4] = {{0,0,0,1},{6,6,5,6}};

int isTraversable(int x1, int y1, int x2, int y2)
{
	int i;
	for(i=0; i<BAD_NUM; i++)
	{
		if((x1==bad[i][0]&&y1==bad[i][1]&&x2==bad[i][2]&&y2==bad[i][3])
		||(x1==bad[i][2]&&y1==bad[i][3]&&x2==bad[i][0]&&y2==bad[i][1]))
			return 0;
	}
	return 1;
}
/*program entry*/
int main()
{
	int width = 6;
	int height = 6; 
	int **roadNum;	
	roadNum = (int **)malloc(sizeof(int*)*(width+2));
	int i, j;
	for(i=0; i<=width; i++)
		roadNum[i] = (int*)malloc(sizeof(int)*(height+2));
	
	for(i=0; i<=width; i++)
	{
		roadNum[i][0] = 0;
		if(isTraversable(i,0,i-1,0) &&((i>1&&roadNum[i-1][0]>0)||i==1))
			roadNum[i][0] = 1;
	}
	
	for(i=0; i<=height; i++)
	{
		roadNum[0][i] = 0;
		if(isTraversable(0,i,0,i-1) &&((i>1&&roadNum[0][i-1]>0)||i==1))
			roadNum[0][i] = 1;
	}

	for(i=1; i<=width; i++)
	{
		for(j=1; j<=height; j++)
		{
			roadNum[i][j] = 0;
			if(isTraversable(i,j,i-1,j))
				roadNum[i][j] += roadNum[i-1][j];
			 if(isTraversable(i,j,i,j-1))
			 	roadNum[i][j] += roadNum[i][j-1];
		}
	}
	printf("%d\n",roadNum[width][height]);
	return 0;
}
