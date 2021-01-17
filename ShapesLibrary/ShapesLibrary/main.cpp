#include "rectangle.h"
#include "line.h"
#include "myshape.h"
#include "h_circle.h"
#include <iostream>

#include "parallelogram.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	screen_init();

	std::cin.get();

	//== 1.Объявление набора фигур ==
	rectangle hat(point(0, 0), point(14, 5));
	line brim(point(0, 15), 17);
	myshape face(point(15, 10), point(27, 18));
	// h_circle beard(point(40, 10), point(50, 20));

	parallelogram p(point(70, 20), point(100, 30), 20),
		p2(point(20, 30), point(30, 40), 5), p3(point(30, 30), point(40, 40), 5);

	shape_refresh();
	std::cout << "=== Generated... ===\n";
	std::cin.get(); //Смотреть исходный набор

	//== 2.Подготовка к сборке ==
	hat.rotate_right();
	brim.resize(2);
	face.resize(2);
	// beard.flip_vertically();

	p.flip_horisontally();
	p2.rotate_left();
	p3.rotate_right();

	shape_refresh();

	std::cout << "=== Prepared... ===\n";
	std::cin.get(); //Смотреть результат поворотов/отражений

	//== 3.Сборка изображения ==
	//	face.move(0, -10); // Лицо - в исходное положение
	up(brim, face);
	up(hat, brim);
	// down(beard, face);

	up(p, hat);
	lowerLeft(p2, face);
	lowerRight(p3, face);

	// p.rotate_left();

	shape_refresh();
	std::cout << "=== Ready! ===\n";
	std::cin.get(); //Смотреть результат
	screen_destroy();
	return 0;
}
