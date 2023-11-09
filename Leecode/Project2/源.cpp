#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <algorithm>
#include<cstdio>
using namespace std;

const int N = 30;
int n, m;
int path[N];
void dfs(int u, int start)
{
    if (u - 1 + n - start + 1 < m) return;//��֦���Ż����ݹ�Ĳ�����ʣ��ĸ����ĺ��Ƿ�С��m����С�����޽�
    if (u > m)
    {
        for (int i = 1; i <= m; i++)
        {
            printf("%d ", path[i]);
        }
        puts("");
        return;//����Ҫ���ӡ��һ�оͽ���������һ�е��������Ż�����Ҫ���鷳
    }
    for (int i = start; i <= n; i++)
    {
        path[u] = i;
        dfs(u + 1, i + 1);
        path[i] = 0;
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    dfs(1, 1);
    return 0;
}