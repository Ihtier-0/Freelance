#include "GaussSolver.h"

GaussSolver::GaussSolver(const std::vector<std::vector<double>>& matrix,
	const std::vector<double>& f) : m_matrix(matrix), m_f(f) {}

bool GaussSolver::Solve(std::vector<double>& answer)
{
	if (!straightRun())
		return false;
	if (!reverseRun())
		return false;

	answer = m_f;

	return true;
}

bool GaussSolver::straightRun()
{
    int size = m_f.size();

    for (int i = 0; i < size; ++i)
    {
        if (m_matrix[i][i] == 0)
            return false;

        double R = 1 / m_matrix[i][i];
        m_matrix[i][i] = 1;

        for (int j = i + 1; j < size; ++j)
        {
            m_matrix[i][j] *= R;
        }
        m_f[i] *= R;

        for (int k = i + 1; k < size; ++k)
        {
            double R = m_matrix[k][i];
            m_matrix[k][i] = 0;

            for (int j = i + 1; j < size; ++j)
            {
                m_matrix[k][j] -= R * m_matrix[i][j];
            }

            m_f[k] -= R * m_f[i];
        }
    }

    return true;
}

bool GaussSolver::reverseRun()
{
    int size = m_f.size();

    for (int i = size - 1; i >= 0; --i)
    {
        for (int k = i - 1; k >= 0; --k)
        {
            m_f[k] -= m_f[i] * m_matrix[k][i];
            m_matrix[k][i] = 0;
        }
    }

    return true;
}

