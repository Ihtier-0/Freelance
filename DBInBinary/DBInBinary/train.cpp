#include "train.h"

#include <string>

std::string name_of_stations[count_of_Intermediate_stations] = {
	"36th Avenue",
	"36th Street",
	"39th Avenue",
	"40th Street–Lowery Street",
	"46th Street–Bliss Street",
	"65th Street",
	"69th Street",
	"75th Avenue",
	"104th Street",
	"110th Street"
};

train::train() : m_number(-1), m_h_departure(-1), m_m_departure(-1),
	m_h_way(-1), m_m_way(-1), m_departure_station(-1), m_destination_station(-1)
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
	const int& a_departure_station,
	const int& a_destination_station,
	const bool const* a_Intermediate_stations)
	: m_number(a_number),
	m_h_departure(a_h_departure),
	m_m_departure(a_m_departure),
	m_h_way(a_h_way),
	m_m_way(a_m_way),
	m_departure_station(a_departure_station),
	m_destination_station(a_destination_station)
{
	for (int i = 0; i < 7; i++)
	{
		m_week[i] = a_week[i];
	}

	for (int i = 0; i < count_of_Intermediate_stations; i++)
	{
		m_Intermediate_stations[i] = a_Intermediate_stations[i];
	}
}

int train::departure_station() const
{
	return m_departure_station;
}

int train::destination_station() const
{
	return m_destination_station;
}

const bool* train::Intermediate_stations() const
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
	out << "departure station: " << name_of_stations[t.m_departure_station] << '\n';
	out << "destination station: " << name_of_stations[t.m_destination_station] << '\n';

	out << "intermediate stations:\n";
	for (int i = 0; i < count_of_Intermediate_stations; ++i)
	{
		if (t.m_Intermediate_stations[i])
		{
			out << name_of_stations[i] << '\n';
		}
	}
	out << '\n';

	return out;
}

bool operator<(const train& left, const train& right)
{
	return left.m_number < right.m_number;
}

bool operator==(const train& left, const train& right)
{
	return left.m_number == right.m_number;
}
