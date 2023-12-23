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

//�ͻ���Ϣ
void Customer::getInfo()
{
	cout <<"����:" << _name <<"\t�绰:" << _phone <<"\t��ַ:" << _address<<"\tvip�ȼ�:" 
		<< _vip<<"\t��Ա����:" << _integral << endl;
}
//��Աע��
void Customer::SignUpVip(int vip)
{
	_vip = vip;
}


//�ͻ�����
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
	// ʹ�� std::to_string() ������ת��Ϊ�ַ���
	std::string s = _name + "\t" + _phone + "\t" + _address + "\t" +
		std::to_string(_vip) + "\t" + std::to_string(_integral);

	return s;
}