/*
��������� ����������� ���������� ���� � ������� ���.
������� ���� �������� 10 �� 10 ������.
��������� ���� �������.
� �������� ������� �� ���:
4 ��������� ��������� �������� � ���� ������,
3 ��������� ������� �������� � ��� ������,
2 ������� ������� �������� � ��� ������
� ���� ������� ������� �������� � ������ ������.
��� ��������, ������ ���� ������������� �� ��������� �� 0 �� 9,
� �� ����������� ����� �� 0 �� 9.
�� �� ����� ������������ ������������ ������������ ������,
����� ��� B4, C6, � ������ ��� �������.
������� ������ �� ������� ����������� �������,
������� � ����� ��������� � ���������� ��������.
��������� ������� � ���� ������ ������������� � ������� �������� ���� ����� ������-����� �� ����, � ������� 2,1.
������� ������������ �� ���� ������ � ����, ������������� � ������� ��������� �� ������ � �����, � �������: 0,1 - 0,3.
������� ����� ���� ����������� ������ ������ �����������, ��� �������������.
��������� ������� �� ��������� � �����������, � ������ �������� �� ���� ���� ���� �������� ������������.
���� ������� �� ����� ���� �������� �� �������� ������� ��-�� ����, ��� �� ��������� � ������ ������� (�������� �� ��� �������)
��� ������ �� ������� ���� ������, �� ������ ������ ���� ������� ��������������,
����� �������� �� ������ ����������� ������� �� ����� �������� ����������.
������, � ����� ���������� �������� ����, �� �� ����� ����������� ��������������� �������� ���� � ������,
� ������ ������� ������ ����� ����� ��������� ���� � ����� �������� � ���� � �����.
����� ���� ��� ��� ������� ���� ����������� ���������� ����.
������ �� ������� ������� ���� �����, ������� ���������� ��������.
����� ��������, � ������� ��������� ���������� � ��� ����������: ����� ��� ����.
���� ������� �������, ������, �� ������� ��� ������� (��� ��� ��������) ���������� � ���������� ������.
���� ������������� �����, ����� ��� ������� ����� �� ������ ����� ��������� ����������.
��� ������ ��� ��������� � ������� ��������� ���������� � ������� ������, ������� �������.
*/

#include <iostream>

using namespace std;

const int Size = 10;

// ����������������� ������� ���� ������� ��������
void initializePlayingField(bool(&playingField)[Size][Size], int size);
// ��������� �-������� �������
bool deliverKDeckShip(bool(&playingField)[Size][Size], int size, int k,
	int x1, int y1,
	int x2, int y2);
// ��������� ������� ����
void fillPlayingField(bool(&playingField)[Size][Size], int size);
// ������ ����
void playGame(bool(&playingField1)[Size][Size], bool(&playingField2)[Size][Size], int size);
// ������ �� ����
bool isEmptyPlayingField(bool(&playingField)[Size][Size], int size);
// ������� �������
bool fire(bool(&playingField)[Size][Size], int size, int x, int y);

int main()
{
	setlocale(LC_ALL, "Russian");

	bool playingField1[Size][Size], playingField2[Size][Size];
	initializePlayingField(playingField1, Size);
	initializePlayingField(playingField2, Size);

	cout << "����� 1:\n";
	fillPlayingField(playingField1, Size);
	cout << "����� 2:\n";
	fillPlayingField(playingField2, Size);

	playGame(playingField1, playingField2, Size);

	if (isEmptyPlayingField(playingField1, Size))
	{
		cout << "������� ������ �����!\n";
	}
	else
	{
		cout << "������� ������ �����!\n";
	}

	return 0;
}

void initializePlayingField(bool(&playingField)[Size][Size], int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			playingField[i][j] = false;
		}
	}
}

