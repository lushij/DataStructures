#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <algorithm>
#include<cstdio>
using namespace std;
const int N = 10;
int n;
int st[N];//�洢���� 0��ʾÿ�зţ�1~n����
bool use[N];//�Ƿ���ʹ��

void dfs(int u)
{
    if (u > n)//�߽��ж�
    {
        for (int i = 1; i <= n; i++)
        {
            printf("%d ", st[i]);
        }
        puts("");
        return;
    }
    //����ö��ÿһ��λ��
    for (int i = 1; i <= n; i++)//������ƾ��Ǵ�С�������򣬵�һ�����־��ǰ����ֵ����������ļ���
    {
        if (!use[i])//false��ȥ������
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
