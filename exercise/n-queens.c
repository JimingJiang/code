#include<stdio.h>
#include<stdlib.h>
#include<math.h>
static int total_num;
/*
* ����k�еĻʺ��ܲ��ܷ��ڵ�x[k]�� 
*/
int place(int *x, int k)
{
	int i;
	for(i=0; i<k; i++)
	{
		if(x[i]==x[k] || abs(x[i]-x[k])==abs(i-k))
			return 0;
	}
	return 1;
}
/*
* ��n queens��һ�����н� 
*/ 
void nQueens(int n)
{
	int *x = (int*)malloc(sizeof(int)*n);
	int i, k;
	for(i=0;i<n;i++)
		x[i]=0;
	k=0;
	while(k>-1)
	{	//n queens
		for(x[k]; k<n && x[k]<n && !place(x,k); x[k]++);
		if(x[k]<n)
		{
			k++;//��һ������һ��
			x[k] = 0;
			if(k==n)
			{	//���һ�����н� 
				for(i=0; i<n; i++)
					printf("%5d", x[i]);
				printf("\n");
				total_num++;
				//break;
				k--;
				x[k]++;
			}
		}
		else
		{
			k--;//���� 
			x[k]++;
		}
	}
}
/*program entry*/ 
int main()
{
	int n = 8;
	nQueens(n);//��8�ʺ����� 
	printf("\n%d�ʺ������ĸ���Ϊ%d\n",n, total_num);
	return 0;
}
