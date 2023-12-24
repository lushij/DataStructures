#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<stdio.h>
using namespace std;
typedef struct BiNode {
	int tag;
	char name[10];
	char birth[20];
	char marry[5];
	char address[20];
	char exist[5];
	char death[20];
	BiNode* lchild, * rchild, * parent, * lsib;
	int flag_self;
	//��ʾ����ڵ��Ƿ����ã�flag_self��ʾ��Ч
	//����ɾ����
}BiNode, * BiTree;
typedef struct QNode {
	BiTree data;
	QNode* next;
}QNode, * Qptr;
typedef struct {
	Qptr head, rear;
}Queue;
void InitQueue(Queue& Q)
{
	Q.head = Q.rear = (Qptr)malloc(sizeof(QNode));
	Q.rear->next = NULL;
	Q.head->next = NULL;
}
void EnQueue(Queue& Q, Qptr e)
{
	Q.rear->next = e;
	Q.rear = e;
}
BiTree DeQueue(Queue& Q)
{
	Qptr p = Q.head->next;
	Q.head->next = p->next;
	if (Q.head->next == NULL)
		Q.rear = Q.head;
	return p->data;
}
void create(BiTree& bt, char str[], Queue& Q)
{
	static int i = 0;
	char ch;
	ch = str[i++];
	if (ch == '.')
	{
		bt = NULL;
	}
	else {
		bt = (BiTree)malloc(sizeof(BiNode));
		BiTree p = DeQueue(Q);
		strcpy(bt->name, p->name);
		strcpy(bt->address, p->address);
		strcpy(bt->birth, p->birth);
		strcpy(bt->death, p->death);
		strcpy(bt->exist, p->exist);
		strcpy(bt->marry, p->marry);
		create(bt->lchild, str, Q);
		create(bt->rchild, str, Q);
	}
}
void level(BiTree T)
{
	int t;
	Queue Q;
	BiTree W, S;
	InitQueue(Q);
	T->parent = NULL;
	T->lsib = NULL;
	T->tag = 1;
	Qptr p = (Qptr)malloc(sizeof(QNode));
	p->data = T;
	p->next = NULL;
	EnQueue(Q, p);
	while (Q.head != Q.rear)
	{
		if (T)
		{
			W = T;
			t = T->tag;
			while (T->rchild)
			{
				S = T;
				T = T->rchild;
				T->parent = W->parent;
				T->lsib = S;
				T->tag = t;
				Qptr p = (Qptr)malloc(sizeof(QNode));
				p->data = T;
				p->next = NULL;
				EnQueue(Q, p);
			}
		}
		T = DeQueue(Q);
		cout << T->name << " " << T->birth << " " << T->marry << " " << T->address << " " << T->exist << " " << T->death << endl;
		t = T->tag;
		W = T;
		T = T->lchild;
		if (T)
		{
			T->tag = t + 1;
			T->parent = W;
			T->lsib = NULL;
			Qptr p = (Qptr)malloc(sizeof(QNode));
			p->data = T;
			p->next = NULL;
			EnQueue(Q, p);
		}
	}
}
void level2(BiTree T)
{
	int x;
	cout << "�����������" << endl;
	cin >> x;
	Queue Q;
	InitQueue(Q);
	Qptr p = (Qptr)malloc(sizeof(QNode));
	p->data = T;
	p->next = NULL;
	EnQueue(Q, p);
	while (Q.head != Q.rear)
	{
		if (T)
		{
			while (T->rchild)
			{
				T = T->rchild;
				Qptr p = (Qptr)malloc(sizeof(QNode));
				p->data = T;
				p->next = NULL;
				EnQueue(Q, p);
			}
		}
		T = DeQueue(Q);
		if (T->tag == x)
			cout << T->name << " " << T->birth << " " << T->marry << " " << T->address << " " << T->exist << " " << T->death << endl;
		T = T->lchild;
		if (T)
		{

			Qptr p = (Qptr)malloc(sizeof(QNode));
			p->data = T;
			p->next = NULL;
			EnQueue(Q, p);
		}
	}
}
void Birth(BiTree T, char s[])
{
	if (T)
	{
		if (strcmp(T->birth, s) == 0)
		{
			cout << T->name << " " << T->birth << " " << T->marry << " " << T->address << " " << T->exist << " " << T->death << endl;
		}
		else {
			Birth(T->lchild, s);
			Birth(T->rchild, s);
		}
	}
}

