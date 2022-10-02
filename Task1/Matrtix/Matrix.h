#pragma once
#include<iostream>
using namespace std;
class Matrix
{
private:
	int** m_matrix_;
	size_t m_matrix_size_;
	void Init(const size_t& matrix_size, int* diag_ptr);
public:
	Matrix() : m_matrix_size_(NULL), m_matrix_(NULL) {}
	Matrix(const size_t& matrix_size);
	Matrix(const size_t& matrix_size, int* diag_ptr) { Init(matrix_size, diag_ptr); }
	Matrix(Matrix& matrix) : m_matrix_size_(NULL), m_matrix_(NULL) { *this = matrix; }
	~Matrix();
	Matrix operator+(const Matrix& s);
	Matrix operator-(const Matrix& s);
	Matrix operator*(const Matrix& s);

	//доп задача началоs
	int* operator[](const size_t& pos);
	int* operator[](const size_t& pos) const;
	class MyMatrixColumn
	{
	private:
		size_t cur_colomn_pos_;
		Matrix* m_matrix_ptr_;
	public:
		explicit MyMatrixColumn(const size_t& colomn, Matrix* matrix_ptr) : cur_colomn_pos_(colomn), m_matrix_ptr_(matrix_ptr) {}
		int& operator[](const size_t&);
	};

	MyMatrixColumn& operator()(const size_t& pos);
	//доп задача конец

	bool operator!=(const Matrix& s);
	bool operator==(const Matrix& s);

	Matrix operator-();
	Matrix& operator=(const Matrix& matrix);
	friend istream& operator>>(istream& input, Matrix& matrix);
	friend ostream& operator<<(ostream& output, const Matrix& matrix);

	Matrix operator()(const size_t& line_pos, const size_t& column_pos);
};
