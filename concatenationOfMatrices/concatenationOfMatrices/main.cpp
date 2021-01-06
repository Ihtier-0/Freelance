/*
������� ���������� ���� ������ ����� ������� (���������, ����� ���������� ����� ������ ���� ����������). ������� ��������.
�������� �������: char** func(char ** matrix1, int m1, int n1, char **matrix2,int m2, int n2);
*/

#include <iostream>

using namespace std;

void inputCharMatrix(char** matrix, int m, int n);
char** concatenationOfMatrices(char** matrix1, int m1, int n1, char** matrix2, int m2, int n2);

int main()
{
	setlocale(LC_ALL, "Russian");

	char** matrix1;
	int m1;
	int n1;
	
	cout << "������� ���������� ����� � ������ �������: ";
	cin >> m1;
	cout << "������� ���������� �������� � ������ �������: ";
	cin >> n1;

	matrix1 = new char* [m1];
	for (int i = 0; i < m1; ++i)
	{
		matrix1[i] = new char[n1];
	}
	inputCharMatrix(matrix1, m1, n1);

	char** matrix2;
	int m2;
	int n2;

	cout << "������� ���������� ����� �� ������ �������: ";
	cin >> m2;
	cout << "������� ���������� �������� �� ������ �������: ";
	cin >> n2;

	matrix2 = new char* [m2];
	for (int i = 0; i < m2; ++i)
	{
		matrix2[i] = new char[n2];
	}
	inputCharMatrix(matrix2, m1, n1);

	char** result = concatenationOfMatrices(matrix1, m1, n1, matrix2, m2, n2);

	if (result)
	{
		for (int i = 0; i < m1; i++)
		{
			cout << result[i] << '\n';
		}
	}
	else
	{
		cout << "��������� ��������� �������!\n";
	}
}

void inputCharMatrix(char** matrix, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		cout << "������� " << i << "-� ������ ������� ������ ������ ��� ������ " << n << ": ";
		cin >> matrix[i];
	}
}

char** concatenationOfMatrices(char** matrix1, int m1, int n1, char** matrix2, int m2, int n2)
{
	char** result = nullptr;

	// ���� ���������� ����� ����������
	if (m1 == m2)
	{
		result = new char*[m1];

		for (int i = 0; i < m1; i++)
		{
			// �������������� ������ ��� '\0'
			result[i] = new char[n1 + n2 + 1];
		}

		for (int i = 0; i < m1; i++)
		{
			for (int j = 0; j < n1 + n2; j++)
			{
				if (j < n1)
				{
					result[i][j] = matrix1[i][j];
				}
				else
				{
					result[i][j] = matrix2[i][j - n1];
				}
			}
			result[i][n1 + n2] = '\0';
		}
	}

	return result;
}
