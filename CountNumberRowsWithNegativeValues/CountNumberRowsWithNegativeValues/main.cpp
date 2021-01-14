#include <iostream>

using namespace std;

int main()
{
	int n;
	cout << "input number of rows: ";
	cin >> n;

	while (n <= 0)
	{
		cout << "input number of rows <= 0! Try again: ";
		cin >> n;
	}

	int m;
	cout << "input number of columns: ";
	cin >> m;

	while (m <= 0)
	{
		cout << "input number of columns <= 0! Try again: ";
		cin >> m;
	}

	double** Array = new double* [n];

	for (int i = 0; i < n; ++i)
	{
		Array[i] = new double[m];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			Array[i][j] = (double)(rand()) / RAND_MAX * (2. - (-1)) + (-1);
		}
	}

	cout << "rand array: \n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << Array[i][j] << ' ';
		}
		cout << '\n';
	}

	int CountNumberRowsWithNegativeValues = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (Array[i][j] < 0)
			{
				CountNumberRowsWithNegativeValues++;
				break;
			}
		}
	}

	cout << "Count Number Of Rows With Negative Values: " << CountNumberRowsWithNegativeValues << '\n';

	for (int i = 0; i < n; i++)
	{
		delete[] Array[i];
	}

	delete[] Array;
}