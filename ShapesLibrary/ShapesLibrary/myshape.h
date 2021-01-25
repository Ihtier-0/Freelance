#pragma once

#include "rectangle.h"
#include "line.h"

// C������ ���������������� ������ - ����������
class myshape : public rectangle
{ // ��� ������ ��������
	int w, h;			             //        ���������������
	line l_eye; // ����� ���� � ��� ������ �������� �����
	line r_eye; // ������ ����
	line mouth; // ���
public:
	myshape(point, point);
	void draw();
	void move(int, int);
	void resize(int) { }
};

myshape::myshape(point a, point b)
	: rectangle(a, b),	//������������� �������� ������
	w(neast().x - swest().x + 1), // ������������� ������
	h(neast().y - swest().y + 1), // - ������ � ������� ����������!
	l_eye(point(swest().x + 2, swest().y + h * 3 / 4), 2),
	r_eye(point(swest().x + w - 4, swest().y + h * 3 / 4), 2),
	mouth(point(swest().x + 2, swest().y + h / 4), w - 4)
{}

void myshape::draw()
{
	try
	{
		rectangle::draw(); //������ ���� (����� � ��� �������� ����!) 
		int a = (swest().x + neast().x) / 2;
		int b = (swest().y + neast().y) / 2;
		put_point(point(a, b)); // ��� � ���������� ������ �� �������!
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << " myshape::draw\n";
		std::cin.get();
	}

}

void myshape::move(int a, int b)
{
	rectangle::move(a, b);
	l_eye.move(a, b);  r_eye.move(a, b);
	mouth.move(a, b);
}
