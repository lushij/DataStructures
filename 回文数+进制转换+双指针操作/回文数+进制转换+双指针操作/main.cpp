#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

//�ж��Ƿ�Ϊ��������
bool isNum(vector<int>k)
{
    //����˫ָ�뷽��
    int i = 0;
    int j = k.size() - 1;
  /*  while (i < j)
    {
        if (k[i++] == k[j--]);
        else return false;
    }
    return true;*/

   ////������
   // for (i = 0; i < j; i++)
   // {
   //     if (k[i] == k[j - i]);
   //     else return false;
   // }
   // return true;

    ////������
    ////ת���ַ���
    //string s;//�洢ԭʼ������ 
    //for (int x : k)
    //{
    //    s.push_back(x);
    //}
    //string st = s;//�����洢��ת���ַ���
    //reverse(st.begin(), st.end());
    //return s == st;
}

//itoa��ʵ��
vector<int> Myitoa(int num, int n)
{
    vector<int>a;
    do {
        a.push_back(num % n);
        num /= n;
    } while (num != 0);
    reverse(a.begin(), a.end());//����洢����˳��洢�����ӡҲ��
    return a;
}

int main()
{
    int num = 0;//����
    int cnt = 0;//ת���Ľ���
    cin >> num >> cnt;
    vector<int>ret = Myitoa(num, cnt);
    isNum(ret) ? puts("Yes") : puts("No");
    for (int i : ret)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}