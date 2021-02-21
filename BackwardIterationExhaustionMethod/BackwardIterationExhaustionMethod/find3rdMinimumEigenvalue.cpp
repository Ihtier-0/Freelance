#include "find3rdMinimumEigenvalue.h"

#include "utils.h"
#include "KhaletskySolver.h"

#include <iostream>

bool find3rdMinimumEigenvalue(const std::vector<std::vector<double>>& matrix,
    const std::pair<double, double> &FirstAndSecondEigenvalue,
    const std::pair<std::vector<double>, std::vector<double>> &FirstAndSecondEigenvector,
    double& ThirdMinimumEigenvalue,
    std::vector<double>& EigenVector,
    const double& EpsilonMinEigenvalue,
    const double& EpsilonEigenVector,
    const std::vector<double>& initialApproximation,
    double& r,
    int& realNumberOfIteration,
    const unsigned int& numberOfIteration)
{
    realNumberOfIteration = 0;

    int size = matrix.size();

    std::vector<std::vector<double>> x1(1), x2(1);
    x1[0] = FirstAndSecondEigenvector.first;
    x2[0] = FirstAndSecondEigenvector.second;

    std::vector<std::vector<double>> rightSideMatrix = createIdentityMatrix(size) - transposition(x1) * x1 - transposition(x2) * x2;

    std::vector<double> x = initialApproximation;
    std::vector<double> xPrev;

    std::vector<double> v;
    std::vector<double> vPrev;

    v = x;    // v[k]
    normalize(v);

    KhaletskySolver S(matrix, v);

    if (!S.Solve(x))  // x[k + 1]
    {
        return false;
    }

    ++realNumberOfIteration;

    for (int i = 1; i < numberOfIteration; ++i)
    {
        vPrev = v;    //  v[k - 1]
        xPrev = x;    //  x[k]

        v = x;        // v[k]
        normalize(v);

        KhaletskySolver S(matrix, rightSideMatrix * v);

        if (!S.Solve(x))  // x[k + 1]
            return false;

        ++realNumberOfIteration;

        // иногда векторы направленны в разные стороны, но угол между -xPrev и x мал
        if (((angleBetweenVectors(x, xPrev) < EpsilonEigenVector) || (angleBetweenVectors(x, (-1) * xPrev) < EpsilonEigenVector)) &&
            (abs((scalarProduct(vPrev, xPrev) - scalarProduct(v, x)) < EpsilonMinEigenvalue)))
        {
            break;
        }
    }

    ThirdMinimumEigenvalue = scalarProduct(v, x);
    ThirdMinimumEigenvalue = 1 / ThirdMinimumEigenvalue;

    r = norm(matrix * v - ThirdMinimumEigenvalue * v);

    EigenVector = v;

    return true;
}
