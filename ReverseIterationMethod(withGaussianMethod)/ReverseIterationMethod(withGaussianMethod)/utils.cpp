#include "utils.h"

std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<double>>& matrix)
{
    unsigned int size = matrix.size();

    for (unsigned int i = 0; i < size; ++i)
    {
        for (unsigned int j = 0; j < matrix[i].size(); ++j)
        {
            out.width(9);
            out << matrix[i][j] << ' ';
        }

        out << '\n';
    }

    return out;
}

std::ostream& operator<<(std::ostream& out, const std::vector<double>& vector)
{
    int size = vector.size();

    for (int i = 0; i < size; ++i)
    {
        out << vector[i] << ' ';
    }

    return out;
}

std::vector<std::vector<double>> operator*(const std::vector<std::vector<double>>& matrix1,
    const std::vector<std::vector<double>>& matrix2)
{
    unsigned int sizeROW1 = matrix1.size();
    unsigned int sizeCOL1 = matrix1[0].size();

    std::vector<std::vector<double>> result(sizeROW1);

    for (unsigned int i = 0; i < sizeROW1; i++)
    {
        result[i].resize(sizeROW1);
        for (unsigned int j = 0; j < sizeROW1; j++)
        {
            result[i][j] = 0;
            for (unsigned int k = 0; k < sizeCOL1; k++)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

std::vector<double> operator*(const std::vector<std::vector<double>>& matrix,
    std::vector<double>& vector)
{
    int size = vector.size();

    std::vector<double> result(size);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

std::vector<std::vector<double>> operator+(const std::vector<std::vector<double>>& matrix1, const std::vector<std::vector<double>>& matrix2)
{
    unsigned int sizeRow = matrix1.size();
    unsigned int sizeCol = matrix1[0].size();

    std::vector<std::vector<double>> result(sizeRow);

    for (unsigned int i = 0; i < sizeRow; ++i)
    {
        result[i].resize(sizeCol);
        for (unsigned int j = 0; j < sizeCol; ++j)
        {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    return result;
}

std::vector<std::vector<double>> operator-(const std::vector<std::vector<double>>& matrix1, const std::vector<std::vector<double>>& matrix2)
{
    return (matrix1 + (-1) * matrix2);
}

std::vector<std::vector<double>> operator*(const std::vector<std::vector<double>>& matrix, const double& k)
{
    unsigned int sizeRow = matrix.size();
    unsigned int sizeCol = matrix[0].size();

    std::vector<std::vector<double>> result(sizeRow);

    for (unsigned int i = 0; i < sizeRow; ++i)
    {
        result[i].resize(sizeCol);
        for (unsigned int j = 0; j < sizeCol; ++j)
        {
            result[i][j] = matrix[i][j] * k;
        }
    }
    return result;
}

std::vector<std::vector<double>> operator*(const double& k, const std::vector<std::vector<double>>& matrix)
{
    return matrix * k;
}

std::vector<double> operator*(const std::vector<double>& vector, const double& k)
{
    unsigned int size = vector.size();

    std::vector<double> result = vector;

    for (unsigned int i = 0; i < size; ++i)
    {
        result[i] *= k;
    }

    return result;
}

std::vector<double> operator*(const double& k, const std::vector<double>& vector)
{
    return vector * k;
}

std::vector<double> operator+(const std::vector<double>& vector1, const std::vector<double>& vector2)
{
    unsigned int size = vector1.size();

    std::vector<double> result(size);

    for (unsigned int i = 0; i < size; ++i)
    {
        result[i] = vector1[i] + vector2[i];
    }

    return result;
}

std::vector<double> operator-(const std::vector<double>& vector1, const std::vector<double>& vector2)
{
    return vector1 + ((-1) * vector2);
}

std::vector<double> randomVector(const unsigned int& size, const unsigned int& maxValue)
{
    std::vector<double> result(size);

    for (unsigned int i = 0; i < size; ++i)
    {
        result[i] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (static_cast<double>(maxValue) + maxValue) - maxValue;
    }

    return result;
}

std::vector<std::vector<double>> createDiagonalMatrix(const std::vector<double>& vector)
{
    unsigned int size = vector.size();

    std::vector<std::vector<double>> result(size);

    for (unsigned int i = 0; i < size; ++i)
    {
        result[i].resize(size);
        for (unsigned int j = 0; j < size; ++j)
        {
            result[i][j] = 0;
        }
        result[i][i] = vector[i];
    }

    return result;
}

std::vector<std::vector<double>> createIdentityMatrix(const unsigned int& size)
{
    std::vector<std::vector<double>> matrix(size);

    for (unsigned int i = 0; i < size; ++i)
    {
        matrix[i].resize(size);
        for (unsigned int j = 0; j < size; ++j)
        {
            matrix[i][j] = 0;
        }
        matrix[i][i] = 1;
    }

    return matrix;
}

std::vector<std::vector<double>> createRandomMatrix(const unsigned int& sizeRow, const unsigned int& sizeCol)
{
    std::vector<std::vector<double>> result(sizeRow);

    for (unsigned int i = 0; i < sizeRow; ++i)
    {
        result[i].resize(sizeCol);
        for (unsigned int j = 0; j < sizeCol; ++j)
        {
            result[i][j] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        }
    }
    return result;
}

std::vector<std::vector<double>> transposition(const std::vector<std::vector<double>>& matrix)
{
    unsigned int sizeRow = matrix.size();
    unsigned int sizeCol = matrix[0].size();

    std::vector<std::vector<double>> result(sizeCol);

    for (unsigned int i = 0; i < sizeCol; ++i)
    {
        result[i].resize(sizeRow);
    }

    for (unsigned int i = 0; i < sizeRow; ++i)
    {
        for (unsigned int j = 0; j < sizeCol; ++j)
        {
            result[j][i] = matrix[i][j];
        }
    }

    return result;
}

std::vector<std::vector<double>> normalize(const std::vector<std::vector<double>>& matrix)
{
    std::vector<std::vector<double>> result = matrix;

    unsigned int sizeRow = matrix.size();
    unsigned int sizeCol = matrix[0].size();

    double sum = 0;

    for (unsigned int i = 0; i < sizeRow; ++i)
    {
        for (unsigned int j = 0; j < sizeCol; ++j)
        {
            sum += result[i][j] * result[i][j];
        }
    }

    return result * (1 / sqrt(sum));
}

void normalize(std::vector<double>& vector)
{
    unsigned int size = vector.size();

    double norma = norm(vector);

    vector = vector * (1 / norma);
}

double norm(const std::vector<double>& vector)
{
    unsigned int size = vector.size();

    double norm = 0;

    for (unsigned int i = 0; i < size; ++i)
    {
        norm += vector[i] * vector[i];
    }

    return sqrt(norm);
}

void findPositionAbsMaximumOutOfDiagonalElement(const std::vector<std::vector<double>>& matrix,
    unsigned int& rowIndex, unsigned int& colIndex)
{
    unsigned int rowSize = matrix.size();
    unsigned int colSize = matrix[0].size();

    unsigned int maxRowIndex = 0, maxColIndex = 1;

    for (int i = 0; i < rowSize; ++i)
    {
        for (int j = 0; j < colSize; ++j)
        {
            if (i == j)
            {
                continue;
            }

            if (abs(matrix[i][j]) > abs(matrix[maxRowIndex][maxColIndex]))
            {
                maxRowIndex = i;
                maxColIndex = j;
            }
        }
    }

    rowIndex = maxRowIndex;
    colIndex = maxColIndex;
}

double findMaxAbsValue(const std::vector<std::vector<double>>& matrix)
{
    int rowSize = matrix.size();
    int colSize = matrix[0].size();

    double absMax = matrix[0][0];

    for (int i = 0; i < rowSize; ++i)
    {
        for (int j = 0; j < colSize; ++j)
        {
            if (abs(matrix[i][j]) > absMax)
            {
                absMax = abs(matrix[i][j]);
            }
        }
    }

    return absMax;
}

int indexMinAbsElement(const std::vector<double>& Qvector)
{
    int minIndex = 0;

    for (int i = 1; i < Qvector.size(); ++i)
    {
        if (abs(Qvector[i]) < abs(Qvector[minIndex]))
        {
            minIndex = i;
        }
    }

    return minIndex;
}

double estimationOfSolutionAccuracy(const std::vector<double>& x, const std::vector<double>& xSolve)
{
    double EstimationOfSolutionAccuracy = -1;

    for (int i = 0; i < x.size(); ++i)
    {
        if (EstimationOfSolutionAccuracy < abs(xSolve[i] - x[i]))
        {
            EstimationOfSolutionAccuracy = abs(xSolve[i] - x[i]);
        }
    }

    return EstimationOfSolutionAccuracy;
}

double angleBetweenVectors(std::vector<double> vector1, std::vector<double> vector2)
{
    double cosA = 0;

    normalize(vector1);
    normalize(vector2);

    for (int i = 0; i < vector1.size(); ++i)
    {
        cosA += vector2[i] * vector1[i];
    }

    return acos(cosA);
}

double scalarProduct(const std::vector<double>& vector1, const std::vector<double>& vector2)
{
    int size = vector1.size();

    double sum = 0;

    for (int i = 0; i < size; ++i)
    {
        sum += vector1[i] * vector2[i];
    }

    return sum;
}

void GenerateMatrixWithEigenValues(std::vector<std::vector<double>>& matrix,
    std::vector<double>& eigenValues,
    std::vector<std::vector<double>>& eigenVectors,
    const unsigned int& matrixDimension,
    const unsigned int& maxEigenValues)
{
    eigenValues = randomVector(matrixDimension, maxEigenValues);

    std::vector<std::vector<double>> DiagonalMatrix = createDiagonalMatrix(eigenValues);

    std::vector<std::vector<double>> IdentityMatrix = createIdentityMatrix(matrixDimension);

    std::vector<std::vector<double>> w = createRandomMatrix(matrixDimension, 1);
    w = normalize(w);

    std::vector<std::vector<double>> H = IdentityMatrix - 2 * w * transposition(w);
    std::vector<std::vector<double>> HT = transposition(H);
    eigenVectors = HT;
    matrix = H * DiagonalMatrix * HT;
}
