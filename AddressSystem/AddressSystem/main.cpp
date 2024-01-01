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
//�˵�
void menu()
{
	cout << "************************" << endl;
	cout << "***** 1.�����ϵ�� *****" << endl;
	cout << "***** 2.ɾ����ϵ�� *****" << endl;
	cout << "***** 3.��ʾ��ϵ�� *****" << endl;
	cout << "***** 4.������ϵ�� *****" << endl;
	cout << "***** 5.�޸���ϵ�� *****" << endl;
	cout << "***** 6.�����ϵ�� *****" << endl;
	cout << "***** 0.�˳�ϵͳ   *****" << endl;
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
	
	cout << "��������Ϣ������" << endl;
	Info _info;
	cin >> _info._name;
	int flag = 0;
	for (auto& x : info)
	{
		if (x._name == _info._name)
		{
			flag = 1;//����
		}
	}
	if (flag == 1)
	{
		cout << "���û��Ѵ���" << endl;
	}
	else
	{
		cout << "���� �绰" <<endl;
		cin >> _info._phone;
		// ��֤�ֻ��ų����Ƿ�Ϊ11λ
		while (_info._phone.length() != 11 || !all_of(_info._phone.begin(), _info._phone.end(), isdigit))
		{
			cout << "�ֻ��ű�����11λ���֣����������룺" << endl;
			cin >> _info._phone;
		}
		cout << "QQ ΢�� ����" << endl;
		cin >> _info._qq >> _info._vx >> _info._email;
		info.push_back(_info);
		// ÿ�������ϵ�˺󣬶� info ������������
		sort(info.begin(), info.end(), [](const Info& a, const Info& b) {
			return a._name < b._name;
			});
		saveFile();
		cout << "��ӳɹ�" << endl;
	}
	
}
void removeInfo()
{
	cout << "������Ҫɾ������ϵ��������";
	string name;
	cin >> name;
	// ʹ�õ��������Ҳ�ɾ��Ԫ��
	for (auto it = info.begin(); it != info.end();) {
		if (it->_name == name) {
			it = info.erase(it);  // ɾ��Ԫ�أ�������ָ����һ��Ԫ�صĵ�����
		}
		else {
			++it;  // ָ����һ��Ԫ��
		}
	}
	saveFile();
	cout << "ɾ���ɹ�" << endl;
}

void eachInfo()
{
	cout << "����\t\t�绰\tQQ\t΢��\t����" << endl;
	for (auto& x : info)
	{
		cout << x._name << "\t" << x._phone << "\t" << x._qq << "\t" << x._vx << "\t" << x._email << endl;
	}
}

void searchInfo()
{
	cout << "������Ҫ���ҵ���ϵ��������";
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
	cout << "δ�ҵ�" << endl;
}
void changeInfo()
{
	cout << "������Ҫ�޸ĵ���ϵ��������";
	string name;
	cin >> name;
	for (auto& x : info)
	{
		if (x._name == name)
		{
			cout << x._name << "\t" << x._phone << "\t" << x._qq << "\t" << x._vx << "\t" << x._email << endl;
			cout << "��������Ҫ�ĵ���Ϣ,ȫ��Ŷ" << endl;
			cin >> x._name >> x._phone >> x._qq >> x._vx >> x._email;
			saveFile();
			cout << "���ĳɹ�" << endl;
			return;
		}
	}
	cout << "δ�ҵ�" << endl;
}
//�û�����������װ
void keyDown()
{
	int userKey = 0;
	cout << "���������ѡ��(0-6)��";
	cin >> userKey;
	switch (userKey)
	{
	case 0:
		cout << "�˳��ɹ�" << endl;
		exit(0);
		break;
	case 1://1.�����ϵ��
		addInfo();
		break;
	case 2://2.ɾ����ϵ��
		removeInfo();
		break;
	case 3://3.��ʾ��ϵ��
		eachInfo();
		break;
	case 4://4.������ϵ��
		searchInfo();
		break;
	case 5://5.�޸���ϵ��
		changeInfo();
		break;
	case 6://6.�����ϵ��
		info.clear();
		saveFile();
		cout << "���" << endl;
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