#include"Map/HashMap.h"
#include"Map/MultiHashMap.h"
#include"../Task1/Matrtix/Matrix.h"
using namespace MapSpace;
#include<string>
#include<iostream>
using namespace std;
template<class K, class V>
void solve(HashMap<K, V> arr)
{
	int n;
	cin >> n;
	for (size_t i = 0; i < n; i++)
	{
		char commands; 
		cin >> commands;
		if (commands == 'A')
		{
			K key;
			V val;
			cin >> key >> val;
			arr.Add(key, val);
		}
		else if (commands == 'R')
		{
			K key;
			cin >> key;
			arr.Delete(key);
		}
	}
	cout << arr.size() << ' ';
	HashMap<V, bool> heap;
	for (auto& it : arr)
	{
		heap.Add(it.val_, true);
	}
	cout << heap.size();
}

void MainSolve()
{
	char key, val;
	cin >> key >> val;
	if (key == 'I')//int
	{
		if (val == 'I')
			solve(HashMap<int, int>());
		else if (val == 'D')
			solve(HashMap<int, double>());
		else if (val == 'S')
			solve(HashMap<int, string>());
	}
	else if (key == 'D')
	{
		if (val == 'I')
			solve(HashMap<double, int>());
		else if (val == 'D')
			solve(HashMap<double, double>());
		else if (val == 'S')
			solve(HashMap<double, string>());
	}
	else if (key == 'S')
	{
		if (val == 'I')
			solve(HashMap<string, int>());
		else if (val == 'D')
			solve(HashMap<string, double>());
		else if (val == 'S')
			solve(HashMap<string, string>());
	}
}

void AdditionalSolve()
{
	MultiHashMap<string, int> arr;
	arr.Add("Max", 5);
	arr.Add("Max", 6);
	arr.Add("Max", 152);
	arr.Add("Jora", 2);
	//
	cout << arr.GetK("Max")[0] << ' ';
	arr.GetK("Max")[0] = 3;
	cout << arr.GetK("Max")[0] << ' ';
	cout << arr.GetK("Max")[1];
	cout << endl << endl;
	//
	cout << "Max counts:" << arr.SizeK("Max") << ' ' << "Jora counts:" << arr.SizeK("Jora") << endl;
	for (auto& it : arr)
		cout << it.key_ << ' ' << it.val_ << endl;
	arr.Delete("Max");
	cout << "------------------------------------------------------" << endl;
	cout << "Max counts:" << arr.SizeK("Max") << ' ' << "Jora counts:" << arr.SizeK("Jora") << endl;
	for (auto& it : arr)
		cout << it.key_ << ' ' << it.val_ << endl;
	cout << "------------------------------------------------------" << endl;\
	arr.Delete("Jora");
	cout << "Max counts:" << arr.SizeK("Max") << ' ' << "Jora counts:" << arr.SizeK("Jora") << endl;
	for (auto& it : arr)
		cout << it.key_ << ' ' << it.val_ << endl;
	cout << endl;
	//
	Matrix kek(10);
	HashMap<Matrix, int> newarr;
	kek[0][0] = 2;
	newarr.Add(kek, 2);
	newarr.Add(Matrix(10), 3);
	for (auto& it : newarr)
	{
		cout << it.key_ << it.val_ << endl;
	}

}

int main()
{
	//MainSolve();
	//AdditionalSolve();
	return 0;
}