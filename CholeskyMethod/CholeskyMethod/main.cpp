#include <iostream>

#include "stripMatrix.h"
#include "utils.h"
#include "CholeskySolver.h"

using namespace std;

int main()
{
	stripMatrix a;
	std::vector<double> x, f, xSolve;

	int countOfIteration = 5;

	double sumRelativeSolutionError = 0;

	for (int size : { 40, 400 })
	{
		for (int length : {size / 10, static_cast<int>(sqrt(size))})
		{
			for (int i = 0; i < countOfIteration; ++i)
			{
				generateStripMatrixSystem(a, size, length, x, f, 10);
				CholeskySolver s(a, f);

				if (!s.Solve(xSolve))
				{
					--i;
					continue;
				}

				sumRelativeSolutionError += relativeSolutionError(x, xSolve);
			}
			std::cout << "\nsize: " << size
				<< "\nlength: " << length
				<< "\nlength\\size: " << static_cast<double>(length) / size
				<< "\nRelativeSolutionError: " << sumRelativeSolutionError / countOfIteration << "\n\n";
		}
	}

	cout << "well conditioned: \n";

	int length;

	for (int size : { 10, 100 })
	{
		length = size / 10;
		for (int i = 0; i < 2; ++i)
		{
			generateStripMatrixSystem(a, size, length, x, f, 10);
			CholeskySolver s(a, f);

			if (!s.Solve(xSolve))
			{
				--i;
				continue;
			}

			std::cout << i
				<< "\nsize: " << size
				<< "\nlength: " << length
				<< "\nRelativeSolutionError: " << relativeSolutionError(x, xSolve) << "\n\n";
		}
	}

	cout << "bad conditioned: \n";

	for (int k : {2, 4, 6})
	{
		for (int size : { 10 })
		{
			length = size / 10;
			for (int i = 0; i < 2; ++i)
			{
				generateIllConditionStripMatrixSystem(a, size, length, x, f, 10, k);

				CholeskySolver s(a, f);

				if (!s.Solve(xSolve))
				{
					--i;
					continue;
				}

				std::cout << i
					<< "\nsize: " << size
					<< "\nlength: " << length
					<< "\norderIllConditioned: " << k
					<< "\nRelativeSolutionError: " << relativeSolutionError(x, xSolve) << "\n\n";
			}
		}
	}
}

