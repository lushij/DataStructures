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
        
        cout << "输入数字" << endl;
        int n;
        cin >> n;
        if (n > num)
        {
            cout << "猜大了" << endl;
        }
        else if (n == num)
        {
            cout << "猜对了" << endl;
            break;
        }
        else
        {
            cout << "猜小了" << endl;
        }
    }
}