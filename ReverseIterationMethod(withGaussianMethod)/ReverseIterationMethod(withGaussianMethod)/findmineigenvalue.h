#pragma once

#include <vector>

bool FindMinEigenValue(const std::vector<std::vector<double>>& matrix,
    double& minEigenvalue,
    std::vector<double>& EigenVector,
    const double& EpsilonMinEigenvalue,
    const double& EpsilonEigenVector,
    const std::vector<double>& initialApproximation,
    double& r,
    int& realNumberOfIteration,
    const unsigned int& numberOfIteration = 1000);