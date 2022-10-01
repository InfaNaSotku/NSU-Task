#include"Mul.h"
#include"../Add/Add.h"
#include"../../SingleExpression/Number/Number.h"
void Mul::parse(string& val)
{
	parseCh(val, this->s_param_);
	parseCh(val, this->f_param_);
}

Mul::~Mul()
{
	delete this->f_param_;
	delete this->s_param_;
}

string Mul::etos()
{
	return '(' + this->f_param_->etos() + '*' + this->s_param_->etos() + ')';
}

void Mul::print()
{
	cout << '(';
	this->f_param_->print();
	cout << '*';
	this->s_param_->print();
	cout << ')';
}

Expression* Mul::derivative(const string unknown)
{
	return new Add(new Mul(this->f_param_->derivative(unknown), this->s_param_), new Mul(this->f_param_, this->s_param_->derivative(unknown)));
}

int Mul::eval(const string unknowns)
{
	return this->f_param_->eval(unknowns) * this->s_param_->eval(unknowns);
}

Expression* Mul::simplification()
{
	this->f_param_ = this->f_param_->simplification();
	this->s_param_ = this->s_param_->simplification();
	//����� ��������� �������
	/*
	a.���� ��������� ����� ��������� ��� ������ - ����
	�����������(�.�.� ��� ��� ����������), �� ���������
	���������� �� ��������� ����������.
	b.���� ��������� ������������ �� ���� ��������� �� 0,
	�� ��� ���������� �� ��������� 0.
	c.���� ��������� ������������ �� ���� ��������� �� 1,
	�� ��� ���������� �� ������ ���������.
	d.���� ��������� ������������ �� ���� ��������� ����
	���������� ������������, �� ��� ���������� ��
	��������� 0.
	*/
	//���� ����� ����������� ����������� ��� ������ �����������\
	����� ��� ������, ��� ��������� ����� �������� ����� ������ ��� Number, ��������� eval ��� ��������\
	������ ����� �������� �����

	//a),�������� b)
	if (this->f_param_->type() == Expression::Type::pNumber &&
		this->s_param_->type() == Expression::Type::pNumber)//����� ���� � �������
	{
		return new Number(this->eval(""));//��������� ��������
	}
	else if (this->f_param_->type() == Expression::Type::pNumber ||
		this->s_param_->type() == Expression::Type::pNumber)
	{
		//b)
		if (this->f_param_->type() == Expression::Type::pNumber)
			if (this->f_param_->eval("") == 0)
				return new Number(0);
		if (this->s_param_->type() == Expression::Type::pNumber)
			if (this->s_param_->eval("") == 0)
				return new Number(0);
		//c)
		if (this->f_param_->type() == Expression::Type::pNumber)
			if (this->f_param_->eval("") == 1)
				return this->s_param_;
		if (this->s_param_->type() == Expression::Type::pNumber)
			if (this->s_param_->eval("") == 1)
				return this->f_param_;
	}
	//d)
	else if (this->f_param_->type() == this->s_param_->type())//���������� ����
	{
		if (this->type() == Expression::Type::pSub)
			if (this->f_param_->etos() == this->s_param_->etos())
				return new Number(0);
	}
	return this;
}