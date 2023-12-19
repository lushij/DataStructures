#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
bool user = false;//注册信息
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
	string name;//书名
	int count;//数量
	string IBSN;//编号
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
	string Pname;//人名
	int count;//数量
	string Bname;//书名
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
			cout << "库存为0" << endl;
		}

	}
	void listBooks()
	{
		if (B.empty())
		{
			cout << "库存为0" << endl;
		}
		for (auto& b : B)
		{
			cout << "书名：" << b.getName() << "\t数量： " << b.getCount() << "\t编号：" << b.getIbsn() << endl;
		}
	}
	bool seacrchBook(string ISBN)
	{
		for (auto& b : B)
		{
			if (b.getIbsn() == ISBN)
			{
				cout << "书名：" << b.getName() << "\t数量： " << b.getCount() << "\t编号：" << b.getIbsn() << endl;
				return true;;
			}
		}
		cout << "未找到" << endl;
		return false;
	}
	void borrow(string ISBN)
	{
		if (seacrchBook(ISBN))
		{
			cout << "是否确认" << endl;
			string key;
			cin >> key;
			if (key == "是")
			{
				string m_Pname;
				string m_Bname;
				string m_data;
				int m_count;
				cout << "请输入[人名，书名，数量，日期（xx.xx.xx）]" << endl;
				cin >> m_Pname >> m_Bname >> m_count >> m_data;
				P.push_back({ m_Pname,m_count,m_Bname,m_data });
				cout << "借阅成功" << endl;
			}
		}
		else
		{
			cout <<"借阅失败" << endl;
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
					cout<<"归还成功" << endl;
				}
				else
				{
					cout << "未找到" << endl;
				}
			}
		}
		else
		{
			cout << "没有要归还的书籍" << endl;
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
Library library;//全局变量
void menu()
{
	printf("--------------【图书管理系统】---------------\n");
	printf("\t\t0.退出系统\n");
	printf("\t\t1.增加图书\n");
	printf("\t\t2.显示图书信息\n");
	printf("\t\t3.删除图书\n");
	printf("\t\t4.查找图书\n");
	printf("\t\t5.借阅图书\n");
	printf("\t\t6.归还图书\n");
	printf("\t\t7.是否保存\n");
	printf("--------------------------------------------\n");
	printf("请输入你选择(0-7):");
}
void addBook()
{
	string ch;
	int num;
	string Isbn;
	cin >> ch >> num >> Isbn;
	library.addBook({ ch,num,Isbn });
	cout << "录入成功" << endl;
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
	cout << "删除成功" << endl;
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
		cout << "请输入图书信息（书名，数量,编号）" << endl;
		addBook();
		break;
	case 2:
		showBook();
		break;
	case 3:
		cout << "请输入要删除书籍的编号: ";
		RomveBook();
		break;
	case 4:
		cout << "请输入要查找书籍的编号: ";
		SeacrchBook();
		break;
	case 5:
		cout << "请输入要借阅图书的编号： ";
		Borrow();
		break;
	case 6:
		cout << "请输入要归还人的姓名： ";
		returnBook();
		break;
	case 7:
		library.saveToFile("save.txt");
		break;

	}
}
//阿甘正传 10 101
void Register()
{
	if (user == false)
	{
		cout << "你还未注册，是否注册" << endl;
		cout << "回复 是 或 否 " << endl;
		string select;
		cin >> select;
		if (select == "是")
		{
			cout << "注册成功" << endl;
			user = true;
			system("pause");
			system("cls");
		}
		else
		{
			cout << "未注册，进入失败" << endl;
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