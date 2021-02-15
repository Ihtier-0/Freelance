#include "CholeskySolver.h"
#include "utils.h"



CholeskySolver::CholeskySolver(const stripMatrix& matrix,
	const std::vector<double>& f) : m_matrix(matrix), m_f(f) {}

#include <iostream>
bool CholeskySolver::Solve(std::vector<double>& answer)
{
	stripMatrix UpperTriangularMatrix(m_matrix.size(), m_matrix.lenght());
	stripMatrix LowerTriangularMatrix(m_matrix.size(), m_matrix.lenght());

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

int CholeskySolver::K0(const int& i)
{
	return i < m_matrix.lenght() ? 0 : i - m_matrix.lenght() + 1;
}

int CholeskySolver::KN(const int& i)
{
	return i < m_matrix.size() - m_matrix.lenght() ? 
		i + m_matrix.lenght() - 1 : m_matrix.size() - 1;
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
		for (int i = j; i < std::min(j + lenght, size); i++)
		{
			sum = 0;
			for (int k = std::max(0, i - lenght + 1); k < j; k++)
			{
				sum += LowerTriangularMatrix(i, k - i + lenght - 1) * UpperTriangularMatrix(k , j - k);
				// sum += B[i * L + k - i + L - 1] * C[k * L + j - k];
			}
			LowerTriangularMatrix(i, j - i + lenght - 1) = m_matrix(i, j - i + lenght - 1) - sum;
			// B[i * L + j - i + L - 1] = A[i * (2 * L - 1) + j - i + L - 1] - S;
		}
		// C[j * L] = 1;
		for (int i = j + 1; i < std::min(j + lenght, size); i++)
		{
			sum = 0;
			for (int k = std::max(0, i - lenght + 1); k < j; k++)
			{
				sum += LowerTriangularMatrix(j, k - j + lenght - 1) * UpperTriangularMatrix(k, i - k);
				// sum += B[j * L + k - j + L - 1] * C[k * L + i - k];
			}

			if (LowerTriangularMatrix(j, j) == 0)
			{
				return false;
			}

			UpperTriangularMatrix(j, i - j) = (m_matrix(j, i - j + lenght - 1) - sum) / LowerTriangularMatrix(j, j);
			// C[j * L + i - j] = (A[j * (2 * L - 1) + i - j + L - 1] - S) / B[j * L + L - 1];
		}
	}

	return true;
}

bool CholeskySolver::solveUpperTriangularMatrix(const stripMatrix& UpperTriangularMatrix,
	const std::vector<double>& f, std::vector<double>& answer)
{
	unsigned int size = UpperTriangularMatrix.size();

	answer.resize(size);

	for (int i = size - 1; i >= 0; --i)
	{
		double summ = 0;
		for (int k = size - 1; k > i; --k)
		{
			summ += UpperTriangularMatrix(i,k) * answer[k];
		}

		if (UpperTriangularMatrix(i, i) == 0)
		{
			return false;
		}

		answer[i] = (f[i] - summ) / UpperTriangularMatrix(i, i);
	}

	return true;
}

bool CholeskySolver::solveLowerTriangularMatrix(const stripMatrix& LowerTriangularMatrix,
	const std::vector<double>& f, std::vector<double>& answer)
{
	unsigned int size = LowerTriangularMatrix.size();

	answer.resize(size);

	for (int i = 0; i < size; i++)
	{
		double summ = 0;
		for (int k = 0; k < i; k++)
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
