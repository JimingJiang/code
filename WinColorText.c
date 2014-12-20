#include<stdio.h>
#include <windows.h>
/*
*功能：
	输出彩色字符串
*输入参数：
	color:颜色选择，1 red, 2 green, 3 yellow, default white
	str: 彩色字符串
*/
void printColorStr(int color, char *str)
{
	HANDLE hd;

    hd = GetStdHandle(STD_OUTPUT_HANDLE);
	switch(color)
	{
		case 1: //red
			SetConsoleTextAttribute(hd,
									FOREGROUND_RED |
									FOREGROUND_INTENSITY);
			break;
		case 2: //green
			 SetConsoleTextAttribute(hd,
								FOREGROUND_GREEN |
								FOREGROUND_INTENSITY);
			break;
		case 3: //yellow
			SetConsoleTextAttribute(hd,
								FOREGROUND_RED | 
								FOREGROUND_GREEN |
								FOREGROUND_INTENSITY);
			break;
		default://white
			SetConsoleTextAttribute(hd,
								FOREGROUND_RED | 
								FOREGROUND_GREEN | 
								FOREGROUND_BLUE);
	}

	printf("%s",str);
}
/*
*功能:
	输入彩色闪烁字符串
*输入参数：
	count:闪烁次数
	str:修饰的字符串
*/
void printTwinkleStr(int count, char *str)
{
	int i,len;
	char *cstr;
	len = strlen(str);
	cstr = (char*)malloc(sizeof(char)*(len+2));
	sprintf(cstr, "%s\r", str);
	if(count%4==0)
		count++;
	for(i=1; i<=count; i++)
	{
		printColorStr(i%4, cstr);
		Sleep(1000);
	}
	printColorStr(4,"\n");
}
//
int main()
{
    printTwinkleStr(6, "---->文字闪烁<----");
    return 0;
}