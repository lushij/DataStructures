#include"main.h"
//创建Prolist头结点
Prolist* createProHeadList()
{
	Prolist* HeadList = NULL;
	HeadList = (Prolist*)calloc(1, sizeof(Prolist));
	HeadList->next = NULL;
	return HeadList;
}

//创建Prolist节点
Prolist* createProNode(PropertyInfo data)
{
	Prolist* newNode = (Prolist*)calloc(1, sizeof(Prolist));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

//添加Prolist信息
void insertProlist(Prolist*& Head, PropertyInfo data)
{
	Prolist* newList = createProNode(data);
	newList->next = Head->next;
	Head->next = newList;
}

//
//遍历房地产信息
void insearchPro(Prolist* Head)
{
	Prolist* Move = Head->next;
	printf("编号\t朝向\t楼层(总层数_层位)\t面积\t价格\t购买意向的人数\n");
	while (Move != NULL)
	{
		printf("%d\t%s\t%s\t%s\t%d\t%d\n"
			, Move->data.id, Move->data.direct, Move->data.floor, Move->data.Sarea, Move->data.price, Move->data.cnt);
		Move = Move->next;
	}
}
//
//链表读取Source文件操作
void readSource(Prolist* headNode, const char* fileURL)
{
	FILE* fp = fopen(fileURL, "r");
	if (fp == NULL)
	{
		fp = fopen(fileURL, "w");
		fclose(fp);
		return;
	}
	PropertyInfo tmp;
	while (fscanf(fp, "%d\t%s\t%s\t%s\t%d\t%d\n", &tmp.id, tmp.direct, tmp.floor, tmp.Sarea, &tmp.price, &tmp.cnt) != EOF)
	{
		insertProlist(headNode, tmp);
	}
	fclose(fp);
}
//
//链表写Source文件
void saveSource(Prolist* headNode, const char* fileURL)
{
	FILE* fp = fopen(fileURL, "w");
	Prolist* Move = headNode->next;
	while (Move)
	{
		fprintf(fp, "%d\t%s\t%s\t%s\t%d\t%d\n",
			Move->data.id, Move->data.direct, Move->data.floor, Move->data.Sarea, Move->data.price, Move->data.cnt);
		Move = Move->next;
	}
	fclose(fp);
}