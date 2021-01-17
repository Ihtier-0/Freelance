#pragma once

#include <iostream>

#include "detail.h"

// конкретная деталь
class specificDetail :
    public detail
{
public:
    // конструктор
    specificDetail();
    // конструктор который принимает все поля класса
    specificDetail(const long long& stockNumber,
        const char* name,
        const long long& value,
        const char* unit,
        const char* Country,
        const double& price);
    // конструктор копирования
    specificDetail(const specificDetail& specificDetail);
    // деструктор
    ~specificDetail() override;
    
private:
    // страна производитель
    char* country;
    // цена
    double price;

    // операторы вывода и ввода
    friend std::ostream& operator<<(std::ostream& out, const specificDetail& Detail);
    friend std::istream& operator>>(std::istream& is, specificDetail& Detail);
};


