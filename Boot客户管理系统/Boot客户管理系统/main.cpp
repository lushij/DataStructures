#define _CRT_SECURE_NO_WARNINGS 1

#include "Customer.h"


//����ȫ�ֱ���
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
    cout << "����\t����ɶ��\tʱ��" << endl;
    string line;
    while (getline(ifs, line))
    {
        cout << line << endl;;
    }
    ifs.close();
}

string getCurrentTime()
{
    // ��ȡ��ǰʱ���
    auto now = std::chrono::system_clock::now();

    // ����ǰʱ���ת��Ϊtime_t����
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // ʹ��std::localtime������time_t���͵�ʱ��ת��Ϊtm�ṹ�壬������ȡ������ʱ����
    std::tm* localTime = std::localtime(&currentTime);

    // ��ʽ�����
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d-%H-%M", localTime);

    return buffer;
}

void menu()
{
    printf("   Boot�ͻ�����ϵͳ   \n");
    printf("     1.�����ͻ�       \n");
    printf("     2.��ѯ�ͻ�       \n");
    printf("     3.ע���Ա       \n");
    printf("     4.��Ա��Ϣ       \n");
    printf("     5.�ͻ�����       \n");
    printf("     6.��ʷ��¼       \n");
    printf("     0.�˳�ϵͳ       \n");
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
    cout << "���������� #";
    cin >> name;
    cout << "������绰 #";
    cin >> phone;
    cout << "�������ַ #";
    cin >> address;
    cout << "�Ƿ�ע���Ա����VIP�ȼ�����(0Ϊ��ע��) #";
    cin >> vip;
    integral += (10*vip);
    cust.push_back(Customer(name, phone, address, vip, integral));
    if(vip==0)
         records.push_back(record_t(name,"��д��Ϣδע���Ա", getCurrentTime()));
    else
        records.push_back(record_t(name, "��д��Ϣ��ע���Ա"+std::to_string(vip)+"��", getCurrentTime()));
    ofsRecod();
    records.clear();
    cust.clear();
    cout << "��ӳɹ�" << endl;
}

void searchInfo()
{
    string name, phone, address, ret;
    string vip , integral;
    if (cust.empty())
    {
        //��˵���ٴδ�ϵͳ��Ҫ������Ϣ
        cout << "������Ϣ..." << endl;
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
    cout << "���سɹ�" << endl;
    cout << "������ͻ����� #";
    cin >> name;
    for (auto& x : Sinfo)
    {
        if (x._name == name)
        {
            cout << "����:" << x._name << "\t�绰:" << x._phone << "\t��ַ:" << x._address << "\tvip�ȼ�:"
                << x._vip << "\t��Ա����:" << x._integral << endl;
            records.push_back(record_t(name, "��ѯ��Ϣ�����ҵ���", getCurrentTime()));
            ofsRecod();
            records.clear();
            Sinfo.clear();
            return;
        }
   }
    cout << "δ�ҵ�" << endl;
    records.push_back(record_t(name, "��ѯ��Ϣ����δ�ҵ�", getCurrentTime()));
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
        //��˵���ٴδ�ϵͳ��Ҫ������Ϣ
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
    cout << "������ͻ����� #";
    cin >> name;
    for (auto& x : Sinfo)
    {
        if (x._name==name && x._vip==0)
        {
            cout << "ע���Ա���� #";
            cin >> vip;
            x._vip=vip;
            x._integral += (vip*10);
            break;
        }
        else if (x._name == name && x._vip != 0)
        {
            cout << "���Ѿ���vip�û��ҵ�ǰ��vip" << x._vip << "��" << endl;
            cout << "�Ƿ�����,����1��0������Ҫ��" << endl;
            int cmd = -1;
            cin >> cmd;
            if (cmd == 0)
            {
                break;
            }
            cout << "�������� #";
            cin >> vip;
            x._vip = vip;
            x._integral += (vip*10);
            break;
        }
    }
    //���¼��ص��ļ���
    ofsVip();
    Sinfo.clear();
}

void vipInfo()
{
    string name, phone, address, ret;
    int vip = 0, integral = 0;
    if (cust.empty())
    {
        //��˵���ٴδ�ϵͳ��Ҫ������Ϣ
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
            cout << "����:" << x._name << "\t�绰:" << x._phone << "\t��ַ:" << x._address << "\tvip�ȼ�:"
                << x._vip << "\t��Ա����:" << x._integral << endl;
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
        //��˵���ٴδ�ϵͳ��Ҫ������Ϣ
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
    cout << "����������� #";
    cin >> name;
    cout << "��Ҫ��������Ϣ #";
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

    //���±�����Ϣ
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
        cout << "�������������(0~6) #";
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
            cout << "�������" << endl;
            continue;
        }
        system("pause");
        system("cls");
    }
    return 0;
}
