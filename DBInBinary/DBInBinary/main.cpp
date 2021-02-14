#include "binaryDB.h"
#include "train.h"

#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

void menu()
{
	std::cout << "1) ���������� ������\n"
		<< "2) ������� �� ����������� ������\n"
		<< "3) ��������\n"
		<< "4) ���������� ������\n"
		<< "5) ����������\n"
		<< "6) ������� � ����������� �������\n"
		<< "7) ���������� ������\n"
		<< "8) ������ ��������� � �������� �������\n"
		<< "9) ���������� ���������\n"
		<< "10) �������� ��� ������\n"
		<< "11) �����\n> ";
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
			cout << "������� ������ ������� ��������: \n";
			cin >> index;

			if (index < 0 || index >= db.size())
			{
				cout << "����� �� ������� ���� ������";
			}
			else
			{
				cout << "���������� �������: " << db[index] << '\n';
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

	//cout << "��������� ������: ";
	//cout << db << '\n';

	//int number_station;
	//cout << "������� ����� �������: ";
	//cin >> number_station;

	//cout << "������ ��������� � " << number_station <<" �������:\n";
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