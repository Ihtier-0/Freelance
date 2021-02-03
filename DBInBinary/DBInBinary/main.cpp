#include "binaryDB.h"
#include "train.h"

#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));

	binaryDB<train> db("db.txt");

	cout << "Начальные данные: ";
	cout << db << '\n';

	int number_station;
	cout << "Введите номер станции: ";
	cin >> number_station;

	cout << "Поезда следующий в " << number_station <<" станцию:\n";
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
}