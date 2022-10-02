
#include"Matrtix/Matrix.h"

int main()
{
	//основная задача
	int n;
	cin >> n;
	int k;
	cin >> k;
	int* ptr = new int[n];
	for (int i = 0; i < n; i++)
	{
		ptr[i] = k;
	}
	Matrix K(n, ptr);
	Matrix A(n), B(n), C(n), D(n);
	cin >> A >> B >> C >> D;
	cout << (A + (B * (-C)) + K) * (-D);
	//доп задача со стоблцами
	/*int n;
	cin >> n;
	Matrix A(n);
	cin >> A;
	int col, pos;
	cin >> col >> pos;
	int val;
	cin >> val;
	A(col)[pos] = val;
	cout << A << endl;
	cout << A(col)[pos];*/

	//доп задача со строками
	/*int n;
	cin >> n;
	Matrix A(n);
	cin >> A;
	int line, pos;
	cin >> line >> pos;
	int val;
	cin >> val;
	A[line][pos] = val;
	cout << A << endl;
	cout << A[line][pos];*/
}
