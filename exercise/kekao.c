/*
*�ɿ������
*/
#include<stdio.h>
int n = 3;
int C=105;/*�ܳɱ�����*/ 
int c[]={30,15,20}; /*�۸�*/ 
float r[]={0.9, 0.8, 0.5}; /*ÿһ���豸�����Ŀɿ��� */

/*��i��ʹ��n���豸�Ŀɿ���*/
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
	
	/*ǰi���豸���ڳɱ�X�µ����ſɿ��� */
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
			 *�ڳɱ� k �£���ǰ i ���豸��߿ɿ���
			 *limitΪ��i���豸��������
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

	printf("��߿ɿ���Ϊ:%.3f\n",f[n][C]);
	return 0;
}
