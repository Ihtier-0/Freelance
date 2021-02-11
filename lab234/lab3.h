#ifndef LAB3_H
#define LAB3_H

#include <random>
#include <iostream>

template<int size>
void printMaxtrix(double (*matrix)[size][size])
{
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            std::wcout << matrix[i][j] << ' ';
        }
        std::wcout << '\n';
    }
}

template<int size>
void fillMatrix(double (*matrix)[size][size])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if(rand() % 2)
            {
                matrix[i][j] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * 200 - 100;
            }
            else // такой рандом чтобы какие-то числа были целыми
            {
                matrix[i][j] = pow(-1, rand() % 2) * (rand() % 100);
            }
        }
    }
}

template<int size>
int sumIntPosiriveElements(double (*matrix)[size][size])
{
    int sum = 0;

    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            if(matrix[i][j] > 0 && matrix[i][j] == static_cast<int>(matrix[i][j]))
            {
                sum += matrix[i][j];
            }
        }
    }

    return sum;
}

void lab3();

#endif // LAB3_H
