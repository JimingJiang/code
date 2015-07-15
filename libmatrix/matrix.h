/*
**matrix.h
**
**矩阵运算
**
**2014-10-27
*/

#ifndef _MATRIX_H
#define _MATRIX_H

#include<iostream>
using namespace std;

typedef unsigned int u_int;


//template < typename MatrixType>
template < class MatrixType>
class Matrix
{
public:
	Matrix(u_int row, u_int col);
	Matrix(u_int row, u_int col, MatrixType*arr);
	Matrix(Matrix &);
	~Matrix();
	
	void print();
	Matrix<MatrixType>* cov();//covariance
	Matrix<MatrixType>* inv();//inverse
	Matrix<MatrixType>* abs();//
	Matrix<MatrixType>* add(Matrix<MatrixType> *m);
	Matrix<MatrixType>* sub(Matrix<MatrixType> *m);
	Matrix<MatrixType>* mul(Matrix<MatrixType> *m);
	Matrix<MatrixType>* div(Matrix<MatrixType> *m);
	Matrix<MatrixType>* k(int );
	Matrix<MatrixType>* T();
	Matrix<MatrixType>* pow(int );
	//运算符重载
	Matrix<MatrixType>& operator +(Matrix<MatrixType> &);
	Matrix<MatrixType>& operator -(Matrix<MatrixType> &);
	Matrix<MatrixType>& operator *(Matrix<MatrixType> &);
	Matrix<MatrixType>& operator /(Matrix<MatrixType> &);
	Matrix<MatrixType>& operator *(int);
	Matrix<MatrixType>& operator ^(int);
private:
	u_int row;
	u_int col;
	MatrixType **matrix;

	void _init(u_int row, u_int col);
};


void selftest();

#endif