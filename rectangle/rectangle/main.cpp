using namespace std;

#include <iostream>

class Point
{
public:
	Point(const double& a_x = 0, const double& a_y = 0);
	double x() const;
	double y() const;

	void setX(const double& x);
	void setY(const double& y);
private:
	double m_x, m_y;

	friend Point operator+(const Point& p1, const Point& p2);
	friend Point operator-(const Point& p1, const Point& p2);
	friend Point operator*(const double& k, const Point& p2);
	friend Point operator*(const Point& p1, const double& k);

	friend std::ostream& operator<<(std::ostream& out, const Point& p);
};

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

void Point::setX(const double& x)
{
	m_x = x;
}

void Point::setY(const double& y)
{
	m_y = y;
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

class rectangle
{
public:
	rectangle();

	rectangle(const Point& a_lowerLeftVertex, const double& a_width, const double& a_height);

	rectangle(const rectangle& r);

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

rectangle::rectangle() : m_lowerLeftVertex(), m_height(0), m_width(0) {}

rectangle::rectangle(const Point& a_lowerLeftVertex, const double& a_width, const double& a_height)
	: m_lowerLeftVertex(a_lowerLeftVertex), m_width(a_width), m_height(a_height) {}

rectangle::rectangle(const rectangle& r) : m_lowerLeftVertex(r.m_lowerLeftVertex), m_width(r.m_width), m_height(r.m_height) {}

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

rectangle minRectangleContainingBothOthers(const rectangle& p1, const rectangle& p2)
{
	Point lowerLeft;
	int maxHeight = 0, maxWidth = 0;

	if (p1.lowerLeftVertex().x() < p2.lowerLeftVertex().x())
	{
		lowerLeft.setX(p1.lowerLeftVertex().x());
	}
	else
	{
		lowerLeft.setX(p2.lowerLeftVertex().x());
	}

	if (p1.lowerLeftVertex().y() < p2.lowerLeftVertex().y())
	{
		lowerLeft.setY(p1.lowerLeftVertex().y());
	}
	else
	{
		lowerLeft.setY(p2.lowerLeftVertex().y());
	}

	if (abs(lowerLeft.x() - p1.topRightVertex().x()) > abs(lowerLeft.x() - p2.topRightVertex().x()))
	{
		maxWidth = abs(lowerLeft.x() - p1.topRightVertex().x());
	}
	else
	{
		maxWidth = abs(lowerLeft.x() - p2.topRightVertex().x());
	}

	if (abs(p1.topRightVertex().y() - lowerLeft.y()) > abs(p2.topRightVertex().y() - lowerLeft.y()))
	{
		maxHeight = abs(p1.topRightVertex().y() - lowerLeft.y());
	}
	else
	{
		maxHeight = abs(p2.topRightVertex().y() - lowerLeft.y());
	}

	return rectangle(lowerLeft, maxWidth, maxHeight);
}

rectangle intersectionRectangles(const rectangle& p1, const rectangle& p2)
{
	Point lowerLeft;
	int height = 0, width = 0;

	if (p1.lowerLeftVertex().x() > p2.lowerLeftVertex().x())
	{
		lowerLeft.setX(p1.lowerLeftVertex().x());
	}
	else
	{
		lowerLeft.setX(p2.lowerLeftVertex().x());
	}

	if (p1.lowerLeftVertex().y() > p2.lowerLeftVertex().y())
	{
		lowerLeft.setY(p1.lowerLeftVertex().y());
	}
	else
	{
		lowerLeft.setY(p2.lowerLeftVertex().y());
	}

	if (abs(lowerLeft.x() - p1.topRightVertex().x()) > abs(lowerLeft.x() - p2.topRightVertex().x()))
	{
		width = abs(lowerLeft.x() - p2.topRightVertex().x());
	}
	else
	{
		width = abs(lowerLeft.x() - p1.topRightVertex().x());
	}

	if (abs(lowerLeft.y() - p1.topRightVertex().y()) > abs(lowerLeft.y() - p2.topRightVertex().y()))
	{
		height = abs(lowerLeft.y() - p2.topRightVertex().y());
	}
	else
	{
		height = abs(lowerLeft.y() - p1.topRightVertex().y());
	}


	return rectangle(lowerLeft, width, height);
}

int main()
{
	rectangle r(Point(1, 1), 3, 5);

	cout << "begin\n";

	cout << "rectangle: width: " << r.width() << " height: " << r.height()
		<< " lowerLeftVertex: " << r.lowerLeftVertex() << " topRightVertex: " << r.topRightVertex() << '\n';

	cout << "move 1, -5\n";

	r.move(Point(1, -5));

	cout << "rectangle: width: " << r.width() << " height: " << r.height()
		<< " lowerLeftVertex: " << r.lowerLeftVertex() << " topRightVertex: " << r.topRightVertex() << '\n';

	cout << "resize 2\n";

	r.resize(2);

	cout << "rectangle: width: " << r.width() << " height: " << r.height()
		<< " lowerLeftVertex: " << r.lowerLeftVertex() << " topRightVertex: " << r.topRightVertex() << '\n';

	rectangle r2(Point(1, 3), 4, 9);
	rectangle c(minRectangleContainingBothOthers(r, r2)), i(intersectionRectangles(r, r2));

	cout << "r1: width: " << r.width() << " height: " << r.height()
		<< " lowerLeftVertex: " << r.lowerLeftVertex() << " topRightVertex: " << r.topRightVertex() << '\n';
	cout << "r2: width: " << r2.width() << " height: " << r2.height()
		<< " lowerLeftVertex: " << r2.lowerLeftVertex() << " topRightVertex: " << r2.topRightVertex() << '\n';
	cout << "min rectangle containing r1 and r2: width: " << c.width() << " height: " << c.height()
		<< " lowerLeftVertex: " << c.lowerLeftVertex() << " topRightVertex: " << c.topRightVertex() << '\n';
	cout << "intersection rectangle r1 and r2: width: " << i.width() << " height: " << i.height()
		<< " lowerLeftVertex: " << i.lowerLeftVertex() << " topRightVertex: " << i.topRightVertex() << '\n';
}