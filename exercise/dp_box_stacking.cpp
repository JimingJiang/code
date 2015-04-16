#include<stdio.h>
#include<stdlib.h>
typedef struct Box{
	int h, w, d;
}Box;
int max(int a, int b)
{
	return (a>b)?a:b;
}
int min(int a, int b)
{
	return (a<b)?a:b;
}
int compareBoxBase(const void*a, const void*b)
{
	return (((Box*)b)->w * ((Box*)b)->d) - (((Box*)a)->w * ((Box*)a)->d);
}
/*DP algorithm*/
int maxStackHeight(Box box[], int n)
{
	Box rotateBox[3*n];
	int i, j;
	for(i=0;i<n;i++)
	{
		rotateBox[i*3].h=box[i].h;
		rotateBox[i*3].w=box[i].w;
		rotateBox[i*3].d=box[i].d;
		
		rotateBox[i*3+1].h=box[i].w;
		rotateBox[i*3+1].w=min(box[i].h, box[i].d);
		rotateBox[i*3+1].d=max(box[i].h, box[i].d);
		
		rotateBox[i*3+2].h=box[i].d;
		rotateBox[i*3+2].w=min(box[i].h, box[i].w);
		rotateBox[i*3+2].d=max(box[i].h, box[i].w);
	}
	n *= 3;
	qsort (rotateBox, n, sizeof(rotateBox[0]), compareBoxBase);
	/*output rotateBox*/
	for(i=0;i<n;i++)
		printf("h=%d,w=%d,d=%d\n",rotateBox[i].h,rotateBox[i].w,rotateBox[i].d);
	
	int H[n];
	for(i=0; i<n; i++)
		H[i] = rotateBox[i].h;
	/*LIS problem*/
	for(i=0; i<n; i++)
	{
		for(j=0; j<i; j++)
		{
			if(H[i]<H[j]+rotateBox[i].h && rotateBox[i].w<rotateBox[j].w && rotateBox[i].d<rotateBox[j].d)
				H[i] = H[j]+rotateBox[i].h; 
		}
	}

	int maxHeight;
	for(i=0,maxHeight=0; i<n; i++)
	{
		printf("%d\n",H[i]);
		if(maxHeight < H[i])
			maxHeight = H[i];
	}	
	return maxHeight;
}
/*start here*/
int main()
{

	Box arr[] = {{1,7,9},{6,3,5},{10,2,4}};
	int n = sizeof(arr)/sizeof(arr[0]);

	printf("Box stacking 's Max Height: %d\n", maxStackHeight (arr, n) );
	return 0;
} 
