#include<stdio.h>
int main()
{
	int n=4;
	int C=12;
	int v[]={10,7,5,1};
	int m[C+1];
	int i, j;
	
	for(i=0; i<=C; i++)
	{
		m[i] = i;
		for(j=0; j<n; j++)
			if(i >= v[j] && (m[i] > m[i-v[j]]+1))
				m[i] = m[i-v[j]] +1;

	}
	printf("%d\n", m[C]);
	return 0;
}
