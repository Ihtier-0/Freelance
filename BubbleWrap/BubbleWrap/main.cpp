/*
������ . �������

����� ������� �� ����� �������� ����. ����� ��� �������� ��������� ����� � �������.
����� � ������� 12 �� 12 �������-���������.
��������� ������ �������� � ��� ������ ���� �� �����, ���� ���, �.�. true ��� false (��� ������� bool).
��� ������, ��������� ����������� ��������� ������� ������������� ������� ��������� ���������� � ��������� ����� �������,
�.�. ��� �������� true. �� ��� ������ ����� ������.

��������� ����������� � ���������������� ������� ����� �������� ���������.
����� ������ ����� �������� ���� ���������� ������������ ��������� ��� �����:
o � ��� ����� ������, x � ��������.
��� ���� ���� �������� � ��������� �������.
����, ��� �������� ���� �������.
������������ ������ ��� ����������: ���������� ������ ������� � ����� �������������� �������.
���� ��������� ������� ������� ������ ���� ����������� � ������� ��������� �������,
��� ��������� ������ ����������� �� �� ����������,
��� ��� � � ������ ��������� ��������� �������� � ����� ������ ���� �������� ������.
����� ������� ������� ������, ������� �� ��� ��� ������ �� ����, � ������� ������ ���������� ��������� �Pop!�.

������� ������ ������������ �� ���������� ��������.
��� ������ ��� ������� ���������, ��������� ����������� ����������.
� ��������, �� ������ ���������� ��������� � ����� ������� �� ����������� ��������� �����,
�.�. ��� ����������� ����� ������� �������.
*/

#include <iostream>

using namespace std;

// ������ ���������� �����
const int Size = 12;

// ��������� ���������� �����
void fillBubbleWrap(bool (&BubbleWrap)[Size][Size], int wrapSize);
// ������� ���������� �����
void outBubbleWrap(bool(&BubbleWrap)[Size][Size], int wrapSize);
// ������� ������ ���������� �����
void burstBubbleWrapSector(bool(&BubbleWrap)[Size][Size], int wrapSize,
	int x1, int y1, // ����� ������� ���� �������
	int x2, int y2);// ������ ������ ���� �������
// ���� �� ��� ����� ������
bool thereAreNoBurstBubbles(bool(&BubbleWrap)[Size][Size], int wrapSize);
// ������ ���������� �����
void burstBubbleWrap(bool(&BubbleWrap)[Size][Size], int wrapSize);

int main()
{
	setlocale(LC_ALL, "Russian");

	// ������ ����������� ������
	bool BubbleWrap[Size][Size];
	// �������������� ���
	fillBubbleWrap(BubbleWrap, Size);
	// ������ �����
	burstBubbleWrap(BubbleWrap, Size);

	return 0;
}

void fillBubbleWrap(bool(&BubbleWrap)[Size][Size], int wrapSize)
{
	for (int i = 0; i < wrapSize; i++)
	{
		for (int j = 0; j < wrapSize; j++)
		{
			// ��������� ����� True - �� ���� �����
			BubbleWrap[i][j] = true;
		}
	}
}

void outBubbleWrap(bool(&BubbleWrap)[Size][Size], int wrapSize)
{
	for (int i = 0; i < wrapSize; i++)
	{
		for (int j = 0; j < wrapSize; j++)
		{
			if (BubbleWrap[i][j])
			{
				// ���� �����, �� 'o'
				cout << 'o';
			}
			else
			{
				// ���� ������, �� 'x'
				cout << 'x';
			}
			cout << ' ';
		}
		cout << '\n';
	}
}

void burstBubbleWrapSector(bool(&BubbleWrap)[Size][Size], int wrapSize,
	int x1, int y1,
	int x2, int y2)
{
	// ���� ����� ������� �� �������, �� �������
	if (x1 >= wrapSize || x2 >= wrapSize ||
		y1 >= wrapSize || y2 >= wrapSize ||
		x1 < 0 || x2 < 0 ||
		y1 < 0 || y2 < 0)
	{
		cout << "����� ������� �� ������� ���������� �����!\n";
	}
	// ����� �������� ������
	else
	{
		for (int i = x1; i <= x2; i++)
		{
			for (int j = y1; j <= y2; j++)
			{
				// ���� ������ �����
				if (BubbleWrap[i][j])
				{
					// ������ ���
					BubbleWrap[i][j] = false;
					// � ������� "Pop!\n"
					cout << "Pop!\n";
				}
			}
		}
	}
}

bool thereAreNoBurstBubbles(bool(&BubbleWrap)[Size][Size], int wrapSize)
{
	for (int i = 0; i < wrapSize; i++)
	{
		for (int j = 0; j < wrapSize; j++)
		{
			if (BubbleWrap[i][j])
			{
				// ���� ����� ����� ������, �� true
				return true;
			}
		}
	}

	// ���� �� ����� false
	return false;
}

void burstBubbleWrap(bool(&BubbleWrap)[Size][Size], int wrapSize)
{
	int x1, y1, x2, y2;

	do
	{
		cout << "������� ���������� ������ �����:\nx: ";
		cin >> x1;
		cout << "y: ";
		cin >> y1;
		cout << "������� ���������� ������ �����:\nx: ";
		cin >> x2;
		cout << "y: ";
		cin >> y2;

		// ���� ������ ����� ������, ������ ���������
		if (x2 < x1)
		{
			swap(x2, x1);
		}
		// ���� ������ ����� ����, ������ ����������
		if (y1 > y2)
		{
			swap(y2, y1);
		}

		burstBubbleWrapSector(BubbleWrap, wrapSize, x1, y1, x2, y2);

		cout << "����� ����� �������:\n";
		outBubbleWrap(BubbleWrap, wrapSize);

	} while (thereAreNoBurstBubbles(BubbleWrap, wrapSize));
}
