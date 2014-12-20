/*
*给二维数据分配连续的内存空间
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/*
*分配连续的内存
*/
float **allocateContinuousMemory(int row, int col)
{
	float **matrix;
	/*row行，每行一个指针，row*col个数组空间*/
	matrix = (float**)malloc(sizeof(float*) *row + sizeof(float) *row *col);
	/*matrix[0][0]的偏移地址*/
	float *offset = (float*)((int)matrix +sizeof(float*) *row);
	int i;
	/*将行首内存的地址保存到相应指针中, 以便可以matrix[i][j]这样存取*/
	for(i=0; i<row; i++)
		matrix[i] = (float*)((int)offset + sizeof(float) *i *col);
	return matrix;
}

void printAddr(float *arr, int n)
{
	int i;
	for(i=0; i<n; i++)
		printf("0x%x ",&arr[i]);
	printf("\n");
}

float getMatrixValue(float*m, int col, int i, int j)
{
	return *(m+i*col+j);
}

    float **citePointer(float *matrix, int row, int col)
    {
		int i;
		float **m;
		m = (float**)malloc(sizeof(float)*row);
		for(i=0; i<row; i++)
			m[i] = (matrix +i*col);
		return m;
    }
    void initMatrix(float *matrix, int row, int col)
    {
		float **m;
		m = citePointer(matrix, row, col);
		int i, j;
		for(i=0; i<row; i++)
			for(j=0; j<col; j++)
				m[i][j] = 119;
		free(m);
    }	
/*program entry*/
int main()
{
	int row, col;
	row=10;
	col=5;
	float **m;
	m = allocateContinuousMemory(row, col);
	int i;
	for(i=0; i<row; i++)
	{
		printf("m[%d]=0x%x, Addr:0x%x\t",i,m[i],&m[i]);
		printAddr(m[i], col);
	}
	initMatrix(m[0], row, col);
	int j;
/*	for(i=0; i<row; i++)
	{
		for(j=0; j<col; j++)
			printf("%f\t", m[i][j]);
		printf("\n");
	}
*/
printf("********************************************###################################\n");
	//test mem copy
	float **temp;
	temp = (float**)malloc(sizeof(float*)*row);//allocateContinuousMemory(row, col);
	for(i=0; i<row; i++)
	{
		temp[i] = m[i];
	}
	for(i=0; i<row; i++)
	{
		printf("temp[%d]=0x%x, Addr:0x%x\t", i, temp[i], &temp[i]);
		printAddr(temp[i], col);
	}
	m[0][30] = 1000000;
	for(i=0; i<row; i++)
	{
		for(j=0; j<col; j++)
			printf("%f\t", temp[0][i*col+j]);
		printf("\n");
	}
	free(m);
	free(temp);

	int aint[4][5];
	aint[0][19] = 100;
	printf("%d==%f\n",aint[3][4], pow(aint[3][4], 2));
	return 0;
}