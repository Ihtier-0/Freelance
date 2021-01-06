/*
Пусть вы находитесь на складе машиностроительного предприятия.
Вам поставлена задача создать учетную базу данных (БД) деталей,
которые этот завод выпускает и затем отвозит на свой склад.
Список разновидностей этих деталей: втулка, корпус, кронштейн, манжета, фланец, панель, шток, винт, гайка.

Написать программу, которая будет содержать в себе БД этих деталей.
В программе должны быть предусмотрены возможности помещения
в БД любого числа объектов каждого типа,
а также вывод на консоль по запросу наименования детали,
количества элементов типа этой детали, которые содержатся в БД.
БД может быть (или не быть) отдельным классом и использовать контейнер std::vector.
*/

#include "partsDatabase.h"
#include "utils.h"

#include <fstream>
#include <windows.h>

using namespace std;

void menu()
{
	cout << "1) Размер базы данных\n"
		<< "2) Количество деталей определенного типа\n"
		<< "3) Добавить деталь определенного типа\n"
		<< "4) Удалить деталь определенного типа\n"
		<< "5) Выход\n";
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
			cout << "Размер базы данных: " << db.size() << '\n';
			break;
		}
		case 2:
		{
			partType type;
			cout << "Введите тип детали количество которых надо посчитать: ";
			cin >> type;

			if (type == partType::unknown)
			{
				cout << "Тип детали не известен!\n";
			}
			else
			{
				cout << "Количество деталей введённного типа: " << db.countParts(partTypeToPart(type)) << '\n';
			}

			break;
		}
		case 3:
		{
			partType type;
			cout << "Введите тип детали которую надо добавить: ";
			cin >> type;

			if (type == partType::unknown)
			{
				cout << "Тип детали не известен!\n";
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
			cout << "Введите тип детали которую надо удалить: ";
			cin >> type;
			db.removePart(partTypeToPart(type));
			break;
		}
		}
	} while (command != 5);

	return 0;
}