void name2(BiTree& T, char name[], BiTree& p)
{
	if (T)
	{
		if (strcmp(T->name, name) == 0)
		{
			p = T;
		}
		else {
			name2(T->lchild, name, p);
			name2(T->rchild, name, p);
		}
	}
}
void Name(BiTree T, char name[])
{
	BiTree p, q;
	name2(T, name, p);
	cout << endl;
	if (p->parent)
	{
		cout << "������Ϣ��" << endl;
		cout << p->parent->name << " " << p->parent->birth << " " << p->parent->address << " " << p->parent->exist << " " << p->parent->death << " " << p->parent->marry << endl;
	}
	cout << endl;
	cout << "������Ϣ��" << endl;
	cout << p->name << " " << p->birth << " " << p->address << " " << p->exist << " " << p->death << " " << p->marry << endl;
	cout << endl;
	q = p->lchild;
	if (q)
	{
		cout << "������Ϣ��" << endl;
		while (q)
		{
			cout << q->name << " " << q->birth << " " << q->address << " " << q->exist << " " << q->death << " " << q->marry << endl;
			q = q->rchild;
		}
	}
	cout << endl;
}
void add(BiTree& T, char name[], BiTree& t)
{
	BiTree p, q;
	name2(T, name, p);
	if (p->lchild == NULL)
	{
		p->lchild = t;
		t->tag = p->tag + 1;
	}
	else {
		q = p->lchild;
		while (q->rchild)
		{
			q = q->rchild;
		}
		q->rchild = t;
		t->tag = q->tag;
	}
}
void change(BiTree T, char name[], char death[])
{
	if (T)
	{
		if (strcmp(T->name, name) == 0)
		{
			strcpy(T->death, death);
		}
		else {
			change(T->lchild, name, death);
			change(T->rchild, name, death);
		}
	}
}
void Delete(BiTree& T, char name[])
{
	BiTree p;
	name2(T, name, p);
	p->lchild = NULL;
	if (p->lsib == NULL)
	{
		p->parent->lchild = p->rchild;

	}
	else {
		p->lsib->rchild = p->rchild;
	}
}
void relation(BiTree T, char nameA[], char nameB[])
{
	cout << endl;
	BiTree p, q;
	name2(T, nameA, p);
	name2(T, nameB, q);
	if (p->parent == q || q->parent == p)
		cout << "�Ǹ��ӹ�ϵ" << endl;
	if (p->parent == q->parent)
		cout << "���ֵܹ�ϵ" << endl;
	cout << endl;
}

void SaveToFile(BiTree T)
{
	fstream file;
	file.open("newData.txt", ios::out);
	Queue Q;
	InitQueue(Q);
	Qptr p = (Qptr)malloc(sizeof(QNode));
	p->data = T;
	p->next = NULL;
	EnQueue(Q, p);

	while (Q.head != Q.rear)
	{
		if (T)
		{
			while (T->rchild)
			{
				T = T->rchild;
				Qptr p = (Qptr)malloc(sizeof(QNode));
				p->data = T;
				p->next = NULL;
				EnQueue(Q, p);
			}
		}
		T = DeQueue(Q);
		file << T->name << " " << T->birth << " " << T->marry << " " << T->address << " " << T->exist << " " << T->death << endl;

		T = T->lchild;
		if (T)
		{
			Qptr p = (Qptr)malloc(sizeof(QNode));
			p->data = T;
			p->next = NULL;
			EnQueue(Q, p);
		}
	}
	file.close();
	cout << "����ɹ���" << endl;
}


