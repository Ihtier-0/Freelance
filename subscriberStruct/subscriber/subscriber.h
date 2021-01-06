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

struct Subscriber
{
	std::string fullName;
	Address address;
	long long telephoneNumber;
	long balance;

	int compare_fullName(const Subscriber& subscriber);
	void read_from_file(std::ifstream& file);
	void print_to_file(std::ofstream& file);
};

