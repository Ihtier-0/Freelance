#include "rectangle.h"

rectangle::rectangle(const Point& a_lowerLeftVertex, const double& a_width, const double& a_height)
	: square(a_lowerLeftVertex, a_width), m_height(a_height) {}

void rectangle::resize(const double& r)
{
	if (r > 0)
	{
		m_height *= r;
		m_width *= r;
	}
}

Point rectangle::topRightVertex()
{
	return Point(m_lowerLeftVertex.x() + m_width, m_lowerLeftVertex.y() + m_height);
}

double rectangle::height()
{
	return m_height;
}
