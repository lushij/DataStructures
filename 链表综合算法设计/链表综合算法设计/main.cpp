#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stdio.h>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<string.h>
#include<stdlib.h>
#include<unordered_map>
using namespace std;
typedef struct peoInfo_t {
	int id;//���
	char name[256];//����
	char depname[256];//��������
	char title[256];//ְ��
	int salary;//нˮ
}pInfo;

//����
typedef struct List {
	pInfo data;
	struct List* next;
}pList;




//����pListͷ���
pList* createProHeadList()
{
	pList* HeadList = NULL;
	HeadList = (pList*)calloc(1, sizeof(pList));
	HeadList->next = NULL;
	return HeadList;
}
//����pList�ڵ�
pList* createProNode(pInfo data)
{
	pList* newNode = (pList*)calloc(1, sizeof(pList));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}
//���pList��Ϣ
void insertlist(pList*& Head, pInfo data)
{
	pList* newList = createProNode(data);
	newList->next = Head->next;
	Head->next = newList;
}

//�����ȡ�ļ�����
void readSource(pList* headNode, const char* fileURL)
{
	FILE* fp = fopen(fileURL, "r");
	if (fp == NULL)
	{
		fp = fopen(fileURL, "w");
		fclose(fp);
		return;
	}
	pInfo tmp;
	while (fscanf(fp, "%d\t%s\t%s\t%s\t%d\n", &tmp.id, tmp.name, tmp.depname, tmp.title, &tmp.salary) != EOF)
	{
		insertlist(headNode, tmp);
	}
	fclose(fp);
}
//����дSource�ļ�
void saveSource(pList* headNode, const char* fileURL)
{
	ofstream ofs(fileURL,std::ios::app);
	if (!ofs)
	{
		cerr << "open faile " << fileURL << endl;
		return;
	}

	pList* Move = headNode->next;
	while (Move)
	{
		ofs << Move->data.id << "\t" << Move->data.name << "\t" << Move->data.depname
			<< "\t" << Move->data.title << "\t" << Move->data.salary << endl;
		Move = Move->next;
	}
	
	ofs.close();
}
void saveSource2(pList* headNode, const char* fileURL)
{
	ofstream ofs(fileURL);
	if (!ofs)
	{
		cerr << "open faile " << fileURL << endl;
		return;
	}

	pList* Move = headNode->next;
	while (Move)
	{
		ofs << Move->data.id << "\t" << Move->data.name << "\t" << Move->data.depname
			<< "\t" << Move->data.title << "\t" << Move->data.salary << endl;
		Move = Move->next;
	}

	ofs.close();
}
void insearchPro(pList*& Head)
{
	if (Head->next == NULL)
	{
		readSource(Head, "data.txt");
	}
	pList* Move = Head->next;
	printf("���\t����\t��������\tְ��\tнˮ\n");
	while (Move != NULL)
	{
		printf("%d\t%s\t%s\t%s\t%d\n"
			, Move->data.id, Move->data.name, Move->data.depname, Move->data.title, Move->data.salary);
		Move = Move->next;
	}


}

void menu()
{
	printf("������Ϣϵͳ\n");
	printf(" 1.����Ա��\n");
	printf(" 2.ɾ��Ա��\n");
	printf(" 3.����Ա��\n");
	printf(" 4.���ʵ���\n");
	printf(" 5.ͳ�Ʒ���\n");
	printf(" 6.��ʾԱ��\n");
	printf(" 0.�˳�ϵͳ\n");
	cout << "���������0~6��>> ";
}

void addInfo(pList* &Head)
{
	printf("������Ա����Ϣ\n");
	pInfo newPeo;
	printf("������:");
	scanf("%d", &newPeo.id);
	printf("��������:");
	scanf("%s", &newPeo.name);
	printf("���벿������:");
	scanf("%s", &newPeo.depname);
	printf("����ְ��:");
	scanf("%s", &newPeo.title);
	printf("����нˮ:");
	scanf("%d", &newPeo.salary);
	insertlist(Head, newPeo);
	cout << "�����ɹ�" << endl;
	cout << "�Ƿ񱣴浽�ļ�" << endl;
	string cmd;
	cout << "�ǻ�� >> ";
	cin >> cmd;
	if (cmd == "��")
	{
		saveSource(Head, "data.txt");
		cout << "�ѱ���" << endl;
	}
}
void removePeo(pList*& Head)
{
	if (Head->next == NULL)
	{
		readSource(Head, "data.txt");
	}
	int removeId;
	cout << "������Ҫɾ����Ա�����: ";
	cin >> removeId;

	pList* prev = Head;
	pList* current = Head->next;

	while (current != NULL)
	{
		if (current->data.id == removeId)
		{
			prev->next = current->next;
			free(current);
			cout << "ɾ���ɹ�" << endl;
			return;
		}

		prev = current;
		current = current->next;
	}

	cout << "δ�ҵ���Ա��" << endl;
}
void searchInfo(pList* Head)
{
	if (Head->next == NULL)
	{
		readSource(Head, "data.txt");
	}
	int Id;
	cout << "������Ҫ���ҵ�Ա�����: ";
	cin >> Id;
	pList* Move = Head->next;
	while (Move)
	{
		if (Move->data.id == Id)
		{
			cout << Move->data.id << "\t" << Move->data.name << "\t" << Move->data.depname << "\t" << Move->data.title
				<< "\t" << Move->data.salary << endl;
			return;
		}
		Move = Move->next;
	}
	cout << "δ�ҵ�" << endl;
}

void analyInfo(pList* &Head)
{
	if (Head->next == NULL)
	{
		readSource(Head, "data.txt");
	}
	unordered_map<string, int>info;
	pList* Move = Head->next;
	while (Move)
	{
		info[Move->data.depname]+=Move->data.salary;
		Move = Move->next;
	}
	for (auto& x : info)
	{
		cout << x.first << "\t" << x.second << endl;
	}
}

void changeSalay(pList* &Head)
{
	if (Head->next == NULL)
	{
		readSource(Head, "data.txt");
	}
	pList* Move = Head->next;
	cout << "��������Ҫ�����Ĳ���:";
	string depname;
	cin >> depname;
	int add = 0;
	cout << "��������Ҫ�����Ĺ��� :";
	cin >> add;
	while (Move)
	{
		if (strcmp(Move->data.depname, depname.c_str()) == 0)
		{
			Move->data.salary += add;
		}
		Move = Move->next;
	}
	saveSource2(Head, "data.txt");
}
int main()
{
	pList* Head = createProHeadList();
	while (1)
	{
		menu();
		int num = 0;
		scanf("%d", &num);
		switch (num)
		{
		case 1:
			addInfo(Head);
			break;
		case 2:
			removePeo(Head);
			break;
		case 3:
			searchInfo(Head);
			break;
		case 4:
			changeSalay(Head);
			break;
		case 5:
			analyInfo(Head);
			break;
		case 6:
			insearchPro(Head);
			break;
		case 0:
			exit(0);
		}


		system("pause");
		system("cls");
	}
	return 0;
}