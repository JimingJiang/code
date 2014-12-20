/*
* 大整数乘法 
*/ 

#include<iostream>
#include<string.h>
using namespace std;

const int N=25;

template<class T>
void reverse(T *s,int n)
{
	int i;
	T c;
	for(i=0; i<n/2; i++)
	{
		c = s[i];
		s[i]=s[n-i-1];
		s[n-i-1]=c;
	}
}

void outDigit(int *s)
{
	for(; *s!=-1; s++)
		cout<<(*s);
	cout<<endl;
}

int main()
{
	char a[N];
	char b[N];
	char i,j,k;
	int t;
	int c[2*N+1];
	
	while(cin>>a>>b)
	{
		memset(c,0,sizeof(int)*2*N);
		reverse(a,strlen(a));
		reverse(b,strlen(b));
		for(i=0; i<strlen(a); i++)
		{
			for(j=0; j<strlen(b); j++)
			{
				t = (a[i]-'0')*(b[j]-'0');	
				for(k=0; t>0; k++)
				{
					c[i+j+k] += t;
					t = c[i+j+k] / 10;
					c[i+j+k] %= 10;
				}
			}
		}

		if(	c[i+j-1])
		{
			reverse(c,i+j);
			c[i+j]=-1;
		}	
		else
		{
			reverse(c,i+j-1);
			c[i+j-1]=-1;
		}
		outDigit(c);	
	}
	return 0;
} 
