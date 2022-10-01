#pragma once
#include"../../Expression.h"

class Variable : public Expression
{
private:
	string val_;
	virtual void parse(string& val) override;
public:
	Variable(string val) : val_(val) {}
	void print() override;
	Expression* derivative(const string unknown) override;
	int eval(const string unknowns) override;
	Expression* simplification() override;
	string etos() override;
	Type type() override { return Type::pVariable; }
};