main.cpp
/*
���������� ������� ����� ��� ����������� �����������,
�������� �������������� �������,
��������� (��������: �������������, ����������� � �.�.),
��������� (��������: 50 100 � �.�.)
� �������� ��������� (��, � � �.�.)
� ����������� ����� ��� ����������� ������������ ����������,
�������� �������-�������������� � �����.

������ �������� ������������, ����������� � ������� ������ ������.
�������� ������ ����������� � ���������.
������� ������������, �������� ������� ��������� � �������� ��������,
� ���������� ���������� �� ���� ��������.
�������������� �������� <<, ������� ����� �������������� ��� ����������� ������.
������ ������ ����������� � ����.
*/

#include "specificElectronicComponent.h"

#include <vector>
#include <fstream>
#include <Windows.h>

using namespace std;

void menu()
{
	cout << "1) �������� ����������\n"
		<< "2) ������� ����������\n"
		<< "3) �������� ��� ����������\n"
		<< "4) ������� ���������� � ����\n"
		<< "5) ������������, �������� ������� ��������� � �������� ��������\n"
		<< "6) �����\n";
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	int command = 0;

	vector<electronic�omponent*> vectorElectronic�omponent;

	ifstream ifs("input.txt");

	specificElectronicComponent tmp;

	while (!ifs.eof())
	{
		ifs >> tmp;
		vectorElectronic�omponent.push_back(new specificElectronicComponent(tmp));
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

			cout << "������� �������������� �����: ";
			cin >> stockNumber;
			cout << "������� ��������: ";
			cin >> name;
			cout << "������� ��������: ";
			cin >> value;
			cout << "������� ������� ���������: ";
			cin >> unit;
			cout << "������� ������ �������������: ";
			cin >> manufacturerCountry;
			cout << "������� ����: ";
			cin >> price;

			vectorElectronic�omponent.push_back(new specificElectronicComponent(stockNumber, name, value, unit,
				manufacturerCountry, price));

			break;
		}
		case 2:
		{
			int number;
			cout << "������� ����� �������� ������� ���� �������: ";
			cin >> number;

			if (number < vectorElectronic�omponent.size())
			{
				vectorElectronic�omponent.erase(vectorElectronic�omponent.begin() + number);
			}
			else
			{
				cout << "����� ������, ��� ���������� ���������!\n";
			}

			break;
		}
		case 3:
		{
			int size = vectorElectronic�omponent.size();

			for (int i = 0; i < size; i++)
			{
				std::cout << *dynamic_cast<specificElectronicComponent*>(vectorElectronic�omponent[i]) << '\n';
			}

			break;
		}
		case 4:
		{
			ofstream ofs("out.txt");

			int size = vectorElectronic�omponent.size();

			for (int i = 0; i < size; i++)
			{
				ofs << vectorElectronic�omponent[i] << '\n';
			}

			break;
		}
		case 5:
		{
			int size = vectorElectronic�omponent.size();

			long long leftBorder, rightBorder;

			cout << "������� ����� �������: ";
			cin >> leftBorder;
			cout << "������� ������ �������: ";
			cin >> rightBorder;

			if (leftBorder > rightBorder)
			{
				cout << "����� ������� ������, ��� ������!\n";
			}

			for (int i = 0; i < size; i++)
			{
				if (vectorElectronic�omponent[i]->get_name() == "�����������" &&
					vectorElectronic�omponent[i]->get_value() > leftBorder &&
					vectorElectronic�omponent[i]->get_value() < rightBorder)
				{
					cout << *dynamic_cast<specificElectronicComponent*>(vectorElectronic�omponent[i]) << '\n';
				}
			}
			break;
		}
		default:
		{
			cout << "������� ������� �����������! ���������� ��� ���!\n";
			break;
		}
		}
	} while (command != 6);

	ofstream ofs("out.txt");

	int size = vectorElectronic�omponent.size();

	for (int i = 0; i < size; i++)
	{
		ofs << vectorElectronic�omponent[i] << '\n';
	}
}
