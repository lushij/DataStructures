#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <fstream>
#include <climits>
#include<stdlib.h>
using namespace std;
#define OK 1
#define ERROR -1;
typedef int Status;

typedef struct {
	int Id;
	string Name;
	string Sex;
	float Length;
	float Weight;
} kingfisher;

typedef struct kingfisherNode {
	kingfisher data;
	struct kingfisherNode* next;
} kingfisherNode, * LinkList;

Status InitList(LinkList& L) {
	L = new kingfisherNode;
	L->next = NULL;
	return OK;
}

void Insert(LinkList& L);
void Delete(LinkList& L);
void Modify(LinkList& L);
void Query(LinkList L);
Status Count(LinkList L);
void Printkingfisher(LinkList L);
void Display();

void Insert(LinkList& L) {
	kingfisher t;
	cout << "==>>请输入kingfisher编号(4位):";
	cin >> t.Id;
	cout << "==>>请输入kingfisher名字:";
	cin >> t.Name;
	cout << "==>>请输入kingfisher性别:";
	cin >> t.Sex;
	cout << "==>>请输入kingfisher身长(cm):";
	cin >> t.Length;
	cout << "==>>请输入kingfisher体重(kg):";
	cin >> t.Weight;
	kingfisherNode* p;
	p = new kingfisherNode;
	p->data.Id = t.Id;
	p->data.Name = t.Name;
	p->data.Sex = t.Sex;
	p->data.Length = t.Length;
	p->data.Weight = t.Weight;
	p->next = L->next;
	L->next = p;
	cout << "<---------信息输入成功!--------->" << endl;
}

void Delete(LinkList& L) {
	int id;
	cout << "==>>请输入您要删除的kingfisher编号(4位):";
	cin >> id;
	kingfisherNode* p, * q;
	p = L->next;
	q = L;
	while (p != NULL) {
		if (p->data.Id == id) {
			q->next = p->next;
			delete p;
			break;
		}
		else {
			q = p;
			p = p->next;
		}
	}
	if (p == NULL) {
		cout << "<--您要删除的kingfisher的信息不存在!->" << endl;
	}
	else {
		cout << "<---------信息删除成功!--------->" << endl;
	}
}

void Modify(LinkList& L) {
	kingfisher t;
	int id, a, b;
	kingfisherNode* p;
	do {
		cout << "==>>请输入您要修改的Seagull编号(4位):";
		cin >> id;
		p = L->next;
		while (p != NULL) {
			if (id == p->data.Id) {
				do {
					a = 0;
					cout << "          1.编号(4位)" << endl << "          2.姓名" << endl << "          3.性别" << endl <<
						"          4.身长(cm)" << endl << "          5.体重(kg)" << endl;
					cout << "==>>请选择要修改信息的序号:";
					int choice;
					cin >> choice;
					switch (choice) {
					case 1:
						cout << "==>>请输入新的编号(4位):";
						cin >> t.Id;
						p->data.Id = t.Id;
						break;
					case 2:
						cout << "==>>请输入新的姓名(Name):";
						cin >> t.Name;
						p->data.Name = t.Name;
						break;
					case 3:
						cout << "==>>请输入新的性别(Sex):";
						cin >> t.Sex;
						p->data.Sex = t.Sex;
						break;
					case 4:
						cout << "==>>请输入新的身长(Length)(cm):";
						cin >> t.Length;
						p->data.Length = t.Length;
						break;
					case 5:
						cout << "==>>请输入新的体重(Weight)(kg):";
						cin >> t.Weight;
						p->data.Weight = t.Weight;
						break;
					default:
						cout << "<-----------输入错误!----------->" << endl;
						cout << "<---------是否重新选择?--------->" << endl;
						cout << "==>>是-->请输入1:" << endl << "==>>否-->请输入0:" << endl;
						cin >> a;
						break;
					}

				} while (a == 1);
				break;
			}
			p = p->next;
		}
		if (p == NULL) {
			cout << "<--------查无此编号(Id)!-------->" << endl;
			cout << "<---------是否重新输入?--------->" << endl;
			cout << "==>>是-->请输入1:" << endl << "==>>否-->请输入0:" << endl;
			cin >> b;
		}
		else {
			cout << "<-----------修改成功!----------->" << endl;
			Printkingfisher(L);
			cout << "<---------是否继续修改?--------->" << endl;
			cout << "==>>是-->请输入1:" << endl << "==>>否-->请输入0:" << endl;
			cin >> b;
		}
	} while (b == 1);
}

void Query(LinkList L) {
	kingfisherNode* p;
	p = L->next;
	int id;
	cout << "==>>请输入你要查询的Seagull编号(4位):" << endl;
	cin >> id;
	while (p != NULL) {
		if (p->data.Id == id) {
			Display();
			cout << p->data.Id << " " << p->data.Name << "  " << p->data.Sex << "    " << p->data.Length << "      "
				<< p->data.Weight << endl;
			break;
		}
		else
			p = p->next;
	}
	if (p == NULL)
		cout << "<--您要查询的kingfisher信息不存在!--->" << endl;
}

Status Count(LinkList L) {
	kingfisherNode* p;
	p = L->next;
	int sum = 0;
	while (p != NULL) {
		p = p->next;
		sum++;
	}
	cout << "==>>已录入的kingfisher个数为:" << sum << "只。" << endl;
	return OK;
}

void Display() {
	cout << "编号" << "  " << "姓名" << "  " << "性别" << " " << "身长(cm)" << " " << "体重(kg)" << endl;
}

void Printkingfisher(LinkList L) {
	kingfisherNode* p;
	p = L->next;
	Display();
	while (p != NULL) {
		cout << p->data.Id << " " << p->data.Name << "  " << p->data.Sex << "    " << p->data.Length << "      "
			<< p->data.Weight << endl;
		p = p->next;
	}
}

