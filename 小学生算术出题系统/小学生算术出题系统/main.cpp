#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<vector>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<fstream>
#include<sstream>
#include<stdio.h>
using namespace std;
typedef struct StuInfo_t {
	StuInfo_t(string name, int id, int score)
		:_name(name)
		, _id(id)
		,_score(score)
	{

	}

	bool operator>(const StuInfo_t &rhs)const
	{
		return _score > rhs._score;
	}
	string _name;
	int _id;
	int _score;
}Sinfo;



char type[4] = { '+','-','/','*' };

void menu()
{
	cout << "��ӭ��������ϵͳ" << endl;
	cout << "  1.������ϰ" << endl;
	cout << "  2.���㿼��" << endl;
	cout << "  3.��ѯ�ɼ�" << endl;
	cout << "  4.�ɼ�����" << endl;
	cout << "  5.ɾ����Ϣ" << endl;
	cout << "  0.�˳�ϵͳ" << endl;
	cout << "���������ѡ��(0~5) >> " << endl;
}

void saveFile(Sinfo info)
{
	ofstream ofs("save.txt", std::ios::app);
	if (!ofs)
	{
		cerr << "open fail" << endl;
		return;
	}
	ofs << info._name<< "\t" << info._id << "\t" << info._score << endl;
	ofs.close();
}
void saveFile(vector<Sinfo>&V)
{
	ofstream ofs("save.txt");
	if (!ofs)
	{
		cerr << "open fail" << endl;
		return;
	}
	for (auto& x : V)
	{
		ofs << x._id << "\t" << x._name << "\t" << x._score << endl;
	}
	
	ofs.close();
}

void sortScore()
{
	vector<Sinfo>stuInfo;
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
		string name;
		int id;
		int score;
		iss >> name >> id >> score;
		stuInfo.push_back(Sinfo(name, id, score));
	}
	sort(stuInfo.begin(), stuInfo.end(), std::greater<Sinfo>());
	for (auto& x : stuInfo)
	{
		cout << x._id << "\t" << x._name << "\t" << x._score << endl;
	}

	ifs.close();
}

void CalculationExercises()
{
	srand((unsigned int)time(NULL));
	int totalQuestions = 0;
	int correctAnswers = 0;
	while (true)
	{
		int rhs = rand() % 100;
		int lhs = rand() % 100;
		int _type = rand() % 4;
		//int _type = 2;
		int ret = 0;
		// Check for division by zero and ensure division results in a whole number
		if (type[_type] == '/')
		{
			while (rhs ==0 || lhs % rhs != 0)
			{
				rhs = rand() % 100;
			}
				
			ret = lhs / rhs;
		}

		switch (type[_type])
		{
		case '+':
			ret = lhs + rhs;
			break;
		case '-':
			ret = lhs - rhs;
			break;
		case '*':
			ret = lhs * rhs;
			break;
		}

		int _ret = 0;
		int _cnt = 0;

		// Allow up to 3 attempts
		while (_cnt < 3)
		{
			cout << "��Ŀ: " << lhs << " " << type[_type] << " " << rhs << endl;
			cout << "��Ĵ�: ";
			cin >> _ret;

			if (_ret == ret)
			{
				cout << "��ȷ!" << endl;
				++correctAnswers;
				break;
			}
			else
			{
				cout << "���󣬻���" << 2 - _cnt <<"�λ���" << endl;
			}

			++_cnt;
		}

		// Display the correct answer if the user couldn't answer correctly
		if (_cnt == 3)
		{
			cout << "������ȷ��Ϊ: " << ret << endl;
		}

		// Increment total question count
		++totalQuestions;

		char choice;
		cout << "�Ƿ����? (Y/N): ";
		cin >> choice;

		if (choice != 'Y' && choice != 'y')
		{
			break;
		}
	}

	// Display results
	cout << "\n\n����Ŀ����: " << totalQuestions << endl;
	cout << "�������: " << correctAnswers << endl;
	cout << "��ȷ��: " << (static_cast<double>(correctAnswers) / totalQuestions) * 100 << "%" << endl;
}

