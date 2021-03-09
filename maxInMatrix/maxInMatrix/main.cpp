/*
Дано: матрица А(n x n).
Найти максимальный элемент, и все элементы, находящиеся в этой строке, возвести в квадрат.
Новую матрицу вывести на экран.
*/

#include <iostream>
using namespace std;

void fillArrayRandomElements(double *& array, const unsigned int& size, const int& maxElement)
{
	for (int i = 0; i < size; ++i)
	{
		array[i] = rand() % maxElement;
	}
}

void randomMatrix(double **&matrix, const unsigned int &size, const int& maxElement)
{
	matrix = new double* [size];

	for (int i = 0; i < size; ++i)
	{
		matrix[i] = new double[size];
		fillArrayRandomElements(matrix[i], size, maxElement);
	}
}

void outMatrix(const double const* const * const& matrix, const unsigned int& size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cout << matrix[i][j] << ' ';
		}
		cout << '\n';
	}
}

int findRowWithMaxElement(const double const* const* const& matrix, const unsigned int& size)
{
	int RowMaxElement = 0;
	int ColMaxElement = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] > matrix[RowMaxElement][ColMaxElement])
			{
				RowMaxElement = i;
				ColMaxElement = j;
			}
		}
	}

	return RowMaxElement;
}

void squareAllElementsArray(double*& array, const unsigned int& size)
{
	for (int i = 0; i < size; ++i)
	{
		array[i] *= array[i];
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int size;
	int maxElement;

	cout << "Введите размерность матрицы: ";
	cin >> size;
	cout << "Введите максимальный элемент в матрице: ";
	cin >> maxElement;

	double** matrix;

	randomMatrix(matrix, size, maxElement);

	cout << "Сгенерированная матрица:\n";
	outMatrix(matrix, size);

	int RowWithMaxElement = findRowWithMaxElement(matrix, size);

	cout << "Строка с максимальным элементом: " << RowWithMaxElement << '\n';

	squareAllElementsArray(matrix[RowWithMaxElement], size);

	cout << "Матрица после возведения в квадрат всех элементов строки с максимальным элементом:\n";
	outMatrix(matrix, size);
}