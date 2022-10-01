#pragma once
#include<iostream>
#include<string>
using namespace std;
class Expression;
Expression* parse(string& val);
Expression* simplification(Expression* expr);
class Expression
{
	friend Expression* parse(string& val);//Обертка 
protected:
	void parseCh(string& val, Expression*& child);
	string GetUnknownValue(const string unknowns, const string unknown);
	virtual void parse(string& val) = 0;//передаваемая строка будет уничтожена,\
				считаем, что на вход подается Польская нотация формулы\
				!!!Эта функция - обертка функции parseCh
public:
	enum class Type
	{
		pAdd,
		pMul,
		pSub,
		pDiv,
		pVariable,
		pNumber
	};
	virtual void print() = 0;
	virtual string etos() = 0;
	virtual Expression* derivative(const string unknown) = 0;
	virtual int eval(const string unknowns) = 0;
	virtual Expression* simplification() = 0;
	virtual Type type() = 0;
};

