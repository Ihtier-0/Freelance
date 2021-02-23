#pragma once
#include <vector>

// решатель систем вида:
// m_matrix * x = m_f
// методом Халецкого
class GaussSolver
{
public:
	GaussSolver(const std::vector<std::vector<double>>& matrix,
		const std::vector<double>& f);

	bool Solve(std::vector<double>& answer);
private:
	std::vector<std::vector<double>> m_matrix;
	std::vector<double> m_f;

	bool straightRun();
	bool reverseRun();
};
