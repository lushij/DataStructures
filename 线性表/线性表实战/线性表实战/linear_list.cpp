#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define Maxsize 100//定义固定大小
//定义线性表结构体
typedef struct {
	int data[Maxsize];//数据域
	int length;//表示长度
}LineList;

//查看数据是否满
int checkfill(LineList& ls)
{
	if (ls.length == Maxsize)
	{
		return 0;
	}
	return 1;
}

//插入数据函数
void insertdata(LineList &ls)//引用
{
	printf("请输入你要插入的数据，几号位置，数据是啥\n");
	int num = 0;
	int loc = 0;
	cin >> loc >> num;
	if (checkfill(ls))
	{
		if (loc < 1 || loc > ls.length+1)
		{
			printf("位置不合法\n");
		}
		else
		{
			
			for (int i = ls.length; i >=loc ; i--)
			{
				//所有数据向后移动
				ls.data[i] = ls.data[i-1];
			}
			ls.data[loc-1] = num;//位置和下标差一
			ls.length++;
		}
	}
	
}

//遍历线性表
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
	//插入数据
	printlist(ls);
	insertdata(ls);
	printlist(ls);
	return 0;
}