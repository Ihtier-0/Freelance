#include "subscriber.h"

void Address::read_from_file(std::ifstream& file)
{
	file >> street >> houseNumber >> apartment;
}

void Address::print_to_file(std::ofstream& file)
{
	file << street << ' ' << houseNumber << ' ' << apartment;
}

//-1 (<) 0 (=) 1 (>)
int Subscriber::compare_fullName(const Subscriber& subscriber)
{
	if (fullName < subscriber.fullName)
	{
		return -1;
	}
	else if (fullName == subscriber.fullName)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void Subscriber::read_from_file(std::ifstream& file)
{
	std::getline(file, fullName);
	address.read_from_file(file);
	file >> telephoneNumber >> balance;
}

void Subscriber::print_to_file(std::ofstream& file)
{
	file << fullName << '\n';
	address.print_to_file(file);
	file << ' ' << telephoneNumber << ' ' << balance << '\n';
}
