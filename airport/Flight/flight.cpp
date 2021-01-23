#include "flight.h"

Flight::Flight() : m_flightNumber(-1), m_destination(), m_departureTime(), m_arrivalTime(), m_numberFreeSeatsInCabin(-1) {}

Flight::Flight(const qint64 &a_flightNumber,
               const QString &a_destination,
               const QDateTime &a_departureTime,
               const QDateTime &a_arrivalTime,
               const qint64 &a_numberFreeSeatsInCabin)
    : m_flightNumber(a_flightNumber), m_destination(a_destination),
      m_departureTime(a_departureTime), m_arrivalTime(a_arrivalTime),
      m_numberFreeSeatsInCabin(a_numberFreeSeatsInCabin)
{
    Q_ASSERT(a_flightNumber < 0);
    Q_ASSERT(a_numberFreeSeatsInCabin < 0);
}
