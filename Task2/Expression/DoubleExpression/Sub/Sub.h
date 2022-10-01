#pragma once
#include"../../Expression.h"

class Sub : public Expression
{
private:
	Expression* f_param_;
	Expression* s_param_;
	virtual void parse(string& val) override;
public:
	//����������� ���-�� ����, ��� ���������� ������ ���������� ���������
	Sub(Expression* f_param, Expression* s_param) : f_param_(f_param), s_param_(s_param) {}
	~Sub();
	void print() override;
	Expression* derivative(const string unknown) override;
	int eval(const string unknowns) override;
	Expression* simplification() override;
	string etos() override;
	Type type() override { return Type::pSub; }
};