#include"Div.h"
#include"../Sub/Sub.h"
#include"../Mul/Mul.h"
#include"../../SingleExpression/Number/Number.h"

void Div::parse(string& val)
{
	parseCh(val, this->s_param_);
	parseCh(val, this->f_param_);
}
Div::~Div()
{
	delete this->f_param_;
	delete this->s_param_;
}

string Div::etos()
{
	return '(' + this->f_param_->etos() + '/' + this->s_param_->etos() + ')';
}

void Div::print()
{
	cout << '(';
	this->f_param_->print();
	cout << '/';
	this->s_param_->print();
	cout << ')';
}

Expression* Div::derivative(const string unknown)
{
	return new Div(new Sub(new Mul(this->f_param_->derivative(unknown), this->s_param_), new Mul(this->f_param_, this->s_param_->derivative(unknown))), new Mul(this->s_param_, this->s_param_));
}

int Div::eval(const string unknowns)
{
	return this->f_param_->eval(unknowns) / this->s_param_->eval(unknowns);
}

Expression* Div::simplification()
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
	//d)
	else if (this->f_param_->type() == this->s_param_->type())//���������� ����
	{
		if (this->type() == Expression::Type::pSub)
			if (this->f_param_->etos() == this->s_param_->etos())
				return new Number(0);
	}
	return this;
}