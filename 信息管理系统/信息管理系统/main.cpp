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
	cout << "==>>������kingfisher���(4λ):";
	cin >> t.Id;
	cout << "==>>������kingfisher����:";
	cin >> t.Name;
	cout << "==>>������kingfisher�Ա�:";
	cin >> t.Sex;
	cout << "==>>������kingfisher��(cm):";
	cin >> t.Length;
	cout << "==>>������kingfisher����(kg):";
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
	cout << "<---------��Ϣ����ɹ�!--------->" << endl;
}

void Delete(LinkList& L) {
	int id;
	cout << "==>>��������Ҫɾ����kingfisher���(4λ):";
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
		cout << "<--��Ҫɾ����kingfisher����Ϣ������!->" << endl;
	}
	else {
		cout << "<---------��Ϣɾ���ɹ�!--------->" << endl;
	}
}

void Modify(LinkList& L) {
	kingfisher t;
	int id, a, b;
	kingfisherNode* p;
	do {
		cout << "==>>��������Ҫ�޸ĵ�Seagull���(4λ):";
		cin >> id;
		p = L->next;
		while (p != NULL) {
			if (id == p->data.Id) {
				do {
					a = 0;
					cout << "          1.���(4λ)" << endl << "          2.����" << endl << "          3.�Ա�" << endl <<
						"          4.��(cm)" << endl << "          5.����(kg)" << endl;
					cout << "==>>��ѡ��Ҫ�޸���Ϣ�����:";
					int choice;
					cin >> choice;
					switch (choice) {
					case 1:
						cout << "==>>�������µı��(4λ):";
						cin >> t.Id;
						p->data.Id = t.Id;
						break;
					case 2:
						cout << "==>>�������µ�����(Name):";
						cin >> t.Name;
						p->data.Name = t.Name;
						break;
					case 3:
						cout << "==>>�������µ��Ա�(Sex):";
						cin >> t.Sex;
						p->data.Sex = t.Sex;
						break;
					case 4:
						cout << "==>>�������µ���(Length)(cm):";
						cin >> t.Length;
						p->data.Length = t.Length;
						break;
					case 5:
						cout << "==>>�������µ�����(Weight)(kg):";
						cin >> t.Weight;
						p->data.Weight = t.Weight;
						break;
					default:
						cout << "<-----------�������!----------->" << endl;
						cout << "<---------�Ƿ�����ѡ��?--------->" << endl;
						cout << "==>>��-->������1:" << endl << "==>>��-->������0:" << endl;
						cin >> a;
						break;
					}

				} while (a == 1);
				break;
			}
			p = p->next;
		}
		if (p == NULL) {
			cout << "<--------���޴˱��(Id)!-------->" << endl;
			cout << "<---------�Ƿ���������?--------->" << endl;
			cout << "==>>��-->������1:" << endl << "==>>��-->������0:" << endl;
			cin >> b;
		}
		else {
			cout << "<-----------�޸ĳɹ�!----------->" << endl;
			Printkingfisher(L);
			cout << "<---------�Ƿ�����޸�?--------->" << endl;
			cout << "==>>��-->������1:" << endl << "==>>��-->������0:" << endl;
			cin >> b;
		}
	} while (b == 1);
}

void Query(LinkList L) {
	kingfisherNode* p;
	p = L->next;
	int id;
	cout << "==>>��������Ҫ��ѯ��Seagull���(4λ):" << endl;
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
		cout << "<--��Ҫ��ѯ��kingfisher��Ϣ������!--->" << endl;
}

Status Count(LinkList L) {
	kingfisherNode* p;
	p = L->next;
	int sum = 0;
	while (p != NULL) {
		p = p->next;
		sum++;
	}
	cout << "==>>��¼���kingfisher����Ϊ:" << sum << "ֻ��" << endl;
	return OK;
}

void Display() {
	cout << "���" << "  " << "����" << "  " << "�Ա�" << " " << "��(cm)" << " " << "����(kg)" << endl;
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

// ����������д��txt�ļ�
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

// ��txt�ļ��ж�ȡ���ݲ���ӵ�����
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
//�������
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
				//��С-->������
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
	cout << "��ӭ����kingfisher��Ϣ����ϵͳ" << endl;
	cout << "<--------[1].����kingfisher;--------->" << endl;
	cout << "<--------[2].ɾ��kingfisher;--------->" << endl;
	cout << "<--------[3].�޸�kingfisher;--------->" << endl;
	cout << "<--------[4].��ѯkingfisher��Ϣ;----->" << endl;
	cout << "<--------[5].ͳ��kingfisher����;----->" << endl;
	cout << "<--------[6].���kingfisher�б�;----->" << endl;
	cout << "<---------[7]. ����������д��txt�ļ�---->" << endl;
	cout << "<---------[8}.��txt�ļ��ж�ȡ���ݲ���ӵ�����" << endl;
	cout << "<--------[9].�˳�;-------------->" << endl;
	cout << "<--------[10].�����������;-------------->" << endl;
	cout << "<--------[11].��ֵ���;-------------->" << endl;
	cout << "<--------[12].����;-------------->" << endl;
	cout << "==>>����������ѡ��(1~12):";
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

			// ���ԭ����
			kingfisherNode* temp;
			while (L->next != nullptr) {
				temp = L->next;
				L->next = temp->next;
				delete temp;
			}
			break;
		case 8:
			// ��txt�ļ��ж�ȡ���ݲ���ӵ�����
			readFromFile(L, "kingfisher_data.txt");
			break;

		case 9:
			cout << "*********************************" << endl;
			cout << "<-----------�˳��ɹ�!----------->" << endl;
			cout << "<--------��ӭ���´ν���!-------->" << endl;
			cout << "*********************************" << endl;
			return 0;
		case 10:
			//��������
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
	// ������д��txt�ļ�
	//writeToFile(L, "kingfisher_data.txt");
//	cout << "Data written to kingfisher_data.txt." << endl;

	// ���ԭ����
	//kingfisherNode *temp;
	//while (L->next != nullptr) {
	//temp = L->next;
	//L->next = temp->next;
	//delete temp;
	//}

	// ��txt�ļ��ж�ȡ���ݲ���ӵ�����
	//readFromFile(L, "kingfisher_data.txt");

	return 0;
}
