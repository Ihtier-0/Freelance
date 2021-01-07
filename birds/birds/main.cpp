#include "duck.h"
#include "nightingale.h"
#include "cell.h"

#include <fstream>

using namespace std;

void menu()
{
	cout << "1) �������� �����\n2) ������ �����\n3) �������� �����\n4) ���������� ����\n5) �������� ���� ����\n6) �����\n";
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int command = -1;

	cell Cell;

	ifstream ifs("birds.txt");

	ifs >> Cell;

	do
	{
		menu();
		cout << "> ";
		cin >> command;

		switch (command)
		{
		case 1:
		{
			std::string identifier;
			std::string sleep;
			std::string sing;

			cout << "������� ��������� �������������: ";
			cin >> identifier;
			cout << "������� ���� ����� ��� ���(sleep/awake): ";
			cin >> sleep;
			cout << "������� ��� ����� ���(quack!quack!/phew!phew!): ";
			cin >> sing;

			bird* tmp = nullptr;

			if (sing == "quack!quack!")
			{
				tmp = new duck(identifier, sleep == "sleep");
			}

			if (sing == "phew!phew!")
			{
				tmp = new nightingale(identifier, sleep == "sleep");
			}

			if (tmp)
			{
				Cell.add(tmp);
			}

			break;
		}
		case 2:
		{
			std::string identifier;
			std::string sleep;
			std::string sing;

			cout << "������� ��������� �������������: ";
			cin >> identifier;
			cout << "������� ���� ����� ��� ���(sleep/awake): ";
			cin >> sleep;
			cout << "������� ��� ����� ���(quack!quack!/phew!phew!): ";
			cin >> sing;

			bird* tmp = nullptr;

			if (sing == "quack!quack!")
			{
				tmp = new duck(identifier, sleep == "sleep");
			}

			if (sing == "phew!phew!")
			{
				tmp = new nightingale(identifier, sleep == "sleep");
			}

			if (tmp)
			{
				Cell.remove(tmp);
			}

			break;
		}
		case 3:
		{
			int index;
			cout << "������� ����� �����, ������� ����� �����: ";
			cin >> index;

			bird *tmp = Cell[index];

			if (tmp)
			{
				cout << *tmp << '\n';
			}
			else
			{
				cout << "������� ������� �����!\n";
			}

			break;
		}
		case 4:
		{
			cout << "���������� ����: " << Cell.size() << '\n';
			break;
		}
		case 5:
		{
			cout << Cell;
			break;
		}
		default:
		{
			cout << "������� ������� �����������!\n";
			break;
		}
		}

	} while (command != 6);
}