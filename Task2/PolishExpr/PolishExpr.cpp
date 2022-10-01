#include"PolishExpr.h"
map<char, int> PolishExpr::operationPriority = {
	{'(', 0},
	{'+', 1},
	{'-', 1},
	{'*', 2},
	{'/', 2},
	{'^', 3},
	{'~', 4}	//	������� �����
};
string GetNextNumber(string val, int& pos, int __cdecl comp(int))
{
	//������ �����
	string rez = "";

	//���������� ������
	for (; pos < val.size(); pos++)
	{
		//����������� ������ ������
		char num = val[pos];

		//���������, �������� ������ ������
		if (comp(num))
			//���� �� - ���������� � ������
			rez += num;
		else
		{
			//���� ���, �� ���������� ������� � ����������� �������
			pos--;
			//� ������� �� �����
			break;
		}
	}

	//���������� �����
	return rez;
}

string itop(string ival)
{
	string pval;
	stack<char> stack;
	for (int i = 0; i < ival.size(); i++)
	{
		//������� ������
		char cur = ival[i];
		//���� ������� - �����
		if (isdigit(cur))
		{
			//������ ���, ������� ������ � ������� �������, � ������� � �������� ������
			pval += GetNextNumber(ival, i, isdigit);
			pval += ' ';
		}
		else if (isalpha(cur))
		{
			pval += GetNextNumber(ival, i, isalpha);
			pval += ' ';
		}
		//���� ������������� ������ 
		else if (cur == '(')
		{
			//������� � � ����
			stack.push(cur);
		}
		//���� ����������� ������
		else if (cur == ')')
		{
			//������� � �������� ������ �� ����� �� ������ �� ����������� ������
			while (stack.size() > 0 && stack.top() != '(')
			{
				pval += stack.top();
				pval += ' ';
				stack.pop();
			}
			//������� ������������� ������ �� �����
			stack.pop();
		}
		//���������, ���������� �� ������ � ������ ����������
		else if (PolishExpr::operationPriority.find(cur) !=
			PolishExpr::operationPriority.end())
		{
			//���� ��, �� ������� ���������
			char op = cur;
			//�������� �� �������� ������� ��������
	
			if (op == '-' && (i == 0 || (i >= 1 && PolishExpr::operationPriority.find(ival[i - 1]) !=
				PolishExpr::operationPriority.end())))
				//���� �� - ����������� ��� � ������
				op = '~';
			//	������� � �������� ������ ��� ��������� �� �����, ������� ����� ������� ���������
			while (stack.size() > 0 && (PolishExpr::operationPriority[stack.top()] >= PolishExpr::operationPriority[op]))
			{
				char sign = stack.top();
				stack.pop();
				pval += sign;
				pval += ' ';
			}
			//	������� � ���� ��������
			stack.push(op);
		}
	}
	while (!stack.empty())
	{
		char sign = stack.top();
		stack.pop();
		pval += sign;
		pval += ' ';
	}
	//	���������� ��������� � ����������� ������
	pval.pop_back();
	return pval;
}

