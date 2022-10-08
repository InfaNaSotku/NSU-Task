#include"Map/HashMap.h"
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
int main()
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
	

	return 0;
}