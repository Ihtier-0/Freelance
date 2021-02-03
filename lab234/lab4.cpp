#include "lab4.h"

bool isPalindrome(const wstring &str)
{
    int size = str.size();
    for(int i = 0; i < size / 2; ++i)
    {
        if(str[i] != str[size - 1 - i])
        {
            return false;
        }
    }

    return true;
}

void lab4()
{
    wcout << L"Лабораторная работа №5. Вариант №22\n"
              << L"Макаров Егор Максимович, группа 19-ВТ-1\n\n"
              << L"Является ли слово палиндромом\n"
              << L"Введите слово: \n";

    wstring str;
    wcin >> str;

    if(isPalindrome(str))
    {
        wcout << L"Введённое слово является палиндромом";
    }
    else
    {
        wcout << L"Введённое слово не является палиндромом";
    }
}
