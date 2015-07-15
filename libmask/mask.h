/*
**掩码相关的一些操作
**1.掩码字符串与整数之间的转换
**2.掩码传参
**3.掩码1000101 -> 11，以及逆变换
**4.读取格式文件的指定列
*/

#ifndef _MASK_H
#define _MASK_H

#include<iostream>
#include<string>
using namespace std;

typedef	unsigned int u_int;
typedef	unsigned long u_long;


class Mask
{
public:
	Mask(string s);
	~Mask();

	bool test(u_long i);
	//bool set(u_long i);
	//bool reset(u_long i);
	u_long valid_bits();
	u_long unvalid_bits();
	long map(u_long i);
	long unmap(u_long i);
private:
	string mask;
	u_long len;
};


void selftest();

#endif