#include "utils.h"

void generateMatrixForSystemSolver(std::vector<double>& a,
	std::vector<double>& b,
	std::vector<double>& c,
	std::vector<double>& f,
	std::vector<double>& p,
	unsigned int& WhenP,
	std::vector<double>& q,
	unsigned int& WhenQ,
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

	WhenP = 1 + rand() % (size - 4);
	WhenQ = WhenP + 2;

	std::vector<std::vector<double>> matrix;
	// a, b, c, p, q пересекаются в некоторых местах, a[0],c[0] и т.д. - выходит за матрицу
	a[0] = 0;
	c[0] = 0;

	p[size - 1 - WhenP] = b[size - 1 - WhenP];
	q[size - 1 - WhenQ] = b[size - 1 - WhenQ];

	p[size - 2 - WhenP] = a[size - 1 - WhenP];
	q[size - 2 - WhenQ] = a[size - 1 - WhenQ];

	p[size - WhenP] = c[size - WhenP];
	q[size - WhenQ] = c[size - WhenQ];

	fillMatrix(matrix, a, b, c, p, WhenP, q, WhenQ);

	f = matrix * x;

	std::cout << "a:\n";
	for (int i = 0; i < size; ++i)
	{
		std::cout << a[i] << ' ';
	}
	std::cout << "\n\n";
	std::cout << "b:\n";
	for (int i = 0; i < size; ++i)
	{
		std::cout << b[i] << ' ';
	}
	std::cout << "\n\n";
	std::cout << "c:\n";
	for (int i = 0; i < size; ++i)
	{
		std::cout << c[i] << ' ';
	}
	std::cout << "\n\n";
	std::cout << "p:\n";
	for (int i = 0; i < size; ++i)
	{
		std::cout << p[i] << ' ';
	}
	std::cout << "\n\n";
	std::cout << "q:\n";
	for (int i = 0; i < size; ++i)
	{
		std::cout << q[i] << ' ';
	}
	std::cout << "\n\n";
	std::cout << "matrix:\n";
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			std::cout << matrix[i][j] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
	std::cout << "x:\n";
	for (int i = 0; i < size; ++i)
	{
		std::cout << x[i] << ' ';
	}
	std::cout << "\n\n";
	std::cout << "f:\n";
	for (int i = 0; i < size; ++i)
	{
		std::cout << f[i] << ' ';
	}
	std::cout << "\n\n";
}

void generateMatrixForSystemSolverWhereXIdentity(std::vector<double>& a,
	std::vector<double>& b,
	std::vector<double>& c,
	std::vector<double>& f,
	std::vector<double>& p,
	unsigned int& WhenP,
	std::vector<double>& q,
	unsigned int& WhenQ,
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

	WhenP = 1 + rand() % (size - 4);
	WhenQ = WhenP + 2;

	a[0] = 0;//объявляю где что пересекается и где выходит за матрицу (0)
	c[0] = 0;

	p[size - 1 - WhenP] = b[size - 1 - WhenP];
	q[size - 1 - WhenQ] = b[size - 1 - WhenQ];

	p[size - 2 - WhenP] = a[size - 1 - WhenP];
	q[size - 2 - WhenQ] = a[size - 1 - WhenQ];

	p[size - WhenP] = c[size - WhenP];
	q[size - WhenQ] = c[size - WhenQ];

	std::vector<std::vector<double>> matrix;

	fillMatrix(matrix, a, b, c, p, WhenP, q, WhenQ);

	f = matrix * x;
}

void fillMatrix(std::vector<std::vector<double>>& matrix, //заполнение матрицы векторами, которые сгенерировали
	const std::vector<double>& a,
	const std::vector<double>& b,
	const std::vector<double>& c,
	const std::vector<double>& p,
	const unsigned int& WhenP,
	const std::vector<double>& q,
	const unsigned int& WhenQ)
{
	int size = a.size();

	matrix.resize(size);

	for (int i = 0; i < size; ++i)
	{
		matrix[i].resize(size);
		for (int j = 0; j < size; ++j)
		{
			if (j == WhenP)
			{
				matrix[i][j] = p[i];
			}
			else if (j == WhenQ)
			{
				matrix[i][j] = q[i];
			}
			else if (i == size - j)
			{
				matrix[i][j] = c[i];
			}
			else if (i == size - 1 - j)
			{
				matrix[i][j] = b[i];
			}
			else if (i == size - 2 - j)
			{
				matrix[i][j] = a[i + 1];
			}
			else
			{
				matrix[i][j] = 0;
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
		vector[i] = rand() % maxInVector;

		/*vector[i] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) *
			(static_cast<double>(maxInVector) + maxInVector) - maxInVector;*/
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