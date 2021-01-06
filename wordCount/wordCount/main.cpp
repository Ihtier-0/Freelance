/*
� ���������� �������� ������.
�������� �������, ������� ���������� ���������� ���� � ������.
����� � ������������������ ��������, ����������� ������������ ����������� ��������.
�������� int function_name (char *s). ����������� ����� ����������.
*/

#include <iostream>
#include <string>

using namespace std;

int wordCount(char* s);

int main()
{
	setlocale(LC_ALL, "Russian");

	char* line = new char[256];
	cout << "������� ������ ��������� �� ���� ���������� ���������:\n";
	fgets(line, 256, stdin);
	cout << "���������� ���� � ������: " << wordCount(line) << '\n';
}

int wordCount(char* s)
{
	int size = strlen(s), result = 0;

	for (int i = 0; i < size; i++)
	{
		if (s[i] != ' ')
		{
			result++;

			while (i < size && s[i] != ' ')
			{
				++i;
			}

			while (i < size && s[i] == ' ')
			{
				++i;
			}
		}
	}

	return result;
}
