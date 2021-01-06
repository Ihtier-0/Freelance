#pragma once

#include <string>
#include <fstream>

struct Address
{
	std::string street;
	unsigned int houseNumber;
	unsigned int apartment;

	void read_from_file(std::ifstream& file);
	void print_to_file(std::ofstream& file);
};

class SUBSCRIBER
{
public:
	SUBSCRIBER(std::ifstream& file);
	SUBSCRIBER();
	int compare_fullName(const SUBSCRIBER& subscriber);
	void print_to_file(std::ofstream& file);

	std::string get_fullName();
	Address get_address();
	long long get_telephoneNumber();
	long get_balance();
private:
	std::string fullName;
	Address address;
	long long telephoneNumber;
	long balance;
};

