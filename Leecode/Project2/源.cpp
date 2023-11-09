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
    if (u - 1 + n - start + 1 < m) return;//剪枝，优化看递归的层数和剩余的个数的和是否小于m，若小于则无解
    if (u > m)
    {
        for (int i = 1; i <= m; i++)
        {
            printf("%d ", path[i]);
        }
        puts("");
        return;//符合要求打印完一行就结束进行下一行的搜索，优化不必要的麻烦
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