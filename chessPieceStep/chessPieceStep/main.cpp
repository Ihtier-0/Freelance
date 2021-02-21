#include <cmath> // abs
#include <iostream>

class Point //Для упрощения работы с клетками шахматной доски создадим отдельный класс. Точка (0;0) соответствует а1
{
private:
	int m_x, m_y;// координаты на доске, числа от 0 до 7
public:
	int x() { return m_x; }
	int y() { return m_y; }
	Point() :m_x(0), m_y(0) {}//констрктор по умолчанию. Задает точку (0;0)
	friend std::ostream& operator<<(std::ostream& out, const Point& point);//оператор вывода
	friend std::istream& operator>>(std::istream& in, Point& point);//оператор ввода
};

// конь - сумма расстояний по осям между клетками всегда равно 3
// и сдвиг не по горизонтали / вертикали
bool knight(Point cell1, Point cell2)
{
	int dx = std::abs(cell1.x() - cell2.x());
	int dy = std::abs(cell1.y() - cell2.y());

	return dx + dy == 3 && dy != 3 && dx != 3;
}

// слон - модуль смещения по одной оси равен модулю смещения по другой.
bool bishop(Point cell1, Point cell2)
{
	return std::abs(cell1.x() - cell2.x()) == std::abs(cell1.y() - cell2.y());
}

// ладья - смещение по любой из осей равно 0.
bool rook(Point cell1, Point cell2)
{
	return !((cell1.x() - cell2.x()) && (cell1.y() - cell2.y()));
}

// ферзь = ладья + слон
bool queen(Point cell1, Point cell2)
{
	return bishop(cell1, cell2) || rook(cell1, cell2);
}

int main()
{
	setlocale(LC_ALL, "Russian");

	Point p1, p2;
	std::cout << "Введите кооринату первой клетки шахматной доски(например а1): ";

	while (true)
	{
		try
		{
			std::cin >> p1;
			break;
		}
		catch(...)
		{
			std::cin.clear();
			while (std::cin.get() != '\n') {}
			std::cout << "Неверно введена точка, попробуйте ещё раз\n";
		}
	}

	std::cout << "Введите координату второй клетки шахматной доски(например а1): ";

	while (true)
	{
		try
		{
			std::cin >> p2;
			break;
		}
		catch(...)
		{
			std::cin.clear();
			while (std::cin.get() != '\n') {}
			std::cout << "Неверно введена точка, попробуйте ещё раз\n";
		}
	}

	bool canMakeStep = false;

	std::cout << "Фигуры который могут сделать ход:\n";
	if (knight(p1, p2))
	{
		std::cout << "конь\n";
		canMakeStep = true;
	}
	if (bishop(p1, p2))
	{
		std::cout << "слон\n";
		canMakeStep = true;
	}
	if (rook(p1, p2))
	{
		std::cout << "ладья\n";
		canMakeStep = true;
	}
	if (queen(p1, p2))
	{
		std::cout << "ферзь\n";
		canMakeStep = true;
	}

	if (!canMakeStep)
	{
		std::cout << "ни одна фигура не может сделать шаг\n";
	}
}

std::ostream& operator<<(std::ostream& out, const Point& point)//выводим координаты точки, при этом для точки 0;0 выведится а1
{
	out << char(point.m_x + 'a') << point.m_y + 1;
	return out;
}

std::istream& operator>>(std::istream& in, Point& point)//вводим координаты точки, при этом координатам а1 соответствует точка 0;0
{
	char c;
	int y;
	in >> c >> y;

	if (c < 'a' || c > 'h' || y < 1 || y > 8)
	{
		throw std::exception("wrong point");
	}

	point.m_x = c - 'a';
	point.m_y = y - 1;
	return in;
}