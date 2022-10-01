#include"Number.h"

void Number::parse(string& val)
{
	//Это есть тут только ради того, чтоб объект не был абстрактным
}

string Number::etos()
{
	return to_string(this->val_);
}

void Number::print()
{
	cout << this->val_;
}

Expression* Number::derivative(const string unknown)
{
	return new Number(0);
}

int Number::eval(const string unknowns)
{
	return this->val_;
}

Expression* Number::simplification()
{
	return this;
}