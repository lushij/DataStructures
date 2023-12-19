#include"main.h"
//����Peolistͷ���
Peolist* createPeoHeadList()
{
	Peolist* HeadList = NULL;
	HeadList = (Peolist*)calloc(1, sizeof(Peolist));
	HeadList->next = NULL;
	return HeadList;
}
//����Peolist�ڵ�
Peolist* createPeoNode(PeopleInfo data)
{
	Peolist* newNode = (Peolist*)calloc(1, sizeof(Peolist));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}
//���Peolist��Ϣ
void insertPeolist(Peolist*& Head, PeopleInfo data)
{
	Peolist* newList = createPeoNode(data);
	newList->next = Head->next;
	Head->next = newList;
}

void insearchPeo(Peolist* Head)
{
	Peolist* Move = Head->next;
	printf("�绰\t����\t������ס�����\tͨ������\t����绰�ط�����\n");
	while (Move != NULL)
	{
		printf("%s\t%s\t%s\t%s\t%s\n"
			, Move->data.phone, Move->data.name, Move->data.hnum, Move->data.num, Move->data.time);
		Move = Move->next;
	}
}

void readGuest(Peolist* headNode, const char* fileURL)
{
	FILE* fp = fopen(fileURL, "r");
	if (fp == NULL)
	{
		fp = fopen(fileURL, "w");
		fclose(fp);
		return;
	}
	PeopleInfo tmp;
	while (fscanf(fp, "%s\t%s\t%s\t%d\t%s\n", tmp.phone, tmp.name, tmp.hnum, &tmp.num, tmp.time) != EOF)
	{
		insertPeolist(headNode, tmp);
	}
	fclose(fp);
}

void saveGuest(Peolist* headNode, const char* fileURL,const char*t)
{
	FILE* fp = fopen(fileURL, t);
	Peolist* Move = headNode->next;
	while (Move)
	{
		fprintf(fp, "%s\t%s\t%s\t%d\t%s\n",
			Move->data.phone, Move->data.name, Move->data.hnum, Move->data.num, Move->data.time);
		Move = Move->next;
	}
	fclose(fp);
}