#pragma once
#include <vector>

// решатель систем вида:
// m_matrix * x = m_f
// методом Халецкого
class KhaletskySolver
{
public:
	KhaletskySolver(const std::vector<std::vector<double>>& matrix,
		const std::vector<double>& f);

	bool Solve(std::vector<double>& answer);
private:
	std::vector<std::vector<double>> m_matrix;
	std::vector<double> m_f;

	// разложить matrix по LU теореме
	bool createUpperAndLowerTriangularMatrix(std::vector<std::vector<double>>& UpperTriangularMatrix,
		std::vector<std::vector<double>>& LowerTriangularMatrix);

	// решить систему Ах=f, где А - верхнетреугольная матрица
	bool solveUpperTriangularMatrix(const std::vector<std::vector<double>>& UpperTriangularMatrix,
		const std::vector<double>& f, std::vector<double>& answer);

	// решить систему Ах=f, где А - нижнетреугольная матрица
	bool solveLowerTriangularMatrix(const std::vector<std::vector<double>>& LowerTriangularMatrix,
		const std::vector<double>& f, std::vector<double>& answer);
};
