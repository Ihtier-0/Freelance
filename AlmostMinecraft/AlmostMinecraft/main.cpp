/*
��� ��-���� ��������� ������� ����� ������� ����������.
��������� �� ������, �� ��� �������� ���������� ������ �� ���������������� ��������.
� ��� ���� ��������� ���������� ��������, �������� 5�5 ��������.
� ������ ������� ������������� ���� (�������) ���������,
������������ ������ �������� � ��� 10 ������.
������� ������ ������� ������ ����� ������� ������������� ������� ���������.
�������� ������ � ��������� ��������� ������ ������� � ����������� ����� �������������� �������
(��� �������������� ����) ������ ���������� ����.
��� ��� ��� ��� ������ ���� ����������� � ���� ���������� �������.
��� �������������� ���� ����� ���� � ��� ��������� ������, ������� ���� ���������� � ���� ������ � �����.
0 � ��� ���������� �������� �� ������ ������ � ������ �����, 1 � ������� ����.

������� ����� �� 0 �� 9 ������������ � ����� ������� � ����������� �����.
*/

#include <iostream>

using namespace std;

const int Size = 5;
const int Height = 10;

void inputChunk(bool(&Chunk)[Size][Size][Height], int size, int height);
void horizontalCut(bool(&Chunk)[Size][Size][Height], int size, int height, int horizontLevel);
void initChunk(bool(&Chunk)[Size][Size][Height], int size, int height);

void menu()
{
	cout << "1) ��������� ����\n"
		<< "2) �������� �������������� ����\n"
		<< "3) �����\n";
}

int main()
{
	setlocale(LC_ALL, "Russian");

	bool Chunk[Size][Size][Height];
	// �� ������ ���� ���-�� ������� �������� ���� �� ����������
	initChunk(Chunk, Size, Height);
	
	int command = 4;

	do
	{
		menu();
		cout << "> ";
		cin >> command;

		switch (command)
		{
		case 1:
		{
			inputChunk(Chunk, Size, Height);
			break;
		}
		case 2:
		{
			int horizontLevel;
			cout << "������� �� ����� ������ ���� ������� ����: ";
			cin >> horizontLevel;

			if (horizontLevel >= Height || horizontLevel < 0)
			{
				cout << "������ ����������� ������!\n";
			}

			horizontalCut(Chunk, Size, Height, horizontLevel);
			break;
		}
		}
	} while (command != 3);
}

void inputChunk(bool(&Chunk)[Size][Size][Height], int size, int height)
{
	bool tmp;

	cout << "0 - �����, �� 0 - �� �����\n";

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << "������ �������� ������� � ������������ (" << i << ", " << j << ")\n";
			for (int k = 0; k < height; k++)
			{
				cout << k << ": ";
				cin >> tmp;
				Chunk[i][j][k] = tmp;
			}
		}
	}
}

void horizontalCut(bool(&Chunk)[Size][Size][Height], int size, int height, int horizontLevel)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (Chunk[i][j][horizontLevel])
			{
				cout << 1;
			}
			else
			{
				cout << 0;
			}
			cout << ' ';
		}
		cout << '\n';
	}
}

void initChunk(bool(&Chunk)[Size][Size][Height], int size, int height)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < height; k++)
			{
				Chunk[i][j][k] = false;
			}
		}
	}
}
