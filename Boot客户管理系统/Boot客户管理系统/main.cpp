#define _CRT_SECURE_NO_WARNINGS 1

#include "Customer.h"


//定义全局变量
vector<record_t>records;
vector<Customer>cust;
vector<search>Sinfo;

void ofsRecod()
{
    ofstream ofs("record.txt", std::ios::app);
    if (!ofs)
    {
        cerr << "open file" << endl;
        return;
    }
    for (auto& x : records)
    {
        ofs << x._name << "\t" << x._did << "\t" << x.time << endl;
    }
    ofs.close();

}

void readRecord()
{
    
    ifstream ifs("record.txt");
    if (!ifs)
    {
        cerr << "open file" << endl;
        return;
    }
    cout << "姓名\t干了啥事\t时间" << endl;
    string line;
    while (getline(ifs, line))
    {
        cout << line << endl;;
    }
    ifs.close();
}

string getCurrentTime()
{
    // 获取当前时间点
    auto now = std::chrono::system_clock::now();

    // 将当前时间点转换为time_t类型
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // 使用std::localtime函数将time_t类型的时间转换为tm结构体，便于提取年月日时分秒
    std::tm* localTime = std::localtime(&currentTime);

    // 格式化输出
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d-%H-%M", localTime);

    return buffer;
}

void menu()
{
    printf("   Boot客户管理系统   \n");
    printf("     1.新增客户       \n");
    printf("     2.查询客户       \n");
    printf("     3.注册会员       \n");
    printf("     4.会员信息       \n");
    printf("     5.客户反馈       \n");
    printf("     6.历史记录       \n");
    printf("     0.退出系统       \n");
}

int cinInfo()
{
    int num = 0;
    while (cin >> num, !cin.eof())
    {
        if (cin.bad())
        {
            cout << "cin has breken!" << endl;
            return -1;
        }
        else if (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "pls input your choice" << endl;
        }
        else
        {
            break;
        }
    }
    return num;
}

void newPeo()
{
    string name, phone, address, ret;
    int vip = 0, integral = 0;
    cout << "请输入姓名 #";
    cin >> name;
    cout << "请输入电话 #";
    cin >> phone;
    cout << "请输入地址 #";
    cin >> address;
    cout << "是否注册会员输入VIP等级即可(0为不注册) #";
    cin >> vip;
    integral += (10*vip);
    cust.push_back(Customer(name, phone, address, vip, integral));
    if(vip==0)
         records.push_back(record_t(name,"填写信息未注册会员", getCurrentTime()));
    else
        records.push_back(record_t(name, "填写信息并注册会员"+std::to_string(vip)+"级", getCurrentTime()));
    ofsRecod();
    records.clear();
    cust.clear();
    cout << "添加成功" << endl;
}

void searchInfo()
{
    string name, phone, address, ret;
    string vip , integral;
    if (cust.empty())
    {
        //就说明再次打开系统需要加载信息
        cout << "加载信息..." << endl;
        ifstream ifs("customer.txt");
        if (!ifs)
        {
            cerr << "open fail" << endl;
            return;
        }
        string line;
        while (getline(ifs, line))
        {
            istringstream iss(line);
            iss >> name >>  phone >> address >> vip >> integral >> ret;
            Sinfo.push_back(search(name, phone, address, atoi(vip.c_str()), atoi(integral.c_str()), ret));
        }
        ifs.close();
    }
    cout << "加载成功" << endl;
    cout << "请输入客户姓名 #";
    cin >> name;
    for (auto& x : Sinfo)
    {
        if (x._name == name)
        {
            cout << "姓名:" << x._name << "\t电话:" << x._phone << "\t地址:" << x._address << "\tvip等级:"
                << x._vip << "\t会员积分:" << x._integral << endl;
            records.push_back(record_t(name, "查询信息并且找到了", getCurrentTime()));
            ofsRecod();
            records.clear();
            Sinfo.clear();
            return;
        }
   }
    cout << "未找到" << endl;
    records.push_back(record_t(name, "查询信息并且未找到", getCurrentTime()));
    ofsRecod();
    records.clear();
    Sinfo.clear();
}
void ofsVip()
{
    ofstream ofs("customer.txt");
    if (!ofs)
    {
        cerr << "open fail" << endl;
        return;
    }
    for (auto& x : Sinfo)
    {
        ofs << x._name << "\t" << x._phone << "\t" << x._address << "\t" << x._vip << "\t" << x._integral << "\t"
            << x._retVal << endl;
    }
    ofs.close();
}

