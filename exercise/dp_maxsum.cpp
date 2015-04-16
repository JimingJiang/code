/*��̬�滮�㷨:
**b[j]=max{a[i]++a[j]},1<=i<=j,��1<=j<=n,�����������Ӷκ�Ϊmax b[j]��1<=j<=n��
**��b[j]�Ķ������֪����b[j-1]>0ʱb[j]=b[j-1]+a[j]������b[j]=a[j]����b[j]�Ķ�̬�滮�ݹ�ʽΪ:
**b[j]=max(b[j-1]+a[j],a[j])��1<=j<=n��
**T(n)=O(n)
*/
#include<stdio.h> 
int dynMaxSum(int *a, int n, int *besti, int *bestj)
{
    int maxSum=0, sum=0;
    int i;
	*besti = *bestj = 0;
    for (i=0; i<n; i++)
    {
        if(sum>0)
        {
			sum += a[i];
		}
        else
		{
            sum = a[i];
			*besti = i;
		}
		if(sum>maxSum)
        {
			maxSum = sum;
			*bestj = i;
		}
    }
    return maxSum;
}
int main()
{
	int sum, start, end, n = 6;
	int a[]={-2,11,-4,13,-5,-2};
	sum = dynMaxSum(a, n, &start, &end);
	printf("start =%d, end=%d, MaxSum=%d\n", start, end, sum);
	return 0;
}
