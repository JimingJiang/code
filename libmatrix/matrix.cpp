/*
**matrix.cpp
**
**2014-10-27
*/
#include"matrix.h"


/*
**输入行数和列数，创建一个矩阵
*/
template < class MatrixType>
void Matrix<MatrixType>::_init(u_int prow, u_int pcol)
{
	if (prow <= 0 || pcol <= 0)
	{
		cout << "fatal error\n";
		exit(-1);
	}
	row = prow;
	col = pcol;
	matrix = new MatrixType*[row];
	for (u_int i = 0; i < row; i++)
	{
		matrix[i] = new MatrixType[col];
	}
}


/*
**输入行数和列数，创建并初始化一个零矩阵
*/
template < class MatrixType>
Matrix<MatrixType>::Matrix(u_int prow, u_int pcol)
{
	_init(prow, pcol);
	for (u_int i = 0; i < row; i++)
	{
		for (u_int j = 0; j < col; j++)
		{
			matrix[i][j] = (MatrixType)0;
		}
	}
}


/*
**根据二维数组arr[prow][pcol]创建并初始化一个矩阵
*/
template < class MatrixType>
Matrix<MatrixType>::Matrix(u_int prow, u_int pcol, MatrixType *arr)
{
	_init(prow, pcol);
	for (u_int i = 0; i < row; i++)
	{
		for (u_int j = 0; j < col; j++)
		{
			matrix[i][j] = *(arr + pcol*i +j);
		}
	}
}
/*
**拷贝构造函数
*/
template < class MatrixType>
Matrix<MatrixType>::Matrix(Matrix<MatrixType> &m )
{
	_init(m.row, m.col);
	for (u_int i = 0; i < row; i++)
	{
		for (u_int j = 0; j < col; j++)
		{
			matrix[i][j] = m.matrix[i][j];
		}
	}
}

/*
**析构函数
*/
template < class MatrixType>
Matrix<MatrixType>::~Matrix()
{
	for (u_int i = 0; i<row; i++)
	{
		delete[col]matrix[i];
		matrix[i] = NULL;
	}
	delete[row]matrix;
	matrix = NULL;
}

