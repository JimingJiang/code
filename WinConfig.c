#include<windows.h> 
//#include<iostream>  
//using namespace std;
#include<stdio.h>
int main(int argc, char *argv[])   
{        
	//��INI�ļ������һЩ��ֵ
	/*
		. ��ʾ��ǰĿ¼��������б�ܣ���һ����ʾת�壬����һ����ʾ·���ָ�
		����  .\\test.ini ��ʾ��ǰĿ¼�µ�test.ini�ļ�
	*/
	/*
		User: ����
		Name: ����
		OneStraw.Net: ��ֵ
		.\\test.ini: ini�ļ���
	*/
//	WritePrivateProfileString ("User", "Name", "OneStraw.Net", ".\\test.ini");   
//	WritePrivateProfileString ("User", "Age", "23", ".\\test.ini");   
    
	char name[100];
	int age = 0;  
	/*
	* ��test.ini�ļ��е�[User]����,���Ҽ���ΪName ��ֵ��
	* ���û���ҵ���������ѵ�����������Not Find������name��
	* name��һ����СΪ100�Ļ�����
	*/
	GetPrivateProfileString ("User", "Name", "Not Find", name, 100, ".\\test.ini");  
	/*
	* ���Ƶأ��˺������ҵ���ֵ���ظ�age
	*���û���ҵ�����ΪAge�Ĳ�������22��ΪĬ��ֵ����
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