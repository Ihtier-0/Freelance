#include "lab3.h"

#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

void printMaxtrix(const double * const * const &matrix, const int &size)
{
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            wcout << matrix[i][j] << ' ';
        }
        wcout << '\n';
    }
}

void fillMatrix(double **matrix, const int &size)
{
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
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

int sumIntPosiriveElements(const double * const * const &matrix, const int &size)
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

void lab3()
{
    srand(time(0));

    wcout << L"Лабораторная работа №4. Вариант №22\n" << L"Макаров Егор Максимович, группа 19-ВТ-1\n\n" << L"сумма положительных целых элементов в матрице\n";

    int size;
    //Ввод размерности матрицы
    while(true)
    {
        wcout << L"Введите размерность матрицы число а (от 1 до 20):\n";

        while(!(wcin >> size) || (wcin.peek() != '\n'))
        {
            wcin.clear();
            while (wcin.get() != '\n') {}
            wcout << L"Необходимо ввести число!" <<endl;
        }

        if(size < 1 || size > 20)
        {
            wcout << L"Ошибка! Введите число в указанном диапазоне!\n";
        }
        else
        {
            break;
        }
    }

    double ** matrix = new double*[size];
    for(int i = 0; i < size; ++i)
    {
        matrix[i] = new double[size];
    }

    fillMatrix(matrix, size);
    wcout << L"Сгенерированная матрица:\n";
    printMaxtrix(matrix, size);

    int sumPositive = sumIntPosiriveElements(matrix, size);

    if(sumPositive == 0)
    {
       wcout << L"В матрице нет положительных или целых элементов\n";
    }
    else
    {
       wcout << L"Сумма положительных целых элементов в матрице: " << sumPositive;
    }
}
