/*
** mask.cpp
*/

#include"mask.h"

Mask::Mask(string s)
{
	mask = s;
	len = s.length();
}

Mask::~Mask()
{
}
/*
**����mask��iλ(0<=i<len)�Ƿ���'1'
*/
bool Mask::test(u_long i)
{
	if (i >= len)
		return false;
	else if (mask[i] == '1')
		return true;
	else
		return false;
}
/*
**ͳ��mask��'1'�ĸ���
*/
u_long Mask::valid_bits()
{
	u_long cnt = 0;
	for (u_long i = 0; i < len; i++)
	{
		if (test(i))
			cnt++;
	}
	return cnt;
}
/*
**ͳ��mask��'0'�ĸ���
*/
u_long Mask::unvalid_bits()
{
	u_long cnt = 0;
	for (u_long i = 0; i < len; i++)
	{
		if (!test(i))
			cnt++;
	}
	return cnt;
}
/*
**��mask�ĵ�iλ(0<=i<len)ӳ�䵽�������е���Чλ'1'�еĴ���n(0 <= n < len)
**��mask="1001001000"
**map(6)=2
*/
long Mask::map(u_long x)
{
	long n = 0;
	if (!test(x))
		return -1;
	for (u_long i = 0; i <= x; i++)
	{
		if (test(i))
			n++;
	}
	return n-1;
}
/*
**��mask����Чλ����x(0 <= x < len)��ԭ����������mask�е�λ��n(1 <= n < len)
**��mask="1001001000"
**map(6)=2
**unmap(2)=6
*/
long Mask::unmap(u_long x)
{
	if (x >= len)
		return -1;
	u_long n = 0;
	u_long i = 0;
	x++;
	for (i = 0; i < len && n < x; i++)
	{
		if (test(i))
			n++;
	}
	if (n == x)
		return i-1;
	else
		return -1;
}
/*
**Mask���Բ��Ժ���
*/
void selftest()
{
	string mask("00000000000010110101110011100001111111111100111111");
	cout << "mask: " << mask << endl;

	cout << "mask" << "\tmap" << "\tunmap" << endl;

	Mask *m = new Mask(mask);
	long tmp;
	for (int i = 0; i < mask.length(); i++)
	{
		if ((tmp = m->map(i)) >= 0)
			cout << i << "\t" << tmp << "\t" << m->unmap(tmp) << endl;

	}
	delete m;
}