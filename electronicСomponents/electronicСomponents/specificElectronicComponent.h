#pragma once

#include <iostream>

#include "electronic�omponent.h"

class specificElectronicComponent :
    public electronic�omponent
{
public:
    specificElectronicComponent();
    specificElectronicComponent(const long long& a_stockNumber,
        const std::string& a_name,
        const long long& a_value,
        const std::string& a_unit,
        const std::string& a_manufacturerCountry,
        const double& a_price);
    specificElectronicComponent(const specificElectronicComponent& s);
    ~specificElectronicComponent() override {}
    
private:
    // ������ �������������
    std::string manufacturerCountry;
    // ����
    double price;

    friend std::ostream& operator<<(std::ostream& out, const specificElectronicComponent& s);
    friend std::istream& operator>>(std::istream& is, specificElectronicComponent& s);
};