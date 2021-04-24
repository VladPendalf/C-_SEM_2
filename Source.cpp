#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <typeinfo>
#include <iomanip>

using namespace std;


//------------------������������ ������ ������-------------------//
/*
					std::exception
						 ^
						 |
						 |
						 |
				     Exception
					 ^        ^
					/          \
				   /            \
				  /              \
		IndexOutOfBounds        WrongDimensionsException
		 Exception                         ^
										   |
										   |
										   |
							    WrongSizeException
*/
//-------------------------------------------------------------//


class Exception : public exception
{
protected:
	string err;
public:
	Exception(const char* str)
	{
		err = string(str);
	}

	Exception(string& str)
	{
		err = str;
	}

	Exception(const Exception& err)
	{
		this->err = err.err;
	}

	virtual ~Exception() {};

	virtual void print() const
	{
		cout << "\nError - " << err << endl;
	}
};

class IndexOutOfBoundsException : public Exception
{
protected:
	int row, columns;
public:
	IndexOutOfBoundsException(string& str, int& r, int& clmn) : Exception(str)
	{
		row = r;
		columns = clmn;
	}

	virtual void print() const
	{
		cout << err << "\n������� � ������ ->" << row << " � �������� -> " << columns << " ����� �� ������� �������\n\a";
	}

};

class WrongDimensionsException : public Exception
{
protected:
	int r_1, c_1, r_2, c_2;
public:
	WrongDimensionsException(string& str, int r1, int c1, int r2, int c2) : Exception(str), r_1(r1), r_2(r2), c_1(c1),c_2(c2) {}

	virtual void print() const
	{
		cout << err << "\n�������� � ������� ��������� ������: A( " << r_1 << " , " << c_1 << " ) � B( " << r_2 << " , " << c_2 << " ) ����������\n\a";
	}
};

//�������� �� �������� ������, �.�. ������� : "�������� ������, � ������� ���������� ������������ �������� �� ������ ������ �������" - �� �������� � ����� ���������.
class WrongSizeException : public Exception
{
protected:
	int rw, cl;
public:
	WrongSizeException(string& str, int r, int c) : Exception(str), rw(r), cl(c) { }

	virtual void print() const
	{
		cout << err << "\n�� ����� ������������ ������� ������� -> ( " << rw << " , " << cl << ")\n\a";
	}
};

class IncorrectDataInMatrix : public Exception
{
private:
	int r, c;
public:
	IncorrectDataInMatrix(string& str, int rw, int cl) : Exception(str), r(rw), c(cl) {}

	virtual void print() const
	{
		cout << err << "\n�� ����� ������������ ������ � �������, ������� -> < " << r << " , " << c << " >\n\a";
	}
};

template <typename temp>
class BaseMatrix
{
protected:
	temp** arr;
	int row, columns;
public:
	BaseMatrix(int r = 2, int cl = 2) : row(r), columns(cl)
	{
		if (r <= 0 || cl <= 0)
		{
			//throw WrongSizeException("������ � �������� �������", row, columns);
			cout << "Err";
		}

		//�������� �������
		arr = new temp * [row];

		for (int i = 0; i < row; ++i)
		{
			arr[i] = new temp[columns];
		}
	}

	BaseMatrix(const BaseMatrix& matrix)
	{
		row = matrix.row;
		columns = matrix.columns;

		arr = new temp * [row];

		for (int i = 0; i < row; ++i)
		{
			arr[row] = new temp[columns];
		}

		for (int i = 0; i < row ; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				arr[i][j] = matrix.arr[i][j];
			}
		}
	}

	~BaseMatrix()
	{
		if (arr != nullptr) 
		{
			for (int i = 0; i < row; ++i)
			{
				delete[] arr[i];
			}
			delete[] arr;
			arr = nullptr;
		}
	}

	virtual void print()
	{
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				cout << std::left << std::setw(9) << std::setprecision(3) << arr[i][j] << ' ';
			}
			cout << '\n';
		}
	}

	virtual temp& operator()(int rw, int cln) const
	{
		if (rw < 0 || cln < 0 || rw > row || cln > columns)
		{
			//throw IndexOutOfBoundsException("������ � ��������� �� ������� -> ", rw, cln);
			cout << "err";
		}
		return arr[rw][cln];
	}

	template<typename T1>
	friend ostream& operator<<(ostream& out, BaseMatrix<T1>& matrix)
	{
		if (typeid(out) != typeid(ofstream)) 
		{
			for (int i = 0; i < matrix.row; i++) 
			{
				for (int j = 0; j < matrix.columns; j++) 
				{
					out << matrix.arr[i][j] << " ";
				}

				out << "\n";
			}
		}
		else 
		{
			out << " " << matrix.row << " " << matrix.columns << " ";
			
			for (int i = 0; i < matrix.row; i++) 
			{
				for (int j = 0; j < matrix.columns; j++)
				{
					out << matrix.arr[i][j];
					
					if (matrix.row != i + 1 || matrix.columns != j + 1)
					{
						out << " ";
					}
				}
			}
		}

		return out;
	}

	template<typename T1>
	friend istream& operator>>(istream& in, BaseMatrix<T1> matrix)
	{
		if (typeid(in) != typeid(ifstream)) 
		{
			for (int i = 0; i < matrix.row; i++)
			{
				for (int j = 0; j < matrix.columns; j++)
				{
					try 
					{
						in >> matrix.arr[i][j];
					}
					catch (...) 
					{
						cout << "�������� ����\n";
					}
				}
			}
		}
		else 
		{
			int row, columns;
			
			in >> row >> columns;
			
			if (row == matrix.height && columns == matrix.columns)
			{
				for (int i = 0; i < matrix.row; i++)
				{
					for (int j = 0; j < matrix.columns; j++)
					{
						try 
						{
							in >> matrix.arr[i][j];
						}
						catch (...) 
						{
							cout << "�������� ����\n";
						}
					}
				}

			}
			else {
				if (in.eof()) {
					cout << "��� ���������\n";
				}
				else {
					cout << "������� �� ���������\n";
				}

			}
		}

		return in;
	}

};

