#include<stdio.h> 
int main()
{
	int n=4;
	int W=10;
	int w[]={0,5,4,6,3};
	int p[]={0,10,40,30,50};
	int A[n+1][W+1];
	int i, j;
	
	for(i=0; i<=n; i++)
		A[i][0] = 0;
	for(i=0; i<=W; i++)
		A[0][i]=0;
	/*dynamic programming*/
	for(i=1; i<=n; i++)
	{
		for(j=1; j<=W; j++)
		{
			if(j>=w[i] && A[i-1][j] <A[i-1][j-w[i]] +p[i])
			{
				A[i][j] = A[i-1][j-w[i]] +p[i];
			}
			else
			{
				A[i][j] = A[i-1][j];
			}
		}
	
	}
	printf("最大收益:%d\n", A[n][W]);
	int y[n+1];
	int Y=W;
	/*输入最优解的选择*/
	for(i=n; i>0; i--)
	{
		if(A[i][Y]==A[i-1][Y])
			y[i] = 0;
		else
		{
			y[i] = 1;
			Y = Y-w[i];
		}
	} 
	for(i=1; i<=n; i++)
		if(y[i])
			printf("i=%d,w=%d,p=%d\n",i, w[i],p[i]);
	return 0;
}
