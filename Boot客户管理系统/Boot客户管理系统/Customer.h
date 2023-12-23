#ifndef CUSTOMER_H
#define CUSTOMER_H
#include"head.h"


//客户类
class Customer {
public:
	//构造函数
	Customer(string name, string phone, string address, int vip = 0, int integral = 0,string ret="");
	//客户信息
	void getInfo();
	//会员注册
	void SignUpVip(int vip);
	//客户反馈
	void returnVal(string ret);

	string getName();
	int getVip();
	void setVip(int vip);
	string OfsFile();
	~Customer();
		
private:
	string _name;//客户名字
	string _phone;//客户手机号
	string _address;//客户地址
	int _vip;//会员等级
	int _integral;//积分
	string _retVal;//客户反馈
};

#endif // CUSTOMER_H
