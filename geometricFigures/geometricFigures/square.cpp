#include "square.h"

square::square(const Point& a_lowerLeftVertex, const double& a_width)
	: m_width(a_width > 0 ? a_width : 0), m_lowerLeftVertex(a_lowerLeftVertex) {}

void square::move(const Point& p)
{
	m_lowerLeftVertex = m_lowerLeftVertex + p;
}

void square::resize(const double& r)
{
	if (r > 0)
	{
		m_width *= r;
	}
}

Point square::lowerLeftVertex()
{
	return m_lowerLeftVertex;
}

Point square::topRightVertex()
{
	return Point(m_lowerLeftVertex.x() + m_width, m_lowerLeftVertex.x() + m_width);
}

double square::width()
{
	return m_width;
}
