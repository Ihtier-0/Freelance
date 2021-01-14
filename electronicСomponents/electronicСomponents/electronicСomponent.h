#pragma once

#include <string>

class electronicСomponent
{
public:
	electronicСomponent();
	electronicСomponent(const long long& a_stockNumber,
		const std::string& name,
		const long long& value,
		const std::string& unit);
	electronicСomponent(const electronicСomponent& e);
	virtual ~electronicСomponent() = 0;

	std::string get_name();

	long long get_value();

protected:
	// номенклатурным номером
	long long stockNumber;
	// название
	std::string name;
	// значение 
	long long value;
	// единица измерения
	std::string unit;
};

