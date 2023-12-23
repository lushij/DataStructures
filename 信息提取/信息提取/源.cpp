#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include<string>
using namespace std;

int main() {
    // ���ļ�
    std::ifstream inputFile("pd_tx_data_thr_30ADC_2.dat");

        if (!inputFile.is_open()) {
            std::cerr << "Unable to open the file." << std::endl;
            return 1;
        }

        std::string line;
        std::vector<std::string> hexValues;

        // ���ж�ȡ�ļ�����
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            std::string hexValue;
            // ��ÿһ�е�16����ֵ�ָ�洢��vector��
            while (iss >> hexValue) {
                hexValues.push_back(hexValue);
            }
            std::vector<std::string> result;
            auto startIt = std::find(hexValues.begin(), hexValues.end(), "FF");
            if (startIt != hexValues.end()) {
                // �ӵ�һ��FF��ʼ��������


                // �ӵ�һ��FF��vector��ĩβ��������
                std::copy(startIt, hexValues.end(), std::back_inserter(result));

                //// ������������
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
