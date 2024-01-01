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
    std::wstring chineseString = L"你是中国";

    // 设置本地化，以便正确处理中文字符
    std::locale::global(std::locale(""));
    // 遍历宽字符串，一个一个汉字输出
    for (size_t i = 0; i < chineseString.length(); ++i) {
        // 输出当前字符
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

