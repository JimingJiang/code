#include<windows.h> 
//#include<iostream>  
//using namespace std;
#include<stdio.h>
int main(int argc, char *argv[])   
{        
	//向INI文件中添加一些键值
	/*
		. 表示当前目录，两个反斜杠，有一个表示转义，另外一个表示路径分隔
		所以  .\\test.ini 表示当前目录下的test.ini文件
	*/
	/*
		User: 段名
		Name: 键名
		OneStraw.Net: 键值
		.\\test.ini: ini文件名
	*/
//	WritePrivateProfileString ("User", "Name", "OneStraw.Net", ".\\test.ini");   
//	WritePrivateProfileString ("User", "Age", "23", ".\\test.ini");   
    
	char name[100];
	int age = 0;  
	/*
	* 在test.ini文件中的[User]段中,查找键名为Name 的值，
	* 如果没有找到这个键，把第三个参数“Not Find”赋给name，
	* name是一个大小为100的缓冲区
	*/
	GetPrivateProfileString ("User", "Name", "Not Find", name, 100, ".\\test.ini");  
	/*
	* 类似地，此函数将找到的值返回给age
	*如果没有找到键名为Age的参数，把22作为默认值返回
	*/
	age = GetPrivateProfileInt("User", "Age", 22, ".\\test.ini");  
	
	printf("Name=%s\nAge=%d\n",name, age);

	char bbuf[16];
	unsigned int mask = 0;
	scanf("%s",bbuf);
	int len = strlen(bbuf);
	int i;
	for(i=0; i<len; i++)
	{
		mask = mask*2 + bbuf[i]-'0';
	}
	printf("%u\n",mask);
	return 0;
}  