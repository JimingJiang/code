#include<stdio.h>
#define FLOAT_MAX 65536	
#define N 7	//5+2
float p[]={0, 0.15, 0.10, 0.05, 0.10, 0.20};
float q[]={0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
int n = sizeof(p)/sizeof(p[0]);

float e[N][N]; //e[i][j]记录从 i到 j 的节点结成的最优二叉树的期望值 
float w[N][N]; //w[i][j]记录从 i到 j 的节点的概率p和 
int root[N][N]; //root[i][j]记录从i 到 j 的节点构成的最优二叉树的根 

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
		* s表迭代次数 
		* 先计算所有的 w[i][i], 再计算所有的w[i][i+1],再w[i][i+2]。。。 
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
		printf("k%d 是 k%d 的左孩子\n", left, parent); 
		printBST(start, parent-1, left);
	}
	else if(start==parent)
	{
		printf("d%d 是 k%d 的左孩子\n",start-1, parent);
	}
	if(end>parent)
	{
		int right = root[parent+1][end];
		printf("k%d 是 k%d 的右孩子\n", right, parent); 
		printBST(parent+1, end, right);
	}
	else if(end==parent)
	{
		printf("d%d 是 k%d 的右孩子\n",end, parent);
	}
}

/* main */
int main()
{
	optimalBST();
	int n = N-2;
	printf("最优二叉树的期望为:%.2f\n\n",e[1][n]);
	
	printf("k%d 是根\n",root[1][n]);
	printBST(1, n, root[1][n]);
	return 0;
} 
