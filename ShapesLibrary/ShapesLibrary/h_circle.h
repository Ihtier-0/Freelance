#pragma once

#include "shape.h"
#include "rectangle.h"
#include "reflectable.h"

class h_circle : public rectangle, public reflectable
{
	bool reflected;
public:
	h_circle(point a, point b, bool r = true) : rectangle(a, b), reflected(r) {}
	void draw();
	void flip_horisontally() {}; // Отразить горизонтально (пустая функция)
	void flip_vertically() { reflected = !reflected; };	// Отразить вертикально
};

void h_circle::draw() //Алгоритм Брезенхэма для окружностей
{   //(выдаются два сектора, указываемые значением reflected)
	int x0 = south().x, y0 = reflected ? sw.y : ne.y;
	int radius = (ne.x - sw.x) / 2;

	int x = 0, y = radius, delta = 2 - 2 * radius, error = 0;
	while (y >= 0) //Цикл рисования
	{
		if (reflected)
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

// Пример добавки: дополнительная функция присоединения…
void down(shape& p, const shape& q)
{
	point n = q.south();
	point s = p.north();
	p.move(n.x - s.x, n.y - s.y - 1);
}
