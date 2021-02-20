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
		<< "5) количество элементов\n"
		<< "6) сортировка\n"
		<< "7) вставка с сохранением порядка\n"
		<< "8) извлечение строки\n"
		<< "9) удаление по индексу\n"
		<< "10) показать все данные\n"
		<< "11) Поезда следующие в выбранную станцию\n"
		<< "12) выход\n> ";
}

train inputTrain()
{
	// номер поезда
	int number;
	// дни недели отправления
	bool week[7];
	// время отправления
	int h_departure, m_departure;
	// время в пути
	int h_way, m_way;
	// станция отправления
	int departure_station;
	// станция назначения
	int destination_station;
	// промежуточные станции
	bool Intermediate_stations[count_of_Intermediate_stations];

	cout << "Введите номер поезда: ";
	cin >> number;

	for (int i = 0; i < 7; ++i)
	{
		cout << "Отправляется ли поезд в " << i << "-й день недели? (1 - да, 0 - нет)";
		cin >> week[i];
	}

	cout << "Часы отправления поезда: ";
	cin >> h_departure;
	cout << "Минуты отправления поезда: ";
	cin >> m_departure;

	cout << "Часы в пути поезда: ";
	cin >> h_way;
	cout << "Минуты в пути поезда: ";
	cin >> m_way;

	cout << "Введите номер станции отправления(число от 0 до " << count_of_Intermediate_stations << "): ";
	cin >> departure_station;
	cout << "Введите номер станции прибытия(число от 0 до " << count_of_Intermediate_stations << "): ";
	cin >> destination_station;

	for (int i = 0; i < count_of_Intermediate_stations; ++i)
	{
		cout << "Отправляется ли поезд в " << i << "-ю станцию? (1 - да, 0 - нет)";
		cin >> Intermediate_stations[i];
	}

	Intermediate_stations[departure_station] = false;
	Intermediate_stations[destination_station] = false;

	return train(number, week, h_departure, m_departure, h_way, m_way,
		departure_station, destination_station, Intermediate_stations);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));

	//// номер поезда
	//int m_number;
	//// дни недели отправления
	//bool m_week[7];
	//// время отправления
	//int m_h_departure, m_m_departure;
	//// время в пути
	//int m_h_way, m_m_way;
	//// станция отправления
	//int m_departure_station;
	//// станция назначения
	//int m_destination_station;
	//// промежуточные станции
	//bool m_Intermediate_stations[count_of_Intermediate_stations];
	//ofstream os("db.txt");
	//for (int i = 0; i < 5; ++i)
	//{
	//	m_number = rand() % 100;
	//	for (int j = 0; j < 7; ++j)
	//	{
	//		m_week[i] = rand() % 2;
	//	}
	//	m_h_departure = rand() % 24;
	//	m_m_departure = rand() % 60;
	//	m_h_way = rand() % 24;
	//	m_m_way = rand() % 60;
	//	m_departure_station = rand() % count_of_Intermediate_stations;
	//	m_destination_station = rand() % count_of_Intermediate_stations;
	//	for (int j = 0; j < count_of_Intermediate_stations; ++j)
	//	{
	//		m_Intermediate_stations[i] = rand() % 2;
	//	}
	//	m_Intermediate_stations[m_departure_station] = false;
	//	m_Intermediate_stations[m_destination_station] = false;
	//	train tmp(m_number, m_week, m_h_departure, m_m_departure, m_h_way, m_m_way, m_departure_station, m_destination_station,
	//		m_Intermediate_stations);
	//	os.write((char*)&tmp, sizeof(train));
	//}
	//os.close();

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
			db.add(inputTrain());
			break;
		}
		case 2:
		{
			int index;

			cout << "Введите куда нужно добавить поезд: ";
			cin >> index;

			if (index < 0 || index > db.size())
			{
				cout << "неверный индекс";
			}
			else
			{
				db.addByIndex(inputTrain(), index);
			}

			break;
		}
		case 3:
		{
			db.erase(inputTrain());
			break;
		}
		case 4:
		{
			int index;

			cout << "Введите индекс который нужно обновить нужно добавить поезд: ";
			cin >> index;

			if (index < 0 || index > db.size())
			{
				cout << "неверный индекс";
			}
			else
			{
				db.replace(inputTrain(), index);
			}

			break;
		}
		case 5:
		{
			cout << "количество элементов: " << db.size() << '\n';
			break;
		}
		case 6:
		{
			if (db.size() > 1)
			{
				db.sort();
			}
			break;
		}
		case 7:
		{
			db.addWithKeepingOrder(inputTrain());
			break;
		}
		case 8:
		{
			int index;

			cout << "Введите индекс поезда данные о котором нужно получить: ";
			cin >> index;

			if (index < 0 || index > db.size())
			{
				cout << "неверный индекс";
			}
			else
			{
				cout << db[index] << '\n';
			}
			break;
		}
		case 9:
		{
			int index;

			cout << "Введите индекс поезда данные о котором нужно удалить: ";
			cin >> index;

			if (index < 0 || index > db.size())
			{
				cout << "индекс выходит за пределы базы данных\n";
			}
			else
			{
				db.eraseByIndex(index);
			}

			break;
		}
		case 10:
		{
			cout << db;

			break;
		}
		case 11:
		{
			int number_station;
			cout << "Введите номер станции: ";
			cin >> number_station;

			cout << "Поезда следующий в " << number_station << " станцию:\n";
			std::function<bool(const train&)> condition = [&](const train& x) -> bool
			{
				return x.departure_station() == number_station
					|| x.destination_station() == number_station
					|| x.Intermediate_stations()[number_station];
			};
			std::function<void(train&)> action = [](train& x)
			{
				cout << x << '\n';
			};

			db.executeIf(condition, action);
			break;
		}
		}
	} while (command != 12);
}