#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<map>
#include<string>
#include<algorithm>
#include <unordered_map>
using namespace std;
int main()
{
    string s = "abcbb";
    unordered_map<char, int>head;
    int ret = 0;
    for (int i = 0, j = 0; i < s.size(); i++)
    {
        // head[i]=i+1;//下标赋值法
        // head[i]++;
        head[s[i]]++;
        while (head[s[i]] > 1) head[s[j++]]--;
        ret = max(ret, i - j + 1);
    }
    for (auto x : head)
    {
        cout << x.first << "\t" << x.second << endl;
    }
    cout << ret << endl;
    return 0;
}