void Operate()
{
	fstream file;
	file.open("����.txt", ios::in);
	Queue Q;
	InitQueue(Q);
	BiTree T, t;
	char name[10], name1[20];
	char birth[20];
	char marry[5];
	char address[20];
	char exist[5];
	char death[20];
	for (int i = 0; i < 20; i++)
	{
		file >> name;
		file >> birth;
		file >> marry;
		file >> address;
		file >> exist;
		file >> death;
		BiTree p = (BiTree)malloc(sizeof(BiNode));
		strcpy(p->name, name);
		strcpy(p->birth, birth);
		strcpy(p->marry, marry);
		strcpy(p->address, address);
		strcpy(p->exist, exist);
		strcpy(p->death, death);
		p->rchild = NULL;
		p->lchild = NULL;
		Qptr q = (Qptr)malloc(sizeof(QNode));
		q->data = p;
		q->next = NULL;
		EnQueue(Q, q);
	}
	file.close();
	char str[50] = "AAAA.A..A.AA.A.A..A..A.A.AA.AA.A..A..A...";
	create(T, str, Q);
	cout << "�������ף�" << endl;
	level(T);
	cout << endl;
	int choice;
	while (1)
	{
		cout << "1. ��ʾĳһ����Ա��Ϣ  " << endl;
		cout << endl;
		cout << "2. ����������ѯ " << endl;
		cout << endl;
		cout << "3. ���ճ������ڲ�ѯ " << endl;
		cout << endl;
		cout << "4. ��ѯ���˹�ϵ" << endl;
		cout << endl;
		cout << "5. ĳ��Ա��Ӻ���" << endl;
		cout << endl;
		cout << "6. ɾ��ĳ��Ա " << endl;
		cout << endl;
		cout << "7. �޸�ĳ��Ա��Ϣ" << endl;
		cout << endl;
		cout << "8. �˳�" << endl;
		cout << endl;
		cout << "9. ������Ϣ" << endl;
		cout << endl;
		cout << "���������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			level2(T);
			break;
		case 2:
			cout << "���������ѯ��Ա������" << endl;
			cin >> name;
			Name(T, name);
			break;
		case 3:
			char s[20];
			cout << "���������ѯ��Ա���գ�" << endl;
			cin >> s;
			cout << "�ó�Ա��Ϣ���£�" << endl;
			Birth(T, s);
			break;
		case 4:
			cout << "�������һ���������Ա��" << endl;
			cin >> name1;
			cout << "������ڶ����������Ա��" << endl;
			cin >> name;
			relation(T, name1, name);
			break;
		case 5:
			cout << "��������޸ĳ�Ա������" << endl;
			cin >> name1;
			cout << "�����뺢��������     ";
			cin >> name;
			cout << "�����뺢�ӳ������ڣ� ";
			cin >> birth;
			cout << "�����뺢�ӻ���״���� ";
			cin >> marry;
			cout << "�����뺢�ӵ�ַ��     ";
			cin >> address;
			cout << "�����뺢�ӽ��ڷ�   ";
			cin >> exist;
			cout << "�����뺢����������� ";
			cin >> death;
			t = (BiTree)malloc(sizeof(BiNode));
			strcpy(t->name, name);
			strcpy(t->address, address);
			strcpy(t->birth, birth);
			strcpy(t->exist, exist);
			strcpy(t->marry, marry);
			strcpy(t->death, death);
			t->lchild = NULL;
			t->rchild = NULL;
			add(T, name1, t);
			cout << endl;
			cout << "��Ӻ��������£�" << endl;
			level(T);
			break;
		case 6:
			cout << endl;
			cout << "�������ɾ����Ա������" << endl;
			cin >> name;
			Delete(T, name);
			cout << "ɾ�������Ϊ��" << endl;
			level(T);
			break;
		case 7:
			cout << "��������޸ĳ�Ա������" << endl;
			cin >> name;
			char death[20];
			cout << "�������޸ĺ������״̬��" << endl;
			cin >> death;
			change(T, name, death);
			cout << "�޸ĺ����Ϊ��" << endl;
			level(T);
			break;
		case 8:
			exit(0);
			break;
		case 9:
			SaveToFile(T);
			break;
		}
	}
}

int main()
{
	Operate();
	return 0;
}
