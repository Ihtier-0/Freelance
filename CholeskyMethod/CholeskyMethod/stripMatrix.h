#pragma once

#include <vector>
#include <ostream>

class stripMatrix
{
public:
    stripMatrix(int a_size, int a_lenght, std::vector<std::vector<double>> a_array);
    stripMatrix(int a_size, int a_lenght);

    const double const & operator()(int row, int column) const;
    double& operator()(int row, int column);

    int size() const;
    int lenght() const;

private:
    int m_size;
    int m_lenght;
    std::vector<std::vector<double>> m_array;

    friend std::ostream& operator<< (std::ostream& out, const stripMatrix& Matrix);
    friend std::vector<double> operator*(const stripMatrix& sm, const std::vector<double>& v);
};

