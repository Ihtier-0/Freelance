#include <iostream>
#include "utils.h"
#include "find3rdMinimumEigenvalue.h"

#include <algorithm>
#include <vector>

int main()
{
    std::vector<std::vector<double>> matrix;
    std::vector<std::vector<double>> EigenVectors;
    std::vector<double> EigenValues
        ;
    std::pair<double, double> FirstAndSecondEigenvalue;
    std::pair<std::vector<double>, std::vector<double>> FirstAndSecondEigenvector;
    double ThirdMinimumEigenvalue;
    std::vector<double> EigenVector;
    double EpsilonMinEigenvalue;
    double EpsilonEigenVector;
    std::vector<double> initialApproximation;
    double r;
    int realNumberOfIteration;

    int firstIndex;
    int secondIndex;
    int ThirdIndex;

    int maxValue[] = { 2, 50 };

    double sumEigenvalueAccuracy;
    double sumEigenvectorAccuracy;
    double sumR;
    double sumIter;

    int countOfIteration = 3;

    for (int d = 10; d <= 50; d += 20)
    {
        for (int m : maxValue)
        {
            for (double accuracy = 1e-5f; accuracy >= 1e-8f; accuracy *= 1e-3f)
            {
                sumEigenvalueAccuracy = 0;
                sumEigenvectorAccuracy = 0;
                sumR = 0;
                sumIter = 0;

                for (int iteration = 0; iteration < countOfIteration; ++iteration)
                {
                    GenerateMatrixWithEigenValues(matrix, EigenValues, EigenVectors, d, m);

                    firstIndex = findIndexAbsMin(EigenValues);
                    secondIndex = findIndexSecondAbsMin(EigenValues);
                    ThirdIndex = findIndexThirdAbsMin(EigenValues);

                    FirstAndSecondEigenvalue.first = EigenValues[firstIndex];
                    FirstAndSecondEigenvalue.second = EigenValues[secondIndex];

                    FirstAndSecondEigenvector.first = EigenVectors[firstIndex];
                    FirstAndSecondEigenvector.second = EigenVectors[secondIndex];

                    if (!find3rdMinimumEigenvalue(matrix, FirstAndSecondEigenvalue, FirstAndSecondEigenvector,
                        ThirdMinimumEigenvalue, EigenVector, accuracy, accuracy, std::vector<double>(d, 1),
                        r, realNumberOfIteration))
                    {
                        --iteration;
                        continue;
                    }

                    sumEigenvalueAccuracy += abs(ThirdMinimumEigenvalue - EigenValues[ThirdIndex]);
                    sumEigenvectorAccuracy += estimationOfSolutionAccuracy(EigenVector, EigenVectors[ThirdIndex]);
                    sumR += r;
                    sumIter += realNumberOfIteration;
                }
                std::cout << "dimension: " << d << '\n';
                std::cout << "rangeEigen: " << m << '\n';
                std::cout << "accuracy: " << accuracy << '\n';
                std::cout << "sr EigenvalueAccuracy: " << sumEigenvalueAccuracy / countOfIteration << '\n';
                std::cout << "sr EigenvectorAccuracy: " << sumEigenvectorAccuracy / countOfIteration << '\n';
                std::cout << "sr R: " << sumR / countOfIteration << '\n';
                std::cout << "sr Iter: " << sumIter / countOfIteration << "\n\n";

            }
        }
    }
}
