#include"requirements.h"


int main()
{
	//основная задача:
	string s;
	cin >> s;
	parse(s)->derivative("x")->print();
	//Доп задача:
	/*string s;
	cin >> s;
	Expression* expr = parse(s);
	cout << endl << endl;
	expr->print();
	cout << endl;
	simplification(expr)->print();*/
}//проблема с тильдой(унарным минусом)