/*
����� �� ���������� �� ������ ������������������� �����������.
��� ���������� ������ ������� ������� ���� ������ (��) �������,
������� ���� ����� ��������� � ����� ������� �� ���� �����.
������ �������������� ���� �������: ������, ������, ���������, �������, ������, ������, ����, ����, �����.

�������� ���������, ������� ����� ��������� � ���� �� ���� �������.
� ��������� ������ ���� ������������� ����������� ���������
� �� ������ ����� �������� ������� ����,
� ����� ����� �� ������� �� ������� ������������ ������,
���������� ��������� ���� ���� ������, ������� ���������� � ��.
�� ����� ���� (��� �� ����) ��������� ������� � ������������ ��������� std::vector.
*/

#include "partsDatabase.h"
#include "utils.h"

#include <fstream>
#include <windows.h>

using namespace std;

void menu()
{
	cout << "1) ������ ���� ������\n"
		<< "2) ���������� ������� ������������� ����\n"
		<< "3) �������� ������ ������������� ����\n"
		<< "4) ������� ������ ������������� ����\n"
		<< "5) �����\n";
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	partsDatabase db;
	ifstream ifs("input.txt");
	ifs >> db;

	int command = 0;

	do
	{
		menu();
		cout << "> ";
		cin >> command;

		switch (command)
		{
		case 1:
		{
			cout << "������ ���� ������: " << db.size() << '\n';
			break;
		}
		case 2:
		{
			partType type;
			cout << "������� ��� ������ ���������� ������� ���� ���������: ";
			cin >> type;

			if (type == partType::unknown)
			{
				cout << "��� ������ �� ��������!\n";
			}
			else
			{
				cout << "���������� ������� ���������� ����: " << db.countParts(partTypeToPart(type)) << '\n';
			}

			break;
		}
		case 3:
		{
			partType type;
			cout << "������� ��� ������ ������� ���� ��������: ";
			cin >> type;

			if (type == partType::unknown)
			{
				cout << "��� ������ �� ��������!\n";
			}
			else
			{
				db.addPart(partTypeToPart(type));
			}
			
			break;
		}
		case 4:
		{
			partType type;
			cout << "������� ��� ������ ������� ���� �������: ";
			cin >> type;
			db.removePart(partTypeToPart(type));
			break;
		}
		}
	} while (command != 5);

	return 0;
}