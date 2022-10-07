#include"Map/HashMap.h"
using namespace MapSpace;

int main()
{

	HashMap<int, int> map;
	map[2] = 2;
	cout << map[1] << ' ' << map[2] << ' ' << map[3] << ' ' << map[2];
	return 0;
}