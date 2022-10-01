#pragma once
#include<iostream>
#include<string>
#include<stack>
#include<map>
using namespace std;

string GetNextNumber(string val, int& pos, int __cdecl comp(int));
string itop(string ival);
class PolishExpr
{
public:
	//Хранит инфиксное выражение
	std::string ival;
	//Хранит постфиксное выражение
	string pval;
	//Список и приоритет операторов
	static map<char, int> operationPriority;
	//Конструктор класса
	PolishExpr(string val)
	{
		//	Инициализируем поля
		ival = val;
		pval = itop(ival + "\r");
	}
};

