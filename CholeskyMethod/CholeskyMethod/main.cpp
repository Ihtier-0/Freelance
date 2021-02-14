#include <iostream>

#include "stripMatrix.h"
#include "utils.h"
#include "CholeskySolver.h"

using namespace std;

int main()
{
	stripMatrix a(5, 2, {
		{0,0,1,1,1},
		{0,1,1,1,1},
		{1,1,1,1,1},
		{1,1,1,1,0},
		{1,1,1,0,0},
		});

	cout << "a:\n" << a << "\n\n";

	std::vector<double> f = { 1,1,1,1,1,1 }, x;

	CholeskySolver s(a, f);

	if (!s.Solve(x))
	{
		cout << "false\n";
	}

	cout << x << '\n';
}