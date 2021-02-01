#include "flight.h"

Flight::Flight() : m_flightNumber(-1), m_destination(), m_departureTime(), m_arrivalTime(), m_numberFreeSeatsInCabin(-1) {}

Flight::Flight(const Flight &f)
    : m_flightNumber(f.m_flightNumber), m_destination(f.m_destination),
      m_departureTime(f.m_departureTime), m_arrivalTime(f.m_arrivalTime),
      m_numberFreeSeatsInCabin(f.m_numberFreeSeatsInCabin) {}

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

QString Flight::toQString() const
{
    return QString::number(m_flightNumber) + ' '
            + m_destination + ' '
            + m_departureTime.toString() + ' '
            + m_arrivalTime.toString() + ' '
            + QString::number(m_numberFreeSeatsInCabin);
}

Flight &Flight::operator=(const Flight &x)
{
    m_flightNumber = x.m_flightNumber;
    m_destination = x.m_destination;
    m_departureTime = x.departureTime();
    m_arrivalTime = x.m_arrivalTime;
    m_numberFreeSeatsInCabin = x.m_numberFreeSeatsInCabin;

    return *this;
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

std::ostream& operator<<(std::ostream& out, const Flight& f)
{
    out << f.toQString().toStdString();

    return out;
}

std::istream &operator>>(std::istream& is, Flight& f)
{
    std::string destination;

    is >> f.m_flightNumber >> destination;

    f.m_destination = destination.c_str();

    std::string tmp1, tmp2, tmp3, tmp4, tmp5;
    is >> tmp1 >> tmp2 >> tmp3 >> tmp4 >> tmp5;

    QString dateTime((tmp1 + ' ' + tmp2 + ' ' + tmp3 + ' ' + tmp4 + ' ' + tmp5).c_str());
    f.m_departureTime = QDateTime::fromString(dateTime);

    is >> tmp1 >> tmp2 >> tmp3 >> tmp4 >> tmp5;
    dateTime = (tmp1 + ' ' + tmp2 + ' ' + tmp3 + ' ' + tmp4 + ' ' + tmp5).c_str();

    f.m_arrivalTime = QDateTime::fromString(dateTime);

    is >> f.m_numberFreeSeatsInCabin;

    return is;
}
