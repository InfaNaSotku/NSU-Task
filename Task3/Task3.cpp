#include"Map/HashMap.h"
using namespace MapSpace;
#include<iostream>
using namespace std;
int main()
{

	HashMap<int, int> map;
	map.Add(1, 2);
	cout << map.Get(1);
	map.Add(100, 50);
	cout << map.Get(1) << ' ' << map.Get(100) << endl;
	map.Delete(1);
	cout << map.Get(100); cout << ' ' << map.Get(1);
	return 0;
}