#include"Matrix.h"



Matrix::Matrix(const size_t& matrix_size)
{
	int* diag_ptr = new int[matrix_size];
	for (size_t i = 0; i < matrix_size; i++)
	{
		diag_ptr[i] = 1;
	}
	Init(matrix_size, diag_ptr);
}
Matrix::~Matrix()
{
	for (size_t i = 0; i < this->m_matrix_size_; i++)
	{
		delete this->m_matrix_[i];
	}
	delete[] this->m_matrix_;
}
void Matrix::Init(const size_t& matrix_size, int* diag_ptr)
{
	if (!matrix_size)
	{
		throw invalid_argument("Bad size");
	}
	this->m_matrix_size_ = matrix_size;
	int** temp_matrix = new int* [matrix_size];
	for (size_t i = 0; i < matrix_size; i++)
	{
		int* temp_line = new int[matrix_size];
		for (size_t j = 0; j < matrix_size; j++)
		{
			if (i == j)
			{
				temp_line[j] = diag_ptr[i];
			}
			else {
				temp_line[j] = 0;
			}
		}
		temp_matrix[i] = temp_line;
	}
	this->m_matrix_ = temp_matrix;
}

//доп задача начало
int* Matrix::operator[](const size_t& pos)
{
	if (pos < 0 || pos >= this->m_matrix_size_)
	{
		throw invalid_argument("Bad size");
	}
	return this->m_matrix_[pos];
}
int* Matrix::operator[](const size_t& pos) const
{
	if (pos < 0 || pos >= this->m_matrix_size_)
	{
		throw invalid_argument("Bad size");
	}
	return this->m_matrix_[pos];
}
int Matrix::MyMatrixColumn::operator[](const size_t& pos)
{
	return this->m_matrix_ptr_->m_matrix_[pos][this->cur_colomn_pos_];
}
Matrix::MyMatrixColumn Matrix::operator()(const size_t& pos)
{
	MyMatrixColumn cur_colomn(pos, this);
	return cur_colomn;
}
//доп задача конец

Matrix Matrix::operator-(const Matrix& s)
{
	if (this->m_matrix_size_ != s.m_matrix_size_)
	{
		throw invalid_argument("The size of the matrices must be equal");
	}
	Matrix temp(this->m_matrix_size_);
	for (size_t i = 0; i < this->m_matrix_size_; i++)
	{
		for (size_t j = 0; j < this->m_matrix_size_; j++)
		{
			temp[i][j] = (*this)[i][j] - s[i][j];
		}
	}
	return temp;
}
Matrix Matrix::operator+(const Matrix& s)
{
	if (this->m_matrix_size_ != s.m_matrix_size_)
	{
		throw invalid_argument("The size of the matrices must be equal");
	}
	Matrix temp(this->m_matrix_size_);
	for (size_t i = 0; i < this->m_matrix_size_; i++)
	{
		for (size_t j = 0; j < this->m_matrix_size_; j++)
		{
			temp[i][j] = (*this)[i][j] + s[i][j];
		}
	}
	return temp;
}
Matrix Matrix::operator*(const Matrix& s)
{
	if (this->m_matrix_size_ != s.m_matrix_size_)
	{
		throw invalid_argument("The size of the matrices must be equal");
	}
	Matrix temp(this->m_matrix_size_);
	for (size_t i = 0; i < this->m_matrix_size_; i++)
	{
		for (size_t j = 0; j < this->m_matrix_size_; j++)
		{
			temp[i][j] = 0;
			for (size_t k = 0; k < this->m_matrix_size_; k++)
			{
				temp[i][j] = temp[i][j] + ((*this)[i][k] * s[k][j]);
			}
		}
	}
	return temp;
}
bool Matrix::operator!=(const Matrix& s)
{
	if (this->m_matrix_size_ != s.m_matrix_size_)
	{
		return true;
	}
	for (size_t i = 0; i < this->m_matrix_size_; i++)
	{
		for (size_t j = 0; j < this->m_matrix_size_; j++)
		{
			if ((*this)[i][j] != s[i][j])
			{
				return true;
			}
		}
	}
	return false;
}
bool Matrix::operator==(const Matrix& s)
{
	if (this->m_matrix_size_ != s.m_matrix_size_)
	{
		return false;
	}
	for (size_t i = 0; i < this->m_matrix_size_; i++)
	{
		for (size_t j = 0; j < this->m_matrix_size_; j++)
		{
			if ((*this)[i][j] != s[i][j])
			{
				return false;
			}
		}
	}
	return true;
}
//пусть -a - транспонирования матрицы a
Matrix Matrix::operator-()
{
	Matrix temp_matrix(this->m_matrix_size_);
	for (size_t i = 0; i < this->m_matrix_size_; i++)
	{
		int* temp_line = new int[this->m_matrix_size_];
		for (size_t j = 0; j < this->m_matrix_size_; j++)
		{

			temp_matrix[i][j] = this->m_matrix_[j][i];
		}
	}
	return temp_matrix;
}
Matrix& Matrix::operator=(const Matrix& matrix)
{
	this->m_matrix_size_ = matrix.m_matrix_size_;
	delete[] this->m_matrix_;
	this->m_matrix_ = new int* [this->m_matrix_size_];
	int** temp_matrix = new int* [this->m_matrix_size_];

	for (size_t i = 0; i < this->m_matrix_size_; i++)
	{
		int* temp_line = new int[this->m_matrix_size_];
		for (size_t j = 0; j < this->m_matrix_size_; j++)
		{
			temp_line[j] = matrix[i][j];
		}
		this->m_matrix_[i] = temp_line;
	}
	return *this;
}
istream& operator>>(istream& input, Matrix& matrix)
{
	size_t matrix_size;
	if (!matrix.m_matrix_size_)
	{
		input >> matrix_size;
	}
	else
	{
		matrix_size = matrix.m_matrix_size_;
	}
	if (!matrix_size)
	{
		throw invalid_argument("Bad size");
	}
	Matrix temp(matrix_size);
	for (size_t i = 0; i < matrix_size; i++)
	{
		for (size_t j = 0; j < matrix_size; j++)
		{
			input >> temp.m_matrix_[i][j];
		}
	}
	matrix = temp;
	return input;
}
ostream& operator<<(ostream& output, const Matrix& matrix)
{
	//output << matrix.m_matrix_size_ << endl;
	for (size_t i = 0; i < matrix.m_matrix_size_; i++)
	{
		for (size_t j = 0; j < matrix.m_matrix_size_; j++)
		{
			output << matrix.m_matrix_[i][j] << ' ';
		}
		cout << endl;
	}
	return output;
}

Matrix Matrix::operator()(const size_t& line_pos, const size_t& column_pos)
{
	if (line_pos < 0 || line_pos >= this->m_matrix_size_ || column_pos < 0 || column_pos >= this->m_matrix_size_)
	{
		throw invalid_argument("Bad pos");
	}
	Matrix temp(this->m_matrix_size_ - 1);
	size_t temp_i = 0, temp_j = 0;
	for (size_t i = 0; i < this->m_matrix_size_; i++)
	{
		if (i == line_pos)
		{
			continue;
		}
		for (size_t j = 0; j < this->m_matrix_size_; j++)
		{
			if (j == column_pos)
			{
				continue;
			}
			temp[temp_i][temp_j] = this->m_matrix_[i][j];
			temp_j++;
		}
		temp_i++;
	}
	return temp;
}