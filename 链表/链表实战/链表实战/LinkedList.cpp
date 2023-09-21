#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;

//链表实战
typedef struct Lnode{
	int data;//数据域
	struct Lnode* next;//指针域
}LinkList,*List;

//头插法
void insert_head(List& l)
{
	l = (List)malloc(sizeof(LinkList));
	l->next=NULL;
	cout << "请输入要插入的数据,999表示结束插入" << endl;
	int num;
	cin >> num;
	while (num!=999)
	{
		List s = (List)malloc(sizeof(LinkList));
		s->data = num;
		s->next = l->next;
		l->next = s;
		cin >> num;
	}

}

//遍历链表
void printList(List l)
{
	l = l->next;//到第一个节点
	while (l!=NULL)
	{
		cout << l->data;
		l = l->next;
		if (l != NULL)
		{
			cout << " ";
		}
	}
	cout << endl;
}
int main()
{
	List L;//定义链表的头部
	insert_head(L);//头插法
	printList(L);//遍历链表


	return 0;
}