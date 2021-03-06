#pragma once

#include <list>
#include "screen.h"
#include <iostream>

struct shape { // ����������� ������� ����� "������"
	static std::list<shape*> shapes;// ������ ����� (���� �� ��� ������!)
	shape() { shapes.push_back(this); } //������ �������������� � ������
	virtual point north() const = 0;	//����� ��� ��������
	virtual point south() const = 0;
	virtual point east() const = 0;
	virtual point west() const = 0;
	virtual point neast() const = 0;
	virtual point seast() const = 0;
	virtual point nwest() const = 0;
	virtual point swest() const = 0;
	virtual void draw() = 0;		//���������
	virtual void move(int, int) = 0;	//�����������
	virtual void resize(int) = 0; 	//��������� �������
};

std::list<shape*> shape::shapes;   // ���������� ������ �����

void shape_refresh() // ����������� ���� ����� �� ������
{
	screen_clear();
	for (auto p : shape::shapes)
	{
		p->draw(); //������������ ����������!!!
	}
	screen_refresh();
}
