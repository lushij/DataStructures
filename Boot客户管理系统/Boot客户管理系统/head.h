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
	string _name;//客户名字
	string _did;//干了啥事
	string time;//时间
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
	string _name;//客户名字
	string _phone;//客户手机号
	string _address;//客户地址
	int _vip;//会员等级
	int _integral;//积分
	string _retVal;//客户反馈
};