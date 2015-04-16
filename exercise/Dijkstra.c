//
#include<stdio.h>
#define N 6
#define MAX 65536
//�ڽӾ����ʾһ��ͼ 
int Route[N][N]={
	{0,7,9,MAX,MAX,14},
	{7,0,10,15,MAX,MAX},
	{9,10,0,11,MAX,2},
	{MAX,15,11,0,6,MAX},
	{MAX,MAX,MAX,6,0,9},
	{14,MAX,2,MAX,9,0}};
	
//�Ӷ���0����������ľ���
int RouteLen[N]; 
int PreNode[N];
int Visit[N];
//Dijkstra's algorithm
void Dijkstra()
{
	int i, j, k, min;
	for(i=0; i<N; i++)
	{
		RouteLen[i] = Route[0][i];
		PreNode[i] = 0;
		Visit[i] = 0;
	}
	Visit[0] = 1;
	for(i=1; i<N; i++)
	{
		min = MAX;
		k=-1;
		for(j=0; j<N; j++)
		{
			if(!Visit[j] && min > RouteLen[j] )
			{
				min = RouteLen[j];
				k = j;
			}	
		}	
		
		for(j=0; j<N; j++)
		{
			if(RouteLen[j] > Route[k][j]+RouteLen[k])
			{
				RouteLen[j] = Route[k][j]+RouteLen[k];
				PreNode[j] = k;
			}	
		}
		Visit[k] = 1;		
	}
	
	printf("��Դ��0���������С����ֱ�Ϊ\n�ڵ��\tǰ���ڵ�\t��С����\n");
	for(i=0; i<N; i++)
		printf(" %d\t%d\t\t%d\n",i, PreNode[i], RouteLen[i]);	
} 
//start from here
int main()
{
	Dijkstra();
	return 0;
}
