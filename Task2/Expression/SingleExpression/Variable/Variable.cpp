#include"Variable.h"
#include"../Number/Number.h"

void Variable::parse(string& val)
{
	//Это есть тут только ради того, чтоб объект не был абстрактным
}

string Variable::etos()
{
	return this->val_;
}

void Variable::print()
{
	cout << this->val_;
}

Expression* Variable::derivative(const string unknown)
{
	if(this->val_ == unknown)
		return new Number(1);
	else
		return new Number(0);
}

int Variable::eval(const string unknowns)
{
	string temp = this->GetUnknownValue(unknowns, this->val_);
	if (temp.size())
		return stoi(temp);
	else
		throw exception("Unknown doesn't exist!");
}

Expression* Variable::simplification()
{
	return this;
}