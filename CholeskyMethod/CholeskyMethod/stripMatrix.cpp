#include "stripMatrix.h"

#include <cassert>
#include <iostream>

stripMatrix::stripMatrix(int a_size, int a_lenght, std::vector<std::vector<double>> a_array)
	: m_size(a_size), m_lenght(a_lenght), m_array(a_array) {}


double stripMatrix::operator()(int row, int column) const
{
    assert(row < m_size && row >= 0);
    assert(column < m_size && column >= 0);

    int NewColumn = m_lenght + column - row;

    if (NewColumn >= 2 * m_lenght + 1 || NewColumn < 0)
    {
        return 0;
    }

    return m_array[row][NewColumn];
}

std::ostream& operator<<(std::ostream& out, const stripMatrix& Matrix)
{
    int size = Matrix.m_size;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            out << Matrix(i, j) << ' ';
            // out << "[" << i << ", " << j << "] = " << Matrix(i, j) << '\n';
        }
        out << '\n';
    }

    return out;
}
