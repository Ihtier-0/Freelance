#pragma once

#include <vector>
#include <iostream>

std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<double>>& matrix);
std::ostream& operator<<(std::ostream& out, const std::vector<double>& vector);

std::vector<std::vector<double>> operator*(const std::vector<std::vector<double>>& matrix1,
	const std::vector<std::vector<double>>& matrix2);

std::vector<double> operator*(const std::vector<std::vector<double>>& matrix,
	std::vector<double>& vector);

std::vector<std::vector<double>> operator+(const std::vector<std::vector<double>>& matrix1,
	const std::vector<std::vector<double>>& matrix2);

std::vector<std::vector<double>> operator-(const std::vector<std::vector<double>>& matrix1,
	const std::vector<std::vector<double>>& matrix2);

std::vector<std::vector<double>> operator*(const std::vector<std::vector<double>>& matrix, const double& k);
std::vector<std::vector<double>> operator*(const double& k, const std::vector<std::vector<double>>& matrix);

std::vector<double> operator*(const std::vector<double>& vector, const double& k);
std::vector<double> operator*(const double& k, const std::vector<double>& vector);

std::vector<double> operator+(const std::vector<double>& vector1, const std::vector<double>& vector2);
std::vector<double> operator-(const std::vector<double>& vector1, const std::vector<double>& vector2);

std::vector<double> randomVector(const unsigned int& size, const unsigned int& maxValue);

std::vector<std::vector<double>> createDiagonalMatrix(const std::vector<double>& vector);

std::vector<std::vector<double>> createIdentityMatrix(const unsigned int& size);

std::vector<std::vector<double>> createRandomMatrix(const unsigned int& sizeRow, const unsigned int& sizeCol);

std::vector<std::vector<double>> transposition(const std::vector<std::vector<double>>& matrix);

// наверное тупо нормализировать матрицу, но тут это используется один раз и для матрицы 1хN
std::vector<std::vector<double>> normalize(const std::vector<std::vector<double>>& matrix);

void normalize(std::vector<double>& vector);

double norm(const std::vector<double>& vector);

void findPositionAbsMaximumOutOfDiagonalElement(const std::vector<std::vector<double>>& matrix,
	unsigned int& rowIndex, unsigned int& colIndex);

double findMaxAbsValue(const std::vector<std::vector<double>>& matrix);

int findIndexAbsMin(const std::vector<double>& vector);

int findIndexSecondAbsMin(const std::vector<double>& vector);

int findIndexThirdAbsMin(const std::vector<double>& vector);

int indexMinAbsElement(const std::vector<double>& Qvector);

double estimationOfSolutionAccuracy(const std::vector<double>& x, const std::vector<double>& xSolve);

double angleBetweenVectors(std::vector<double> vector1,
	std::vector<double> vector2);

double scalarProduct(const std::vector<double>& vector1,
	const std::vector<double>& vector2);

void GenerateMatrixWithEigenValues(std::vector<std::vector<double>>& matrix,
	std::vector<double>& eigenValues,
	std::vector<std::vector<double>>& eigenVectors,
	const unsigned int& matrixDimension,
	const unsigned int& maxEigenValues);