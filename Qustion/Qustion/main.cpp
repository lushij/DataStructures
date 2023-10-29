#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stdio.h>
using namespace std;

int main()
{
    /*int a = 16;
    cout << (~a);*/
    int arr[5] = { 0 };
    int n = 5;
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
    }
    int del = 0;
    cin >> del;
    for (int i = 0; i < n; i++)
    {   
        if (arr[i] != del) {
            cout << arr[i];
        }
    }
}
