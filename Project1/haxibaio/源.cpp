#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <string>
#include <algorithm>
#include<cstdio>
#include<unordered_map>
using namespace std;
unordered_map<char, int>heap;
int cont(string s)
{
	int ret = 0;
	for (int i = 0; i < s.size(); i++)
	{
		ret += heap[s[i]];
	}
	return ret;
}

int main()
{
	
	string s="how are you";
	//getline(cin,s);
	heap['a'] = 1;
	heap['b'] = 2;
	heap['c'] = 3;
	heap['d'] = 1;
	heap['e'] = 2;
	heap['f'] = 3;
	heap['g'] = 1;
	heap['h'] = 2;
	heap['i'] = 3;
	heap['j'] = 1;
	heap['k'] = 2;
	heap['l'] = 3;
	heap['m'] = 1;
	heap['n'] = 2;
	heap['o'] = 3;
	heap['p'] = 1;
	heap['q'] = 2;
	heap['r'] = 3;
	heap['s'] = 4;
	heap['t'] = 1;
	heap['u'] = 2;
	heap['v'] = 3;
	heap['w'] = 1;
	heap['x'] = 2;
	heap['y'] = 3;
	heap['z'] = 4;
	heap[' '] = 1;
	int ret = cont(s);
	cout << ret;
	return 0;
}