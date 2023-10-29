#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<cstdio>
using namespace std;
int main()
{
    long n;
    scanf("%d", &n);
    int ret = 0, res = 0;
    while (n)
    {
        if (n % 2 == 1) ret++;
        else res++;
        n /= 2;
    }
    cout << res << endl;
   
}