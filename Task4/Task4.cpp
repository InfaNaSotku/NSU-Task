#include"StateMachine/StateMachine.h"
#include<fstream>
using namespace StateMachine;
using namespace std;




void MainSolve()
{
	int n;
	cin >> n;
	Machine m(n, Machine::MachineUpdateTypeState::pDYNAMICAL);
	int k;
	cin >> k; 
	m.SetInitialCondition(k);
	int f;
	cin >> f;
	for (size_t i = 0; i < f; i++)
	{
		int fi;
		cin >> fi;
		m.SetFinalCondition(fi);
	}
	int p;
	cin >> p;
	for (size_t i = 0; i < p; i++)
	{
		int from, to;
		char val;
		cin >> from >> to >> val;
		m.UpdateTransition(from, to, val);
	}
	Machine m1(Machine::Determinise(m));
	int t;
	cin >> t;	
	for (size_t i = 0; i < t; i++)
	{
		string str;
	    cin >> str;
		if (m1.CheckRecognizability(str))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
}

void AdditionalSolve()
{
	ifstream fin;
	fin.open("input.txt");
	int n;
	fin >> n;
	Machine m(n, Machine::MachineUpdateTypeState::pDYNAMICAL);
	int k;
	fin >> k;
	m.SetInitialCondition(k);
	int f;
	fin >> f;
	for (size_t i = 0; i < f; i++)
	{
		int fi;
		fin >> fi;
		m.SetFinalCondition(fi);
	}
	int p;
	fin >> p;
	for (size_t i = 0; i < p; i++)
	{
		int from, to;
		char val;
		fin >> from >> to >> val;
		m.UpdateTransition(from, to, val);
	}
	m.print(cout);
	cout << "--------------------------------------" << endl;
	Machine m1(Machine::Determinise(m));
	m1.print(cout);
	cout << "--------------------------------------" << endl;

	string s;
	cin >> s;
	Machine::parse(s).print(cout);
	cout << "--------------------------------------" << endl;
	int t;
	cin >> t;
	for (size_t i = 0; i < t; i++)
	{
		string str;
		cin >> str;
		if (m1.CheckRecognizability(str))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	fin.close();
}


int main()
{
	MainSolve();
	//AdditionalSolve();
	return 0;
}

