#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;
string longestPalindrome(string s) {
    string res;
    for (int i = 0; i < s.size(); i++)
    {
        int l = i - 1, r = i + 1;//奇数
        while (l >= 0 && r < s.size() && s[l] == s[r]) l--, r++;
        if (res.size() < r - l - 1) res = s.substr(l + 1, r - l - 1);
        l = i, r = i + 1;//偶数情况
        while (l >= 0 && r < s.size() && s[l] == s[r]) l--, r++;
        if (res.size() < r - l - 1) res = s.substr(l + 1, r - l - 1);
    }
    return res;
}

int main()
{
    string s = "babad";
    cout<<longestPalindrome(s);
	return 0;
}