/*
*可靠性设计
*/
#include<stdio.h>
int n = 3;
int C=105;/*总成本上限*/ 
int c[]={30,15,20}; /*价格*/ 
float r[]={0.9, 0.8, 0.5}; /*每一级设备单个的可靠性 */

/*第i级使用n个设备的可靠性*/
float g(int i, int n)
{
	int j;
	float ret=1;
	for(j=0; j<n; j++)
		ret *= (1-r[i]);
	return 1-ret;
}
/*start from here*/ 
int main()
{
	int limit, sum, i, k, j;
	float temp;
	
	/*前i级设备，在成本X下的最优可靠性 */
	float f[n+1][C+1];	
	for(i=0;i<=n;i++)
		f[i][0] = 1;
	for(i=0; i<=C; i++)
		f[0][i] = 1;
	/*DP*/
	for(i=1; i<=n; i++)
	{
		for(k=1; k<=C; k++)
		{
			f[i][k]=0;
			for(j=0,sum=0;j<i;j++)
				sum+=c[j];
			/*
			 *在成本 k 下，求前 i 级设备最高可靠性
			 *limit为第i级设备个数上限
			 */
			limit = (k-sum)/c[i-1] +1;
			
			for(j=1; j<=limit && k>=j*c[i-1]; j++)
			{
				temp =g(i-1, j) * f[i-1][k-j*c[i-1]];
				if(f[i][k] < temp)
					f[i][k] = temp;
			}
		}
	}

	printf("最高可靠性为:%.3f\n",f[n][C]);
	return 0;
}
