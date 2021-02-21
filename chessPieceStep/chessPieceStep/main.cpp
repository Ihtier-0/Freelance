#include <cmath> // abs
#include <iostream>

class Point //��� ��������� ������ � �������� ��������� ����� �������� ��������� �����. ����� (0;0) ������������� �1
{
private:
	int m_x, m_y;// ���������� �� �����, ����� �� 0 �� 7
public:
	int x() { return m_x; }
	int y() { return m_y; }
	Point() :m_x(0), m_y(0) {}//���������� �� ���������. ������ ����� (0;0)
	friend std::ostream& operator<<(std::ostream& out, const Point& point);//�������� ������
	friend std::istream& operator>>(std::istream& in, Point& point);//�������� �����
};

// ���� - ����� ���������� �� ���� ����� �������� ������ ����� 3
// � ����� �� �� ����������� / ���������
bool knight(Point cell1, Point cell2)
{
	int dx = std::abs(cell1.x() - cell2.x());
	int dy = std::abs(cell1.y() - cell2.y());

	return dx + dy == 3 && dy != 3 && dx != 3;
}

// ���� - ������ �������� �� ����� ��� ����� ������ �������� �� ������.
bool bishop(Point cell1, Point cell2)
{
	return std::abs(cell1.x() - cell2.x()) == std::abs(cell1.y() - cell2.y());
}

// ����� - �������� �� ����� �� ���� ����� 0.
bool rook(Point cell1, Point cell2)
{
	return !((cell1.x() - cell2.x()) && (cell1.y() - cell2.y()));
}

// ����� = ����� + ����
bool queen(Point cell1, Point cell2)
{
	return bishop(cell1, cell2) || rook(cell1, cell2);
}

int main()
{
	setlocale(LC_ALL, "Russian");

	Point p1, p2;
	std::cout << "������� ��������� ������ ������ ��������� �����(�������� �1): ";

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
			std::cout << "������� ������� �����, ���������� ��� ���\n";
		}
	}

	std::cout << "������� ���������� ������ ������ ��������� �����(�������� �1): ";

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
			std::cout << "������� ������� �����, ���������� ��� ���\n";
		}
	}

	bool canMakeStep = false;

	std::cout << "������ ������� ����� ������� ���:\n";
	if (knight(p1, p2))
	{
		std::cout << "����\n";
		canMakeStep = true;
	}
	if (bishop(p1, p2))
	{
		std::cout << "����\n";
		canMakeStep = true;
	}
	if (rook(p1, p2))
	{
		std::cout << "�����\n";
		canMakeStep = true;
	}
	if (queen(p1, p2))
	{
		std::cout << "�����\n";
		canMakeStep = true;
	}

	if (!canMakeStep)
	{
		std::cout << "�� ���� ������ �� ����� ������� ���\n";
	}
}

std::ostream& operator<<(std::ostream& out, const Point& point)//������� ���������� �����, ��� ���� ��� ����� 0;0 ��������� �1
{
	out << char(point.m_x + 'a') << point.m_y + 1;
	return out;
}

std::istream& operator>>(std::istream& in, Point& point)//������ ���������� �����, ��� ���� ����������� �1 ������������� ����� 0;0
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