/*
**打印整个矩阵
*/
template < class MatrixType>
void Matrix<MatrixType>::print()
{
	for (u_int i = 0; i < row; i++)
	{
		for (u_int j = 0; j < col; j++)
		{
			cout << matrix[i][j] << '\t';
		}
		cout << endl;
	}
}
/*
**计算矩阵的协方差矩阵
*/
template < class MatrixType>
Matrix<MatrixType>* Matrix<MatrixType>::cov()
{
	u_int i;
	u_int j;
	u_int k;

	Matrix<MatrixType> *cov_matrix = new Matrix<MatrixType>(col, col);

	MatrixType sum;
	MatrixType *avg;
	avg = new MatrixType[col];//保存每一列的均值

	//first，计算特征的均值
	for (i = 0; i<col; i++)
	{
		for (sum = 0, j = 0; j<row; j++)
			sum += matrix[j][i];
		avg[i] = sum / row;
	}
	//second, 计算协方差
	for (i = 0; i<col; i++)
	{
		for (j = 0; j<col; j++)
		{
			if (i <= j)
			{
				for (sum = 0, k = 0; k<row; k++)
				{
					sum += (matrix[k][i] - avg[i])*(matrix[k][j] - avg[j]);
				}
				//协方差(i,j)=（第i列所有元素-第i列均值）*（第j列所有元素-第j列均值）/（样本数-1）
				cov_matrix->matrix[i][j] = (MatrixType)sum / (row - 1);
			}
			else
			{//利用矩阵对称
				cov_matrix->matrix[i][j] = cov_matrix->matrix[j][i];
			}
		}
	}
	cov_matrix->print();
	delete avg;
	return cov_matrix;
}
/*
**计算矩阵的逆矩阵
*/
template < class MatrixType>
Matrix<MatrixType>* Matrix<MatrixType>::inv()
{
	if (col != row)
	{
		cout << "该矩阵不是一个方阵!\n";
		return NULL;
	}
	u_int i, j, k;
	u_int num = col;
	Matrix<MatrixType> *MatEnhanced;//增广矩阵(A|E)
	MatEnhanced = new Matrix<MatrixType>(row, row*2);

	MatrixType *temp;
	temp = new MatrixType[row * 2];

	MatrixType xishu = 1;//初等变换时系数，设初值为1

	for (i = 0; i<num; i++)                            //增广矩阵赋值，前半部分
	{
		for (j = 0; j<num; j++)
			MatEnhanced->matrix[i][j] = matrix[i][j];
	}
	for (i = 0; i<num; i++)                            //增广矩阵赋值，后半部分
	{
		for (j = num; j<2 * num; j++)
			MatEnhanced->matrix[i][j] = 0;//先将后半部分全部赋值为0

		MatEnhanced->matrix[i][i + num] = 1;//再将其对角线部分赋值为1
	}

	//接下来进行初等行变换
	for (i = 0; i<num; i++)
	{
		if (MatEnhanced->matrix[i][i] == 0)//如果前半部分的对角线上的元素为0，此时进行行变换
		{
			if (i == num - 1)//如果是最后一行，那么说明该矩阵不可逆
				return false;
			//对第i行以后的各行进行判断，找到第i个元素不为零的行，并与第i行进行交换
			for (j = i; j<num; j++)
			{
				if (MatEnhanced->matrix[j][i] != 0)
				{
					k = j;//记住该行的行号
					break;//退出循环
				}
			}
			//接下来对第i行和第k行进行交换
			temp = MatEnhanced->matrix[k];//第k行
			MatEnhanced->matrix[k] = MatEnhanced->matrix[i];
			MatEnhanced->matrix[i] = temp;
		}

		//初等变换
		for (j = 0; j<num; j++)//对其他行的所有列进行计算
		{
			if (j != i)//本行不参与计算
			{
				if (MatEnhanced->matrix[j][i] != 0)//只有当其不为零时进行计算，否则不计算
				{
					xishu = MatEnhanced->matrix[j][i] / MatEnhanced->matrix[i][i];
					for (k = i; k<2 * num; k++)//对后面的所有列进行计算
					{
						MatEnhanced->matrix[j][k] -= xishu*MatEnhanced->matrix[i][k];
					}
				}
			}
		}
		//将本行所有列都除以对角线上的值，将前半部分化成单位矩阵
		xishu = MatEnhanced->matrix[i][i];
		for (j = i; j<2 * num; j++)
		if (xishu != 0)
			MatEnhanced->matrix[i][j] /= xishu;
	}

	Matrix<MatrixType> *inv_m = new Matrix<MatrixType>(row, row);
	//计算完成后，后半部分即为原矩阵的逆矩阵，将其赋值给InvMat.
	for (i = 0; i<num; i++)
	{
		for (j = 0; j<num; j++)
			inv_m->matrix[i][j] = MatEnhanced->matrix[i][j + num];
	}
	//内存释放
	delete MatEnhanced;
	delete temp;

	return inv_m;
}




/*
**计算矩阵的绝对值
*/
template < class MatrixType>
Matrix<MatrixType>* Matrix<MatrixType>::abs()
{
	Matrix<MatrixType>* abs_matrix = new Matrix<MatrixType>(row, col);
	for (u_int i = 0; i < row; i++)
		for (u_int j = 0; j < col; j++)
			abs_matrix->matrix[i][j] = matrix[i][j] > 0 ? (matrix[i][j]) : ((-1)*matrix[i][j]);

	return abs_matrix;
}


/*
**
*/
template < class MatrixType>
Matrix<MatrixType>* Matrix<MatrixType>::add(Matrix<MatrixType> *m)
{
	if (row != m->row || col != m->col)
	{
		cout << "两个矩阵维数不匹配\n";
		return NULL;
	}
	Matrix<MatrixType> *res = new Matrix<MatrixType>(row, col);
	for (u_int i = 0; i < row; i++)
		for (u_int j = 0; j < col; j++)
			res->matrix[i][j] = matrix[i][j] + m->matrix[i][j];
	return res;
}

/*
**
*/
template < class MatrixType>
Matrix<MatrixType>* Matrix<MatrixType>::sub(Matrix<MatrixType> *m)
{
	if (row != m->row || col != m->col)
	{
		cout << "两个矩阵维数不匹配\n";
		return NULL;
	}
	Matrix<MatrixType> *res = new Matrix<MatrixType>(row, col);
	for (u_int i = 0; i < row; i++)
		for (u_int j = 0; j < col; j++)
			res->matrix[i][j] = matrix[i][j] - m->matrix[i][j];
	return res;
}

