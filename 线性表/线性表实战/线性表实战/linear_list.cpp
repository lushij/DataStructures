#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define Maxsize 100//����̶���С
//�������Ա�ṹ��
typedef struct {
	int data[Maxsize];//������
	int length;//��ʾ����
}LineList;

//�鿴�����Ƿ���
int checkfill(LineList& ls)
{
	if (ls.length == Maxsize)
	{
		return 0;
	}
	return 1;
}

//�������ݺ���
void insertdata(LineList &ls)//����
{
	printf("��������Ҫ��������ݣ�����λ�ã�������ɶ\n");
	int num = 0;
	int loc = 0;
	cin >> loc >> num;
	if (checkfill(ls))
	{
		if (loc < 1 || loc > ls.length+1)
		{
			printf("λ�ò��Ϸ�\n");
		}
		else if (ls.length==Maxsize)
		{
			printf("�洢�ռ�����\n");
		}
		else
		{
			
			for (int i = ls.length; i >=loc ; i--)
			{
				//������������ƶ�
				ls.data[i] = ls.data[i-1];
			}
			ls.data[loc-1] = num;//λ�ú��±��һ
			ls.length++;
		}
	}
	
}

//�ı�����
void changeData(LineList& ls)
{
	cout << "��������Ҫ�ı�����ݵ�λ�ú�Ҫ�ı������" << endl;
	int loc = 0;
	int num = 0;
	cin >> loc>>num;
	if (loc<1 || loc>ls.length + 1)
	{
		cout << "λ�ò��Ϸ�" << endl;
	}
	else
	{
		ls.data[loc-1] = num;//λ�ú��±����
		cout << "change successuful!" << endl;
	}
}

//ɾ������
void deletData(LineList& ls)
{
	cout << "����Ҫɾ��������ֵ" << endl;
	int num = 0;
	cin >> num;
	for (int i = 0; i < ls.length; i++)
	{
		if (ls.data[i] == num)
		{
			//i�ĺ����ֵ��ǰ�ƶ�����length-1
			for (int j = i; j < ls.length; j++)
			{
				ls.data[j] = ls.data[j + 1];
			}
			ls.length--;
			cout << "delete successful" << endl;
			break;
		}
		else
		{
			cout << "������δ�ҵ�" << endl;
			break;
		}
	}
}
//�������Ա�
void printlist(LineList ls)
{
	for (int i = 0; i < ls.length; i++)
	{
		printf("%d  ", ls.data[i]);
	}
	cout << endl;
}
int main()
{
	LineList ls;
	ls.length = 3;
	ls.data[0] = 1;
	ls.data[1] = 2;
	ls.data[2] = 3;
	//��������
	printlist(ls);
	/*insertdata(ls);
	printlist(ls);*/
	/*changeData(ls);
	printlist(ls);*/
	deletData(ls);
	printlist(ls);
	return 0;
}