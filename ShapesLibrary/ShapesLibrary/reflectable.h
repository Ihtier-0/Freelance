#pragma once

#include "shape.h"

class reflectable : virtual public shape  // ������, ���������
{				  // � ����������� ���������
public:
	virtual void flip_horisontally() = 0;	// �������� �������������
	virtual void flip_vertically() = 0;	// �������� �����������
};
