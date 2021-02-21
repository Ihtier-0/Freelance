#pragma once

#include <vector>

bool find3rdMinimumEigenvalue(const std::vector<std::vector<double>>& matrix,
    const std::pair<double, double>& FirstAndSecondEigenvalue,
    const std::pair<std::vector<double>, std::vector<double>>& FirstAndSecondEigenvector,
    double& ThirdMinimumEigenvalue,
    std::vector<double>& EigenVector,
    const double& EpsilonMinEigenvalue,
    const double& EpsilonEigenVector,
    const std::vector<double>& initialApproximation,
    double& r,
    int& realNumberOfIteration,
    const unsigned int& numberOfIteration = 1000);