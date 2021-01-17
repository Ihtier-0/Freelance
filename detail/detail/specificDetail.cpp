#include "specificDetail.h"

std::ostream& operator<<(std::ostream& out, const specificDetail& Detail)
{
	out << Detail.stockNumber << ' '
		<< Detail.name << ' '
		<< Detail.value << ' '
		<< Detail.measure << ' '
		<< Detail.country << ' '
		<< Detail.price;

	return out;
}

std::istream& operator>>(std::istream& is, specificDetail& Detail)
{
	Detail.name = new char[256];
	Detail.measure = new char[256];
	Detail.country = new char[256];

	is >> Detail.stockNumber
		>> Detail.name
		>> Detail.value
		>> Detail.measure
		>> Detail.country
		>> Detail.price;

	return is;
}

specificDetail::specificDetail() : detail()
{
	price = 0;
	country = nullptr;
}

specificDetail::specificDetail(const long long& stockNumber,
	const char* name,
	const long long& value,
	const char* unit,
	const char* Country,
	const double& price)
	:detail(stockNumber, name, value, unit), price(price)
{
	unsigned int sizemanufacturerCountry = strlen(Country) + 1;

	country = new char[sizemanufacturerCountry];

	for (unsigned int i = 0; i < sizemanufacturerCountry; i++)
	{
		country[i] = Country[i];
	}
}

specificDetail::specificDetail(const specificDetail& s)
	:detail(s), price(s.price)
{
	unsigned int sizemanufacturerCountry = strlen(s.country) + 1;

	country = new char[sizemanufacturerCountry];

	for (unsigned int i = 0; i < sizemanufacturerCountry; i++)
	{
		country[i] = s.country[i];
	}
}

specificDetail::~specificDetail()
{
	if (country)
	{
		delete country;
	}
}
