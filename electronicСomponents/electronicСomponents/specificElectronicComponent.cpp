#include "specificElectronicComponent.h"

std::ostream& operator<<(std::ostream& out, const specificElectronicComponent& s)
{
	out << s.stockNumber << ' '
		<< s.name << ' '
		<< s.value << ' '
		<< s.unit << ' '
		<< s.manufacturerCountry << ' '
		<< s.price;

	return out;
}

std::istream& operator>>(std::istream& is, specificElectronicComponent& s)
{
	is >> s.stockNumber
		>> s.name
		>> s.value
		>> s.unit
		>> s.manufacturerCountry
		>> s.price;

	return is;
}

specificElectronicComponent::specificElectronicComponent()
{
	price = 0;
}

specificElectronicComponent::specificElectronicComponent(const long long& a_stockNumber,
	const std::string& a_name,
	const long long& a_value,
	const std::string& a_unit,
	const std::string& a_manufacturerCountry,
	const double& a_price)
	:electronic—omponent(a_stockNumber, a_name, a_value, a_unit), manufacturerCountry(a_manufacturerCountry), price(a_price) {}

specificElectronicComponent::specificElectronicComponent(const specificElectronicComponent& s)
	:electronic—omponent(s), manufacturerCountry(s.manufacturerCountry), price(s.price) {}
