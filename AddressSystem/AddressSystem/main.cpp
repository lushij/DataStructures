#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

struct Info
{
	Info()
	{

	}
	Info(string name, string phone, string qq, string vx, string eml)
		:_name(name)
		,_phone(phone)
		,_qq(qq)
		,_vx(vx)
		,_email(eml)
	{

	}
	string _name;
	string _phone;
	string _qq;
	string _vx;
	string _email;
};

vector<Info>info;
//菜单
void menu()
{
	cout << "************************" << endl;
	cout << "***** 1.添加联系人 *****" << endl;
	cout << "***** 2.删除联系人 *****" << endl;
	cout << "***** 3.显示联系人 *****" << endl;
	cout << "***** 4.查找联系人 *****" << endl;
	cout << "***** 5.修改联系人 *****" << endl;
	cout << "***** 6.清空联系人 *****" << endl;
	cout << "***** 0.退出系统   *****" << endl;
	cout << "************************" << endl;
}

void saveFile()
{
	ofstream ofs("save.txt");
	if (!ofs)
	{
		cerr << "open fail" << endl;
		return;
	}
	for (auto& x : info)
	{
		ofs << x._name << "\t" << x._phone << "\t" << x._qq << "\t" << x._vx << "\t" << x._email << endl;
	}
	ofs.close();
}

void readFile()
{
	ifstream ifs("save.txt");
	if (!ifs)
	{
		cerr << "open fail" << endl;
		return;
	}
	string line;
	while (getline(ifs, line))
	{
		istringstream iss(line);
		string _name;
		string _phone;
		string _qq;
		string _vx;
		string _email;
		iss >> _name >> _phone >> _qq >> _vx >> _email;
		info.push_back(Info(_name, _phone, _qq, _vx, _email));
	}
	ifs.close();
}
void addInfo()
{
	
	cout << "请输入信息：姓名" << endl;
	Info _info;
	cin >> _info._name;
	int flag = 0;
	for (auto& x : info)
	{
		if (x._name == _info._name)
		{
			flag = 1;//查重
		}
	}
	if (flag == 1)
	{
		cout << "该用户已存在" << endl;
	}
	else
	{
		cout << "输入 电话" <<endl;
		cin >> _info._phone;
		// 验证手机号长度是否为11位
		while (_info._phone.length() != 11 || !all_of(_info._phone.begin(), _info._phone.end(), isdigit))
		{
			cout << "手机号必须是11位数字，请重新输入：" << endl;
			cin >> _info._phone;
		}
		cout << "QQ 微信 邮箱" << endl;
		cin >> _info._qq >> _info._vx >> _info._email;
		info.push_back(_info);
		// 每次添加联系人后，对 info 向量进行排序
		sort(info.begin(), info.end(), [](const Info& a, const Info& b) {
			return a._name < b._name;
			});
		saveFile();
		cout << "添加成功" << endl;
	}
	
}
void removeInfo()
{
	cout << "请输入要删除的联系人姓名：";
	string name;
	cin >> name;
	// 使用迭代器查找并删除元素
	for (auto it = info.begin(); it != info.end();) {
		if (it->_name == name) {
			it = info.erase(it);  // 删除元素，并返回指向下一个元素的迭代器
		}
		else {
			++it;  // 指向下一个元素
		}
	}
	saveFile();
	cout << "删除成功" << endl;
}

void eachInfo()
{
	cout << "姓名\t\t电话\tQQ\t微信\t邮箱" << endl;
	for (auto& x : info)
	{
		cout << x._name << "\t" << x._phone << "\t" << x._qq << "\t" << x._vx << "\t" << x._email << endl;
	}
}

void searchInfo()
{
	cout << "请输入要查找的联系人姓名：";
	string name;
	cin >> name;
	for (auto& x : info)
	{
		if (x._name == name)
		{
			cout << x._name << "\t" << x._phone << "\t" << x._qq << "\t" << x._vx << "\t" << x._email << endl;
			return;
		}
	}
	cout << "未找到" << endl;
}
void changeInfo()
{
	cout << "请输入要修改的联系人姓名：";
	string name;
	cin >> name;
	for (auto& x : info)
	{
		if (x._name == name)
		{
			cout << x._name << "\t" << x._phone << "\t" << x._qq << "\t" << x._vx << "\t" << x._email << endl;
			cout << "请输入你要改的信息,全部哦" << endl;
			cin >> x._name >> x._phone >> x._qq >> x._vx >> x._email;
			saveFile();
			cout << "更改成功" << endl;
			return;
		}
	}
	cout << "未找到" << endl;
}
//用户交互按键封装
void keyDown()
{
	int userKey = 0;
	cout << "请输入你的选择(0-6)：";
	cin >> userKey;
	switch (userKey)
	{
	case 0:
		cout << "退出成功" << endl;
		exit(0);
		break;
	case 1://1.添加联系人
		addInfo();
		break;
	case 2://2.删除联系人
		removeInfo();
		break;
	case 3://3.显示联系人
		eachInfo();
		break;
	case 4://4.查找联系人
		searchInfo();
		break;
	case 5://5.修改联系人
		changeInfo();
		break;
	case 6://6.清空联系人
		info.clear();
		saveFile();
		cout << "清空" << endl;
		break;
	}
}

int main()
{
	readFile();
	while (1)
	{
		menu();
		keyDown();
		system("pause");
		system("cls");
	}
	return 0;
}