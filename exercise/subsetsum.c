#include<stdio.h>
#include<stdlib.h>
void printSubset(int *a, int n)
{
	for(int i = 0; i < n; i++)
    {
        printf("%5d", a[i]);
    }
    printf("\n");
}
/*
w: ��������
x: ѡ�е��Ӽ�
w_size: w����ĳ���
x_size: x����ĳ���
left_sum: x����Ԫ�صĺ� 
iter: x���������
right_sum: iter�����Ԫ�غ� 
target_sum: Ŀ��� 
*/
void subset_sum(int *w, int *x, int w_size, int x_size, int left_sum, int iter, int right_sum, int target_sum)
{
	if(left_sum + right_sum < target_sum)
		return;
	if(left_sum == target_sum)
	{
		printSubset(x, x_size);
		if(iter < w_size && left_sum - w[iter-1] + w[iter] <= target_sum)
			subset_sum(w, x, w_size, x_size-1, left_sum-w[iter-1], iter, right_sum+w[iter-1], target_sum);
		return;
	}
	else
	{
		int i;
		for(i=iter; i<w_size; i++)
		{
			if(left_sum+w[i]<=target_sum)
			{
				x[x_size] = w[i];
				subset_sum(w, x, w_size, x_size+1, left_sum+w[i], i+1, right_sum-w[i], target_sum);
			}
			
		}
	}
}

int compare(const void*a, const void *b)
{
	return(*(int*)a- *(int*)b);
}
int main()
{
	int w[]={10,7,5,18,12,20,15};
	int n = sizeof(w)/sizeof(w[0]);
	int M = 45;
	qsort(w, n, sizeof(w[0]), compare);
	
	int *x;
	x = (int*)malloc(sizeof(int)*n);
	
	int sum, i;
	for(sum=0, i=0; i<n; i++)
		sum += w[i];
	subset_sum(w, x, n, 0, 0, 0, sum, M);
	free(x);
	return 0;
} 
