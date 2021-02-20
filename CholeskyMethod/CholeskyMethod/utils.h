#pragma once

#include <vector>
#include <ostream>

#include "stripMatrix.h"

template<class T>
std::ostream& operator<<(std::ostream &out, const std::vector<T>& v)
{
	int size = v.size();

	for (int i = 0; i < size; ++i)
	{
		out << v[i] << ' ';
	}

	return out;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<T>>& v)
{
	int size = v.size();

	for (int i = 0; i < size; ++i)
	{
		out << v[i] << '\n';
	}

	return out;
}

void randVector(std::vector<double>&, const int& size, const double& maxElement);

void generateStripMatrixSystem(stripMatrix &m, const int& size, const int& length,
	std::vector<double> &x, std::vector<double> &f, const double& maxElement);

stripMatrix RandomLowerTriangularMatrix(const int& size, const int& length, const double& maxValue);

stripMatrix RandomUpperTriangularMatrix(const int& size, const int& length, const double& maxValue);

void makeMatrixIllConditioned(stripMatrix& matrix, const unsigned int& orderIllConditioned);

void generateIllConditionStripMatrixSystem(stripMatrix& m, const int& size, const int& length,
	std::vector<double>& x, std::vector<double>& f, const double& maxElement, const unsigned int& orderIllConditioned);

void compressValues(stripMatrix& matrix, const int& maxValue);

double relativeSolutionError(const std::vector<double>& x, const std::vector<double>& xSolve, const double& q = 1);