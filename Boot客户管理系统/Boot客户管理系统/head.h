#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<stdio.h>
#include<sstream>
#include<time.h>
#include<stdlib.h>
#include <chrono>
using namespace std;

struct record_t
{
	record_t(string name,string did,string time) : _name(name), _did(did), time(time) {}
	string _name;//�ͻ�����
	string _did;//����ɶ��
	string time;//ʱ��
};
struct search
{
	search(string name, string phone, string address, int vip, int integral, string ret)
		:_name(name)
		, _phone(phone)
		, _address(address)
		, _vip(vip)
		, _integral(integral)
		, _retVal(ret){}
	string _name;//�ͻ�����
	string _phone;//�ͻ��ֻ���
	string _address;//�ͻ���ַ
	int _vip;//��Ա�ȼ�
	int _integral;//����
	string _retVal;//�ͻ�����
};