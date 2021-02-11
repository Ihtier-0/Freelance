#include "lab3.h"

#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

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

    double matrix[20][20];

    fillMatrix(&matrix);
    wcout << L"Сгенерированная матрица:\n";
    printMaxtrix(&matrix);

    int sumPositive = sumIntPosiriveElements(&matrix);

    if(sumPositive == 0)
    {
       wcout << L"В матрице нет положительных или целых элементов\n";
    }
    else
    {
       wcout << L"Сумма положительных целых элементов в матрице: " << sumPositive;
    }
}
