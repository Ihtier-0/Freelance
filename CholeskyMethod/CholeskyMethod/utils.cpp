#include "utils.h"

#include <iostream>
void randVector(std::vector<double>& v, const int& size, const double& maxElement)
{
	v.resize(size);

	for (int i = 0; i < size; ++i)
	{
		v[i] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxElement + maxElement) - maxElement;
	}
}

void generateStripMatrixSystem(stripMatrix& m, const int& size, const int& length,
	std::vector<double>& x, std::vector<double>& f, const double& maxElement)
{
	m = stripMatrix(size, length);

	for (int i = 0; i < size; i++)
	{
		for (int j = std::max(0, i - length); j < std::min(size, i + length + 1); j++)
		{
			m(i,j) = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxElement + maxElement) - maxElement;
		}
	}

	randVector(x, size, maxElement);

	f = m * x;
}

void generateIllConditionStripMatrixSystem(stripMatrix& m, const int& size, const int& length,
    std::vector<double>& x, std::vector<double>& f, const double& maxElement, const unsigned int& orderIllConditioned)
{
    m = stripMatrix(size, length);

    stripMatrix LowerTriangularMatrix = RandomLowerTriangularMatrix(size, length, maxElement);
    stripMatrix UpperTriangularMatrix = RandomUpperTriangularMatrix(size, length, maxElement);

    makeMatrixIllConditioned(LowerTriangularMatrix, orderIllConditioned);
    makeMatrixIllConditioned(UpperTriangularMatrix, orderIllConditioned);

    m = LowerTriangularMatrix * UpperTriangularMatrix;
    
    // строка наёба
    {
        compressValues(m, maxElement);
    }

    randVector(x, size, maxElement);

    f = m * x;
}

stripMatrix RandomLowerTriangularMatrix(const int& size, const int& length, const double& maxValue)
{
    stripMatrix result(size, length);

    for (int i = 0; i < size; ++i)
    {
        for (int j = std::max(0, i - length); j <= i; j++)
        {
            result(i,j) = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) *
                (maxValue + maxValue) - maxValue;
        }
    }

    return result;
}

stripMatrix RandomUpperTriangularMatrix(const int& size, const int& length, const double& maxValue)
{
    stripMatrix result(size, length);

    for (int i = 0; i < size; ++i)
    {
        for (int j = i; j < std::min(size, i + length + 1); j++)
        {
                result(i,j) = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) *
                    (maxValue + maxValue) - maxValue;
        }
    }

    return result;
}

void makeMatrixIllConditioned(stripMatrix& matrix, const unsigned int& orderIllConditioned)
{
    unsigned int size = matrix.size();
    double powTen = 1;

    for (int i = 0; i < orderIllConditioned; ++i)
    {
        powTen *= 10;
    }

    powTen = 1 / powTen;

    for (int i = 0; i < size; ++i)
    {
        matrix(i,i) *= powTen;
    }
}

void compressValues(stripMatrix& matrix, const int& maxValue)
{
    int size = matrix.size();
    int length = matrix.lenght();

    for (int i = 0; i < size; ++i)
    {
        for (int j = std::max(0, i - length); j < std::min(size, i + length + 1); j++)
        {
            while (abs(matrix(i,j)) < maxValue)
            {
                matrix(i, j) *= 10;
            }

            while (abs(matrix(i, j)) > maxValue)
            {
                matrix(i, j) /= 10;
            }

            if (abs(matrix(i, j)) > maxValue)
            {
                matrix(i, j) -= maxValue / 2;
            }

            if (abs(matrix(i, j)) < maxValue)
            {
                matrix(i, j) += maxValue / 2;
            }
        }
    }
}

double relativeSolutionError(const std::vector<double>& x, const std::vector<double>& xSolve, const double& q)
{
    double relativeSolutionError = -1;

    for (int i = 0; i < x.size(); ++i)
    {
        if (abs(x[i]) > q)
        {
            if (relativeSolutionError < abs((x[i] - xSolve[i]) / x[i]))
            {
                relativeSolutionError = abs((x[i] - xSolve[i]) / x[i]);
            }
        }
        else
        {
            if (relativeSolutionError < abs(x[i] - xSolve[i]))
            {
                relativeSolutionError = abs(x[i] - xSolve[i]);
            }
        }
    }

    return relativeSolutionError;
}