#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
using namespace std;
typedef struct que_t {
	int data;
	struct que_t* next;
}Q, * Qu;
typedef struct lq_t {
	Qu front;
	Qu rear;
}Lq, * lq;

void insertQ(lq& l)
{
	int num = 0;
	cout << "��������Ҫ���������" << endl;
	scanf("%d", &num);
	while (num != 999)
	{
		//��ǰ�ڵ� 
		//�����µ�����ڵ� 
		Qu cur = (Qu)malloc(sizeof(Q));
		cur->data = num;
		cur->next = NULL;
		l->rear->next = cur;
		l->rear = cur;
		scanf("%d", &num);
	}
}

void search(lq& l)
{
	Qu cur;
	cur = l->front->next;
	int num = 0;
	cout << "��������Ҫ���ҵ�����" << endl;
	scanf("%d", &num);
	bool found = false;
	while (cur)
	{
		if (num == cur->data)
		{
			cout << "�ҵ���" << endl;
			found = true;
			break;
		}
		else {
			cur = cur->next;
		}
	}
	if (!found) cout << "δ�ҵ�" << endl;
}

//�������ݡ�
void popLq(lq& l)
{
	int num = 0;
	while (l->front != l->rear)
	{
		//����ͷ�� ע���һ���ڵ�Ϊ����ͷ�ڵ㣬���������ݴӵ�һ���ڵ����һ����ʼ 
		num = l->front->next->data;
		l->front = l->front->next;
		cout << num << " ";
	}
	cout << endl;
}
int main()
{
	//�����Ƚ��ȳ�
	//������� 
	lq q = (lq)malloc(sizeof(Lq));
	//�������� 
	q->front = q->rear = (Qu)malloc(sizeof(Q));
	insertQ(q);
	//��������
	search(q);
	//��������
	popLq(q);
	return 0;
}
