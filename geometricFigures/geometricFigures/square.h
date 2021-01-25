#pragma once
#include "geometricFigure.h"

class square :
    public geometricFigure
{
public:
    square(const Point& a_lowerLeftVertex, const double& a_width);
    void move(const Point& p);
    virtual  void resize(const double& r);

    Point lowerLeftVertex();
    virtual Point topRightVertex();
    double width();
protected:
    Point m_lowerLeftVertex;
    double m_width;
};

