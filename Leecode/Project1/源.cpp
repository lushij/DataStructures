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
	cout << "请输入你要插入的数据" << endl;
	scanf("%d", &num);
	while (num != 999)
	{
		//当前节点 
		//创建新的链表节点 
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
	cout << "请输入你要查找的数据" << endl;
	scanf("%d", &num);
	bool found = false;
	while (cur)
	{
		if (num == cur->data)
		{
			cout << "找到了" << endl;
			found = true;
			break;
		}
		else {
			cur = cur->next;
		}
	}
	if (!found) cout << "未找到" << endl;
}

//弹出数据、
void popLq(lq& l)
{
	int num = 0;
	while (l->front != l->rear)
	{
		//弹出头部 注意第一个节点为虚拟头节点，弹出的数据从第一个节点的下一个开始 
		num = l->front->next->data;
		l->front = l->front->next;
		cout << num << " ";
	}
	cout << endl;
}
int main()
{
	//队列先进先出
	//定义队列 
	lq q = (lq)malloc(sizeof(Lq));
	//定义链表 
	q->front = q->rear = (Qu)malloc(sizeof(Q));
	insertQ(q);
	//查找数据
	search(q);
	//弹出数据
	popLq(q);
	return 0;
}
