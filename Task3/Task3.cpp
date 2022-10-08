#include"Map/HashMap.h"
using namespace MapSpace;
#include<iostream>
#include<map>
using namespace std;
int main()
{
	map<int, int> aa;
	HashMap<int, int> map;
	map.Add(1, 2);
	map.Add(100, 50);
	map.Add(100, 20);
	map.Add(101, 21);
	for (auto& it : map)
		cout << it.key_ << ' ' << it.val_ << endl;
	return 0;
}