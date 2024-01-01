#define _CRT_SECURE_NO_WARNINGS 1
#include <sstream>
#include <iostream>
#include <locale>
#include <codecvt>
int main() {
    std::locale::global(std::locale(""));
    // Just use wide characters everywhere.
    {
        std::wistringstream iss(L"你是中国");
        std::wstring character;
        while (iss >> character) {
            std::wcout << character << '\n';
        }
    }
    // Convert from multibyte to wide characters on the fly.
    {
        std::istringstream iss("你是中国");
        std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(iss.rdbuf());
        std::wistream wiss(&conv);
        //
        std::wstring character;
        while (wiss >> character) {
            std::wcout << character << '\n';
        }
    }
}