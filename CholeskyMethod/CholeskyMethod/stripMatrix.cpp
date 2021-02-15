#include "stripMatrix.h"

#include <iostream>
#include <exception>

stripMatrix::stripMatrix(int a_size, int a_lenght, std::vector<std::vector<double>> a_array)
	: m_size(a_size), m_lenght(a_lenght), m_array(a_array)
{
    if (m_size <= 0)
    {
        throw std::exception("size <= 0");
    }

    if (m_lenght <= 0)
    {
        throw std::exception("lenght <= 0");
    }

    if (m_size < m_lenght)
    {
        throw std::exception("m_size < m_lenght");
    }
}

stripMatrix::stripMatrix(int a_size, int a_lenght)
    : m_size(a_size), m_lenght(a_lenght)
{
    m_array.resize(m_size);

    for (int i = 0; i < m_size; ++i)
    {
        m_array[i].resize(2 * m_lenght + 1);
    }
}

const double const & stripMatrix::operator()(int row, int column) const
{
    if (row > m_size || row < 0)
    {
        throw std::exception("row > m_size || row < 0");
    }
    if (column > m_size || column < 0)
    {
        throw std::exception("row > m_size || row < 0");
    }

    int NewColumn = m_lenght + column - row;

    if (NewColumn >= 2 * m_lenght + 1 || NewColumn < 0)
    {
        return 0;
    }

    return m_array[row][NewColumn];
}

double& stripMatrix::operator()(int row, int column)
{
    if (row > m_size || row < 0)
    {
        throw std::exception("row > m_size || row < 0");
    }
    if (column > m_size || column < 0)
    {
        throw std::exception("row > m_size || row < 0");
    }

    int NewColumn = m_lenght + column - row;

    if (NewColumn >= 2 * m_lenght + 1 || NewColumn < 0)
    {
        throw std::exception("going beyond the bounds of the tape");
    }

    return m_array[row][NewColumn];
}

int stripMatrix::size() const
{
    return m_size;
}

int stripMatrix::lenght() const
{
    return m_lenght;
}

std::ostream& operator<<(std::ostream& out, const stripMatrix& Matrix)
{
    int size = Matrix.m_size;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            out << Matrix(i, j) << ' ';
        }
        out << '\n';
    }

    return out;
}

std::vector<double> operator*(const stripMatrix& sm, const std::vector<double>& v)
{
    int size = sm.size();

    if (size != v.size())
    {
        throw std::exception("different size");
    }

    std::vector<double> result(size, 0);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            result[i] += sm(i, j) * v[j];
        }
    }

    return result;
}
