#include "circle.h"

circle::circle(const Point& a_center, const double& a_radius)
	: m_center(a_center), m_radius(a_radius > 0 ? a_radius : 0) {}

void circle::move(const Point& p)
{
	m_center = m_center + p;
}

void circle::resize(const double& r)
{
	if (r > 0)
	{
		m_radius *= r;
	}
}

Point circle::center()
{
	return m_center;
}

double circle::radius()
{
	return m_radius;
}
