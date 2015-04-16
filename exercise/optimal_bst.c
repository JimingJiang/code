#include<stdio.h>
#define FLOAT_MAX 65536	
#define N 7	//5+2
float p[]={0, 0.15, 0.10, 0.05, 0.10, 0.20};
float q[]={0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
int n = sizeof(p)/sizeof(p[0]);

float e[N][N]; //e[i][j]��¼�� i�� j �Ľڵ��ɵ����Ŷ�����������ֵ 
float w[N][N]; //w[i][j]��¼�� i�� j �Ľڵ�ĸ���p�� 
int root[N][N]; //root[i][j]��¼��i �� j �Ľڵ㹹�ɵ����Ŷ������ĸ� 

/*dp construct optimal-bst*/ 
void optimalBST()
{
	int i, j, s, k;
	for(i=1; i<N; i++)
	{
		e[i][i-1] = q[i-1];
		w[i][i-1] = q[i-1];
	}
	float t;
	for(s=1; s<N-1; s++)
	{
		/*
		* s��������� 
		* �ȼ������е� w[i][i], �ټ������е�w[i][i+1],��w[i][i+2]������ 
		*/
		for(i=1; i<N-s+1; i++)
		{
			j =  i+s-1;
			e[i][j] = FLOAT_MAX;
			w[i][j] = w[i][j-1] + p[j] +q[j];
			for(k=i; k<=j; k++)
			{
				t = e[i][k-1] + e[k+1][j] + w[i][j];
				if(t < e[i][j])
				{
					e[i][j] = t;
					root[i][j] = k;
				}
			}		
		}
	}
} 
/*output*/
void printBST(int start, int end, int parent)
{
	if(start<parent)
	{
		int left = root[start][parent-1];
		printf("k%d �� k%d ������\n", left, parent); 
		printBST(start, parent-1, left);
	}
	else if(start==parent)
	{
		printf("d%d �� k%d ������\n",start-1, parent);
	}
	if(end>parent)
	{
		int right = root[parent+1][end];
		printf("k%d �� k%d ���Һ���\n", right, parent); 
		printBST(parent+1, end, right);
	}
	else if(end==parent)
	{
		printf("d%d �� k%d ���Һ���\n",end, parent);
	}
}

/* main */
int main()
{
	optimalBST();
	int n = N-2;
	printf("���Ŷ�����������Ϊ:%.2f\n\n",e[1][n]);
	
	printf("k%d �Ǹ�\n",root[1][n]);
	printBST(1, n, root[1][n]);
	return 0;
} 
