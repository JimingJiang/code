#include<stdio.h>
#define COMPUTER 1	//MAX 
#define MAN 2	//MIN
#define WIN 10000
#define LOSE -10000

int min(int a, int b)
{
	return (a>b)?b:a;
}
int max(int a, int b)
{
	return (a>b)?a:b;
}
int minMax(int role, int p, int depth)
{
	int i,j,temp,flag;
	if(p==1||p==2)
	{
		if(role==MAN)
			return 	WIN;
		if(role==COMPUTER)
			return LOSE;
	}
	if(role==MAN)
	{
		int minValue = WIN+1; 
		for(i=1; i<(p+1)/2; i++)
		{
			printf("depth=%d---%d--%d\n",depth, i,p-i);
			minValue = min(minValue, minMax(COMPUTER, i, depth+1));
			minValue = min(minValue, minMax(COMPUTER, p-i, depth+1));
		}
		return minValue;
	}
	if(role == COMPUTER)
	{
		int maxValue = LOSE-1; 
		for(i=1; i<(p+1)/2; i++)
		{
			printf("depth=%d---%d--%d\n",depth, i,p-i);
			maxValue = max(maxValue, minMax(COMPUTER, i,depth+1));
			maxValue = max(maxValue, minMax(COMPUTER, p-i, depth+1));
		}
		return maxValue;
	}
}
/*run from here*/
int main()
{
	
	printf("%d", minMax(MAN, 7, 0));
	return 0;
} 
