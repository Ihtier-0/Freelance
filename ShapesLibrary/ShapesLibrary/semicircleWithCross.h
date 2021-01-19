#pragma once

#include "shape.h"
#include "rectangle.h"
#include "reflectable.h"

#define _USE_MATH_DEFINES
#include <math.h>

class semicircleWithCross : public reflectable, public rotatable
{
	/*	   
	nw	  ___n___	 ne
	    _/       \_       
	w _/	 c	   \_ e         
	 /		         \ 
	sw ----- s ----- se

	вектор n сонаправлен с (s, n)
	*/
protected:
	point center;
	int radius;
	point n; // вектор сонаправленный с вектором от центра окружности до центра отображаемой дуги
	// (0, 1), (0, -1), (1, 0), (-1, 0)
public:
	semicircleWithCross(point c, int r, point N = point(0, 1)) : center(c), radius(r), n(N)
	{
		/*std::cout << "nw " << nwest().x << ' ' << nwest().y << '\n'
			<< "n " << north().x << ' ' << north().y << '\n'
			<< "ne " << neast().x << ' ' << neast().y << '\n'
			<< "e " << east().x << ' ' << east().y << '\n'
			<< "se " << seast().x << ' ' << seast().y << '\n'
			<< "s " << south().x << ' ' << south().y << '\n'
			<< "sw " << swest().x << ' ' << swest().y << '\n'
			<< "w " << west().x << ' ' << west().y << '\n';*/
	}
	point north() const 	//Точки для привязки
	{
		if (n.x == 0
			&& n.y == 1)
		{
			return point(center.x, center.y + radius);
		}
		else if (n.x == 0
			&& n.y == -1)
		{
			return center;
		}
		else if (n.x == 1
			&& n.y == 0)
		{
			return point(center.x + radius / 2, center.y + radius);
		}
		else if (n.x == -1
			&& n.y == 0)
		{
			return point(center.x - radius / 2, center.y + radius);
		}
	}
	point south() const
	{
		if (n.x == 0
			&& n.y == 1)
		{
			return center;
		}
		else if (n.x == 0
			&& n.y == -1)
		{
			return point(center.x, center.y - radius);
		}
		else if (n.x == 1
			&& n.y == 0)
		{
			return point(center.x + radius / 2, center.y - radius);
		}
		else if (n.x == -1
			&& n.y == 0)
		{
			return point(center.x - radius / 2, center.y - radius);
		}
	}
	point east() const
	{
		if (n.x == 0
			&& n.y == 1)
		{
			return point(center.x + radius, center.y + radius / 2);
		}
		else if (n.x == 0
			&& n.y == -1)
		{
			return point(center.x + radius, center.y - radius / 2);
		}
		else if (n.x == 1
			&& n.y == 0)
		{
			return point(center.x + radius, center.y);
		}
		else if (n.x == -1
			&& n.y == 0)
		{
			return center;
		}
	}
	point west() const
	{
		if (n.x == 0
			&& n.y == 1)
		{
			return point(center.x - radius, center.y + radius / 2);
		}
		else if (n.x == 0
			&& n.y == -1)
		{
			return point(center.x - radius, center.y - radius / 2);
		}
		else if (n.x == 1
			&& n.y == 0)
		{
			return center;
		}
		else if (n.x == -1
			&& n.y == 0)
		{
			return point(center.x - radius, center.y);
		}
	}
	point neast() const
	{
		if (n.x == 0
			&& n.y == 1)
		{
			return point(center.x + radius, center.y + radius);
		}
		else if (n.x == 0
			&& n.y == -1)
		{
			return point(center.x + radius, center.y);
		}
		else if (n.x == 1
			&& n.y == 0)
		{
			return point(center.x + radius, center.y + radius);
		}
		else if (n.x == -1
			&& n.y == 0)
		{
			return point(center.x, center.y + radius);
		}
	}
	point seast() const
	{
		if (n.x == 0
			&& n.y == 1)
		{
			return point(center.x + radius, center.y);
		}
		else if (n.x == 0
			&& n.y == -1)
		{
			return point(center.x + radius, center.y - radius);
		}
		else if (n.x == 1
			&& n.y == 0)
		{
			return point(center.x + radius, center.y - radius);
		}
		else if (n.x == -1
			&& n.y == 0)
		{
			return point(center.x, center.y - radius);
		}
	}
	point nwest() const
	{
		if (n.x == 0
			&& n.y == 1)
		{
			return point(center.x - radius, center.y + radius);
		}
		else if (n.x == 0
			&& n.y == -1)
		{
			return point(center.x - radius, center.y);
		}
		else if (n.x == 1
			&& n.y == 0)
		{
			return point(center.x, center.y + radius);
		}
		else if (n.x == -1
			&& n.y == 0)
		{
			return point(center.x - radius, center.y + radius);
		}
	}
	point swest() const
	{
		if (n.x == 0
			&& n.y == 1)
		{
			return point(center.x - radius, center.y);
		}
		else if (n.x == 0
			&& n.y == -1)
		{
			return point(center.x - radius, center.y - radius);
		}
		else if (n.x == 1
			&& n.y == 0)
		{
			return point(center.x, center.y - radius);
		}
		else if (n.x == -1
			&& n.y == 0)
		{
			return point(center.x - radius, center.y - radius);
		}
	}

