#include <iostream>

using namespace std;

class matrix
{
public:
	matrix() : m_matrix(nullptr), m_row(0), m_col(0) {}
	matrix(const int& a_row, const int& a_col) : m_row(a_row), m_col(a_col)
	{
		m_matrix = new int* [m_row];

		for (int i = 0; i < m_row; ++i)
		{
			m_matrix[i] = new int[m_col];
		}

		for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j < m_col; j++)
			{
				m_matrix[i][j] = 0;
			}
		}
	}
	matrix(const int const* const* const& a_matrix, const int& a_row, const int& a_col) : m_row(a_row), m_col(a_col)
	{
		m_matrix = new int* [m_row];

		for (int i = 0; i < m_row; ++i)
		{
			m_matrix[i] = new int[m_col];
		}

		for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j < m_col; j++)
			{
				m_matrix[i][j] = a_matrix[i][j];
			}
		}
	}
	matrix(const matrix& m) : m_row(m.m_row), m_col(m.m_col)
	{
		m_matrix = new int* [m_row];

		for (int i = 0; i < m_row; ++i)
		{
			m_matrix[i] = new int[m_col];
		}

		for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j < m_col; j++)
			{
				m_matrix[i][j] = m.m_matrix[i][j];
			}
		}
	}
	~matrix()
	{
		for (int i = 0; i < m_row; i++)
		{
			delete[] m_matrix[i];
		}

		delete[] m_matrix;

		m_matrix = nullptr;

		m_row = 0;
		m_col = 0;
	}
	void resizeCol(const int& a_col)
	{
		int** matrix = new int* [m_row];

		for (int i = 0; i < m_row; ++i)
		{
			matrix[i] = new int[a_col];
		}

		for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j < a_col; j++)
			{
				matrix[i][j] = 0;
			}
		}

		if (a_col < m_col)
		{
			for (int i = 0; i < m_row; i++)
			{
				for (int j = 0; j < a_col; j++)
				{
					matrix[i][j] = m_matrix[i][j];
				}
			}
		}
		else
		{
			for (int i = 0; i < m_row; i++)
			{
				for (int j = 0; j < m_col; j++)
				{
					matrix[i][j] = m_matrix[i][j];
				}
			}
		}

		m_col = a_col;

		for (int i = 0; i < m_row; i++)
		{
			delete[] m_matrix[i];
		}

		delete[] m_matrix;

		m_matrix = matrix;
	}

	void resizeRow(const int& a_row)
	{
		int** matrix = new int* [a_row];

		for (int i = 0; i < a_row; ++i)
		{
			matrix[i] = new int[m_col];
		}

		for (int i = 0; i < a_row; i++)
		{
			for (int j = 0; j < m_col; j++)
			{
				matrix[i][j] = 0;
			}
		}

		if (a_row < m_row)
		{
			for (int i = 0; i < a_row; i++)
			{
				for (int j = 0; j < m_col; j++)
				{
					matrix[i][j] = m_matrix[i][j];
				}
			}
		}
		else
		{
			for (int i = 0; i < m_row; i++)
			{
				for (int j = 0; j < m_col; j++)
				{
					matrix[i][j] = m_matrix[i][j];
				}
			}
		}

		for (int i = 0; i < m_row; i++)
		{
			delete[] m_matrix[i];
		}

		delete[] m_matrix;

		m_row = a_row;

		m_matrix = matrix;
	}

private:
	int** m_matrix;
	int m_row;
	int m_col;

	friend ostream& operator<<(ostream& out, const matrix& m)
	{
		for (int i = 0; i < m.m_row; i++)
		{
			for (int j = 0; j < m.m_col; j++)
			{
				out << m.m_matrix[i][j] << ' ';
			}
			out << '\n';
		}

		return out;
	}
};

