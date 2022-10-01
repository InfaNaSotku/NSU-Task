#pragma once
#include"../../Expression.h"

class Number : public Expression
{
private:
	int val_;
	virtual void parse(string& val) override;
public:
	Number(int val) : val_(val) {}
	void print() override;
	Expression* derivative(const string unknown) override;
	int eval(const string unknowns) override;
	Expression* simplification() override;
	string etos() override;
	Type type() override { return Type::pNumber; }
};