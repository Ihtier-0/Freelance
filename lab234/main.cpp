#include <ctime>

#ifdef WIN32
#include <math.h>
#include <windows.h>
#endif // WIN32

#include "lab2.h"
#include "lab3.h"
#include "lab4.h"
#include "aboutauthor.h"

using namespace std;

void menu()
{
    wcout << L"Выберите пункт меню\n"
          << L"1. Лабораторная работа №2\n"
          << L"2. Лабораторная работа №3\n"
          << L"3. Лабораторная работа №4\n"
          << L"4. Об авторе\n"
          << L"5. Выход\n\n";
}

bool tasks(const int& command)
{
    switch(command)
    {
    case 1:
    {
        lab2();
        break;
    }
    case 2:
    {
        lab3();
        break;
    }
    case 3:
    {
        lab4();
        break;
    }
    case 4:
    {
        aboutAuthor();
        break;
    }
    }

    return !(command < 1 || command > 5);
}

int main()
{
#ifdef WIN32
    SetConsoleOutputCP( 1251 );
    SetConsoleCP( 1251 );
#endif // WIN32
    setlocale( LC_ALL, "Russian" );
    setlocale( LC_NUMERIC, "C" );

    int command = 0;

    do
    {
        menu();
        while(true)
        {
            while(!(wcin >> command) || (wcin.peek() != '\n'))
            {
                wcin.clear();
                while (wcin.get() != '\n') {}
                wcout << L"Необходимо ввести число!" <<endl;
            }

            if(!tasks(command))
            {
                wcout << L"Ошибка! Введите число в указанном диапазоне!\n";
            }
            else
            {
                break;
            }
        }

        wcout << "\n\n";
        for(int i = 0; i < 100; ++i)
        {
            wcout << '-';
        }
        wcout << "\n\n";
    }while(command != 5);
}
