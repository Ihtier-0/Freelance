#include "Point.h"

Point::Point(const double& a_x, const double& a_y)
	: m_x(a_x), m_y(a_y) {}

double Point::x() const
{
	return m_x;
}

double Point::y() const
{
	return m_y;
}

Point operator+(const Point& p1, const Point& p2)
{
	return Point(p1.m_x + p2.m_x, p1.m_y + p2.m_y);
}

Point operator-(const Point& p1, const Point& p2)
{
	return Point(p1.m_x - p2.m_x, p1.m_y - p2.m_y);
}

Point operator*(const double& k, const Point& p2)
{
	return Point(k * p2.m_x, k * p2.m_y);
}

Point operator*(const Point& p1, const double& k)
{
	return Point(k * p1.m_x, k * p1.m_y);
}

std::ostream& operator<<(std::ostream& out, const Point& p)
{
	out << p.m_x << ' ' << p.m_y;
	return out;
}