/*
**
*/
template < class MatrixType>
Matrix<MatrixType>* Matrix<MatrixType>::mul(Matrix<MatrixType> *m)
{
	if (this->col != m->row)
	{
		cout << "不符合矩阵乘法要求!" << endl;
		return NULL;
	}
	Matrix<MatrixType> *res = new Matrix<MatrixType>(row, m->col);
	for (u_int i = 0; i < res->row; i++)
	{
		for (u_int j = 0; j < res->col; j++)
		{
			res->matrix[i][j] = 0;
			for (u_int k = 0; k < this->col; k++)
			{
				res->matrix[i][j] += matrix[i][k] * m->matrix[k][j];
			}
		}
	}
	return res;
}

template < class MatrixType>
Matrix<MatrixType>* Matrix<MatrixType>::div(Matrix<MatrixType> *m)
{
	return this->mul(m->inv());
}
/*
**数乘矩阵
*/
template < class MatrixType>
Matrix<MatrixType>* Matrix<MatrixType>::k(int r)
{
	Matrix<MatrixType> *res = new Matrix<MatrixType>(row, col);
	for (u_int i = 0; i < res->row; i++)
	{
		for (u_int j = 0; j < res->col; j++)
		{
			res->matrix[i][j] = matrix[i][j] * r;
		}
	}
	return res;
}

/*
**矩阵转置
*/
template < class MatrixType>
Matrix<MatrixType>* Matrix<MatrixType>::T()
{
	Matrix<MatrixType> *res = new Matrix<MatrixType>(col, row);
	for (u_int i = 0; i < row; i++)
	{
		for (u_int j = 0; j < col; j++)
		{
			res->matrix[j][i] = matrix[i][j];
		}
	}
	return res;
}
/*
**矩阵n次方
*/
template < class MatrixType>
Matrix<MatrixType>* Matrix<MatrixType>::pow(int n)
{
	Matrix<MatrixType> *res = new Matrix<MatrixType>(col, row);
	res = this->k(1);
	for (int i = 1; i < n; i++)
	{
		res = res->mul(this);
	}
	return res;
}
//运算符重载
template < class MatrixType>
Matrix<MatrixType>& Matrix<MatrixType>::operator +(Matrix<MatrixType> &m)
{
	return *(this->add(&m));
}

template < class MatrixType>
Matrix<MatrixType>& Matrix<MatrixType>::operator -(Matrix<MatrixType> &m)
{
	return *(this->sub(&m));
}

template < class MatrixType>
Matrix<MatrixType>& Matrix<MatrixType>::operator *(Matrix<MatrixType> &m)
{
	return *(this->mul(&m));
}

template < class MatrixType>
Matrix<MatrixType>& Matrix<MatrixType>::operator /(Matrix<MatrixType> &m)
{
	return *(this->div(&m));
}

template < class MatrixType>
Matrix<MatrixType>& Matrix<MatrixType>::operator *(int n)
{
	return *(this->k(n));
}
template < class MatrixType>
Matrix<MatrixType>& Matrix<MatrixType>::operator ^(int n)
{
	return *(this->pow(n));
}
/*********************selftest***************************/

void t_add()
{
	float a1[2][2] = { { 1, 2 }, { 4, 9 } };
	float a2[2][2] = { { 10, 20 }, { 9, 99 } };
	Matrix<float> m1 (2, 2, a1[0]);
	Matrix<float> m2 (2, 2, a2[0]);

	cout << "\n矩阵1\n";
	m1.print();
	cout << "\n矩阵2\n";
	m2.print();
	cout << "\n矩阵1 + 矩阵2\n";
	Matrix<float> m = m1 + m2;
	m.print();
	//delete m1;
	//delete m2;
//	delete m3;
}
void t_sub()
{
	float a1[2][2] = { { 1, 2 }, { 4, 9 } };
	float a2[2][2] = { { 10, 20 }, { 9, 99 } };
	Matrix<float>* m1 = new Matrix<float>(2, 2, a1[0]);
	Matrix<float>* m2 = new Matrix<float>(2, 2, a2[0]);
	Matrix<float>*m3;
	cout << "\n矩阵1\n";
	m1->print();
	cout << "\n矩阵2\n";
	m2->print();
	cout << "\n矩阵1 - 矩阵2\n";
	m3 = m1->sub(m2);
	m3->print();
	delete m1;
	delete m2;
	delete m3;
}

