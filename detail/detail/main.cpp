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

#include "specificDetail.h"

#include <vector>
#include <fstream>
#include <Windows.h>
#include <cstring>

using namespace std;

// меню
void menu()
{
	cout << "1) Добавить деталь\n"
		<< "2) Удалить деталь\n"
		<< "3) Показать все детали\n"
		<< "4) Вывести детали в файл\n"
		<< "5) Конденсаторы, значение которых находятся в заданных пределах\n"
		<< "6) Выход\n";
}

void add_detail(vector<detail*> &vectorDetail)
{
	long long stockNumber;
	char name[256];
	long long value;
	char unit[256];
	char manufacturerCountry[256];
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

	vectorDetail.push_back(new specificDetail(stockNumber, name, value, unit,
		manufacturerCountry, price));
}

void remove_detail(vector<detail*>& vectorDetail)
{
	int number;
	cout << "Введите номер элемента который надо удалить: ";
	cin >> number;

	if (number < vectorDetail.size())
	{
		vectorDetail.erase(vectorDetail.begin() + number);
	}
	else
	{
		cout << "Номер больше, чем количество элементов!\n";
	}
}

void out_detail(vector<detail*>& vectorDetail)
{
	int size = vectorDetail.size();

	for (int i = 0; i < size; i++)
	{
		std::cout << *dynamic_cast<specificDetail*>(vectorDetail[i]) << '\n';
	}
}

void out_detail_in_file(vector<detail*>& vectorDetail, ofstream &ofs)
{
	int size = vectorDetail.size();

	for (int i = 0; i < size; i++)
	{
		ofs << vectorDetail[i] << '\n';
	}
}

void capacitors(vector<detail*>& vectorDetail)
{
	int size = vectorDetail.size();

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
		if (std::strcmp(vectorDetail[i]->Name(), "конденсатор") &&
			vectorDetail[i]->Value() > leftBorder &&
			vectorDetail[i]->Value() < rightBorder)
		{
			cout << *dynamic_cast<specificDetail*>(vectorDetail[i]) << '\n';
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	int command = 0;

	vector<detail*> vectorDetail;

	ifstream ifs("input.txt");

	specificDetail tmp;

	while (!ifs.eof())
	{
		ifs >> tmp;
		vectorDetail.push_back(new specificDetail(tmp));
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
			add_detail(vectorDetail);

			break;
		}
		case 2:
		{
			remove_detail(vectorDetail);

			break;
		}
		case 3:
		{
			out_detail(vectorDetail);

			break;
		}
		case 4:
		{
			ofstream ofs("out.txt");

			out_detail_in_file(vectorDetail, ofs);

			break;
		}
		case 5:
		{
			capacitors(vectorDetail);

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

	int size = vectorDetail.size();

	for (int i = 0; i < size; i++)
	{
		ofs << vectorDetail[i] << '\n';
	}
}
