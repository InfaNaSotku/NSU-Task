#include"../requirements.h"
#include"../PolishExpr/PolishExpr.h"
string Expression::GetUnknownValue(const string unknowns, const string unknown)
{
	int pos = unknowns.find(unknown);
	if (pos >= 0)
		return unknowns.substr(pos + 4 + unknown.size(), unknowns.find(';', pos + 5) - pos - 5);
	else
		return "";
}

Expression* get_next_expr(string& val)
{
	if (!val.size())//что-то пошло не так и мы вылетели за предел формулы
		throw exception("Bad val string!");
	//скипаем вонючии пробелы
	int rpos = val.size() - 1;
	while (val[rpos] == ' ' && rpos > 0)
		rpos--;
	if (val[rpos] == ' ')//такого быть не должно
		throw exception("Bad val");
	int lpos = rpos;
	if (isdigit(val[rpos]))
	{
		while (lpos > 0)
			if (isdigit(val[lpos - 1]) || val[lpos - 1] == '~')
				lpos--;
			else
				break;
		if (val[lpos] == '~')
			val[lpos] = '-';
		string temp = val.substr(lpos, rpos - lpos + 1);
		val = val.substr(0, lpos);
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
		return new Variable(temp);
	}
	else
	{
		char sign = val[rpos];//остается ток вариант с одним символом
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
	//преобразуем из инфиксной в постфиксную
	val = itop(val);
	//А вот тут уже спокойно с постфиксной польской нотацией работаем
	Expression* expr = get_next_expr(val);
	if (expr->type() != Expression::Type::pNumber && expr->type() != Expression::Type::pVariable)//тут знаки, надо парсить дальше
		expr->parse(val);
	return expr;
}

void Expression::parseCh(string& val, Expression*& child)
{
	child = get_next_expr(val);
	if (child->type() != Expression::Type::pNumber && child->type() != Expression::Type::pVariable)//тут знаки, надо парсить дальше
		child->parse(val);
	//как хочется питсы и чтоб знаки выражений сами определялись......
}

Expression* simplification(Expression* expr)
{
	string temp = expr->etos();
	return parse(temp)->simplification();
}
