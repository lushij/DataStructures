#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	int num = 1;
	char* p = (char*) & num;
	if (*p == 1)
	{
		//0001  ��λ-->��λ 
		//1000  �͵�ַ---->�ߵ�ַ
		printf("С�˴洢");
	}

	return 0;
}