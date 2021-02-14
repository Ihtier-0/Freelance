#include "binaryDB.h"
#include "train.h"

#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

void menu()
{
	std::cout << "1) добавление строки\n"
		<< "2) вставка по логическому номеру\n"
		<< "3) удаление\n"
		<< "4) обновление строки\n"
		<< "5) сортировка\n"
		<< "6) вставка с сохранением порядка\n"
		<< "7) извлечение строки\n"
		<< "8) поезда следующие в заданную станцию\n"
		<< "9) количество элементов\n"
		<< "10) показать все данные\n"
		<< "11) выход\n> ";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));

	binaryDB<train> db("db.txt");

	int command = 0;

	do
	{
		menu();
		cin >> command;

		switch (command)
		{
		case 1:
		{

			break;
		}
		case 2:
		{

			break;
		}
		case 3:
		{

			break;
		}
		case 4:
		{

			break;
		}
		case 5:
		{
			db.sort();
			break;
		}
		case 6:
		{

			break;
		}
		case 7:
		{
			int index;
			cout << "введите индекс нужного элемента: \n";
			cin >> index;

			if (index < 0 || index >= db.size())
			{
				cout << "выход за пределы базы данных";
			}
			else
			{
				cout << "полученный элемент: " << db[index] << '\n';
			}
			break;
		}
		case 8:
		{

			break;
		}
		case 9:
		{
			cout << db.size() << '\n';
			break;
		}
		case 10:
		{
			cout << db << '\n';
			break;
		}
		}

	} while (command != 11);

	//cout << "Начальные данные: ";
	//cout << db << '\n';

	//int number_station;
	//cout << "Введите номер станции: ";
	//cin >> number_station;

	//cout << "Поезда следующий в " << number_station <<" станцию:\n";
	//std::function<bool(const train&)> condition = [&](const train& x) -> bool
	//{
	//	return x.departure_station() == number_station
	//		|| x.destination_station() == number_station
	//		|| x.Intermediate_stations()[number_station];
	//};
	//std::function<void(train&)> action = [](train& x)
	//{
	//	cout << x << '\n';
	//};

	//db.executeIf(condition, action);
}