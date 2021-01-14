#include "electronic—omponent.h"

electronic—omponent::electronic—omponent()
{
	stockNumber = 0;
	value = 0;
}

electronic—omponent::electronic—omponent(const long long& a_stockNumber,
	const std::string& a_name,
	const long long& a_value,
	const std::string& a_unit)
	:stockNumber(a_stockNumber), name(a_name), value(a_value), unit(a_unit) {}

electronic—omponent::electronic—omponent(const electronic—omponent& e)
	:stockNumber(e.stockNumber), name(e.name), value(e.value), unit(e.unit) {}

electronic—omponent::~electronic—omponent() {}

std::string electronic—omponent::get_name()
{
	return name;
}

long long electronic—omponent::get_value()
{
	return value;
}
