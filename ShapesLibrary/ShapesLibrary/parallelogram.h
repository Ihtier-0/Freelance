#pragma once

#include "reflectable.h"
#include "rotatable.h"

#define _USE_MATH_DEFINES
#include <math.h>

// уравнение прямой
auto straightLineEquation(const point& p1, const point& p2)
{
	return [=](const double& x) -> double
	{
		return (static_cast<double>(p2.y) - p1.y) / (static_cast<double>(p2.x) - p1.x) * (x - p1.x) + p1.y;
	};
}

double distanceBetweenPoints(const point& p1, const point& p2)
{
	return sqrt((static_cast<double>(p1.x) - p2.x) * (static_cast<double>(p1.x) - p2.x) +
		(static_cast<double>(p1.y) - p2.y) * (p1.y - p2.y));
}

double scalarProduct(const point& v1, const point& v2)
{
	return static_cast<double>(v1.x) * v2.x + static_cast<double>(v1.y) * v2.y;
}

double vectorLength(const point& v)
{
	return sqrt(static_cast<double>(v.x) * v.x + static_cast<double>(v.y) * v.y);
}

double angleBetweenVectors(const point& v1, const point& v2)
{
	double ScalarProduct = scalarProduct(v1, v2);
	double v1Lenght = vectorLength(v1);
	double v2Lenght = vectorLength(v2);

	return acos(ScalarProduct / (v1Lenght * v2Lenght));
}

class parallelogram : public reflectable, public rotatable
{
/*      nw ------ n ------ ne
       /		           /
      /		              / 
     w	       c         e
    /		            /
   /		           /
  sw ------ s ------ se */
protected:
	point sw, ne;
	int sw_se; // длина отрезка (sw, se)
public:
	parallelogram(point a, point b, int base) : sw(a), ne(b), sw_se(base) {}
	point north() const { return point(ne.x - sw_se / 2, ne.y); }	//Точки для привязки
	point south() const { return point(sw.x + sw_se / 2, sw.y); }
	point east() const
	{
		point se = seast();

		if (se.x == ne.x) // проверка на квадрат
		{
			return point(se.x, se.y + (ne.y - se.y) / 2);
		}

		// уравнение прямой
		auto y = straightLineEquation(se, ne);

		if (se.x < ne.x)
		{
			return point(se.x + (ne.x - se.x) / 2, y(static_cast<double>(se.x) + (ne.x - se.x) / 2));
		}
		else
		{
			return point(se.x - (se.x - ne.x) / 2, y(static_cast<double>(se.x) - (se.x - ne.x) / 2));
		}
	} 
	point west() const
	{
		point e = east();

		return point(e.x - sw_se, e.y);
	}  
	point neast() const { return ne; }
	point seast() const { return point(sw.x + sw_se, sw.y); }
	point nwest() const { return point(ne.x - sw_se, ne.y); }
	point swest() const { return sw; }

	void draw()		//Рисование
	{
		put_line(ne, seast());
		put_line(sw, seast());
		put_line(sw, nwest());
		put_line(ne, nwest());
	}

	void move(int a, int b)	//Перемещение
	{
		sw.x += a;
		ne.x += a;

		sw.y += b;
		ne.y += b;
	}

	void resize(int d) 	//Изменение размера
	{
		sw_se += sw_se * (d - 1);

		point se = seast();

		auto y = straightLineEquation(se, ne);

		if (se.x < ne.x)
		{
			ne = point(se.x + (ne.x - se.x) * d, y(static_cast<double>(se.x) + (static_cast<double>(ne.x) - se.x) * d));
		}
		else
		{
			ne = point(se.x - (se.x - ne.x) * d, y(static_cast<double>(se.x) - (static_cast<double>(se.x) - ne.x) * d));
		}
	}

	void flip_horisontally()	// Отразить горизонтально
	{
		int parallelogramHeight = ne.y - sw.y;

		point new_ne = seast();
		new_ne.y += parallelogramHeight;

		point new_sw = nwest();
		new_sw.y -= parallelogramHeight;

		ne = new_ne;
		sw = new_sw;
	}

	void flip_vertically()	// Отразить вертикально
	{
		// y не изменяется
		point new_ne(0, ne.y);

		point se = seast();

		if (ne.x > se.x)
		{
			new_ne.x = ne.x - 2 * (ne.x - se.x);
		}
		else
		{
			new_ne.x = se.x + (se.x - ne.x);
		}

		ne = new_ne;
	}

	void rotate_left()	//Повернуть влево
	{
		double new_sw_se = distanceBetweenPoints(seast(), ne);

		point sw_save = sw;

		move(-sw.x, -sw.y);

		point nw = nwest(), se = seast();

		double angle = angleBetweenVectors(point(-1, 0), nwest());

		point new_sw(cos(angle) * nw.x - sin(angle) * nw.y,
			sin(angle) * nw.x + cos(angle) * nw.y);

		point new_ne(cos(angle) * se.x - sin(angle) * se.y,
			sin(angle) * se.x + cos(angle) * se.y);

		sw_se = new_sw_se;
		sw = new_sw;
		ne = new_ne;

		move(sw_save.x, sw_save.y);
	}

	void rotate_right()	//Повернуть вправо
	{
		double new_sw_se = distanceBetweenPoints(seast(), ne);

		point se_save = seast();

		move(-se_save.x, -se_save.y);

		point nw = nwest(), se = seast();

		double angle = angleBetweenVectors(point(1, 0), ne);

		point new_sw = se;

		point new_ne(cos(-angle) * nw.x - sin(-angle) * nw.y,
			sin(-angle) * nw.x + cos(-angle) * nw.y);

		sw_se = new_sw_se;
		sw = new_sw;
		ne = new_ne;

		move(se_save.x, se_save.y);
	}
};

void lowerLeft(shape& p, const shape& q) // поместить p слева снизу от q
{	//Это ОБЫЧНАЯ функция, не член класса! Динамическое связывание!!
	point n = q.swest();
	point s = p.neast();

	p.move(n.x - s.x, n.y - s.y);
}

void lowerRight(shape& p, const shape& q) // поместить p над q
{	//Это ОБЫЧНАЯ функция, не член класса! Динамическое связывание!!
	point n = q.seast();
	point s = p.nwest();

	p.move(n.x - s.x, n.y - s.y);
}