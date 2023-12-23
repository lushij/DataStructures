#include "Customer.h"

Customer::Customer(string name, string phone, string address, int vip , int integral ,string ret)
	:_name(name)
	, _phone(phone)
	, _address(address)
	, _vip(vip)
	, _integral(integral)
	,_retVal(ret)
{
	ofstream ofs("customer.txt", std::ios::app);
	if (!ofs)
	{
		cerr << "open fail" << endl;
		return;
	}
	ofs << _name << "\t" << _phone << "\t" << _address << "\t" << _vip << "\t" << _integral << "\t"
		<< ret << endl;
	ofs.close();
}
Customer::~Customer()
{

}

//客户信息
void Customer::getInfo()
{
	cout <<"姓名:" << _name <<"\t电话:" << _phone <<"\t地址:" << _address<<"\tvip等级:" 
		<< _vip<<"\t会员积分:" << _integral << endl;
}
//会员注册
void Customer::SignUpVip(int vip)
{
	_vip = vip;
}


//客户反馈
void Customer::returnVal(string retVal)
{
	_retVal = retVal;
}


string Customer::getName()
{
	return _name;
}
int Customer::getVip()
{
	return _vip;
}
void Customer::setVip(int vip)
{
	_vip = vip;
}

string Customer::OfsFile()
{
	// 使用 std::to_string() 将整型转换为字符串
	std::string s = _name + "\t" + _phone + "\t" + _address + "\t" +
		std::to_string(_vip) + "\t" + std::to_string(_integral);

	return s;
}