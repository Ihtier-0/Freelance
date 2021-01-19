#include "rectangle.h"
#include "line.h"
#include "myshape.h"
#include "h_circle.h"
#include <iostream>

#include "semicircleWithCross.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	screen_init();

	std::cin.get();

	//== 1.Объявление набора фигур ==
	rectangle hat(point(0, 0), point(14, 5));
	line brim(point(0, 15), 17);
	myshape face(point(15, 10), point(27, 18));

	semicircleWithCross s(point(100, 30), 15);
	rectangle r2(point(85, 30), point(115, 45));

	h_circle k(point(30, 20), point(50, 40));
	rectangle r(point(30, 20), point(50, 40));
	// h_circle beard(point(40, 10), point(50, 20));

	shape_refresh();
	std::cout << "=== Generated... ===\n";
	std::cin.get(); //Смотреть исходный набор

	//== 2.Подготовка к сборке ==
	hat.rotate_right();
	brim.resize(2);
	face.resize(2);
	// beard.flip_vertically();

	s.flip_horisontally();
	//r.rotate_left();

	shape_refresh();

	std::cout << "=== Prepared... ===\n";
	std::cin.get(); //Смотреть результат поворотов/отражений

	//== 3.Сборка изображения ==
	//	face.move(0, -10); // Лицо - в исходное положение
	up(brim, face);
	up(hat, brim);
	// down(beard, face);



	// p.rotate_left();

	shape_refresh();
	std::cout << "=== Ready! ===\n";
	std::cin.get(); //Смотреть результат
	screen_destroy();
	return 0;
}
