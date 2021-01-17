#pragma once

#include <iostream>

#include "detail.h"

// ���������� ������
class specificDetail :
    public detail
{
public:
    // �����������
    specificDetail();
    // ����������� ������� ��������� ��� ���� ������
    specificDetail(const long long& stockNumber,
        const char* name,
        const long long& value,
        const char* unit,
        const char* Country,
        const double& price);
    // ����������� �����������
    specificDetail(const specificDetail& specificDetail);
    // ����������
    ~specificDetail() override;
    
private:
    // ������ �������������
    char* country;
    // ����
    double price;

    // ��������� ������ � �����
    friend std::ostream& operator<<(std::ostream& out, const specificDetail& Detail);
    friend std::istream& operator>>(std::istream& is, specificDetail& Detail);
};


