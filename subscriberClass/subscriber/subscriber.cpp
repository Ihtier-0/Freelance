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
int SUBSCRIBER::compare_fullName(const SUBSCRIBER& subscriber)
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

SUBSCRIBER::SUBSCRIBER(std::ifstream& file)
{
	std::getline(file, fullName);
	address.read_from_file(file);
	file >> telephoneNumber >> balance;
}

SUBSCRIBER::SUBSCRIBER()
{
	telephoneNumber = 0;
	balance = 0;
}

void SUBSCRIBER::print_to_file(std::ofstream& file)
{
	file << fullName << '\n';
	address.print_to_file(file);
	file << ' ' << telephoneNumber << ' ' << balance << '\n';
}

std::string SUBSCRIBER::get_fullName()
{
	return fullName;
}

Address SUBSCRIBER::get_address()
{
	return address;
}

long long SUBSCRIBER::get_telephoneNumber()
{
	return telephoneNumber;
}

long SUBSCRIBER::get_balance()
{
	return balance;
}
