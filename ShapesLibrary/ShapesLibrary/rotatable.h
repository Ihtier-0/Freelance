#pragma once

#include "shape.h"

class rotatable : virtual public shape  //Фигуры, пригодные к повороту 
{
public:
	virtual void rotate_left() = 0;	//Повернуть влево
	virtual void rotate_right() = 0;	//Повернуть вправо
};


