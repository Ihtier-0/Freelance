#include <iostream>
#include "utils.h"
#include "findmineigenvalue.h"

#include <vector>

int main()
{
    int ranges[] = { 2, 50 };
    int countOfIteration = 10;

    for (int rangeEigen : ranges)
    {
        for (double accuracy = 1e-5f; accuracy >= 1e-8f; accuracy *= 1e-3f)
        {
            for (double dimension = 10; dimension <= 50; dimension += 20)
            {
                double sumEigenvalueAccuracy = 0;
                double sumEigenvectorAccuracy = 0;
                double sumR = 0;
                double sumIter = 0;
                for (int iteration = 0; iteration < countOfIteration; ++iteration)
                {
                    std::vector<std::vector<double>> matrix;
                    std::vector<std::vector<double>> eigenVectors;
                    std::vector<double> eigenValues;

                    GenerateMatrixWithEigenValues(matrix, eigenValues, eigenVectors, dimension, rangeEigen);

                    int minIndex = indexMinAbsElement(eigenValues);
                    double minEigenvalue;
                    std::vector<double> EigenVector;
                    std::vector<double> initialApproximation(dimension, 1);
                    double r;
                    int realNumberOfIteration;

                    if (!FindMinEigenValue(matrix, minEigenvalue, EigenVector, accuracy, accuracy,
                        initialApproximation, r, realNumberOfIteration))
                    {
                        --iteration;
                        continue;
                    }

                    sumEigenvalueAccuracy += abs(minEigenvalue - eigenValues[minIndex]);
                    sumEigenvectorAccuracy += estimationOfSolutionAccuracy(EigenVector, eigenVectors[minIndex]);
                    sumR += r;
                    sumIter += realNumberOfIteration;
                }
                std::cout << "dimension: " << dimension << '\n';
                std::cout << "rangeEigen: " << rangeEigen << '\n';
                std::cout << "accuracy: " << accuracy << '\n';
                std::cout << "sr EigenvalueAccuracy: " << sumEigenvalueAccuracy / countOfIteration << '\n';
                std::cout << "sr EigenvectorAccuracy: " << sumEigenvectorAccuracy / countOfIteration << '\n';
                std::cout << "sr R: " << sumR / countOfIteration << '\n';
                std::cout << "sr Iter: " << sumIter / countOfIteration << "\n\n";
            }
        }
    }
}
