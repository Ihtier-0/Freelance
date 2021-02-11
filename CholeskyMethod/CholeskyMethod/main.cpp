#include <iostream>

#include "stripMatrix.h"

using namespace std;

int main()
{
	stripMatrix m(5, 2, {
		{0,0,2,3,6},
		{0,1,2,3,6},
		{5,1,2,3,6},
		{5,1,2,3,0},
		{5,1,2,0,0}
		});

	cout << m << '\n';
}