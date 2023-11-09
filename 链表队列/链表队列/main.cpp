#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef struct Link {
	int data;
	struct Link* next;
}LinkNode,*LNode;

typedef struct Queue_s {
	LNode front;//��ͷ
	LNode rear;//��β
	int size;
}Queue,*QL;

void InitQueue(Queue& q) 
{
	q.front =q.rear= (LNode)calloc(1, sizeof(LinkNode));//calloc Ĭ�ϳ�ʼ��Ϊnull��0
	q.size = 0;
}
void EnQueue(Queue& q,int data)
{
	//������ͷ���Ķ���
	LNode newCur = (LNode)calloc(1, sizeof(LinkNode));
	if (q.size == 0) 
	{
		if (newCur == NULL) return;
		newCur->data = data;
		q.front->next = newCur;
		q.rear = q.front=newCur;//��֤rearָ��β��
	}
	else 
	{
		if (newCur == NULL) return;
		newCur->data = data;
		q.rear->next = newCur;
		q.rear = newCur;
	}
	++q.size;
}

void EnHeadQueue(Queue& q, int data)
{
	//��������ͷ���Ķ���
	LNode newCur = (LNode)calloc(1, sizeof(LinkNode));
	if (newCur == NULL) return;
	newCur->data = data;
	q.rear->next = newCur;
	q.rear = newCur;//��֤rearָ��β��
	++q.size;
}
void DeQueue(Queue& q,int &x)
{
	//�Ƚ��ȳ�
	//��ͷ���ĳ���
	if (q.size == 0) return;
	LNode Cur = q.front;
	x = Cur->data;
	q.front = Cur->next;//����
	if (Cur == q.rear)//��ʾͷָ���βָ��ָ��һ��λ��
	{
		q.rear = q.front;//������Ϊ��
	}
	free(Cur);
	--q.size;
}
void DeQueue(Queue& q, int& x)
{
	//�Ƚ��ȳ�
	//��ͷ���ĳ���
	if (q.size == 0) return;
	LNode Cur = q.front->next;
	x = Cur->data;
	q.front->next = Cur->next;//����
	if (Cur == q.rear)//��ʾͷָ���βָ��ָ��һ��λ��
	{
		q.rear = q.front;//������Ϊ��
	}
	free(Cur);
	--q.size;
}

int main()
{
	Queue Q;
	//��ʼ��
	InitQueue(Q);
	//β�巨
	EnQueue(Q, 1);
	EnQueue(Q, 2);
	EnQueue(Q, 3);
	//����
	int x;
	DeQueue(Q,x);
	DeQueue(Q, x);

	return 0;
}