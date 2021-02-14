#include "train.h"

train::train() : m_number(-1), m_h_departure(-1), m_m_departure(-1),
	m_h_way(-1), m_m_way(-1), m_departure_station(), m_destination_station()
{
	for (int i = 0; i < 7; i++)
	{
		m_week[i] = false;
	}
}

train::train(const int& a_number,
	const bool const* a_week,
	const int& a_h_departure,
	const int& a_m_departure,
	const int& a_h_way,
	const int& a_m_way,
	const char const* a_departure_station,
	const char const* a_destination_station,
	const int& a_real_cout_of_Intermediate_stations,
	const char const* const* a_Intermediate_stations)
	: m_number(a_number),
	m_h_departure(a_h_departure),
	m_m_departure(a_m_departure),
	m_h_way(a_h_way),
	m_m_way(a_m_way),
	m_real_cout_of_Intermediate_stations(a_real_cout_of_Intermediate_stations)
{
	for (int i = 0; i < 7; i++)
	{
		m_week[i] = a_week[i];
	}
}

std::string train::departure_station() const
{
	return m_departure_station;
}

std::string train::destination_station() const
{
	return m_destination_station;
}

const std::string* train::Intermediate_stations() const
{
	return m_Intermediate_stations;
}

std::ostream& operator<<(std::ostream& out, const train& t)
{
	out << "number: " << t.m_number << '\n';
	out << "days of the week of departure: ";
	for (int i = 0; i < 7; ++i)
	{
		if (t.m_week[i])
		{
			out << i + 1 << ' ';
		}
	}
	out << '\n';

	out << "time departure: " << t.m_h_departure << ':' << t.m_m_departure << '\n';
	out << "travel time: " << t.m_h_way << ':' << t.m_m_way << '\n';
	out << "departure station: " << t.m_departure_station << '\n';
	out << "destination station: " << t.m_destination_station << '\n';

	out << "intermediate stations:\n";
	for (int i = 0; i < t.m_real_cout_of_Intermediate_stations; ++i)
	{
		out << t.m_Intermediate_stations[i] << '\n';
	}
	out << '\n';

	return out;
}

bool operator<(const train& left, const train& right)
{
	return left.m_number < right.m_number;
}
