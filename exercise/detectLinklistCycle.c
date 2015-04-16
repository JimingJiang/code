#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	char value;
	struct Node *next;
}Node;

void constructCycleLinlist(Node *head)
{
	int i;
	Node *newNode, *p;
	p = head;
	for(i=0; i<10000; i++)
	{
		newNode = (Node*)malloc(sizeof(Node));
		newNode->value = 'A';
		newNode->next = NULL;
		p->next = newNode;
		p = p->next;
	}
	//构造环，注释掉可测试无循环的情形 
	p = head;
	for(i=0; i<10; i++)
		p = p->next;
	newNode->next = p;
}

void detectCycle(Node *head)
{
	Node *p1, *p2;
	p1 = head;
	p2 = head->next->next;
	
	while(p1 != p2)
	{
		if(p1 && p1->next)
			p1=p1->next;
		else
			p1=NULL;
		
		if(p2 && p2->next && p2->next->next)
			p2 = p2->next->next;
		else
			p2 = NULL;
	}
	if(p1==NULL)
		printf("no cycle\n");
	else
		printf("find cycle\n");
}

int main()
{
	Node *head;
	head = (Node*)malloc(sizeof(Node));
	constructCycleLinlist(head);
	detectCycle(head);
	return 0;
}
 
