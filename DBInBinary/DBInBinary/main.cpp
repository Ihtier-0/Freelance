#include "binaryDB.h"

#include <iostream>

using namespace std;

int main()
{
	/*std::ofstream out("db.txt");
	double i0 = 5;
	double i1 = 2;
	double i2 = 2;
	double i3 = 4;
	double i4 = 0;
	double i5 = 5;
	double i6 = -1;
	double i7 = 5;
	double i8 = 6;
	double i9 = 100;
	out.write((char*)&i0, sizeof(double));
	out.write((char*)&i1, sizeof(double));
	out.write((char*)&i2, sizeof(double));
	out.write((char*)&i3, sizeof(double));
	out.write((char*)&i4, sizeof(double));
	out.write((char*)&i5, sizeof(double));
	out.write((char*)&i6, sizeof(double));
	out.write((char*)&i7, sizeof(double));
	out.write((char*)&i8, sizeof(double));
	out.write((char*)&i9, sizeof(double));
	out.close();*/

	binaryDB<double> db("db.txt");

	for (int i = 0; i < db.size(); ++i)
	{
		std::cout << db[i] << '\n';
	}

	cout << "size: " << db.size() << '\n';

	db.addByIndex(15, 5);

	cout << '\n';
	for (int i = 0; i < db.size(); ++i)
	{
		std::cout << db[i] << '\n';
	}
}