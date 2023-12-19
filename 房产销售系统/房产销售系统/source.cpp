#include"main.h"
//����Prolistͷ���
Prolist* createProHeadList()
{
	Prolist* HeadList = NULL;
	HeadList = (Prolist*)calloc(1, sizeof(Prolist));
	HeadList->next = NULL;
	return HeadList;
}

//����Prolist�ڵ�
Prolist* createProNode(PropertyInfo data)
{
	Prolist* newNode = (Prolist*)calloc(1, sizeof(Prolist));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

//���Prolist��Ϣ
void insertProlist(Prolist*& Head, PropertyInfo data)
{
	Prolist* newList = createProNode(data);
	newList->next = Head->next;
	Head->next = newList;
}

//
//�������ز���Ϣ
void insearchPro(Prolist* Head)
{
	Prolist* Move = Head->next;
	printf("���\t����\t¥��(�ܲ���_��λ)\t���\t�۸�\t�������������\n");
	while (Move != NULL)
	{
		printf("%d\t%s\t%s\t%s\t%d\t%d\n"
			, Move->data.id, Move->data.direct, Move->data.floor, Move->data.Sarea, Move->data.price, Move->data.cnt);
		Move = Move->next;
	}
}
//
//�����ȡSource�ļ�����
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
//����дSource�ļ�
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