void CalculationExam()
{
	string name;
	int id = 0;
	printf("��������:");
	cin >> name;
	printf("���ѧ��:");
	cin >> id;
	vector<string>sum;//�ܽ�
	double totalQuestions = 0;
	int n = 0;
	printf("��ս��Ŀ������:");
	cin >> n;
	double fm = 1.0 * 100 / n;
	while (n--)
	{
		srand((unsigned int)time(NULL));
		int rhs = rand() % 100;
		int lhs = rand() % 100;
		int _type = rand() % 4;
		int ret = 0;
		int _ret = 0;
		string line;
		// Check for division by zero and ensure division results in a whole number
		if (type[_type] == '/')
		{
			while (rhs == 0 || lhs % rhs != 0)
			{
				rhs = rand() % 100;
			}

			ret = lhs / rhs;
		}
		switch (type[_type])
		{
		case '+':
			ret = lhs + rhs;
			break;
		case '-':
			ret = lhs - rhs;
			break;
		case '*':
			ret = lhs * rhs;
			break;
		}
		cout << "��Ŀ: " << lhs << " " << type[_type] << " " << rhs << endl;
		cout << "��Ĵ�: ";
		cin >> _ret;
		if (ret == _ret)
		{
			totalQuestions += fm;
			line = to_string(lhs) + type[_type] + to_string(rhs) + "  ��ȷ";
			sum.push_back(line);
		}
		else
		{
			line = to_string(lhs) + type[_type] + to_string(rhs) + "  ����";
			sum.push_back(line);
		}
	}
	cout << "�ܷ�Ϊ:" << totalQuestions << endl;
	cout << "��Ŀ���:" << endl;
	for (auto& x : sum)
	{
		cout << x << endl;
	}
	Sinfo s(name, id, (int)totalQuestions);
	saveFile(s);
}

void searchScore()
{
	vector<Sinfo>stuInfo;
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
		string name;
		int id;
		int score;
		iss >> name >> id >> score;
		stuInfo.push_back(Sinfo(name, id, score));
	}
	string _name;
	int id;
	cout << "������������� ";
	cin >> _name;
	cout << "�������ѧ�� :";
	cin >> id;
	for (auto& x : stuInfo)
	{
		if (x._id == id && x._name == _name)
		{
			cout << x._id <<"\t" << x._name <<"\t" << x._score << endl;
			return;
		}
	}
	cout << "δ�ҵ�" << endl;
	ifs.close();
}

void removeStu() {
	vector<Sinfo> stuInfo;
	ifstream ifs("save.txt");
	if (!ifs) {
		cerr << "open fail" << endl;
		return;
	}

	string line;
	while (getline(ifs, line)) {
		istringstream iss(line);
		string name;
		int id, score;
		iss >> name >> id >> score;
		stuInfo.push_back(Sinfo(name, id, score));
	}

	string _name;
	int id;
	cout << "�������������: ";
	cin >> _name;
	cout << "�������ѧ��: ";
	cin >> id;

	// Use iterator to find and erase the element
	auto it = find_if(stuInfo.begin(), stuInfo.end(), [_name, id](const Sinfo& x) {
		return x._id == id && x._name == _name;
		});

	if (it != stuInfo.end()) {
		// Element found, erase it
		stuInfo.erase(it);
		cout << "ѧ����Ϣ��ɾ��" << endl;
	}
	else {
		cout << "δ�ҵ�ƥ���ѧ����Ϣ" << endl;
	}

	ifs.close();
	saveFile(stuInfo);
}
int main()
{
	
	while (1)
	{
		menu();
		int cmd=0;
		scanf("%d", &cmd);
		switch (cmd)
		{
		case 1:
			CalculationExercises();
			break;
		case 2:
			CalculationExam();
			break;
		case 3:
			//��ѯ
			searchScore();
			break;
		case 4:
			sortScore();
			break;
		case 5:
			removeStu();
			break;
		case 0:
			exit(0);
		}
		system("pause");
		system("cls");
	}

	return 0;
}