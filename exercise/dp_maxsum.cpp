/*动态规划算法:
**b[j]=max{a[i]++a[j]},1<=i<=j,且1<=j<=n,则所求的最大子段和为max b[j]，1<=j<=n。
**由b[j]的定义可易知，当b[j-1]>0时b[j]=b[j-1]+a[j]，否则b[j]=a[j]。故b[j]的动态规划递归式为:
**b[j]=max(b[j-1]+a[j],a[j])，1<=j<=n。
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
