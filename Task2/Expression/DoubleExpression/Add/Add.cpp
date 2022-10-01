#include"../../../requirements.h"

void Add::parse(string& val)
{
	parseCh(val, this->s_param_);
	parseCh(val, this->f_param_);
}

Add::~Add()
{
	delete this->f_param_;
	delete this->s_param_;
}

string Add::etos()
{
	return '(' + this->f_param_->etos() + '+' + this->s_param_->etos() + ')';
}

void Add::print()
{
	cout << '(';
	this->f_param_->print();
	cout << '+';
	this->s_param_->print();
	cout << ')';
}

Expression* Add::derivative(const string unknown)
{
	return new Add(this->f_param_->derivative(unknown), this->s_param_->derivative(unknown));
}

int Add::eval(const string unknowns)
{
	return this->f_param_->eval(unknowns) + this->s_param_->eval(unknowns);
}

Expression* Add::simplification()
{
	this->f_param_ = this->f_param_->simplification();
	this->s_param_ = this->s_param_->simplification();
	//имеем несколько случаев
	/*
	a.Если выражение можно вычислить без какого - либо
	означивания(т.е.в нем нет переменных), то выражение
	заменяется на результат вычисления.
	b.Если выражение представляет из себя умножение на 0,
	то оно заменяется на константу 0.
	c.Если выражение представляет из себя умножение на 1,
	то оно заменяется на второй множитель.
	d.Если выражение представляет из себя вычитание двух
	одинаковых подвыражений, то оно заменяется на
	константу 0.
	*/
	//ниже будем производить означивание без строки означивания\
	можем так делать, ибо совершать такие действия будем только над Number, результат eval для которого\
	всегда равен значению числа

	//a),частично b)
	if (this->f_param_->type() == Expression::Type::pNumber &&
		this->s_param_->type() == Expression::Type::pNumber)//имеем дело с числами
	{
		return new Number(this->eval(""));//результат считаемс
	}
	//d)
	else if (this->f_param_->type() == this->s_param_->type())//одинаковые типы
	{
		if (this->type() == Expression::Type::pSub)
			if (this->f_param_->etos() == this->s_param_->etos())
				return new Number(0);
	}
	return this;
}