	void draw()		//Рисование
	{
		std::cout << "nw " << nwest().x << ' ' << nwest().y << '\n'
			<< "n " << north().x << ' ' << north().y << '\n'
			<< "ne " << neast().x << ' ' << neast().y << '\n'
			<< "e " << east().x << ' ' << east().y << '\n'
			<< "se " << seast().x << ' ' << seast().y << '\n'
			<< "s " << south().x << ' ' << south().y << '\n'
			<< "sw " << swest().x << ' ' << swest().y << '\n'
			<< "w " << west().x << ' ' << west().y << '\n'
			<< "normal " << n.x << ' ' << n.y << '\n'
			<< "center " << center.x << ' ' << center.y << '\n';

		put_line(west(), east());
		put_line(south(), north());

		put_point(west());
		put_point(east());
		put_point(south());
		put_point(north());

		int x0 = center.x, y0 = seast().y;

		if (n.x == 0 && n.y == 1)
		{
			y0 = seast().y;
		}
		else if (n.x == 0 && n.y == -1)
		{
			y0 = nwest().y;
		}
		else if (n.x == 1 && n.y == 0)
		{
			y0 = nwest().y;
		}
		else if (n.x == -1 && n.y == 0)
		{
			y0 = seast().y;
		}

		int x = 0, y = radius, delta = 2 - 2 * radius, error = 0;
		while (y >= 0) //Цикл рисования
		{
			if (n.x == 0 && n.y == 1)
			{
				put_point(x0 + x, y0 + y * 0.7);
				put_point(x0 - x, y0 + y * 0.7);
			}
			else
			{
				put_point(x0 + x, y0 - y * 0.7);
				put_point(x0 - x, y0 - y * 0.7);
			}

			error = 2 * (delta + y) - 1;

			if (delta < 0 && error <= 0)
			{
				++x;
				delta += 2 * x + 1;
				continue;
			}

			error = 2 * (delta - x) - 1;

			if (delta > 0 && error > 0)
			{
				--y;
				delta += 1 - 2 * y;
				continue;
			}

			++x; delta += 2 * (x - y);  --y;
		}
	}

	void move(int a, int b)	//Перемещение
	{
		center.x += a;
		center.y += b;
	}

	void resize(int d) 	//Изменение размера
	{
		radius += radius * (d - 1);
	}

	void flip_horisontally()	// Отразить горизонтально
	{
		n.x *= -1;
	}

	void flip_vertically()	// Отразить вертикально
	{
		n.y *= -1;
	}

	void rotate_left()	//Повернуть влево
	{
		n = point(cos(M_PI_2) * n.x - sin(M_PI_2) * n.y,
			sin(M_PI_2) * n.x + cos(M_PI_2) * n.y);

		std::cout << "n " << n.x << ' ' << n.y << '\n';
	}

	void rotate_right()	//Повернуть вправо
	{
		n = point(cos(-M_PI_2) * n.x - sin(-M_PI_2) * n.y,
			sin(-M_PI_2) * n.x + cos(-M_PI_2) * n.y);
	}
};