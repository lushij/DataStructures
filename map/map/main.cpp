
#include "Map.h"
#include <mysql.h>
#include <string>

/* ��Ŀ˵��
* Ŀ������ map.dat �ļ������Ƶ� Tank.sln �� /Tank/res/data/map.dat ��ʹ�á�
* ������ȫ��ʹ�ø���Ŀ���ɣ�ֱ�ӽ��������뵽 map.dat��
* ��ͼ���Լ����
	0 �յ�
	1 ɭ��
	2 ��
	3 ǽ
	4 ����
	5 ʯͷ
	- ÿһ�����ֶ�Ӧ��Ϸ���ڵ�ÿ�еĿ飨��Ϸ����ͬ������Ϊ 26*26 ������飬һ����ռ 4*4 ���أ�
*/


/**********���ݿ���ص�**************/
string ip = "localhost";
unsigned short port = 3306;
string user = "root";
string password = "root123.";
string dbname = "test";//���ݿ�����


// ���ݿ������
class MySQL
{
public:
	// ��ʼ�����ݿ�����
	MySQL()
	{
		_conn = mysql_init(nullptr);
	}
	// �ͷ����ݿ�������Դ
	~MySQL()
	{
		if (_conn != nullptr)
			mysql_close(_conn);
	}
	// �������ݿ�
	bool connect(string ip, unsigned short port, string user, string password,
		string dbname)
	{
		MYSQL* p = mysql_real_connect(_conn, ip.c_str(), user.c_str(),
			password.c_str(), dbname.c_str(), port, nullptr, 0);
		return p != nullptr;
	}
	// ���²��� insert��delete��update
	bool update(string sql)
	{
		if (mysql_query(_conn, sql.c_str()))
		{
			LOG("����ʧ��:" + sql);
			return false;
		}
		return true;
	}
	// ��ѯ���� select
	MYSQL_RES* query(string sql)
	{
		if (mysql_query(_conn, sql.c_str()))
		{
			LOG("��ѯʧ��:" + sql);
			return nullptr;
		}
		return mysql_use_result(_conn);
	}
private:
	MYSQL* _conn; // ��ʾ��MySQL Server��һ������
};

void InsertTestMysql(const char *dt)
{
	MySQL msl;
	if (msl.connect(ip, port, user, password, dbname))
	{
		std::cout << "�ɹ����ӵ����ݿ⣡" << std::endl;
		char ist[1024] = { 0 };
		sprintf(ist, "insert into map(data) values('%s')", dt);
		if (msl.update(ist)) {
			std::cout << "�����ѯ�ɹ�ִ�У�" << std::endl;
		}
		else {
			std::cout << "�޷�ִ�в����ѯ��" << std::endl;
		}
	}
	else
	{
		std::cout << "����ʧ��" << endl;
	}

}

void readData()
{
	MySQL msl;
	ofstream ofs("map.dat");
	if (!ofs)
	{
		LOG("open file fail");
		return;
	}
	if (msl.connect(ip, port, user, password, dbname))
	{
		std::cout << "�ɹ����ӵ����ݿ⣡" << std::endl;
		//ȥȡ���ݿ����
		const char* query = "select * from map";
		MYSQL_RES*ret = msl.query(query);
		if (ret == nullptr)
		{
			LOG("��ѯʧ��");
			ofs.close();
			return;
		}
		MYSQL_ROW row;
		while ((row = mysql_fetch_row(ret)) != nullptr)
		{
			if (row[0] != nullptr)
			{
				const string data(row[0]);
				ofs << data << endl;//����ÿһ��ÿһ�����ݴ���map.dat�У���Ҳ���ԸĶ�Ӧ�ĸ�ʽ
			}
		}
	}
	else
	{
		std::cout << "����ʧ��" << endl;
	}
	ofs.close();
}

/************************************************************************/

void writeMap();
void TestRead();


int main()
{
	//writeMap();
	////TestRead();	// ���Զ�ȡ��ͼ
	//_getch();


	/********************************************************/
	//const char* dt = "00000000000000000000000000";
	//InsertTestMysql(dt);
	/*MAP map[35];
	map[0].map_1();*/

	//��ʽ����

	//writeMap();	//��������ݴ������ݿ⣬��һ�ξͺ�
	readData(); //��ȡ���ݿ��ļ�����map.dat��
}












void writeMap()
{
	MAP map[35];
	map[0].map_1();
	map[1].map_2();
	map[2].map_3();
	map[3].map_4();
	map[4].map_5();
	map[5].map_6();
	map[6].map_7();
	map[7].map_8();
	map[8].map_9();
	map[9].map_10();
	map[10].map_11();
	map[11].map_12();
	map[12].map_13();
	map[13].map_14();
	map[14].map_15();
	map[15].map_16();
	map[16].map_17();
	map[17].map_18();
	map[18].map_19();
	map[19].map_20();
	map[20].map_21();
	map[21].map_22();
	map[22].map_23();
	map[23].map_24();
	map[24].map_25();
	map[25].map_26();
	map[26].map_27();
	map[27].map_28();
	map[28].map_29();
	map[29].map_30();
	map[30].map_31();
	map[31].map_32();
	map[32].map_33();
	map[33].map_34();
	map[34].map_35();




	/*FILE* fp = NULL;
	fopen_s(&fp, "map.dat", "ab+");
	for (int i = 0; i < 35; i++)
		fwrite(&map[i], sizeof(MAP), 1, fp);
	fclose(fp);

	cout << "map.dat �����ɵ���Ŀ��·���¡�" << endl;*/
}







void TestRead()
{
	MAP map;
	FILE* fp = NULL;
	fopen_s(&fp, "map.dat", "rb");

	for (int m = 0; m < 35; m++)
	{
		fread(&map, sizeof(MAP), 1, fp);
		for (int i = 0; i < 26; i++)
		{
			cout << map.buf[i] << endl;
		}
		cout << endl;
	}
	fclose(fp);


	cout << "��ͼ��ȡ����ȷ��" << endl;
}














