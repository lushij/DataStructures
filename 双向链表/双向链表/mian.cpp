#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef struct node_s {
	int val;
	struct node_s* next;
	struct node_s* proc;
}Node, * Dnode;

bool initDnode(Dnode& l)
{
	l = (Dnode)malloc(sizeof(Node));
	if (l == NULL)
	{
		return false;
	}
	l->next = NULL;
	l->proc = NULL;
	return true;
}
bool insertDnode(Dnode& l, int val)
{
	Dnode body = (Dnode)malloc(sizeof(Node));//
	if (body == NULL)
	{
		return false;
	}
	body->next = l->next;
	if (l->next != NULL)
	{
		l->next->proc = body;
	}
	l->next = body;
	body->proc = l;
	body->val = val;
	return true;
}
void traverse(Dnode l)
{
	l = l->next;//ÐéÄâÍ·½áµã£¬ÉÚ±ø
	while (l != NULL)
	{
		cout <<l->val << " ";
		l = l->next;
	}
	cout << endl;
}
int main()
{
	Dnode l;
	initDnode(l);
	int val = 0;
	insertDnode(l, val);
	insertDnode(l, 2);
	insertDnode(l, 3);
	cout << l->next->next->next->proc->val<<endl;
	traverse(l);
	return 0;
}