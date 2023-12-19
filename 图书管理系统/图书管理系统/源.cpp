#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
bool user = false;//ע����Ϣ
class Book
{
public:
	Book(string name, int count, string Isbn)
	{
		this->name = name;
		this->count = count;
		this->IBSN = Isbn;
	}
	void setName(string name)
	{
		this->name = name;
	}
	void setCount(int count)
	{
		this->count = count;
	}
	string& getName()
	{
		return name;
	}
	int& getCount()
	{
		return count;
	}
	void setIbsn(string& ibsn)
	{
		this->IBSN = ibsn;
	}
	string& getIbsn()
	{
		return IBSN;
	}
private:
	string name;//����
	int count;//����
	string IBSN;//���
};
class Person
{
public:
	Person(string Pname, int count, string Bname, string data)
	{
		this->Bname = Bname;
		this->count = count;
		this->Pname = Pname;
		this->data = data;
	}
	string& getBname()
	{
		return Bname;
	}
	string& getPname()
	{
		return Pname;
	}
	string& getData()
	{
		return data;
	}
	int& getCount()
	{
		return count;
	}
private:
	string Pname;//����
	int count;//����
	string Bname;//����
	string data;
};
class Library
{
public:
	void addBook(const Book& book)
	{
		B.push_back(book);
	}
	void removeBookByIbsn(const string& ibsn)
	{
		if (!B.empty())
		{
			for (auto& v : B)
			{
				if (v.getIbsn() == ibsn)
				{
					B.erase(remove_if(B.begin(), B.end(),
						[&](Book& book) { return book.getIbsn() == ibsn; }),
						B.end());
				}
			}
		}
		else
		{
			cout << "���Ϊ0" << endl;
		}

	}
	void listBooks()
	{
		if (B.empty())
		{
			cout << "���Ϊ0" << endl;
		}
		for (auto& b : B)
		{
			cout << "������" << b.getName() << "\t������ " << b.getCount() << "\t��ţ�" << b.getIbsn() << endl;
		}
	}
	bool seacrchBook(string ISBN)
	{
		for (auto& b : B)
		{
			if (b.getIbsn() == ISBN)
			{
				cout << "������" << b.getName() << "\t������ " << b.getCount() << "\t��ţ�" << b.getIbsn() << endl;
				return true;;
			}
		}
		cout << "δ�ҵ�" << endl;
		return false;
	}
	void borrow(string ISBN)
	{
		if (seacrchBook(ISBN))
		{
			cout << "�Ƿ�ȷ��" << endl;
			string key;
			cin >> key;
			if (key == "��")
			{
				string m_Pname;
				string m_Bname;
				string m_data;
				int m_count;
				cout << "������[���������������������ڣ�xx.xx.xx��]" << endl;
				cin >> m_Pname >> m_Bname >> m_count >> m_data;
				P.push_back({ m_Pname,m_count,m_Bname,m_data });
				cout << "���ĳɹ�" << endl;
			}
		}
		else
		{
			cout <<"����ʧ��" << endl;
		}
		
	}
	void Return(string ISBN)
	{
		if (!P.empty())
		{
			for (auto& v : P)
			{
				if (v.getPname() == ISBN)
				{
					P.erase(remove_if(P.begin(), P.end(),
						[&](Person& p) { return p.getPname() == ISBN; }),
						P.end());
					cout<<"�黹�ɹ�" << endl;
				}
				else
				{
					cout << "δ�ҵ�" << endl;
				}
			}
		}
		else
		{
			cout << "û��Ҫ�黹���鼮" << endl;
		}
	}
	void saveToFile(const string& filename)
	{
		ofstream outputFile(filename);
		// Save book information
		for (auto& book : B)
		{
			outputFile << "Book|" << book.getName() << "|" << book.getCount() << "|" << book.getIbsn() << endl;
		}
		// Save person information
		for (auto& person : P)
		{
			outputFile << "Person|" << person.getPname() << "|" << person.getCount() << "|" << person.getBname() << "|" << person.getData() << endl;
		}
		outputFile.close();
		cout << "Data saved to file: " << filename << endl;
	}
private:
	vector<Book> B;
	vector<Person> P;
};
Library library;//ȫ�ֱ���
void menu()
{
	printf("--------------��ͼ�����ϵͳ��---------------\n");
	printf("\t\t0.�˳�ϵͳ\n");
	printf("\t\t1.����ͼ��\n");
	printf("\t\t2.��ʾͼ����Ϣ\n");
	printf("\t\t3.ɾ��ͼ��\n");
	printf("\t\t4.����ͼ��\n");
	printf("\t\t5.����ͼ��\n");
	printf("\t\t6.�黹ͼ��\n");
	printf("\t\t7.�Ƿ񱣴�\n");
	printf("--------------------------------------------\n");
	printf("��������ѡ��(0-7):");
}
void addBook()
{
	string ch;
	int num;
	string Isbn;
	cin >> ch >> num >> Isbn;
	library.addBook({ ch,num,Isbn });
	cout << "¼��ɹ�" << endl;
}
void showBook()
{
	library.listBooks();
}
void RomveBook()
{
	string nAme;
	cin >> nAme;
	library.removeBookByIbsn(nAme);
	cout << "ɾ���ɹ�" << endl;
}
void SeacrchBook()
{
	string ISBN;
	cin >> ISBN;
	library.seacrchBook(ISBN);
}
void Borrow()
{
	string ISBN;
	cin >> ISBN;
	library.borrow(ISBN);
	
}
void returnBook()
{
	string ISBN;
	cin >> ISBN;
	library.Return(ISBN);
	
}
void keyDown()
{
	int select = 0;
	cin >> select;
	switch (select)
	{
	case 0:
		exit(0);
		break;
	case 1:
		cout << "������ͼ����Ϣ������������,��ţ�" << endl;
		addBook();
		break;
	case 2:
		showBook();
		break;
	case 3:
		cout << "������Ҫɾ���鼮�ı��: ";
		RomveBook();
		break;
	case 4:
		cout << "������Ҫ�����鼮�ı��: ";
		SeacrchBook();
		break;
	case 5:
		cout << "������Ҫ����ͼ��ı�ţ� ";
		Borrow();
		break;
	case 6:
		cout << "������Ҫ�黹�˵������� ";
		returnBook();
		break;
	case 7:
		library.saveToFile("save.txt");
		break;

	}
}
//�������� 10 101
void Register()
{
	if (user == false)
	{
		cout << "�㻹δע�ᣬ�Ƿ�ע��" << endl;
		cout << "�ظ� �� �� �� " << endl;
		string select;
		cin >> select;
		if (select == "��")
		{
			cout << "ע��ɹ�" << endl;
			user = true;
			system("pause");
			system("cls");
		}
		else
		{
			cout << "δע�ᣬ����ʧ��" << endl;
			exit(0);
		}
	}
}
int main()
{
	Register();
	if (user == true)
	{
		while (1)
		{
			menu();
			keyDown();
			system("pause");
			system("cls");
		}
	}
	return 0;
}