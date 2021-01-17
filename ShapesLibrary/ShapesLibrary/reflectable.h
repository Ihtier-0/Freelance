#pragma once

#include "shape.h"

class reflectable : virtual public shape  // Фигуры, пригодные
{				  // к зеркальному отражению
public:
	virtual void flip_horisontally() = 0;	// Отразить горизонтально
	virtual void flip_vertically() = 0;	// Отразить вертикально
};
