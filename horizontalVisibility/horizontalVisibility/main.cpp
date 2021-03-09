/*
* В массиве H[n] хранятся значения высот некоторого профиля местности с постоянным шагом по горизонтали.
Найти номера точек, невидимых из точки Н[0].
*/

#include <iostream>

using namespace std;

constexpr double radiusEarth = 6371;

void fillArrayRandomElements(double*& array, const unsigned int& size, const int& maxElement)
{
	for (int i = 0; i < size; ++i)
	{
		array[i] = rand() % maxElement;
	}
}

void outArray(const double const * const & array, const unsigned int& size)
{
	for (int i = 0; i < size; ++i)
	{
		cout << array[i] << ' ';
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Введите количество шагов от точки H[0]: ";
	int steps;
	cin >> steps;
	cout << "Введите максимальную высоту местности(км): ";
	int maxHeight;
	cin >> maxHeight;
	cout << "Введите горизонтальный шаг(км): ";
	double horizontalStep;
	cin >> horizontalStep;

	double* H = new double[steps + 1];
	fillArrayRandomElements(H, steps + 1, maxHeight);
	cout << "Полученная карта местности:\n";
	outArray(H, steps + 1);
	cout << '\n';

	double VisibleHorizon = sqrt((radiusEarth + H[0]) * (radiusEarth + H[0]) - radiusEarth * radiusEarth);
	cout << "Видимый горизонт:" << VisibleHorizon << '\n';

	bool check;

	cout << "Точки видимые из H[0]:\n";
	for (int i = 1; i <= steps; ++i)
	{
		if (i * horizontalStep > VisibleHorizon)
		{
			break;
		}

		check = true;

		for (int j = 1; j < i; ++j)
		{
			auto y = [&](const double x) -> double
			{
				return ((H[i] - H[0]) / (i - 0)) * (x - 0) + H[0];
			};

			if (H[j] >= y(j))
			{
				check = false;
				break;
			}
		}

		if (check)
		{
			cout << i << ' ';
		}
	}
}