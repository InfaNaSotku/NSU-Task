#include"PolishExpr.h"
map<char, int> PolishExpr::operationPriority = {
	{'(', 0},
	{'+', 1},
	{'-', 1},
	{'*', 2},
	{'/', 2},
	{'^', 3},
	{'~', 4}	//	Унарный минус
};
string GetNextNumber(string val, int& pos, int __cdecl comp(int))
{
	//Хранит число
	string rez = "";

	//Перебираем строку
	for (; pos < val.size(); pos++)
	{
		//Разбираемый символ строки
		char num = val[pos];

		//Проверяем, является символ числом
		if (comp(num))
			//Если да - прибавляем к строке
			rez += num;
		else
		{
			//Если нет, то перемещаем счётчик к предыдущему символу
			pos--;
			//И выходим из цикла
			break;
		}
	}

	//Возвращаем число
	return rez;
}

string itop(string ival)
{
	string pval;
	stack<char> stack;
	for (int i = 0; i < ival.size(); i++)
	{
		//Текущий символ
		char cur = ival[i];
		//Если симовол - цифра
		if (isdigit(cur))
		{
			//Парсим его, передав строку и текущую позицию, и заносим в выходную строку
			pval += GetNextNumber(ival, i, isdigit);
			pval += ' ';
		}
		else if (isalpha(cur))
		{
			pval += GetNextNumber(ival, i, isalpha);
			pval += ' ';
		}
		//Если открывающаяся скобка 
		else if (cur == '(')
		{
			//Заносим её в стек
			stack.push(cur);
		}
		//Если закрывающая скобка
		else if (cur == ')')
		{
			//Заносим в выходную строку из стека всё вплоть до открывающей скобки
			while (stack.size() > 0 && stack.top() != '(')
			{
				pval += stack.top();
				pval += ' ';
				stack.pop();
			}
			//Удаляем открывающуюся скобку из стека
			stack.pop();
		}
		//Проверяем, содержится ли символ в списке операторов
		else if (PolishExpr::operationPriority.find(cur) !=
			PolishExpr::operationPriority.end())
		{
			//Если да, то сначала проверяем
			char op = cur;
			//Является ли оператор унарным символом
	
			if (op == '-' && (i == 0 || (i >= 1 && PolishExpr::operationPriority.find(ival[i - 1]) !=
				PolishExpr::operationPriority.end())))
				//Если да - преобразуем его в тильду
				op = '~';
			//	Заносим в выходную строку все операторы из стека, имеющие более высокий приоритет
			while (stack.size() > 0 && (PolishExpr::operationPriority[stack.top()] >= PolishExpr::operationPriority[op]))
			{
				char sign = stack.top();
				stack.pop();
				pval += sign;
				pval += ' ';
			}
			//	Заносим в стек оператор
			stack.push(op);
		}
	}
	while (!stack.empty())
	{
		char sign = stack.top();
		stack.pop();
		pval += sign;
		pval += ' ';
	}
	//	Возвращаем выражение в постфиксной записи
	pval.pop_back();
	return pval;
}

