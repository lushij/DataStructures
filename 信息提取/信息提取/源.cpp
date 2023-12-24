#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <stdio.h>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;

void test()
{
    vector<string>oldData;
    vector<string>newData;
    ifstream ifs("data.txt");
    if (!ifs)
    {
        cerr << "open file" << endl;
        return;
    }
    string line;
    while (getline(ifs, line))
    {
        istringstream iss(line);
        string word;
        while (iss >> word)
        {
            oldData.push_back(word);
        }
        bool flag = false;
        for (int i = 0; i < oldData.size(); ++i)
        {
            if (oldData[i] == "FF")
            {
                flag = true;
            }
            if (flag == true)
            {
               // cout << oldData[i] << " ";
                newData.push_back(oldData[i]);
            }
        }
        //读取一行处理一行
        ofstream ofs("deal.txt", std::ios::app);
        if (!ofs)
        {
            cerr << "open fail" << endl;
            return;
        }
        for (int j = 1; j < newData.size(); ++j)
        {
            if (newData[j] == "FF" && newData[j - 1] != "FF")
            {
                ofs << newData[j - 2] << " " << newData[j - 1] << " ";
            }
        }
        ofs << endl;
        ofs.close();
        oldData.clear();
        newData.clear();
    }

    ifs.close();
}
int main()
{
    test();
    return 0;
}

