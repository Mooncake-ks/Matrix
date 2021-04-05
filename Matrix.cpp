#include <iostream>
#include <cassert>
#include <initializer_list>
class Matrix
{
public:
	Matrix();
	Matrix(int row, int col);
	Matrix(const Matrix& other);
	Matrix(const std::initializer_list< std::initializer_list<int>>& list);
	Matrix& operator =(const Matrix& other);
	Matrix operator *(const Matrix& other);
	int* operator [](int index);
	int  operator [](int indexcol);
	void cleer(Matrix& other);
	int** creature(int row,int col);
	void copy(Matrix& other,const Matrix& other_2);
	int** get_ptrarr();
	void transpose();
	~Matrix();
	void print() {
		std::cout << row << "\t" << col << "\n";
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				std::cout << ptrarr[i][j] << " ";
			}
			std::cout << std::endl;
		}
		
	}
private:
	int row, col;
	int** ptrarr;
	int *indexrow;
};
int main()
{
	Matrix A{ {1,2,3},{4,5,6},{7,8,9} };
	Matrix B{ {1,2,3},{4,5,6} };
	B.transpose();
	Matrix C;
	C = A;
	C = A * B;
	std::cout << "A :\n";
	A.print();
	std::cout << "\nB :\n";
	B.print();
	std::cout << "\nC :\n";
	C.print();
	C.transpose();
	C.print();
	system("pause");
	return 0;
}
Matrix::Matrix() :row{ 0 }, col{ 0 }, ptrarr{ nullptr }{}
Matrix::Matrix(int row, int col) : row{ row }, col{ col }
{
	ptrarr = new int* [row];
	for (int i = 0; i < row; i++)
	{
		ptrarr[i] = new int[col];
	}
}
Matrix::Matrix(const Matrix& other) : row{ other.row }, col{ other.col }
{
	this->ptrarr = creature(row, col);
	copy(*this, other);
}
Matrix::Matrix(const std::initializer_list< std::initializer_list<int>>& list)
{
	row = list.size();
	col = 0;
	for (const auto &el:list)
	{
		col = el.size();
	}
	ptrarr = creature(row, col);
	auto el = list.begin();
	for (int i = 0; i < row; i++,el++)
	{
		ptrarr[i] = new int[col];
		std::copy(el->begin(), el->end(), ptrarr[i]);
	}
}
Matrix& Matrix::operator=(const Matrix& other)
{
	cleer(*this);
	this->row = other.row;
	this->col = other.col;
	this->ptrarr = creature(row, col);
	copy(*this, other);
	return *this;
}
Matrix Matrix::operator*(const Matrix& other)
{
	int x = 0, sizerow = 0, sizecol = 0;
	sizerow = this->row;
	sizecol = other.col;
	Matrix test(sizerow, sizecol);

	if (this->col == other.row)
	{
		for (int i = 0; i < sizerow; i++)
		{
			for (int j = 0; j < sizecol; j++)
			{
				test.ptrarr[i][j] = 0;
			}

		}
		for (int i = 0; i < sizerow; i++)
		{
			for (int j = 0; j < sizecol; j++)
			{
				for (int k = 0; k < this->col; k++)
				{
					test.ptrarr[i][j] += this->ptrarr[i][k] * other.ptrarr[k][j];
				}
			}
		}
	}
	else
		std::cout << "Failed to multiply matrices\n";
	return test;
}
int* Matrix::operator[](int index)
{
	this->indexrow = ptrarr[index];
	return indexrow;
}
void Matrix::cleer(Matrix& other)
{
	for (int i = 0; i < row; i++)
	{
		delete[] other.ptrarr[i];
	}
	delete[] other.ptrarr;
}
int** Matrix::creature(int row, int col)
{
	
	int **other = new int*[row];
	for (int i = 0; i < row; i++)
	{
		other[i] = new int[col];
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			other[i][j] = 0;
		}
	}
	return other;
}
void Matrix::copy(Matrix& other, const Matrix& other_2)
{
	if (!(other.row == other_2.row && other.col == other_2.col))
	{
		return;
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			other.ptrarr[i][j] = other_2.ptrarr[i][j];
		}
	}
}
int** Matrix::get_ptrarr()
{
	return ptrarr;
}
void Matrix::transpose()
{
	if (row==col)
	{
		int x = 0;
		for (int i = 0; i < row; i++)
		{
			for (int j = i; j < col; j++)
			{
				if (!(i == j))
				{
					x = ptrarr[i][j];
					ptrarr[i][j] = ptrarr[j][i];
					ptrarr[j][i] = x;
				}
			}
		}
	
	}
	else
	{
		int** test = creature(this->col,this->row);
		for (int i = 0; i <this-> col; i++)
		{
			for (int j = 0; j < this->row; j++)
			{
				
				test[i][j] = ptrarr[j][i];
			}
		}
		cleer(*this);
		this->ptrarr = creature(col, row);
		for (int i = 0; i < col; i++)
		{
			for (int j = 0; j < row; j++)
			{
				
				ptrarr[i][j] = test[i][j];
					
				
			}
		}
		std::swap(row,col);
		
	}
}
Matrix::~Matrix()
{
	for (int i = 0; i < row; i++)
	{
		delete[] ptrarr[i];
	}
	delete[]ptrarr;
}

