#pragma once

#include "shape.h"

class rotatable : virtual public shape  //������, ��������� � �������� 
{
public:
	virtual void rotate_left() = 0;	//��������� �����
	virtual void rotate_right() = 0;	//��������� ������
};