bool deliverKDeckShip(bool(&playingField)[Size][Size], int size, int k, int x1, int y1, int x2, int y2)
{
	if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 ||
		x1 >= size || y1 >= size || x2 >= size || y2 >= size)
	{
		return false;
	}
	else
	{
		if (x1 == x2 && abs(y1 - y2) == k - 1)
		{
			int min, max;

			if (y1 > y2)
			{
				min = y2;
				max = y1;
			}
			else
			{
				min = y1;
				max = y2;
			}

			for (int i = min; i <= max; ++i)
			{
				if (playingField[x1][i])
				{
					return false;
				}
				else
				{
					playingField[x1][i] = true;
				}
			}
		}
		else if(y1 == y2 && abs(x1 - x2) == k - 1)
		{
			int min, max;

			if (x1 > x2)
			{
				min = x2;
				max = x1;
			}
			else
			{
				min = x1;
				max = x2;
			}

			for (int i = min; i <= max; ++i)
			{
				if (playingField[i][y1])
				{
					return false;
				}
				else
				{
					playingField[i][y1] = true;
				}
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

void fillPlayingField(bool(&playingField)[Size][Size], int size)
{
	int x1, y1, x2, y2;

	for (int i = 0; i < 4; ++i)
	{
		cout << "������� ���������� ������������� �������\nx: ";
		cin >> x1;
		cout << "y: ";
		cin >> y1;

		if (!deliverKDeckShip(playingField, size, 1, x1, y1, x1, y1))
		{
			cout << "��������� ������� �� �������! ���������� ��� ���!\n";
			--i;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		cout << "������� ���������� ������ ������������� �������\nx: ";
		cin >> x1;
		cout << "y: ";
		cin >> y1;
		cout << "������� ���������� ����� ������������� �������\nx: ";
		cin >> x2;
		cout << "y: ";
		cin >> y2;

		if (!deliverKDeckShip(playingField, size, 2, x1, y1, x2, y2))
		{
			cout << "��������� ������� �� �������! ���������� ��� ���!\n";
			--i;
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		cout << "������� ���������� ������ ������������� �������\nx: ";
		cin >> x1;
		cout << "y: ";
		cin >> y1;
		cout << "������� ���������� ����� ������������� �������\nx: ";
		cin >> x2;
		cout << "y: ";
		cin >> y2;

		if (!deliverKDeckShip(playingField, size, 3, x1, y1, x2, y2))
		{
			cout << "��������� ������� �� �������! ���������� ��� ���!\n";
			--i;
		}
	}

	for (int i = 0; i < 1; ++i)
	{
		cout << "������� ���������� ������ ���������������� �������\nx: ";
		cin >> x1;
		cout << "y: ";
		cin >> y1;
		cout << "������� ���������� ����� ���������������� �������\nx: ";
		cin >> x2;
		cout << "y: ";
		cin >> y2;

		if (!deliverKDeckShip(playingField, size, 4, x1, y1, x2, y2))
		{
			cout << "��������� ������� �� �������! ���������� ��� ���!\n";
			--i;
		}
	}
}

void playGame(bool(&playingField1)[Size][Size], bool(&playingField2)[Size][Size], int size)
{
	int x, y;

	while (!isEmptyPlayingField(playingField1, size) && !isEmptyPlayingField(playingField2, size))
	{
		do
		{
			cout << "��� ������� ������\nx: ";
			cin >> x;
			cout << "y: ";
			cin >> y;
		} while (fire(playingField2, size, x, y) && !isEmptyPlayingField(playingField2, size));

		// �� ������ ���� ������ ����� �������, ����� ������ �� ������� ���� ���
		if (isEmptyPlayingField(playingField2, size))
		{
			return;
		}

		do
		{
			cout << "��� ������� ������\nx: ";
			cin >> x;
			cout << "y: ";
			cin >> y;
		} while (fire(playingField1, size, x, y) && !isEmptyPlayingField(playingField1, size));
	}
}

bool isEmptyPlayingField(bool(&playingField)[Size][Size], int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (playingField[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

bool fire(bool(&playingField)[Size][Size], int size, int x, int y)
{
	if (x < 0 || y < 0 || x >= size || y >= size || !playingField[x][y])
	{
		cout << "����!\n";
		return false;
	}
	else
	{
		cout << "�����!\n";
		playingField[x][y] = false;
		return true;
	}
}