void signVip()
{
    string name, phone, address, ret;
    int vip = 0, integral = 0;
    if (cust.empty())
    {
        //就说明再次打开系统需要加载信息
        ifstream ifs("customer.txt");
        if (!ifs)
        {
            cerr << "open fail" << endl;
            return;
        }
        string line;
        while (getline(ifs, line))
        {
            istringstream iss(line);
            iss >> name >> phone >> address >> vip >> integral >> ret;
            Sinfo.push_back(search(name, phone, address, vip, integral, ret));
        }
        ifs.close();
    }
    cout << "请输入客户姓名 #";
    cin >> name;
    for (auto& x : Sinfo)
    {
        if (x._name==name && x._vip==0)
        {
            cout << "注册会员几级 #";
            cin >> vip;
            x._vip=vip;
            x._integral += (vip*10);
            break;
        }
        else if (x._name == name && x._vip != 0)
        {
            cout << "你已经是vip用户且当前是vip" << x._vip << "级" << endl;
            cout << "是否升级,输入1或0（不需要）" << endl;
            int cmd = -1;
            cin >> cmd;
            if (cmd == 0)
            {
                break;
            }
            cout << "升到几级 #";
            cin >> vip;
            x._vip = vip;
            x._integral += (vip*10);
            break;
        }
    }
    //重新加载到文件里
    ofsVip();
    Sinfo.clear();
}

void vipInfo()
{
    string name, phone, address, ret;
    int vip = 0, integral = 0;
    if (cust.empty())
    {
        //就说明再次打开系统需要加载信息
        ifstream ifs("customer.txt");
        if (!ifs)
        {
            cerr << "open fail" << endl;
            return;
        }
        string line;
        while (getline(ifs, line))
        {
            istringstream iss(line);
            iss >> name >> phone >> address >> vip >> integral >> ret;
            Sinfo.push_back(search(name, phone, address, vip, integral, ret));
        }
        ifs.close();
    }
 
    for (auto& x : Sinfo)
    {
        if (x._vip != 0)
        {
            cout << "姓名:" << x._name << "\t电话:" << x._phone << "\t地址:" << x._address << "\tvip等级:"
                << x._vip << "\t会员积分:" << x._integral << endl;
        }
    }
    Sinfo.clear();
}

void logRet()
{
    string name, phone, address, ret;
    int vip = 0, integral = 0;
    if (cust.empty())
    {
        //就说明再次打开系统需要加载信息
        ifstream ifs("customer.txt");
        if (!ifs)
        {
            cerr << "open fail" << endl;
            return;
        }
        string line;
        while (getline(ifs, line))
        {
            istringstream iss(line);
            iss >> name >> phone >> address >> vip >> integral >> ret;
            Sinfo.push_back(search(name, phone, address, vip, integral, ret));
        }
        ifs.close();
    }
    cout << "输入你的姓名 #";
    cin >> name;
    cout << "你要反馈的信息 #";
    cin >> ret;
    for (auto& x : Sinfo)
    {
        if (x._name== name)
        {
            x._retVal=ret;
            x._integral += 10;
            break;
        }
    }

    //重新保存信息
    ofstream ofs("customer.txt");
    if (!ofs)
    {
        cerr << "open fail" << endl;
        return;
    }
    for (auto& x : Sinfo)
    {
        ofs << x._name << "\t" << x._phone << "\t" << x._address << "\t" << x._vip << "\t" << x._integral << "\t"
            << x._retVal << endl;
    }
    ofs.close();
    Sinfo.clear();
}
int main() 
{
    while (1)
    {
        menu();
        cout << "请输入你的命令(0~6) #";
        int num = cinInfo();
        switch (num)
        {
        case 1:
            newPeo();
            break;
        case 2:
            searchInfo();
            break;
        case 3:
            signVip();
            break;
        case 4:
            vipInfo();
            break;
        case 5:
            logRet();
            break;
        case 6:
            readRecord();
            break;
        case 0:
            exit(0);
        default:
            cout << "命令不存在" << endl;
            continue;
        }
        system("pause");
        system("cls");
    }
    return 0;
}
