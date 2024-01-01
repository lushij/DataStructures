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

//创建头结点
List* createHeadList()
{
	List* HeadList = NULL;
	HeadList = new List;
	HeadList->next = NULL;
	return HeadList;
}

//创建节点
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
	std::wifstream ifs("data.txt");  // 使用wifstream读取宽字符
	if (!ifs) {
		std::wcerr << L"打开文件失败" << std::endl;
		return;
	}

	std::wstring line;
	while (std::getline(ifs, line)) {
		// 遍历宽字符串，一个一个汉字输出
		for (size_t i = 0; i < line.length(); ++i) {
			// 输出当前字符
			//std::wcout << line[i] << L" ";

			read newdata;
			newdata._name = line[i];
			newdata.cnt = 1;
			List* Move = headNode->next;
			int flag = 0;
			while (Move != NULL) {

				if (Move->data._name == newdata._name) {
					++Move->data.cnt;  // 更新词频
					flag = 1;
				}
				Move = Move->next;
			}

			// 如果未找到，则添加新条目
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
	cout << "输入汉字" << endl;
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
	cout << "未找到" << endl;
}
int main()
{
	// 设置本地化，以便正确处理中文字符
	std::locale::global(std::locale(""));
	List* Headlist = createHeadList();
	readFile(Headlist);
	//sortList(Headlist);
	while (1)
	{
		printf("1.查找汉字\n2.排序词频\n");
		cout << "输入你的命令 >>";
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
			cout << "数据保存在save.txt"<<endl;
			break;
		case 0:
			return 0;
		}
		system("pause");
		system("cls");
	}
	return 0;
}