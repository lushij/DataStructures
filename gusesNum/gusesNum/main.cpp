#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<ctime>
using namespace std;

int main()
{
    srand(time(NULL));
    int num = rand() % 10 + 1;
    while (1)
    {
        
        cout << "��������" << endl;
        int n;
        cin >> n;
        if (n > num)
        {
            cout << "�´���" << endl;
        }
        else if (n == num)
        {
            cout << "�¶���" << endl;
            break;
        }
        else
        {
            cout << "��С��" << endl;
        }
    }
}