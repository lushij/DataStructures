#include"main.h"
//创建slist头结点
slist* createSHeadList()
{
	slist* HeadList = NULL;
	HeadList = (slist*)calloc(1, sizeof(slist));
	HeadList->next = NULL;
	return HeadList;
}
//创建slist节点
slist* createSNode(soldInfo data)
{
	slist* newNode = (slist*)calloc(1, sizeof(slist));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}
//添加slist信息
void insertSlist(slist*& Head, soldInfo data)
{
	slist* newList = createSNode(data);
	newList->next = Head->next;
	Head->next = newList;
}

//链表读取sold文件操作
void readSold(slist* headNode, const char* fileURL)
{
	FILE* fp = fopen(fileURL, "r");
	if (fp == NULL)
	{
		fp = fopen(fileURL, "w");
		fclose(fp);
		return;
	}
	soldInfo tmp;
	while (fscanf(fp, "%d\t%s\t%d\t%s\t%s\t%s\t%s\n", tmp.id,tmp.Sarea,tmp.price,tmp.time,tmp.Cno,tmp.hname,tmp.phone) != EOF)
	{
		insertSlist(headNode, tmp);
	}
	fclose(fp);
}
//链表写sold文件
void saveSold(slist* headNode, const char* fileURL)
{
	FILE* fp = fopen(fileURL, "a+");
	slist* Move = headNode->next;
	while (Move)
	{
		fprintf(fp, "%d\t%s\t%d\t%s\t%s\t%s\t%s\n",
			Move->data.id, Move->data.Sarea, Move->data.price, Move->data.time, Move->data.Cno,Move->data.hname,Move->data.phone);
		Move = Move->next;
	}
	fclose(fp);
}