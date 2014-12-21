#include<stdio.h>
#include<windows.h>
int main()
{
	int i;
	printf("downloading SwordGame from onestraw...\n");
	for(i=0; i<=100; i++)
	{
		printf("finish %d%%...\r",i);
		Sleep(100);
	}
	printf("\ndone\n");
	return 0;
} 
