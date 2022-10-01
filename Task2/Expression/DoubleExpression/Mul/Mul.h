#pragma once
#include"../../Expression.h"

class Mul : public Expression
{
private:
	Expression* f_param_;
	Expression* s_param_;
	virtual void parse(string& val) override;
public:
	//гарантируем где-то себе, что передаются только правильные указатели
	Mul(Expression* f_param, Expression* s_param) : f_param_(f_param), s_param_(s_param) {}
	~Mul();
	void print() override;
	Expression* derivative(const string unknown) override;
	int eval(const string unknowns) override;
	Expression* simplification() override;
	string etos() override;
	Type type() override { return Type::pMul; }
};