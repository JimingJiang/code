/*
**������ص�һЩ����
**1.�����ַ���������֮���ת��
**2.���봫��
**3.����1000101 -> 11���Լ���任
**4.��ȡ��ʽ�ļ���ָ����
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