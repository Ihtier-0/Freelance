#pragma once

#include "Point.h"

class rectangle
{
public:
    rectangle(const Point& a_lowerLeftVertex, const double& a_width, const double& a_height);

    void resize(const double& r);

    Point topRightVertex() const;
    Point lowerLeftVertex() const;

    double height() const;
    double width() const;

    void move(const Point& p);

private:
    double m_height;
    double m_width;
    Point m_lowerLeftVertex;
};
