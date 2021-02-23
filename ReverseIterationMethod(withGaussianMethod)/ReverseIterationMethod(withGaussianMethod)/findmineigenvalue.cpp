#include "findmineigenvalue.h"
#include "utils.h"
#include "GaussSolver.h"

#include <iostream>

bool FindMinEigenValue(const std::vector<std::vector<double>>& matrix,
    double& minEigenvalue,
    std::vector<double>& EigenVector,
    const double& EpsilonMinEigenvalue,
    const double& EpsilonEigenVector,
    const std::vector<double>& initialApproximation,
    double& r,
    int& realNumberOfIteration,
    const unsigned int& numberOfIteration)
{
    realNumberOfIteration = 0;

    std::vector<double> x = initialApproximation;
    std::vector<double> xPrev;

    std::vector<double> v;
    std::vector<double> vPrev;

    v = x;    // v[k]
    normalize(v);
    GaussSolver S(matrix, v);

    if (!S.Solve(x))  // x[k + 1]
        return false;

    ++realNumberOfIteration;

    for (int i = 1; i < numberOfIteration; ++i)
    {
        vPrev = v;    //  v[k - 1]
        xPrev = x;    //  x[k]

        v = x;        // v[k]
        normalize(v);

        GaussSolver S(matrix, v);

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

    minEigenvalue = scalarProduct(v, x);
    minEigenvalue = 1 / minEigenvalue;

    r = norm(matrix * v - minEigenvalue * v);

    EigenVector = v;

    return true;
}
