#pragma once
#include "geometricFigure.h"

class circle :
    public geometricFigure 
{
public:
    circle(const Point& a_center, const double& a_radius);
    virtual void move(const Point& p);
    virtual void resize(const double& r);

    Point center();
    double radius();
private:
    Point m_center;
    double m_radius;
};

