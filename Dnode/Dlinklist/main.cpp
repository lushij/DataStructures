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

bool initDnode(Dnode &l)
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
	Dnode body = (Dnode)malloc(sizeof(Node));//创建新的节点
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

int main()
{
	Dnode l;
	initDnode(l);
	int val = 0;
	insertDnode(l, val);
	insertDnode(l, 2);
	insertDnode(l, 3);
	cout << l->next->next->next->proc->val;
	return 0;
}