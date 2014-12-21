#include<stdio.h>
#include <windows.h>
/*
*���ܣ�
	�����ɫ�ַ���
*���������
	color:��ɫѡ��1 red, 2 green, 3 yellow, default white
	str: ��ɫ�ַ���
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
*����:
	�����ɫ��˸�ַ���
*���������
	count:��˸����
	str:���ε��ַ���
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
    printTwinkleStr(6, "---->������˸<----");
    return 0;
}