void t_abs()
{
	float a1[2][2] = { { 1, 2 }, { 4, 9 } };
	float a2[2][2] = { { 10, 20 }, { 9, 99 } };
	Matrix<float>* m1 = new Matrix<float>(2, 2, a1[0]);
	Matrix<float>* m2 = new Matrix<float>(2, 2, a2[0]);
	Matrix<float>* m3;
	cout << "\n矩阵1\n";
	m1->print();
	cout << "\n矩阵2\n";
	m2->print();
	cout << "\n|矩阵1 - 矩阵2|\n";
	m3 = m1->sub(m2)->abs();
	m3->print();
	delete m1;
	delete m2;
	delete m3;
}
/* test on matlab
>> m=[41,67,34,0;69,24,78,58;62,64,5,45]

m =

41    67    34     0
69    24    78    58
62    64     5    45

>> cov(m)

ans =

1.0e+003 *

0.2123   -0.2578    0.1890    0.4433
-0.2578    0.5763   -0.7875   -0.5248
0.1890   -0.7875    1.3510    0.3660
0.4433   -0.5248    0.3660    0.9263
*/
void t_cov()
{
	float a1[3][4] = { { 41, 67, 34, 0 }, { 69, 24, 78, 58 }, { 62, 64, 5, 45 } };
	Matrix<float>*m1 = new Matrix<float>(3, 4, a1[0]);
	Matrix<float>*m3;
	cout << "\n矩阵1\n";
	m1->print();
	cout << "\n矩阵1的协方差矩阵\n";
	m3 = m1->cov();
	m3->print();
	delete m1;
	delete m3;
}
/*

>> m1=[41,67,34,0;69,24,78,58;62,64,5,45]

m1 =

41    67    34     0
69    24    78    58
62    64     5    45

>> m3=[92,82,21,16,18;95,47,26,71,38;69,12,67,99,35;94,3,11,22,33]

m3 =

92    82    21    16    18
95    47    26    71    38
69    12    67    99    35
94     3    11    22    33

>> m1*m3

ans =

12483        6919        4881        8779        4474
19462        7896        7937       11806        6798
16359        8287        3796        7021        5208

>>
*/
void t_mul()
{
	float a1[3][4] = { { 41, 67, 34, 0 }, { 69, 24, 78, 58 }, { 62, 64, 5, 45 } };
	float a2[4][5] = { { 92, 82, 21, 16, 18 }, { 95, 47, 26, 71, 38 }, { 69, 12, 67, 99, 35 }, { 94, 3, 11, 22, 33 } };
	Matrix<float>*m1 = new Matrix<float>(3, 4, a1[0]);
	Matrix<float>*m2 = new Matrix<float>(4, 5, a2[0]);
	Matrix<float>*m3;
	cout << "\n矩阵1\n";
	m1->print();
	cout << "\n矩阵2\n";
	m2->print();
	cout << "\n矩阵1 * 矩阵2\n";
	m3 = m1->mul(m2);
	m3->print();
	delete m1;
	delete m2;
	delete m3;
}

/*
>> m=[41,67,34;69,24,78;62,64,5]

m =

41    67    34
69    24    78
62    64     5

>> inv(m)

ans =

-0.0243    0.0092    0.0220
0.0224   -0.0095   -0.0042
0.0146    0.0076   -0.0181

>>
*/
void t_inv()
{
	float a1[3][3] = { { 41, 67, 34 }, { 69, 24, 78 }, { 62, 64, 5 } };
	Matrix<float>*m1 = new Matrix<float>(3, 3, a1[0]);
	Matrix<float>*m3;
	cout << "\n矩阵1\n";
	m1->print();
	cout << "\n矩阵1的逆矩阵\n";
	m3 = m1->inv();
	m3->print();
	delete m1;
	delete m3;
}

/*
>> m=[41,67,34;69,24,78;62,64,5]
m =

41    67    34
69    24    78
62    64     5

>> m^3

ans =

1216511     1154908      829376
1371036     1164003     1134852
1154428     1087196      751517
*/
void t_pow()
{
	float a1[3][3] = { { 41, 67, 34 }, { 69, 24, 78 }, { 62, 64, 5 } };
	Matrix<float> m1(3, 3, a1[0]);
	cout << "\n矩阵1\n";
	m1.print();
	cout << "\n矩阵1的3次方\n";
	Matrix<float> m3 = m1^3 ;
	m3.print();
}
/*
**Matrix类自测试函数
*/
void selftest()
{
#define FUNC_NUM 7
	typedef void(*FUNC)(void);
	FUNC testfunc[FUNC_NUM] = { t_add, t_sub, t_abs, t_cov, t_mul, t_inv, t_pow };
	//while (1)  //测试内存泄露
	for (u_int i = 0; i < FUNC_NUM; i++)
	{
		cout << "-----------------" << i << "----------------" << endl;
		//cout << testfunc[i] << endl;;
		testfunc[i]();
	}

	int end;
	cin >> end;
}