#pragma once

#include "Point.h"

class geometricFigure
{
public:
	virtual void move(const Point& p) = 0;
	virtual void resize(const double& r) = 0;
};

