#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include<string>
using namespace std;

int main() {
    // 打开文件
    std::ifstream inputFile("pd_tx_data_thr_30ADC_2.dat");

        if (!inputFile.is_open()) {
            std::cerr << "Unable to open the file." << std::endl;
            return 1;
        }

        std::string line;
        std::vector<std::string> hexValues;

        // 逐行读取文件内容
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            std::string hexValue;
            // 将每一行的16进制值分割并存储到vector中
            while (iss >> hexValue) {
                hexValues.push_back(hexValue);
            }
            std::vector<std::string> result;
            auto startIt = std::find(hexValues.begin(), hexValues.end(), "FF");
            if (startIt != hexValues.end()) {
                // 从第一个FF开始保存数据


                // 从第一个FF到vector的末尾复制数据
                std::copy(startIt, hexValues.end(), std::back_inserter(result));

                //// 输出保存的数据
                //for (const auto& value : result) {
                //    std::cout << value << " ";
                //}

                std::cout << std::endl;
            }
            else {
                std::cerr << "First FF not found." << std::endl;
            }
            for (int i = 1; i < result.size(); ++i)
            {
                if (result[i] == "FF" && result[i - 1] != "FF")
                {
                    cout << result[i - 2] << " " << result[i - 1] << endl;
                }

            }
            result.clear();
            hexValues.clear();
        }

        inputFile.close();
       
        
        return 0;
    }
