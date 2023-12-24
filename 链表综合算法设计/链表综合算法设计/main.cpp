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
	int id;//编号
	char name[256];//姓名
	char depname[256];//部门名称
	char title[256];//职称
	int salary;//薪水
}pInfo;

//链表
typedef struct List {
	pInfo data;
	struct List* next;
}pList;




//创建pList头结点
pList* createProHeadList()
{
	pList* HeadList = NULL;
	HeadList = (pList*)calloc(1, sizeof(pList));
	HeadList->next = NULL;
	return HeadList;
}
//创建pList节点
pList* createProNode(pInfo data)
{
	pList* newNode = (pList*)calloc(1, sizeof(pList));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}
//添加pList信息
void insertlist(pList*& Head, pInfo data)
{
	pList* newList = createProNode(data);
	newList->next = Head->next;
	Head->next = newList;
}

//链表读取文件操作
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
//链表写Source文件
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
	printf("编号\t姓名\t部门名称\t职称\t薪水\n");
	while (Move != NULL)
	{
		printf("%d\t%s\t%s\t%s\t%d\n"
			, Move->data.id, Move->data.name, Move->data.depname, Move->data.title, Move->data.salary);
		Move = Move->next;
	}


}

void menu()
{
	printf("人事信息系统\n");
	printf(" 1.新增员工\n");
	printf(" 2.删除员工\n");
	printf(" 3.查找员工\n");
	printf(" 4.工资调整\n");
	printf(" 5.统计分析\n");
	printf(" 6.显示员工\n");
	printf(" 0.退出系统\n");
	cout << "请输入命令（0~6）>> ";
}

void addInfo(pList* &Head)
{
	printf("请输入员工信息\n");
	pInfo newPeo;
	printf("输入编号:");
	scanf("%d", &newPeo.id);
	printf("输入姓名:");
	scanf("%s", &newPeo.name);
	printf("输入部门名称:");
	scanf("%s", &newPeo.depname);
	printf("输入职称:");
	scanf("%s", &newPeo.title);
	printf("输入薪水:");
	scanf("%d", &newPeo.salary);
	insertlist(Head, newPeo);
	cout << "新增成功" << endl;
	cout << "是否保存到文件" << endl;
	string cmd;
	cout << "是或否 >> ";
	cin >> cmd;
	if (cmd == "是")
	{
		saveSource(Head, "data.txt");
		cout << "已保存" << endl;
	}
}
void removePeo(pList*& Head)
{
	if (Head->next == NULL)
	{
		readSource(Head, "data.txt");
	}
	int removeId;
	cout << "请输入要删除的员工编号: ";
	cin >> removeId;

	pList* prev = Head;
	pList* current = Head->next;

	while (current != NULL)
	{
		if (current->data.id == removeId)
		{
			prev->next = current->next;
			free(current);
			cout << "删除成功" << endl;
			return;
		}

		prev = current;
		current = current->next;
	}

	cout << "未找到该员工" << endl;
}
void searchInfo(pList* Head)
{
	if (Head->next == NULL)
	{
		readSource(Head, "data.txt");
	}
	int Id;
	cout << "请输入要查找的员工编号: ";
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
	cout << "未找到" << endl;
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
	cout << "请输入你要调整的部门:";
	string depname;
	cin >> depname;
	int add = 0;
	cout << "请输入你要调整的工资 :";
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