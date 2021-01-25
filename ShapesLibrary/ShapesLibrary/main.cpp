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

	semicircleWithCross s1(point(40, 30), 5), s2(point(70, 30), 5), s3(point(100, 30), 5);

	shape_refresh();
	std::cout << "=== Generated... ===\n";
	std::cin.get(); //Смотреть исходный набор

	//== 2.Подготовка к сборке ==
	hat.rotate_right();
	brim.resize(2);
	face.resize(2);

	s1.flip_vertically();
	s2.rotate_left();
	s3.rotate_right();

	shape_refresh();

	std::cout << "=== Prepared... ===\n";
	std::cin.get(); //Смотреть результат поворотов/отражений

	//== 3.Сборка изображения ==
	up(brim, face);
	up(hat, brim);
	down(s1, face);
	left(s3, brim);
	right(s2, brim);

	shape_refresh();
	std::cout << "=== Ready! ===\n";
	std::cin.get(); //Смотреть результат
	screen_destroy();
	return 0;
}
