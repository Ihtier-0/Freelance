#include "detail.h"

#include <string>

detail::detail()
{
	stockNumber = 0;
	value = 0;
	this->name = nullptr;
	this->measure = nullptr;
}

detail::detail(const long long& StockNumber,
	const char* Name,
	const long long& Value,
	const char* measure)
	:stockNumber(StockNumber), value(Value)
{
	unsigned int nameSize = strlen(Name) + 1;

	name = new char[nameSize];

	for (unsigned int i = 0; i < nameSize; i++)
	{
		name[i] = Name[i];
	}

	unsigned int unitSize = strlen(measure) + 1;

	this->measure = new char[unitSize];

	for (unsigned int i = 0; i < unitSize; i++)
	{
		this->measure[i] = measure[i];
	}
}

detail::detail(const detail& Detail)
	:stockNumber(Detail.stockNumber),value(Detail.value)
{
	unsigned int nameSize = strlen(Detail.name) + 1;

	name = new char[nameSize];

	for (unsigned int i = 0; i < nameSize; i++)
	{
		name[i] = Detail.name[i];
	}

	unsigned int unitSize = strlen(Detail.measure) + 1;

	measure = new char[unitSize];

	for (unsigned int i = 0; i < unitSize; i++)
	{
		measure[i] = Detail.measure[i];
	}
}

detail::~detail()
{
	if (measure)
	{
		delete measure;
	}

	if (name)
	{
		delete name;
	}
}

char * detail::Name()
{
	return name;
}

long long detail::Value()
{
	return value;
}
