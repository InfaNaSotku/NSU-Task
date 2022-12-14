#pragma once
#include<iostream>
using std::istream;
using std::ostream;
using std::cin;
using std::exception;
using std::endl;
using std::cout;
constexpr long long base1 = 111;
constexpr long long base2 = 111;
class Matrix
{
private:
	int** m_matrix_;
	size_t m_matrix_size_;
	void Init(const size_t& matrix_size, int* diag_ptr);
public:
	Matrix() : m_matrix_size_(0), m_matrix_(nullptr) {}
	Matrix(const size_t& matrix_size);
	Matrix(const size_t& matrix_size, int* diag_ptr) { Init(matrix_size, diag_ptr); }
	Matrix(const Matrix& matrix) : m_matrix_size_(0), m_matrix_(nullptr) { *this = matrix; }
	~Matrix();
	Matrix operator+(const Matrix& s);
	Matrix operator-(const Matrix& s);
	Matrix operator*(const Matrix& s);


	//??? ?????? ??????s
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

	MyMatrixColumn operator()(const size_t& pos);
	//??? ?????? ?????

	bool operator!=(const Matrix& s);
	bool operator==(const Matrix& s);

	Matrix operator-();
	Matrix& operator=(const Matrix& matrix);
	friend istream& operator>>(istream& input, Matrix& matrix);
	friend ostream& operator<<(ostream& output, const Matrix& matrix);

	Matrix operator()(const size_t& line_pos, const size_t& column_pos);

	size_t GetHash() const;
};


namespace std
{
	template<>
	struct hash<Matrix>
	{
		size_t operator()(const Matrix& k) const
		{
			return k.GetHash();
		}
	};
}