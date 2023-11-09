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
	LNode front;//队头
	LNode rear;//队尾
	int size;
}Queue,*QL;

void InitQueue(Queue& q) 
{
	q.front =q.rear= (LNode)calloc(1, sizeof(LinkNode));//calloc 默认初始化为null和0
	q.size = 0;
}
void EnQueue(Queue& q,int data)
{
	//不含有头结点的队列
	LNode newCur = (LNode)calloc(1, sizeof(LinkNode));
	if (q.size == 0) 
	{
		if (newCur == NULL) return;
		newCur->data = data;
		q.front->next = newCur;
		q.rear = q.front=newCur;//保证rear指向尾部
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
	//含有虚拟头结点的队列
	LNode newCur = (LNode)calloc(1, sizeof(LinkNode));
	if (newCur == NULL) return;
	newCur->data = data;
	q.rear->next = newCur;
	q.rear = newCur;//保证rear指向尾部
	++q.size;
}
void DeQueue(Queue& q,int &x)
{
	//先进先出
	//无头结点的出队
	if (q.size == 0) return;
	LNode Cur = q.front;
	x = Cur->data;
	q.front = Cur->next;//断链
	if (Cur == q.rear)//表示头指针和尾指针指向一个位置
	{
		q.rear = q.front;//队列置为空
	}
	free(Cur);
	--q.size;
}
void DeQueue(Queue& q, int& x)
{
	//先进先出
	//有头结点的出队
	if (q.size == 0) return;
	LNode Cur = q.front->next;
	x = Cur->data;
	q.front->next = Cur->next;//断链
	if (Cur == q.rear)//表示头指针和尾指针指向一个位置
	{
		q.rear = q.front;//队列置为空
	}
	free(Cur);
	--q.size;
}

int main()
{
	Queue Q;
	//初始化
	InitQueue(Q);
	//尾插法
	EnQueue(Q, 1);
	EnQueue(Q, 2);
	EnQueue(Q, 3);
	//出队
	int x;
	DeQueue(Q,x);
	DeQueue(Q, x);

	return 0;
}