#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <algorithm>
#include<cstdlib>
#include<string>
int cnt = 0;//用户输入的最大次数
int cont = 0;//实际执行的次数
using namespace std;

void rvs(int num)
{
    
    string s = to_string(num);
    string st = s;
    reverse(st.begin(), st.end());
    if (st == s) {
        cout << stoi(st) <<" " << cont;
    }
    else
    {
        num += stoi(st);
        cont++;
        if (cont > cnt)
        {
            cout << stoi(s) << " " << cont;
            return ;
        }
        rvs(num);
    }
}

int main()
{
    int num = 0;
    cin >> num >> cnt;
    rvs(num);
}