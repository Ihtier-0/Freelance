#pragma once

#include <vector>
#include <iostream>

std::ostream& operator<<(std::ostream& out, const std::vector<double>& v);
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<double>>& matrix);

// ��������� ������� � - ���������
void generateMatrixForSystemSolver(std::vector<double>& a,
    std::vector<double>& b,
    std::vector<double>& c,
    std::vector<double>& f,
    std::vector<double>& p,
    std::vector<double>& q,
    unsigned int& k,
    std::vector<double>& x,
    const unsigned int& size = rand(),
    const int& maxInVectors = std::numeric_limits<int>::max());

// ��������� �������  � ������� (1, 1, ..., 1)
void generateMatrixForSystemSolverWhereXIdentity(std::vector<double>& a,
    std::vector<double>& b,
    std::vector<double>& c,
    std::vector<double>& f,
    std::vector<double>& p,
    std::vector<double>& q,
    unsigned int& k,
    std::vector<double>& x,
    const unsigned int& size = rand(),
    const int& maxInVectors = std::numeric_limits<int>::max());

void fillMatrix(std::vector<std::vector<double>>& matrix, //���������� ������� ���������, ������� �������������
    const std::vector<double>& a,
    const std::vector<double>& b,
    const std::vector<double>& c,
    const std::vector<double>& p,
    const std::vector<double>& q,
    const unsigned int& k);

void makeIdentity(std::vector<double>& vector);

void randomVector(std::vector<double>& vector, const int& maxInVectors);

// �������� ������� �� ������
std::vector<double> operator*(const std::vector<std::vector<double>>& matrix,
    const std::vector<double>& vector);

double estimationOfSolutionAccuracy(const std::vector<double>& x,
    const std::vector<double>& xSolve);

double relativeSolutionError(const std::vector<double>& x,
    const std::vector<double>& xSolve, const double& q = 1);
