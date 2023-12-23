#ifndef CUSTOMER_H
#define CUSTOMER_H
#include"head.h"


//�ͻ���
class Customer {
public:
	//���캯��
	Customer(string name, string phone, string address, int vip = 0, int integral = 0,string ret="");
	//�ͻ���Ϣ
	void getInfo();
	//��Աע��
	void SignUpVip(int vip);
	//�ͻ�����
	void returnVal(string ret);

	string getName();
	int getVip();
	void setVip(int vip);
	string OfsFile();
	~Customer();
		
private:
	string _name;//�ͻ�����
	string _phone;//�ͻ��ֻ���
	string _address;//�ͻ���ַ
	int _vip;//��Ա�ȼ�
	int _integral;//����
	string _retVal;//�ͻ�����
};

#endif // CUSTOMER_H
