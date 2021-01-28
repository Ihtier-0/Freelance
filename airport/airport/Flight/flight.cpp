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
    Q_ASSERT(m_flightNumber > 0);
    Q_ASSERT(m_numberFreeSeatsInCabin >= 0);
    Q_ASSERT(m_departureTime < m_arrivalTime);
}

qint64 Flight::flightNumber() const
{
    return m_flightNumber;
}

QString Flight::destination() const
{
    return m_destination;
}

QDateTime Flight::departureTime() const
{
    return m_departureTime;
}

QDateTime Flight::arrivalTime() const
{
    return m_arrivalTime;
}

qint64 Flight::numberFreeSeatsInCabin() const
{
    return m_numberFreeSeatsInCabin;
}

QString Flight::toQString()
{
    return QString::number(m_flightNumber) + ' ' + m_destination + ' '
            + m_departureTime.toString() + ' ' + m_arrivalTime.toString() + ' ' + QString::number(m_numberFreeSeatsInCabin);
}

bool operator==(const Flight& left, const Flight& right)
{
    return left.m_arrivalTime == right.m_arrivalTime &&
            left.m_departureTime == right.m_departureTime &&
            left.m_destination == right.m_destination &&
            left.m_flightNumber == right.m_flightNumber &&
            left.m_numberFreeSeatsInCabin == right.m_numberFreeSeatsInCabin;
}

bool operator!=(const Flight& left, const Flight& right)
{
    return !(left == right);
}

