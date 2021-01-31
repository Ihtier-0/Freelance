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

	// запись случайных данных в файл 
	ofstream out("db.txt");
	double t;
	for (int i = 0; i < size; ++i)
	{
		t = pow(-1, rand() % 2) * (rand() % 100 + 0.1 * (rand() % 10));
		out.write((char*)&t, sizeof(double));
	}
	out.close();

	binaryDB<double> db("db.txt");

	cout << "Тест на int\nДанные из файла:\n";
	std::cout << db << '\n';

	db.add(static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxNumber + maxNumber) - maxNumber);
	cout << "Добавить в конец случайное число от -100 до 100:\n" << db << '\n';

	db.addByIndex(static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxNumber + maxNumber) - maxNumber, 3);
	cout << "Добавить в позицию 3 случайное число от -100 до 100:\n" << db << '\n';

	db.eraseByIndex(6);
	cout << "Удалить число на 6й позиции:\n" << db << '\n';

	int ind = rand() % db.size();
	db.erase(db[ind]);
	cout << "Данные после удаления " << db[ind] << " :\n" << db << '\n';

	db.replace(static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxNumber + maxNumber) - maxNumber, 5);
	cout << "Заменить элемент на 5й позиции случайным от -100 до 100:\n" << db << '\n';

	cout << "Размер базы данных: " << db.size() << '\n';

	db.sort();
	cout << "Отсортированные данные:\n" << db << '\n';

	db.addWithKeepingOrder(static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (maxNumber + maxNumber) - maxNumber);
	cout << "Добавить случайное число от -100 до 100 с сохранением порядка:\n" << db << '\n';
}