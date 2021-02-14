using namespace std;

#include <iostream>

// класс точки
class Point
{
public:
	// конструктор, по умолчанию точка в начале координта
	Point(const double& a_x = 0, const double& a_y = 0);
	// геттер х
	double x() const;
	// геттер у
	double y() const;

	// сеттер х
	void setX(const double& x);
	// сеттер у
	void setY(const double& y);
private:
	double m_x, m_y;

	// оператор сложения
	friend Point operator+(const Point& p1, const Point& p2);
	// оператор разности
	friend Point operator-(const Point& p1, const Point& p2);
	// оператор умножения на число
	friend Point operator*(const double& k, const Point& p2);
	friend Point operator*(const Point& p1, const double& k);

	// оператор вывода
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
	// покоординатная сумма
	return Point(p1.m_x + p2.m_x, p1.m_y + p2.m_y);
}

Point operator-(const Point& p1, const Point& p2)
{
	// покоординатная разность
	return Point(p1.m_x - p2.m_x, p1.m_y - p2.m_y);
}

Point operator*(const double& k, const Point& p2)
{
	// покоординатное умножение на число 
	return Point(k * p2.m_x, k * p2.m_y);
}

Point operator*(const Point& p1, const double& k)
{
	// покоординатное умножение на число
	return Point(k * p1.m_x, k * p1.m_y);
}

std::ostream& operator<<(std::ostream& out, const Point& p)
{
	// вывод координат через пробел
	out << p.m_x << ' ' << p.m_y;
	return out;
}

// премоугольник
class rectangle
{
public:
	// конструктор по умолчанию
	rectangle();

	// конструктор принимающий нижнюю левую точку, ширину и высоту
	rectangle(const Point& a_lowerLeftVertex, const double& a_width, const double& a_height);

	// конструктор копирования
	rectangle(const rectangle& r);

	// изменение размерности
	void resize(const double& r);

	// геттер верхней правой вершины
	Point topRightVertex() const;
	// геттер левой нижней вершины
	Point lowerLeftVertex() const;

	// гетте высоты
	double height() const;
	// геттер ширины
	double width() const;

	// сдвиг на р
	void move(const Point& p);

private:
	double m_height;
	double m_width;
	Point m_lowerLeftVertex;
};

// по умолчанию прямоугольник вырожден в точку в начале координат
rectangle::rectangle() : m_lowerLeftVertex(), m_height(0), m_width(0) {}

rectangle::rectangle(const Point& a_lowerLeftVertex, const double& a_width, const double& a_height)
	: m_lowerLeftVertex(a_lowerLeftVertex), m_width(a_width), m_height(a_height) {}

rectangle::rectangle(const rectangle& r) : m_lowerLeftVertex(r.m_lowerLeftVertex), m_width(r.m_width), m_height(r.m_height) {}

void rectangle::resize(const double& r)
{
	if (r >= 0)
	{
		// умножаем длину и ширину
		m_height *= r;
		m_width *= r;
	}
	else
	{
		// длина не может быть меньше 0
		throw std::exception("lenght < 0");
	}
}

Point rectangle::topRightVertex() const
{
	// сдвиг на ширину по х и на высоту по у, от левой нижней точки
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
	// сдвигаем левую нижнюю точку
	m_lowerLeftVertex = m_lowerLeftVertex + p;
}

