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
		<< "5) ���������� ���������\n"
		<< "6) ����������\n"
		<< "7) ������� � ����������� �������\n"
		<< "8) ���������� ������\n"
		<< "9) �������� �� �������\n"
		<< "10) �������� ��� ������\n"
		<< "11) ������ ��������� � ��������� �������\n"
		<< "12) �����\n> ";
}

train inputTrain()
{
	// ����� ������
	int number;
	// ��� ������ �����������
	bool week[7];
	// ����� �����������
	int h_departure, m_departure;
	// ����� � ����
	int h_way, m_way;
	// ������� �����������
	int departure_station;
	// ������� ����������
	int destination_station;
	// ������������� �������
	bool Intermediate_stations[count_of_Intermediate_stations];

	cout << "������� ����� ������: ";
	cin >> number;

	for (int i = 0; i < 7; ++i)
	{
		cout << "������������ �� ����� � " << i << "-� ���� ������? (1 - ��, 0 - ���)";
		cin >> week[i];
	}

	cout << "���� ����������� ������: ";
	cin >> h_departure;
	cout << "������ ����������� ������: ";
	cin >> m_departure;

	cout << "���� � ���� ������: ";
	cin >> h_way;
	cout << "������ � ���� ������: ";
	cin >> m_way;

	cout << "������� ����� ������� �����������(����� �� 0 �� " << count_of_Intermediate_stations << "): ";
	cin >> departure_station;
	cout << "������� ����� ������� ��������(����� �� 0 �� " << count_of_Intermediate_stations << "): ";
	cin >> destination_station;

	for (int i = 0; i < count_of_Intermediate_stations; ++i)
	{
		cout << "������������ �� ����� � " << i << "-� �������? (1 - ��, 0 - ���)";
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

	//// ����� ������
	//int m_number;
	//// ��� ������ �����������
	//bool m_week[7];
	//// ����� �����������
	//int m_h_departure, m_m_departure;
	//// ����� � ����
	//int m_h_way, m_m_way;
	//// ������� �����������
	//int m_departure_station;
	//// ������� ����������
	//int m_destination_station;
	//// ������������� �������
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

			cout << "������� ���� ����� �������� �����: ";
			cin >> index;

			if (index < 0 || index > db.size())
			{
				cout << "�������� ������";
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

			cout << "������� ������ ������� ����� �������� ����� �������� �����: ";
			cin >> index;

			if (index < 0 || index > db.size())
			{
				cout << "�������� ������";
			}
			else
			{
				db.replace(inputTrain(), index);
			}

			break;
		}
		case 5:
		{
			cout << "���������� ���������: " << db.size() << '\n';
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

			cout << "������� ������ ������ ������ � ������� ����� ��������: ";
			cin >> index;

			if (index < 0 || index > db.size())
			{
				cout << "�������� ������";
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

			cout << "������� ������ ������ ������ � ������� ����� �������: ";
			cin >> index;

			if (index < 0 || index > db.size())
			{
				cout << "������ ������� �� ������� ���� ������\n";
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
			cout << "������� ����� �������: ";
			cin >> number_station;

			cout << "������ ��������� � " << number_station << " �������:\n";
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