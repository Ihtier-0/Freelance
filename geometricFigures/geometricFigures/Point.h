#pragma once

#include <iostream>

class Point
{
public:
	Point(const double& a_x, const double& a_y);
	double x() const;
	double y() const;
private:
	double m_x, m_y;

	friend Point operator+(const Point& p1, const Point& p2);
	friend Point operator-(const Point& p1, const Point& p2);
	friend Point operator*(const double& k, const Point& p2);
	friend Point operator*(const Point& p1, const double& k);

	friend std::ostream& operator<<(std::ostream &out, const Point& p);
};

