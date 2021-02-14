#pragma once

#include <vector>
#include "stripMatrix.h"

// �������� ������ ����:
// m_matrix * x = m_f
// ������� ���������
class CholeskySolver
{
public:
	CholeskySolver(const stripMatrix& matrix,
		const std::vector<double>& f);

	bool Solve(std::vector<double>& answer);
private:
	stripMatrix m_matrix;
	std::vector<double> m_f;

	// ��������� matrix �� LU �������
	bool createUpperAndLowerTriangularMatrix(std::vector<std::vector<double>>& UpperTriangularMatrix,
		std::vector<std::vector<double>>& LowerTriangularMatrix);

	// ������ ������� ��=f, ��� � - ����������������� �������
	bool solveUpperTriangularMatrix(const std::vector<std::vector<double>>& UpperTriangularMatrix,
		const std::vector<double>& f, std::vector<double>& answer);

	// ������ ������� ��=f, ��� � - ���������������� �������
	bool solveLowerTriangularMatrix(const std::vector<std::vector<double>>& LowerTriangularMatrix,
		const std::vector<double>& f, std::vector<double>& answer);
};

