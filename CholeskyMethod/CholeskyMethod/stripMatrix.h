#pragma once

#include <vector>
#include <ostream>

class stripMatrix
{
public:
    stripMatrix(int a_size, int a_lenght, std::vector<std::vector<double>> a_array);

    double operator()(int row, int column) const;

private:
    int m_size;
    int m_lenght;
    std::vector<std::vector<double>> m_array;

    friend std::ostream& operator<< (std::ostream& out, const stripMatrix& Matrix);
};

