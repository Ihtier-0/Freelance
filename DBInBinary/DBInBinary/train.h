#pragma once

#include <string>
#include <iostream>

constexpr int max_count_of_Intermediate_stations = 50;
constexpr int max_long_of_name = 50;

class train
{
public:
	train();
	train(const int& a_number,
		const bool const* a_week,
		const int& a_h_departure,
		const int& a_m_departure,
		const int& a_h_way,
		const int& a_m_way,
		const char const * a_departure_station,
		const char const * a_destination_station,
		const int& a_real_cout_of_Intermediate_stations,
		const char const* const * a_Intermediate_stations);

	friend std::ostream& operator<<(std::ostream& out, const train& t);

	std::string departure_station() const;
	std::string destination_station() const;
	const std::string* Intermediate_stations() const;

	friend bool operator<(const train& left, const train& right);

private:
	// номер поезда
	int m_number;
	// дни недели отправления
	bool m_week[7];
	// время отправления
	int m_h_departure, m_m_departure;
	// время в пути
	int m_h_way, m_m_way;
	// станция отправления
	char m_departure_station[max_long_of_name];
	// станция назначения
	char m_destination_station[max_long_of_name];
	// промежуточные станции
	int m_real_cout_of_Intermediate_stations;
	char m_Intermediate_stations[max_count_of_Intermediate_stations][max_long_of_name];
};

