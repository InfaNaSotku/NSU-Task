#include"../requirements.h"
#include"../PolishExpr/PolishExpr.h"
string Expression::GetUnknownValue(const string unknowns, const string unknown)
{
	string temp = unknown;
	if (unknown[0] == '-')//������
		temp.erase(temp.begin());
	int pos = unknowns.find(temp);
	if (pos >= 0)
		return unknowns.substr(pos + 4 + temp.size(), unknowns.find(';', pos + 5) - pos - 5);
	else
		return "";
}

Expression* get_next_expr(string& val)
{
	if (!val.size())//���-�� ����� �� ��� � �� �������� �� ������ �������
		throw exception("Bad val string!");
	//������� ������� �������
	int rpos = val.size() - 1;
	while (val[rpos] == ' ' && rpos > 0)
		rpos--;
	if (val[rpos] == ' ')//������ ���� �� ������
		throw exception("Bad val");
	int lpos = rpos;
	bool tilda = false;
	if (val[rpos] == '~')
	{
		tilda = true;
		val = val.substr(0, rpos);
		rpos = val.size() - 1;
		while (val[rpos] == ' ' && rpos > 0)
			rpos--;
		if (val[rpos] == ' ')//������ ���� �� ������
			throw exception("Bad val");
		lpos = rpos;
	}
	if (isdigit(val[rpos]))
	{
		while (lpos > 0)
			if (isdigit(val[lpos - 1]) || val[lpos - 1] == '~')
				lpos--;
			else
				break;
		string temp = val.substr(lpos, rpos - lpos + 1);
		val = val.substr(0, lpos);
		if(tilda)
			return new Number(-stoi(temp));
		else
			return new Number(stoi(temp));
		//cout << stoi(val.substr(lpos, rpos - lpos + 1));
	}
	else if (isalpha(val[rpos]))
	{
		while (lpos > 0)
			if (isalpha(val[lpos - 1]) || val[lpos - 1] == '~')
				lpos--;
			else
				break;
		string temp = val.substr(lpos, rpos - lpos + 1);
		val = val.substr(0, lpos);
		if(tilda)
			temp.insert(temp.begin(), '-');
		return new Variable(temp);
	}
	else
	{
		char sign = val[rpos];//�������� ��� ������� � ����� ��������
		val = val.substr(0, rpos);
		switch (sign)
		{
		case '+':
			return new Add(NULL, NULL);
			break;
		case '-':
			return new Sub(NULL, NULL);
			break;
		case '/':
			return new Div(NULL, NULL);
			break;
		case '*':
			return new Mul(NULL, NULL);
			break;
		default:
			break;
		}
	}
}

Expression* parse(string& val)
{
	//����������� �� ��������� � �����������
	val = itop(val);
	//� ��� ��� ��� �������� � ����������� �������� �������� ��������
	Expression* expr = get_next_expr(val);
	if (expr->type() != Expression::Type::pNumber && expr->type() != Expression::Type::pVariable)//��� �����, ���� ������� ������
		expr->parse(val);
	return expr;
}

void Expression::parseCh(string& val, Expression*& child)
{
	child = get_next_expr(val);
	if (child->type() != Expression::Type::pNumber && child->type() != Expression::Type::pVariable)//��� �����, ���� ������� ������
		child->parse(val);
	//��� ������� ����� � ���� ����� ��������� ���� ������������......
}

Expression* simplification(Expression* expr)
{
	string temp = expr->etos();
	return parse(temp)->simplification();
}
