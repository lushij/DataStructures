#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
using namespace std;


#include <iostream>
#include <string>
#include <locale>

//
struct t {
    wstring data;
    int cnt;
};
vector<t>_t;
int main() {
    std::wstring chineseString = L"�����й�";

    // ���ñ��ػ����Ա���ȷ���������ַ�
    std::locale::global(std::locale(""));
    // �������ַ�����һ��һ���������
    for (size_t i = 0; i < chineseString.length(); ++i) {
        // �����ǰ�ַ�
        std::wcout << chineseString[i] << " ";
        t t;
        t.data = chineseString[i];
        _t.push_back(t);
    }

    std::wcout << std::endl;

    for (auto& x : _t)
    {
        wcout << x.data << endl;
    }
    return 0;
}

