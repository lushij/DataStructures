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
		//0001  高位-->低位 
		//1000  低地址---->高地址
		printf("小端存储");
	}

	return 0;
}