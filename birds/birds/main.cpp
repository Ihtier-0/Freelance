#include "duck.h"
#include "nightingale.h"
#include "cell.h"

#include <fstream>

using namespace std;

void menu()
{
	cout << "1) Добавить птицу\n2) Убрать птицу\n3) Показать птицу\n4) Количество птиц\n5) Показать всех птиц\n6) Выход\n";
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

			cout << "Введите строковый идентификатор: ";
			cin >> identifier;
			cout << "Введите спит птица или нет(sleep/awake): ";
			cin >> sleep;
			cout << "Введите как птица поёт(quack!quack!/phew!phew!): ";
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

			cout << "Введите строковый идентификатор: ";
			cin >> identifier;
			cout << "Введите спит птица или нет(sleep/awake): ";
			cin >> sleep;
			cout << "Введите как птица поёт(quack!quack!/phew!phew!): ";
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
			cout << "Введите номер птицы, которую нужно найти: ";
			cin >> index;

			bird *tmp = Cell[index];

			if (tmp)
			{
				cout << *tmp << '\n';
			}
			else
			{
				cout << "Слишком большой номер!\n";
			}

			break;
		}
		case 4:
		{
			cout << "Количество птиц: " << Cell.size() << '\n';
			break;
		}
		case 5:
		{
			cout << Cell;
			break;
		}
		default:
		{
			cout << "Команда введена неправильно!\n";
			break;
		}
		}

	} while (command != 6);
}