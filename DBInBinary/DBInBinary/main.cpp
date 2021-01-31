#include "binaryDB.h"

#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));

	int size = 6, maxNumber = 100;

	// ������ ��������� ������ � ���� 
	ofstream out("db.txt");
	double t;
	for (int i = 0; i < size; ++i)
	{
		t = pow(-1, rand() % 2) * (rand() % 100 + 0.1 * (rand() % 10));
		out.write((char*)&t, sizeof(double));
	}
	out.close();

	binaryDB<double> db("db.txt");

	cout << "���� �� int\n������ �� �����:\n";
	std::cout << db << '\n';

	db.add(static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxNumber + maxNumber) - maxNumber);
	cout << "�������� � ����� ��������� ����� �� -100 �� 100:\n" << db << '\n';

	db.addByIndex(static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxNumber + maxNumber) - maxNumber, 3);
	cout << "�������� � ������� 3 ��������� ����� �� -100 �� 100:\n" << db << '\n';

	db.eraseByIndex(6);
	cout << "������� ����� �� 6� �������:\n" << db << '\n';

	int ind = rand() % db.size();
	db.erase(db[ind]);
	cout << "������ ����� �������� " << db[ind] << " :\n" << db << '\n';

	db.replace(static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxNumber + maxNumber) - maxNumber, 5);
	cout << "�������� ������� �� 5� ������� ��������� �� -100 �� 100:\n" << db << '\n';

	cout << "������ ���� ������: " << db.size() << '\n';

	db.sort();
	cout << "��������������� ������:\n" << db << '\n';

	db.addWithKeepingOrder(static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxNumber + maxNumber) - maxNumber);
	cout << "�������� ��������� ����� �� -100 �� 100 � ����������� �������:\n" << db << '\n';
}