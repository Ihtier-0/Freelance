#include "rectangle.h"

rectangle::rectangle(const Point& a_lowerLeftVertex, const double& a_width, const double& a_height)
	: m_lowerLeftVertex(a_lowerLeftVertex), m_width(a_width), m_height(a_height) {}

void rectangle::resize(const double& r)
{
	if (r > 0)
	{
		m_height *= r;
		m_width *= r;
	}
}

Point rectangle::topRightVertex() const
{
	return Point(m_lowerLeftVertex.x() + m_width, m_lowerLeftVertex.y() + m_height);
}

Point rectangle::lowerLeftVertex() const
{
	return m_lowerLeftVertex;
}

double rectangle::height() const
{
	return m_height;
}

double rectangle::width() const
{
	return m_width;
}

void rectangle::move(const Point& p)
{
	m_lowerLeftVertex = m_lowerLeftVertex + p;
}
