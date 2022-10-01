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
	//������ ��������� ���������
	std::string ival;
	//������ ����������� ���������
	string pval;
	//������ � ��������� ����������
	static map<char, int> operationPriority;
	//����������� ������
	PolishExpr(string val)
	{
		//	�������������� ����
		ival = val;
		pval = itop(ival + "\r");
	}
};

