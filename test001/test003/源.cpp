#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <fstream>
#include <unordered_map>

bool isStartOfUTF8Char(char byte) {
    // UTF-8����ĺ���ͨ����0xE��ͷ
    return (byte & 0xC0) == 0xC0;
}

int getUTF8CharLength(char startByte) {
    // ����UTF-8�������ȷ���ַ��ĳ���
    if ((startByte & 0xE0) == 0xC0) {
        return 2;
    }
    else if ((startByte & 0xF0) == 0xE0) {
        return 3;
    }
    else if ((startByte & 0xF8) == 0xF0) {
        return 4;
    }
    return 1;
}

std::string readUTF8Char(std::ifstream& file, char startByte, int charLength) {
    std::string utf8Char;
    utf8Char += startByte;
    for (int i = 1; i < charLength; ++i) {
        char nextByte;
        file >> nextByte;
        utf8Char += nextByte;
    }
    return utf8Char;
}

int main() {
    std::string filename="data.txt";
    /*std::cout << "�������ļ�����";
    std::cin >> filename;*/

    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "�޷����ļ���" << filename << std::endl;
        return 1;
    }

    std::unordered_map<std::string, int> frequency;

    char byte;
    while (file >> byte) {
        if (isStartOfUTF8Char(byte)) {
            int charLength = getUTF8CharLength(byte);
            std::string utf8Char = readUTF8Char(file, byte, charLength);
            frequency[utf8Char]++;
        }
    }

    file.close();

    std::cout << "����Ƶ��ͳ�ƣ�" << std::endl;
    for (const auto& pair : frequency) {
        std::cout << pair.first << ": " << pair.second << "��" << std::endl;
    }

    return 0;
}