template<class T>
class templateMatrix
{
public:
	templateMatrix() : m_matrix(nullptr), m_row(0), m_col(0) {}
	templateMatrix(const int& a_row, const int& a_col) : m_row(a_row), m_col(a_col)
	{
		m_matrix = new T* [m_row];

		for (int i = 0; i < m_row; ++i)
		{
			m_matrix[i] = new T[m_col];
		}

		for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j < m_col; j++)
			{
				m_matrix[i][j] = T();
			}
		}
	}
	templateMatrix(const T const* const* const& a_matrix, const int& a_row, const int& a_col) : m_row(a_row), m_col(a_col)
	{
		m_matrix = new T* [m_row];

		for (int i = 0; i < m_row; ++i)
		{
			m_matrix[i] = new T[m_col];
		}

		for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j < m_col; j++)
			{
				m_matrix[i][j] = a_matrix[i][j];
			}
		}
	}
	templateMatrix(const matrix& m) : m_row(m.m_row), m_col(m.m_col)
	{
		m_matrix = new T* [m_row];

		for (int i = 0; i < m_row; ++i)
		{
			m_matrix[i] = new T[m_col];
		}

		for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j < m_col; j++)
			{
				m_matrix[i][j] = m.m_matrix[i][j];
			}
		}
	}
	~templateMatrix()
	{
		for (int i = 0; i < m_row; i++)
		{
			delete[] m_matrix[i];
		}

		delete[] m_matrix;

		m_matrix = nullptr;

		m_row = 0;
		m_col = 0;
	}
	void resizeCol(const int& a_col)
	{
		T** matrix = new T* [m_row];

		for (int i = 0; i < m_row; ++i)
		{
			matrix[i] = new T[a_col];
		}

		for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j < a_col; j++)
			{
				matrix[i][j] = 0;
			}
		}

		if (a_col < m_col)
		{
			for (int i = 0; i < m_row; i++)
			{
				for (int j = 0; j < a_col; j++)
				{
					matrix[i][j] = m_matrix[i][j];
				}
			}
		}
		else
		{
			for (int i = 0; i < m_row; i++)
			{
				for (int j = 0; j < m_col; j++)
				{
					matrix[i][j] = m_matrix[i][j];
				}
			}
		}

		m_col = a_col;

		for (int i = 0; i < m_row; i++)
		{
			delete[] m_matrix[i];
		}

		delete[] m_matrix;

		m_matrix = matrix;
	}

	void resizeRow(const int& a_row)
	{
		T** matrix = new T* [a_row];

		for (int i = 0; i < a_row; ++i)
		{
			matrix[i] = new T[m_col];
		}

		for (int i = 0; i < a_row; i++)
		{
			for (int j = 0; j < m_col; j++)
			{
				matrix[i][j] = 0;
			}
		}

		if (a_row < m_row)
		{
			for (int i = 0; i < a_row; i++)
			{
				for (int j = 0; j < m_col; j++)
				{
					matrix[i][j] = m_matrix[i][j];
				}
			}
		}
		else
		{
			for (int i = 0; i < m_row; i++)
			{
				for (int j = 0; j < m_col; j++)
				{
					matrix[i][j] = m_matrix[i][j];
				}
			}
		}

		for (int i = 0; i < m_row; i++)
		{
			delete[] m_matrix[i];
		}

		delete[] m_matrix;

		m_row = a_row;

		m_matrix = matrix;
	}

private:
	T** m_matrix;
	int m_row;
	int m_col;

	friend ostream& operator<<(ostream& out, const templateMatrix& m)
	{
		for (int i = 0; i < m.m_row; i++)
		{
			for (int j = 0; j < m.m_col; j++)
			{
				out << m.m_matrix[i][j] << ' ';
			}
			out << '\n';
		}

		return out;
	}
};

int main()
{
	int **M = new int*[3];
	M[0] = new int[2];
	M[0][0] = 1; M[0][1] = 2;
	M[1] = new int[2];
	M[1][0] = 3; M[1][1] = 0;
	M[2] = new int[2];
	M[2][0] = -1; M[2][1] = -20;
	matrix m(M, 3, 2);

	cout << m << '\n';

	m.resizeCol(5);

	cout << m << '\n';

	m.resizeRow(5);

	cout << m << '\n';

	m.resizeCol(2);
	m.resizeRow(2);

	cout << m << '\n';

	cout << "\n\n\n";

	double** Mt = new double* [3];
	Mt[0] = new double[2];
	Mt[0][0] = 1.5; Mt[0][1] = 2.1;
	Mt[1] = new double[2];
	Mt[1][0] = 3.77; Mt[1][1] = 0.2;
	Mt[2] = new double[2];
	Mt[2][0] = -1.15; Mt[2][1] = -20.14;
	templateMatrix<double> mt(Mt, 3, 2);

	cout << mt << '\n';

	mt.resizeCol(5);

	cout << mt << '\n';

	mt.resizeRow(5);

	cout << mt << '\n';

	mt.resizeCol(2);
	mt.resizeRow(2);

	cout << mt << '\n';
}