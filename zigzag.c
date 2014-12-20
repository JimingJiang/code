#include<stdio.h>

int main()
{
	int a[] = { 70, 55, 13, 2, 99, 2, 80, 80, 80, 80, 100, 19, 7, 5, 5, 5, 1000, 32, 32 };
	int n = sizeof(a)/sizeof(a[0]);
	int *len = (int*)malloc(sizeof(int)*(n+1));
	int *sign = (int*)malloc(sizeof(int)*(n+1));
	int i, j;
	for(i=0; i<n; i++)
	{
		len[i] = 1;
		sign[i] = 0;
	}	
	for(i=1; i<n; i++)
	{
		for(j=0; j<i; j++)
		{
			if((sign[j]==0||sign[j]==-1) && a[i] >a[j] && len[i] <len[j]+1)
			{
				len[i] = len[j] + 1;
				sign[i] = 1;
			}
			if((sign[j]==0||sign[j]==1) && a[i] < a[j] && len[i] <len[j]+1)	
			{
				len[i] = len[j] + 1;
				sign[i] = -1;
			}		
		}
	}
	
	printf("%d\n",len[n-1]);
	return 0;
} 

/*
	for(i=1; i<n; i++)
	{
		for(j=0; j<i; j++)
		{
			switch(sign[j])
			{
				case 0:
					if(a[i] > a[j])
					{
						len[i] = len[j] + 1;
						sign[i] = 1;
					}
					else if(a[i] < a[j])
					{
						len[i] = len[j] + 1;
						sign[i] = -1;
					}
					break;
				case 1:
					if(a[i]<a[j] && len[i] <len[j]+1)
					{
						len[i] = len[j] + 1;
						sign[i] = -1;
					}
					break;
				case -1:
					if(a[i] > a[j] && len[i] <len[j]+1)
					{
						len[i] = len[j] + 1;
						sign[i] = 1;
					}
					break;
			}
		}
	}
*/
