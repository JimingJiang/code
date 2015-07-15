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
**测试mask第i位(0<=i<len)是否是'1'
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
**统计mask中'1'的个数
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
**统计mask中'0'的个数
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
**将mask的第i位(0<=i<len)映射到其在所有的有效位'1'中的次序n(0 <= n < len)
**如mask="1001001000"
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
**将mask的有效位次序x(0 <= x < len)还原到其在整个mask中的位置n(1 <= n < len)
**如mask="1001001000"
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
**Mask类自测试函数
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