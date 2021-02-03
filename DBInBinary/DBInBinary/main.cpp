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

	cout << "��������� ������: ";
	cout << db << '\n';

	int number_station;
	cout << "������� ����� �������: ";
	cin >> number_station;

	cout << "������ ��������� � " << number_station <<" �������:\n";
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