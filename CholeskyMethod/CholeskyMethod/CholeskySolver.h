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

	int K0(const int& i);
	int KN(const int& i);

	// ��������� matrix �� LU �������
	bool createUpperAndLowerTriangularMatrix(stripMatrix& UpperTriangularMatrix,
		stripMatrix& LowerTriangularMatrix);

	// ������ ������� ��=f, ��� � - ����������������� �������
	bool solveUpperTriangularMatrix(const stripMatrix& UpperTriangularMatrix,
		const std::vector<double>& f, std::vector<double>& answer);

	// ������ ������� ��=f, ��� � - ���������������� �������
	bool solveLowerTriangularMatrix(const stripMatrix& LowerTriangularMatrix,
		const std::vector<double>& f, std::vector<double>& answer);
};

