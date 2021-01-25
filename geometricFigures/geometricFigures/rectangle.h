#pragma once
#include "square.h"

class rectangle :
    public square
{
public:
    rectangle(const Point& a_lowerLeftVertex, const double& a_width, const double& a_height);

    void resize(const double& r) override;
    Point topRightVertex() override;
    double height();
private:
    double m_height;
};

