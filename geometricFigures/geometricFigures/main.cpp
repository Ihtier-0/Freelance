#include <iostream>

using namespace std;

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

class geometricFigure
{
public:
	virtual void move(const Point& p) = 0;
	virtual void resize(const double& r) = 0;
};

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

class rectangle :
	public square
{
public:
	rectangle(const Point& a_lowerLeftVertex, const double& a_width, const double& a_height);

	void resize(const double& r) override;
	Point topRightVertex() override;
	double height();
private:
	double m_height;
};

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

int main()
{
	circle c(Point(0,0), 4);
	rectangle r(Point(1, 1), 3, 5);
	square s(Point(2, 2), 2);

	cout << "begin:\n";

	cout << "circle: center: " << c.center() << " radius: " << c.radius() << '\n';
	cout << "rectangle: width: " << r.width() << " height: " << r.height()
		<< " lowerLeftVertex: " << r.lowerLeftVertex() << " topRightVertex: " << r.topRightVertex() << '\n';
	cout << "square: width: " << s.width()
		<< " lowerLeftVertex: " << s.lowerLeftVertex() << " topRightVertex: " << s.topRightVertex() << '\n';

	cout << "move (1, -5):\n";

	c.move(Point(1, -5));
	r.move(Point(1, -5));
	s.move(Point(1, -5));

	cout << "circle: center: " << c.center() << " radius: " << c.radius() << '\n';
	cout << "rectangle: width: " << r.width() << " height: " << r.height()
		<< " lowerLeftVertex: " << r.lowerLeftVertex() << " topRightVertex: " << r.topRightVertex() << '\n';
	cout << "square: width: " << s.width()
		<< " lowerLeftVertex: " << s.lowerLeftVertex() << " topRightVertex: " << s.topRightVertex() << '\n';

	cout << "resize 2:\n";

	c.resize(2);
	r.resize(2);
	s.resize(2);

	cout << "circle: center: " << c.center() << " radius: " << c.radius() << '\n';
	cout << "rectangle: width: " << r.width() << " height: " << r.height()
		<< " lowerLeftVertex: " << r.lowerLeftVertex() << " topRightVertex: " << r.topRightVertex() << '\n';
	cout << "square: width: " << s.width()
		<< " lowerLeftVertex: " << s.lowerLeftVertex() << " topRightVertex: " << s.topRightVertex() << '\n';
}