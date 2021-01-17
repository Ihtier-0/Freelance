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

#include "specificDetail.h"

#include <vector>
#include <fstream>
#include <Windows.h>
#include <cstring>

using namespace std;

// ����
void menu()
{
	cout << "1) �������� ������\n"
		<< "2) ������� ������\n"
		<< "3) �������� ��� ������\n"
		<< "4) ������� ������ � ����\n"
		<< "5) ������������, �������� ������� ��������� � �������� ��������\n"
		<< "6) �����\n";
}

void add_detail(vector<detail*> &vectorDetail)
{
	long long stockNumber;
	char name[256];
	long long value;
	char unit[256];
	char manufacturerCountry[256];
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

	vectorDetail.push_back(new specificDetail(stockNumber, name, value, unit,
		manufacturerCountry, price));
}

void remove_detail(vector<detail*>& vectorDetail)
{
	int number;
	cout << "������� ����� �������� ������� ���� �������: ";
	cin >> number;

	if (number < vectorDetail.size())
	{
		vectorDetail.erase(vectorDetail.begin() + number);
	}
	else
	{
		cout << "����� ������, ��� ���������� ���������!\n";
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
		if (std::strcmp(vectorDetail[i]->Name(), "�����������") &&
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
			cout << "������� ������� �����������! ���������� ��� ���!\n";
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
