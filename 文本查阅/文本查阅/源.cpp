#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<fstream>
#include<string>
#include <iostream>
#include<algorithm>
#include <locale> 
using namespace std;


struct read {
	wchar_t _name;
	int cnt;
};
struct List {
	read data;
	List* next;
};

//����ͷ���
List* createHeadList()
{
	List* HeadList = NULL;
	HeadList = new List;
	HeadList->next = NULL;
	return HeadList;
}

//�����ڵ�
List* createNode(read data)
{
	List* newNode = new List;
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

//
void insertList(List*& Head, read data)
{
	List* newList = createNode(data);
	newList->next = Head->next;
	Head->next = newList;
}



void readFile(List* headNode) {
	std::wifstream ifs("data.txt");  // ʹ��wifstream��ȡ���ַ�
	if (!ifs) {
		std::wcerr << L"���ļ�ʧ��" << std::endl;
		return;
	}

	std::wstring line;
	while (std::getline(ifs, line)) {
		// �������ַ�����һ��һ���������
		for (size_t i = 0; i < line.length(); ++i) {
			// �����ǰ�ַ�
			//std::wcout << line[i] << L" ";

			read newdata;
			newdata._name = line[i];
			newdata.cnt = 1;
			List* Move = headNode->next;
			int flag = 0;
			while (Move != NULL) {

				if (Move->data._name == newdata._name) {
					++Move->data.cnt;  // ���´�Ƶ
					flag = 1;
				}
				Move = Move->next;
			}

			// ���δ�ҵ������������Ŀ
			if (flag == 0) {
				insertList(headNode, newdata);
			}
		}
	}

	ifs.close();
}
void saveFile(List* headNode)
{
	wofstream ofs("save.txt", ofstream::binary);
	if (!ofs)
	{
		cerr << "open fail" << endl;
		return;
	}
	List* Move = headNode->next;
	while (Move != NULL)
	{
		//cout << Move->data._name << endl;
		ofs << Move->data._name << Move->data.cnt << endl;
		Move = Move->next;
	}
	ofs.close();
}
void sortList(List* headNode)
{
	if (headNode == NULL || headNode->next == NULL)
		return;  // Empty list or only one element, no need to sort

	bool swapped;
	List* current;
	List* lastSorted = NULL;

	do {
		swapped = false;
		current = headNode->next;

		while (current->next != lastSorted) {
			if (current->data.cnt < current->next->data.cnt) {
				// Swap data
				swap(current->data, current->next->data);
				swapped = true;
			}
			current = current->next;
		}

		lastSorted = current;
	} while (swapped);
}
void seach(List* Headlist)
{
	wchar_t name;
	cout << "���뺺��" << endl;
	wcin >> name;
	List* Move = Headlist->next;
	while (Move != NULL)
	{
		if (Move->data._name == name)
		{
			wcout << Move->data._name <<"\t" << Move->data.cnt << endl;
			return;
		}
		Move = Move->next;
	}
	cout << "δ�ҵ�" << endl;
}
int main()
{
	// ���ñ��ػ����Ա���ȷ���������ַ�
	std::locale::global(std::locale(""));
	List* Headlist = createHeadList();
	readFile(Headlist);
	//sortList(Headlist);
	while (1)
	{
		printf("1.���Һ���\n2.�����Ƶ\n");
		cout << "����������� >>";
		int id = -1;
		scanf("%d", &id);
		switch (id)
		{
		case 1:
			seach(Headlist);
			break;
		case 2:
			sortList(Headlist);
			saveFile(Headlist);
			cout << "���ݱ�����save.txt"<<endl;
			break;
		case 0:
			return 0;
		}
		system("pause");
		system("cls");
	}
	return 0;
}