template<typename T1>
class Matrix : public BaseMatrix<T1>
{
public:
	Matrix(int row = 2, int columns = 2) : BaseMatrix<T1>(row, columns) {}

	Matrix(istream& in)
	{
		in >> this->row >> this->columns;

		if (this->row <= 0 || this->columns <= 0)
		{
			throw WrongSizeException("������ � �������� ������� -> ", this->row, this->columns);
		}

		this->arr = new T1 * [this->row];

		for (int i = 0; i < this->row; ++i)
		{
			this->arr[i] = new T1[this->columns];
		}

		for (int i = 0; i < this->row; i++)
		{
			for (int j = 0; j < this->columns; ++j)
			{
				in >> this->arr[i][j];
			}
		}
	}

	void rewrite_matrix(istream& in)
	{
		if (this->arr != nullptr)
		{
			for (int i = 0; i < this->row; ++i)
			{
				delete[] this->arr[i];
			}
			delete[] this->arr;
			this->arr = nullptr;
		}

		in >> this->row >> this->columns;

		if (this->row <= 0 || this->columns <= 0)
		{
			throw WrongSizeException("������ � �������� ������� -> ", this->row, this->columns);
		}
		
		this->arr = new T1 * [this->row];
		for (int i = 0; i < this->row; ++i)
		{
			this->arr[i] = new T1[this->columns];
		}

		for (int i = 0; i < this->row; ++i)
		{
			for (int j = 0; j < this->columns; ++j)
			{
				in >> this->arr[i][j];
			}
		}
	}

	template<typename T1>
	Matrix<T1> Max_Vector()
	{
		T1* temp = new T1[this->row]; //������ ���� �������� �� ������ ������ �������

		for (int i = 0; i < this->row; ++i)
		{
			for (int j = 0; j < this->columns-1; ++j)
			{
				if (this->arr[i][j] <= this->arr[i][j + 1])
				{
					temp[i] = this->arr[i][j + 1]; //��������� ������
				}
			}
		}

		for (int i = 0; i < this->row; ++i)
		{
			delete[] this->arr[i]; //������� �������
		}
		delete[] this->arr;

		Matrix<T1> answer(this->row, 1); //������� ������

		for (int i = 0; i < answer.row; ++i)
		{ 
			answer[i][0] = temp[i]; //��������� ������� ������
		}

		delete[] temp; //������� ������ ���� ��������

		return answer;
	}

	void RandomNums()
	{
		for (int i = 0; i < this->row; ++i)
		{
			for (int j = 0; j < this->columns;++j)
			{
				this->arr[i][j] = (T1)((rand()% 100) - 69 );
			}
		}
	}

	//�� ���� ������ , �� �� �� ����� �-�� print() �� ������������� ������
	virtual void print()
	{
		for (int i = 0; i < this->row; ++i)
		{
			for (int j = 0; j < this->columns; ++j)
			{
				cout << std::left << std::setw(9) << std::setprecision(3) << this->arr[i][j] << ' ';
			}
			cout << '\n';
		}
	}
};

int main()
{
	setlocale(LC_ALL, "Ru-ru");

	Matrix<int> answ(3,3);
	Matrix<int> m1(3, 3);
	m1.RandomNums();

	m1.print();

	answ = m1.Max_Vector();

	return 0;
}