// минимальный прямоугольник содержащий оба переданных
rectangle minRectangleContainingBothOthers(const rectangle& p1, const rectangle& p2)
{
	// параметры итогового прямоугольника
	Point lowerLeft;
	int maxHeight = 0, maxWidth = 0;

	// ищем самый левый х
	if (p1.lowerLeftVertex().x() < p2.lowerLeftVertex().x())
	{
		lowerLeft.setX(p1.lowerLeftVertex().x());
	}
	else
	{
		lowerLeft.setX(p2.lowerLeftVertex().x());
	}

	// ищем самый нижний у
	if (p1.lowerLeftVertex().y() < p2.lowerLeftVertex().y())
	{
		lowerLeft.setY(p1.lowerLeftVertex().y());
	}
	else
	{
		lowerLeft.setY(p2.lowerLeftVertex().y());
	}

	// ищем максимальную ширину
	if (abs(lowerLeft.x() - p1.topRightVertex().x()) > abs(lowerLeft.x() - p2.topRightVertex().x()))
	{
		maxWidth = abs(lowerLeft.x() - p1.topRightVertex().x());
	}
	else
	{
		maxWidth = abs(lowerLeft.x() - p2.topRightVertex().x());
	}

	// ищем максимальную высоту
	if (abs(p1.topRightVertex().y() - lowerLeft.y()) > abs(p2.topRightVertex().y() - lowerLeft.y()))
	{
		maxHeight = abs(p1.topRightVertex().y() - lowerLeft.y());
	}
	else
	{
		maxHeight = abs(p2.topRightVertex().y() - lowerLeft.y());
	}

	// возвращаем созданный прямоугольник
	return rectangle(lowerLeft, maxWidth, maxHeight);
}

// пересечение 2х прямоугольников
bool intersectionRectangles(const rectangle& p1, const rectangle& p2, rectangle& result)
{
	if ((p1.lowerLeftVertex().x() < p2.lowerLeftVertex().x() && p1.topRightVertex().x() < p2.lowerLeftVertex().x()) || 
		(p1.lowerLeftVertex().x() > p2.lowerLeftVertex().x() && p1.lowerLeftVertex().x() > p2.topRightVertex().x()) ||
		(p1.lowerLeftVertex().y() > p2.topRightVertex().y()) || 
		(p2.lowerLeftVertex().y() > p1.topRightVertex().y()))
	{
		return false;
	}

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


	result = rectangle(lowerLeft, width, height);

	return true;
}

int main()
{
	rectangle r(Point(1, 1), 3, 5);

	cout << "begin\n";

	// начальные данные о прямоугольнике
	cout << "rectangle: width: " << r.width() << " height: " << r.height()
		<< " lowerLeftVertex: " << r.lowerLeftVertex() << " topRightVertex: " << r.topRightVertex() << '\n';

	cout << "move 1, -5\n";

	r.move(Point(1, -5));

	// данные о прямоугольнике сдвинутом на (1, -5)
	cout << "rectangle: width: " << r.width() << " height: " << r.height()
		<< " lowerLeftVertex: " << r.lowerLeftVertex() << " topRightVertex: " << r.topRightVertex() << '\n';

	cout << "resize 2\n";

	r.resize(2);

	// данные о прямоугольнике увеличенном в 2 раза
	cout << "rectangle: width: " << r.width() << " height: " << r.height()
		<< " lowerLeftVertex: " << r.lowerLeftVertex() << " topRightVertex: " << r.topRightVertex() << '\n';

	rectangle r2(Point(1, 3), 4, 9);
	rectangle c(minRectangleContainingBothOthers(r, r2)), i;

	cout << "r1: width: " << r.width() << " height: " << r.height()
		<< " lowerLeftVertex: " << r.lowerLeftVertex() << " topRightVertex: " << r.topRightVertex() << '\n';
	cout << "r2: width: " << r2.width() << " height: " << r2.height()
		<< " lowerLeftVertex: " << r2.lowerLeftVertex() << " topRightVertex: " << r2.topRightVertex() << '\n';
	// прямоугольник содержащий оба заданных
	cout << "min rectangle containing r1 and r2: width: " << c.width() << " height: " << c.height()
		<< " lowerLeftVertex: " << c.lowerLeftVertex() << " topRightVertex: " << c.topRightVertex() << '\n';
	// пересечение прямоугольников
	cout << "intersection rectangle r1 and r2: width: ";

	if (intersectionRectangles(r, r2, i))
	{
		cout << i.width() << " height: " << i.height()
			<< " lowerLeftVertex: " << i.lowerLeftVertex() << " topRightVertex: " << i.topRightVertex() << '\n';
	}
	else
	{
		cout << "rectangles do not intersect\n";
	}
}