#include "utils.h"

std::ostream& operator<<(std::ostream& out, const std::vector<double>& v)
{
	int size = v.size();

	for (int i = 0; i < size; ++i)
	{
		out << v[i] << ' ';
	}

	return out;
}

std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<double>>& matrix)
{
	int size = matrix.size();

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			out << matrix[i][j] << ' ';
		}
		out << '\n';
	}

	return out;
}

void generateMatrixForSystemSolver(std::vector<double>& a,
	std::vector<double>& b,
	std::vector<double>& c,
	std::vector<double>& f,
	std::vector<double>& p,
	std::vector<double>& q,
	unsigned int& k,
	std::vector<double>& x,
	const unsigned int& size,
	const int& maxInVectors)
{
	a.resize(size);
	randomVector(a, maxInVectors);
	b.resize(size);
	randomVector(b, maxInVectors);
	c.resize(size);
	randomVector(c, maxInVectors);
	p.resize(size);
	randomVector(p, maxInVectors);
	q.resize(size);
	randomVector(q, maxInVectors);
	x.resize(size);
	randomVector(x, maxInVectors);

	k = 2 + ((size - 5) > 0 ? rand() % (size - 5) : 0);

	a[0] = 0;//объявляю где что пересекается и где выходит за матрицу (0)
	c[0] = 0;

	c[0] = a[size - 1] = 0.0;
	q[size - k - 2] = a[size - k - 2];
	q[size - k - 1] = b[size - k - 1];
	q[size - k] = c[size - k];
	p[size - k] = b[size - k];
	p[size - k - 1] = a[size - k - 1];
	p[size - k + 1] = c[size - k + 1];

	std::vector<std::vector<double>> matrix;
	// a, b, c, p, q пересекаются в некоторых местах, a[0],c[0] и т.д. - выходит за матрицу

	fillMatrix(matrix, a, b, c, p, q, k);

	f = matrix * x;
}

void generateMatrixForSystemSolverWhereXIdentity(std::vector<double>& a,
	std::vector<double>& b,
	std::vector<double>& c,
	std::vector<double>& f,
	std::vector<double>& p,
	std::vector<double>& q,
	unsigned int& k,
	std::vector<double>& x,
	const unsigned int& size,
	const int& maxInVectors)
{
	a.resize(size);
	randomVector(a, maxInVectors);
	b.resize(size);
	randomVector(b, maxInVectors);
	c.resize(size);
	randomVector(c, maxInVectors);
	p.resize(size);
	randomVector(p, maxInVectors);
	q.resize(size);
	randomVector(q, maxInVectors);
	x.resize(size);
	makeIdentity(x);

	k = 2 + ((size - 5) > 0 ? rand() % (size - 5) : 0);

	c[0] = a[size - 1] = 0.0;
	q[size - k - 2] = a[size - k - 2];
	q[size - k - 1] = b[size - k - 1];
	q[size - k] = c[size - k];
	p[size - k] = b[size - k];
	p[size - k - 1] = a[size - k - 1];
	p[size - k + 1] = c[size - k + 1];

	std::vector<std::vector<double>> matrix;

	fillMatrix(matrix, a, b, c, p, q, k);

	f = matrix * x;
}

void fillMatrix(std::vector<std::vector<double>>& matrix, //заполнение матрицы векторами, которые сгенерировали
	const std::vector<double>& a,
	const std::vector<double>& b,
	const std::vector<double>& c,
	const std::vector<double>& p,
	const std::vector<double>& q,
	const unsigned int& k)
{
	int size = a.size();

	matrix.resize(size);

	for (int i = 0; i < size; ++i)
	{
		matrix[i].resize(size);
		for (int j = 0; j < size; ++j)
		{
			matrix[i][k - 1] = p[i];
			matrix[i][k] = q[i];
			matrix[i][size - 1 - i] = b[i];

			if (i > 0)
			{
				matrix[i][size - i] = c[i];
			}

			if (i < size - 1)
			{
				matrix[i][size - i - 2] = a[i];
			}
		}
	}
}

void makeIdentity(std::vector<double>& vector)
{
	int size = vector.size();

	for (int i = 0; i < size; ++i)
	{
		vector[i] = 1;
	}
}

void randomVector(std::vector<double>& vector, const int& maxInVector)
{
	int size = vector.size();

	for (int i = 0; i < size; ++i)
	{
		// vector[i] = rand() % maxInVector;

		vector[i] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) *
			(static_cast<double>(maxInVector) + maxInVector) - maxInVector;
	}
}

std::vector<double> operator*(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector)
{
	int sizeRow = matrix.size();
	int sizeCol = matrix[0].size();
	std::vector<double> result(sizeRow);

	double sum;
	for (int i = 0; i < sizeRow; ++i)
	{
		sum = 0;
		for (int j = 0; j < sizeCol; ++j)
		{
			sum += matrix[i][j] * vector[j];
		}
		result[i] = sum;
	}

	return result;
}

double estimationOfSolutionAccuracy(const std::vector<double>& x, const std::vector<double>& xSolve)
{
	double EstimationOfSolutionAccuracy = -1;

	for (int i = 0; i < x.size(); ++i)
	{
		if (EstimationOfSolutionAccuracy < abs(xSolve[i] - x[i]))
		{
			EstimationOfSolutionAccuracy = abs(xSolve[i] - x[i]);
		}
	}

	return EstimationOfSolutionAccuracy;
}

double relativeSolutionError(const std::vector<double>& x,
	const std::vector<double>& xSolve, const double& q)
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