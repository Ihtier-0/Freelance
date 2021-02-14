#include "CholeskySolver.h"
#include "utils.h"

CholeskySolver::CholeskySolver(const stripMatrix& matrix,
	const std::vector<double>& f) : m_matrix(matrix), m_f(f) {}

#include <iostream>
bool CholeskySolver::Solve(std::vector<double>& answer)
{
	std::vector<std::vector<double>> UpperTriangularMatrix(m_matrix.size());
	std::vector<std::vector<double>> LowerTriangularMatrix(m_matrix.size());

	if (!createUpperAndLowerTriangularMatrix(UpperTriangularMatrix, LowerTriangularMatrix))
	{
		std::cout << UpperTriangularMatrix << '\n' << LowerTriangularMatrix << '\n';
		return false;
	}

	std::vector<double> y;

	if (!solveLowerTriangularMatrix(LowerTriangularMatrix, m_f, y))
	{
		return false;
	}

	std::vector<double> x;

	if (!solveUpperTriangularMatrix(UpperTriangularMatrix, y, x))
	{
		return false;
	}

	answer = x;

	return true;
}

bool CholeskySolver::createUpperAndLowerTriangularMatrix(std::vector<std::vector<double>>& UpperTriangularMatrix,
	std::vector<std::vector<double>>& LowerTriangularMatrix)
{
	for (int i = 0; i < m_matrix.size(); ++i)
	{
		UpperTriangularMatrix[i].resize(m_matrix.size());
		LowerTriangularMatrix[i].resize(m_matrix.size());

		for (int j = 0; j < m_matrix.size(); ++j)
		{
			UpperTriangularMatrix[i][j] = 0;
			LowerTriangularMatrix[i][j] = 0;

			if (i == j)
			{
				UpperTriangularMatrix[i][j] = 1;
			}
		}
	}

	double sum;

	for (int i = 0; i < m_matrix.size(); ++i)
	{
		for (int j = i; j < m_matrix.size(); ++j)
		{
			sum = 0;
			for (int k = 0; k < i; k++)
			{
				sum += (LowerTriangularMatrix[j][k] * UpperTriangularMatrix[k][i]);
			}

			LowerTriangularMatrix[j][i] = m_matrix(j,i) - sum;
		}

		for (int j = i + 1; j < m_matrix.size(); ++j)
		{
			sum = 0;
			for (int k = 0; k < i; k++)
			{
				sum += (LowerTriangularMatrix[i][k] * UpperTriangularMatrix[k][j]);
			}
			if (!LowerTriangularMatrix[i][i])
			{
				return false;
			}

			UpperTriangularMatrix[i][j] = (m_matrix(j, i) - sum) / LowerTriangularMatrix[i][i];
		}
	}

	return true;
}

bool CholeskySolver::solveUpperTriangularMatrix(const std::vector<std::vector<double>>& UpperTriangularMatrix,
	const std::vector<double>& f, std::vector<double>& answer)
{
	unsigned int size = UpperTriangularMatrix.size();

	answer.resize(size);

	for (int i = size - 1; i >= 0; --i)
	{
		double summ = 0;
		for (int k = size - 1; k > i; --k)
		{
			summ += UpperTriangularMatrix[i][k] * answer[k];
		}

		if (UpperTriangularMatrix[i][i] == 0)
		{
			return false;
		}

		answer[i] = (f[i] - summ) / UpperTriangularMatrix[i][i];
	}

	return true;
}

bool CholeskySolver::solveLowerTriangularMatrix(const std::vector<std::vector<double>>& LowerTriangularMatrix,
	const std::vector<double>& f, std::vector<double>& answer)
{
	unsigned int size = LowerTriangularMatrix.size();

	answer.resize(size);

	for (int i = 0; i < size; i++)
	{
		double summ = 0;
		for (int k = 0; k < i; k++)
		{
			summ += LowerTriangularMatrix[i][k] * answer[k];
		}

		if (LowerTriangularMatrix[i][i] == 0)
		{
			return false;
		}

		answer[i] = (f[i] - summ) / LowerTriangularMatrix[i][i];
	}

	return true;
}
