#pragma once

#include <string>
#include <iostream>

constexpr int count_of_Intermediate_stations = 10;

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
		const int& a_departure_station,
		const int& a_destination_station,
		const bool const* a_Intermediate_stations);

	friend std::ostream& operator<<(std::ostream& out, const train& t);

	int departure_station() const;
	int destination_station() const;
	const bool* Intermediate_stations() const;

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
	int m_departure_station;
	// станция назначения
	int m_destination_station;
	// промежуточные станции
	bool m_Intermediate_stations[count_of_Intermediate_stations];
};