// 将链表数据写入txt文件
void writeToFile(LinkList L, const string& filename) {
	ofstream outFile(filename);
	if (!outFile.is_open()) {
		cout << "Unable to open file " << filename << endl;
		return;
	}

	kingfisherNode* p = L->next;
	while (p != nullptr) {
		outFile << p->data.Id << " " << p->data.Name << " " << p->data.Sex << " " << p->data.Length << " " << p->data.Weight <<
			endl;
		p = p->next;
	}
	outFile.close();
}

// 从txt文件中读取数据并添加到链表
void readFromFile(LinkList& L, const string& filename) {
	ifstream inFile(filename);
	if (!inFile.is_open()) {
		cout << "Unable to open file " << filename << endl;
		return;
	}

	kingfisher t;
	kingfisherNode* p;
	while (inFile >> t.Id >> t.Name >> t.Sex >> t.Length >> t.Weight) {
		p = new kingfisherNode;
		p->data = t;
		p->next = L->next;
		L->next = p;
	}
	inFile.close();
}

/*******************************************************************************/
//逆序输出
void ReverseList(LinkList& L) {
	kingfisherNode* prev = nullptr;
	kingfisherNode* current = L->next;
	kingfisherNode* nextNode;

	while (current != nullptr) {
		nextNode = current->next;
		current->next = prev;
		prev = current;
		current = nextNode;
	}

	L->next = prev;
}

int FindMaxID(LinkList L) {
	kingfisherNode* p = L->next;
	int maxID = INT_MIN;

	while (p != nullptr) {
		if (p->data.Id > maxID) {
			maxID = p->data.Id;
		}
		p = p->next;
	}

	return maxID;
}
int FindMinID(LinkList L) {
	kingfisherNode* p = L->next;
	int minID = INT_MAX;

	while (p != nullptr) {
		if (p->data.Id < minID) {
			minID = p->data.Id;
		}
		p = p->next;
	}

	return minID;
}

void SwapNodes(kingfisherNode* a, kingfisherNode* b) {
	kingfisher temp = a->data;
	a->data = b->data;
	b->data = temp;
}

void SortByID(LinkList& L) {
	int swapped;
	kingfisherNode* ptr1;
	kingfisherNode* lptr = nullptr;

	if (L == nullptr)
		return;

	do {
		swapped = 0;
		ptr1 = L->next;

			while (ptr1->next != lptr)
			{
				//从小-->大排序
			if (ptr1->data.Id > ptr1->next->data.Id) {
				SwapNodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);
}


void Menu() {
	cout << "欢迎进入kingfisher信息管理系统" << endl;
	cout << "<--------[1].增加kingfisher;--------->" << endl;
	cout << "<--------[2].删除kingfisher;--------->" << endl;
	cout << "<--------[3].修改kingfisher;--------->" << endl;
	cout << "<--------[4].查询kingfisher信息;----->" << endl;
	cout << "<--------[5].统计kingfisher个数;----->" << endl;
	cout << "<--------[6].输出kingfisher列表;----->" << endl;
	cout << "<---------[7]. 将链表数据写入txt文件---->" << endl;
	cout << "<---------[8}.从txt文件中读取数据并添加到链表" << endl;
	cout << "<--------[9].退出;-------------->" << endl;
	cout << "<--------[10].逆序输出链表;-------------->" << endl;
	cout << "<--------[11].最值编号;-------------->" << endl;
	cout << "<--------[12].排序;-------------->" << endl;
	cout << "==>>请输入您的选择(1~12):";
}

int main() {
	int choice;
	LinkList L;
	InitList(L);
	while (1) {
		Menu();
		cin >> choice;
		switch (choice) {
		case 1:
			Insert(L);
			break;
		case 2:
			Delete(L);
			break;
		case 3:
			Modify(L);
			break;
		case 4:
			Query(L);
			break;
		case 5:
			Count(L);
			break;
		case 6:
			Printkingfisher(L);
			break;
		case 7:
			writeToFile(L, "kingfisher_data.txt");
			cout << "Data written to kingfisher_data.txt." << endl;

			// 清空原链表
			kingfisherNode* temp;
			while (L->next != nullptr) {
				temp = L->next;
				L->next = temp->next;
				delete temp;
			}
			break;
		case 8:
			// 从txt文件中读取数据并添加到链表
			readFromFile(L, "kingfisher_data.txt");
			break;

		case 9:
			cout << "*********************************" << endl;
			cout << "<-----------退出成功!----------->" << endl;
			cout << "<--------欢迎您下次进入!-------->" << endl;
			cout << "*********************************" << endl;
			return 0;
		case 10:
			//逆序链表
			ReverseList(L);
			cout << "Linked list reversed." << endl;
			Printkingfisher(L);
			break;
		case 11:
			cout << "Maximum ID: " << FindMaxID(L) << endl;
			cout << "Minimum ID: " << FindMinID(L) << endl;
			break;
		case 12:
			SortByID(L);
			cout << "Linked list sorted by ID." << endl;
			Printkingfisher(L);
			break;
		}
		system("pause");
		system("cls");
	}
	// 将数据写入txt文件
	//writeToFile(L, "kingfisher_data.txt");
//	cout << "Data written to kingfisher_data.txt." << endl;

	// 清空原链表
	//kingfisherNode *temp;
	//while (L->next != nullptr) {
	//temp = L->next;
	//L->next = temp->next;
	//delete temp;
	//}

	// 从txt文件中读取数据并添加到链表
	//readFromFile(L, "kingfisher_data.txt");

	return 0;
}
