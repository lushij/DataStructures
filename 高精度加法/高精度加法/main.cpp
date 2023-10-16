#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int>add(vector<int>& A, vector<int>& B)
{
    vector<int>c;
    int t = 0;//进位
    for (int i = 0; i < A.size() || i < B.size(); i++)
    {
        if (i < A.size()) t += A[i];
        if (i < B.size()) t += B[i];
        c.push_back(t % 10);
        t /= 10;

    }
    if (t) c.push_back(1);
    return c;
}

int main()
{
    string a, b;//字符串保存数字
    cin >> a >> b;
    vector<int>A, B;//数组保存每一个数
    for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');//逆序存储并且转换类型
    for (int i = b.size() - 1; i >= 0; i--) B.push_back(b[i] - '0');
    auto C = add(A, B);
    for (int i = C.size() - 1; i >= 0; i--)
    {
        printf("%d", C[i]);
    }
    cout << endl;
}