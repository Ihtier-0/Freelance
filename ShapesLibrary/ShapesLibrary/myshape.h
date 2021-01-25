#pragma once

#include "rectangle.h"
#include "line.h"

// Cборна€ пользовательска€ фигура - физиономи€
class myshape : public rectangle
{ // ћо€ фигура я¬Ћя≈“—я
	int w, h;			             //        пр€моугольником
	line l_eye; // левый глаз Ц мо€ фигура —ќƒ≈–∆»“ линию
	line r_eye; // правый глаз
	line mouth; // рот
public:
	myshape(point, point);
	void draw();
	void move(int, int);
	void resize(int) { }
};

myshape::myshape(point a, point b)
	: rectangle(a, b),	//»нициализаци€ базового класса
	w(neast().x - swest().x + 1), // »нициализаци€ данных
	h(neast().y - swest().y + 1), // - строго в пор€дке объ€влени€!
	l_eye(point(swest().x + 2, swest().y + h * 3 / 4), 2),
	r_eye(point(swest().x + w - 4, swest().y + h * 3 / 4), 2),
	mouth(point(swest().x + 2, swest().y + h / 4), w - 4)
{}

void myshape::draw()
{
	try
	{
		rectangle::draw(); // онтур лица (глаза и нос рисуютс€ сами!) 
		int a = (swest().x + neast().x) / 2;
		int b = (swest().y + neast().y) / 2;
		put_point(point(a, b)); // Ќос Ц существует только на рисунке!
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
