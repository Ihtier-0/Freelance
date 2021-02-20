#include "CholeskySolver.h"
#include "utils.h"

#include <algorithm>

CholeskySolver::CholeskySolver(const stripMatrix& matrix,
	const std::vector<double>& f) : m_matrix(matrix), m_f(f) {}

bool CholeskySolver::Solve(std::vector<double>& answer)
{
	stripMatrix UpperTriangularMatrix(m_matrix.size(), m_matrix.lenght() + 1);
	stripMatrix LowerTriangularMatrix(m_matrix.size(), m_matrix.lenght() + 1);

	if (!createUpperAndLowerTriangularMatrix(UpperTriangularMatrix, LowerTriangularMatrix))
	{
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

bool CholeskySolver::createUpperAndLowerTriangularMatrix(stripMatrix& UpperTriangularMatrix,
	stripMatrix& LowerTriangularMatrix)
{
	for (int i = 0; i < m_matrix.size(); ++i)
	{
		UpperTriangularMatrix(i, i) = 1;
	}

	double sum;

	int size = m_matrix.size();
	int lenght = m_matrix.lenght();

	for (int j = 0; j < size; j++)
	{
		for (int i = j; i < std::min(j + lenght + 1, size); i++)
		{
			sum = 0;
			for (int k = std::max(0, i - lenght - 1); k < j; k++)
			{
				sum += LowerTriangularMatrix(i, k) * UpperTriangularMatrix(k, j);
			}
			LowerTriangularMatrix(i, j) = m_matrix(i, j) - sum;
		}
		for (int i = j + 1; i < std::min(j + lenght + 1, size); i++)
		{
			sum = 0;
			for (int k = std::max(0, i - lenght - 1); k < j; k++)
			{
				sum += LowerTriangularMatrix(j, k) * UpperTriangularMatrix(k, i);
			}

			if (LowerTriangularMatrix(j, j) == 0)
			{
				return false;
			}

			UpperTriangularMatrix(j, i) = (m_matrix(j, i) - sum) / LowerTriangularMatrix(j, j);
		}
	}

	return true;
}

bool CholeskySolver::solveUpperTriangularMatrix(const stripMatrix& UpperTriangularMatrix,
	const std::vector<double>& f, std::vector<double>& answer)
{
	int size = UpperTriangularMatrix.size();

	answer.resize(size);

	int lenght = m_matrix.lenght();

	for (int i = size - 1; i >= 0; --i)
	{
		double summ = 0;
		for (int k = std::min(i + lenght, size - 1); k > i; --k)
		{
			summ += UpperTriangularMatrix(i, k) * answer[k];
		}

		if (UpperTriangularMatrix(i, i) == 0)
		{
			return false;
		}

		answer[i] = (f[i] - summ);// / UpperTriangularMatrix(i, i);
	}

	return true;
}

bool CholeskySolver::solveLowerTriangularMatrix(const stripMatrix& LowerTriangularMatrix,
	const std::vector<double>& f, std::vector<double>& answer)
{
	unsigned int size = LowerTriangularMatrix.size();

	int lenght = m_matrix.lenght();

	answer.resize(size);

	for (int i = 0; i < size; i++)
	{
		double summ = 0;
		for (int k = std::max(0, i - lenght - 1); k < i; k++)
		{
			summ += LowerTriangularMatrix(i, k) * answer[k];
		}

		if (LowerTriangularMatrix(i, i) == 0)
		{
			return false;
		}

		answer[i] = (f[i] - summ) / LowerTriangularMatrix(i, i);
	}

	return true;
}
