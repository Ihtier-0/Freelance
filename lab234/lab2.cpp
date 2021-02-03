#include "lab2.h"

#include <iostream>
#include <cmath>

using namespace std;

void lab2()
{
    wcout << L"Лабораторная работа №2. Вариант №22\n" << L"Макаров Егор Максимович, группа 19-ВТ-1\n\n" << L"Задание: (a^b)-(c%2)\n";

    float a,b,c;
    //Ввод значений коэффициентов уравнения

    while(true)
    {
        wcout << L"Введите вещественное число а (от -1000.0 до 1000.0):\n";
        while (!(wcin >> a) || (wcin.peek() != '\n'))
        {
            wcin.clear();
            while (wcin.get() != '\n') {};
            wcout << L"Необходимо ввести число!" <<endl;
        }

        if(a < 1 || a > 100)
        {
            wcout << L"Ошибка! Введите число в указанном диапазоне!";
        }
        else
        {
                break;
        }
    }

    while(true)
    {
        wcout << L"Введите вещественное число b (от -1000.0 до 1000.0):\n";
        while (!(wcin >> b) || (wcin.peek() != '\n'))
        {
            wcin.clear();
            while (wcin.get() != '\n') {};
            wcout << L"Необходимо ввести число!" << endl;
        }

        if(b < 1 || b > 100)
        {
            wcout << L"Ошибка! Введите число в указанном диапазоне!";
        }
        else
        {
            break;
        }
    }

    while (true)
    {
        wcout << L"Введите вещественное число c (от -1000.0 до 1000.0):\n";
        while (!(wcin >> c) || (wcin.peek() != '\n'))
        {
            wcin.clear();
            while (wcin.get() != '\n') {};
            wcout << L"Необходимо ввести число!" << endl;
        }

        if(c < 1 || c > 100)
        {
            wcout << L"Ошибка! Введите число в указанном диапазоне!";
        }
        else
        {
            break;
        }
    }

    wcout << L"Результат: " << (pow(a,b)) - fmod(c,2); // Вычисление уравнения
}
