main.cpp
/*
Определите базовый класс для электронных компонентов,
заданных номенклатурным номером,
названием (например: сопротивление, конденсатор и т.д.),
значением (например: 50 100 и т.д.)
и единицей измерения (Ом, Н и т.д.)
и производный класс для конкретного электронного компонента,
заданный страной-производителем и ценой.

Классы включают конструкторы, деструкторы и функции вывода членов.
Предметы должны добавляться и удаляться.
Найдите конденсаторы, значение которых находятся в заданных пределах,
и отобразите информацию об этих объектах.
Переопределите операцию <<, которая будет использоваться для отображения данных.
Данные должны сохраняться в файл.
*/

#include "specificElectronicComponent.h"

#include <vector>
#include <fstream>
#include <Windows.h>

using namespace std;

void menu()
{
	cout << "1) Добавить компоненту\n"
		<< "2) Удалить компоненту\n"
		<< "3) Показать все компоненты\n"
		<< "4) Вывести компоненты в файл\n"
		<< "5) Конденсаторы, значение которых находятся в заданных пределах\n"
		<< "6) Выход\n";
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	int command = 0;

	vector<electronicСomponent*> vectorElectronicСomponent;

	ifstream ifs("input.txt");

	specificElectronicComponent tmp;

	while (!ifs.eof())
	{
		ifs >> tmp;
		vectorElectronicСomponent.push_back(new specificElectronicComponent(tmp));
	}

	do
	{
		menu();
		cout << "> ";
		cin >> command;

		switch (command)
		{
		case 1:
		{
			long long stockNumber;
			string name;
			long long value;
			string unit;
			string manufacturerCountry;
			double price;

			cout << "Введите номенклатурный номер: ";
			cin >> stockNumber;
			cout << "Введите название: ";
			cin >> name;
			cout << "Введите значение: ";
			cin >> value;
			cout << "Введите единицу измерения: ";
			cin >> unit;
			cout << "Введите страну производитель: ";
			cin >> manufacturerCountry;
			cout << "Введите цену: ";
			cin >> price;

			vectorElectronicСomponent.push_back(new specificElectronicComponent(stockNumber, name, value, unit,
				manufacturerCountry, price));

			break;
		}
		case 2:
		{
			int number;
			cout << "Введите номер элемента который надо удалить: ";
			cin >> number;

			if (number < vectorElectronicСomponent.size())
			{
				vectorElectronicСomponent.erase(vectorElectronicСomponent.begin() + number);
			}
			else
			{
				cout << "Номер больше, чем количество элементов!\n";
			}

			break;
		}
		case 3:
		{
			int size = vectorElectronicСomponent.size();

			for (int i = 0; i < size; i++)
			{
				std::cout << *dynamic_cast<specificElectronicComponent*>(vectorElectronicСomponent[i]) << '\n';
			}

			break;
		}
		case 4:
		{
			ofstream ofs("out.txt");

			int size = vectorElectronicСomponent.size();

			for (int i = 0; i < size; i++)
			{
				ofs << vectorElectronicСomponent[i] << '\n';
			}

			break;
		}
		case 5:
		{
			int size = vectorElectronicСomponent.size();

			long long leftBorder, rightBorder;

			cout << "Введите левую границу: ";
			cin >> leftBorder;
			cout << "Введите правую границу: ";
			cin >> rightBorder;

			if (leftBorder > rightBorder)
			{
				cout << "Левая граница больше, чем правая!\n";
			}

			for (int i = 0; i < size; i++)
			{
				if (vectorElectronicСomponent[i]->get_name() == "конденсатор" &&
					vectorElectronicСomponent[i]->get_value() > leftBorder &&
					vectorElectronicСomponent[i]->get_value() < rightBorder)
				{
					cout << *dynamic_cast<specificElectronicComponent*>(vectorElectronicСomponent[i]) << '\n';
				}
			}
			break;
		}
		default:
		{
			cout << "Команда введена неправильно! Попробуйте ещё раз!\n";
			break;
		}
		}
	} while (command != 6);

	ofstream ofs("out.txt");

	int size = vectorElectronicСomponent.size();

	for (int i = 0; i < size; i++)
	{
		ofs << vectorElectronicСomponent[i] << '\n';
	}
}
