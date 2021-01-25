#include "square.h"
#include "rectangle.h"
#include "circle.h"

using namespace std;

int main()
{
	circle c(Point(0,0), 4);
	rectangle r(Point(1, 1), 3, 5);
	square s(Point(2, 2), 2);

	cout << "begin\n";

	cout << "circle: center: " << c.center() << " radius: " << c.radius() << '\n';
	cout << "rectangle: width: " << r.width() << " height: " << r.height()
		<< " lowerLeftVertex: " << r.lowerLeftVertex() << " topRightVertex: " << r.topRightVertex() << '\n';
	cout << "square: width: " << s.width()
		<< " lowerLeftVertex: " << s.lowerLeftVertex() << " topRightVertex: " << s.topRightVertex() << '\n';

	cout << "move 1, -5\n";

	c.move(Point(1, -5));
	r.move(Point(1, -5));
	s.move(Point(1, -5));

	cout << "circle: center: " << c.center() << " radius: " << c.radius() << '\n';
	cout << "rectangle: width: " << r.width() << " height: " << r.height()
		<< " lowerLeftVertex: " << r.lowerLeftVertex() << " topRightVertex: " << r.topRightVertex() << '\n';
	cout << "square: width: " << s.width()
		<< " lowerLeftVertex: " << s.lowerLeftVertex() << " topRightVertex: " << s.topRightVertex() << '\n';

	cout << "resize 2\n";

	c.resize(2);
	r.resize(2);
	s.resize(2);

	cout << "circle: center: " << c.center() << " radius: " << c.radius() << '\n';
	cout << "rectangle: width: " << r.width() << " height: " << r.height()
		<< " lowerLeftVertex: " << r.lowerLeftVertex() << " topRightVertex: " << r.topRightVertex() << '\n';
	cout << "square: width: " << s.width()
		<< " lowerLeftVertex: " << s.lowerLeftVertex() << " topRightVertex: " << s.topRightVertex() << '\n';
}