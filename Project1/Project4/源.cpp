#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <algorithm>
#include<cstdio>
using namespace std;
const int N = 10;
int n;
int st[N];//存储方案 0表示每有放，1~n放数
bool use[N];//是否已使用

void dfs(int u)
{
    if (u > n)//边界判断
    {
        for (int i = 1; i <= n; i++)
        {
            printf("%d ", st[i]);
        }
        puts("");
        return;
    }
    //依次枚举每一个位置
    for (int i = 1; i <= n; i++)//咱们设计就是从小到大排序，第一个数字就是按照字典序进行排序的即可
    {
        if (!use[i])//false进去函数内
        {
            st[u] = i;
            use[i] = true;
            dfs(u + 1);
            use[i] = false;
        }
    }
}

int main()
{
    cin >> n;
    dfs(1);
    return 0;

}
