#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;

//����ʵս
typedef struct Lnode{
	int data;//������
	struct Lnode* next;//ָ����
}LinkList,*List;

//ͷ�巨
void insert_head(List& l)
{
	l = (List)malloc(sizeof(LinkList));
	l->next=NULL;
	cout << "������Ҫ���������,999��ʾ��������" << endl;
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

//��������
void printList(List l)
{
	l = l->next;//����һ���ڵ�
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
	List L;//���������ͷ��
	insert_head(L);//ͷ�巨
	printList(L);//��������


	return 0;
}