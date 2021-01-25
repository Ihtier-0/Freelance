#include "rectangle.h"

using namespace std;

rectangle rectangleContainingBothOthers(const rectangle& p1, const rectangle& p2)
{
	return rectangle(Point
	(
		p1.lowerLeftVertex().x() < p2.lowerLeftVertex().x() ? p1.lowerLeftVertex().x() : p2.lowerLeftVertex().x(),
		p1.lowerLeftVertex().y() < p2.lowerLeftVertex().y() ? p1.lowerLeftVertex().y() : p2.lowerLeftVertex().y()
	), 0, 0);
}

int main()
{
	rectangle r(Point(1, 1), 3, 5);

	cout << "begin\n";

	cout << "rectangle: width: " << r.width() << " height: " << r.height()
		<< " lowerLeftVertex: " << r.lowerLeftVertex() << " topRightVertex: " << r.topRightVertex() << '\n';

	cout << "move 1, -5\n";

	r.move(Point(1, -5));

	cout << "rectangle: width: " << r.width() << " height: " << r.height()
		<< " lowerLeftVertex: " << r.lowerLeftVertex() << " topRightVertex: " << r.topRightVertex() << '\n';

	cout << "resize 2\n";

	r.resize(2);

	cout << "rectangle: width: " << r.width() << " height: " << r.height()
		<< " lowerLeftVertex: " << r.lowerLeftVertex() << " topRightVertex: " << r.topRightVertex() << '\n';

}