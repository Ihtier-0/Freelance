#ifndef FLIGHT_H
#define FLIGHT_H

#include <QDateTime>
#include <QString>
#include <iostream>

// класс хранящий информацию о рейсе
class Flight
{
public:
    Flight();
    Flight(const qint64& a_flightNumber,
           const QString& a_destination,
           const QDateTime& a_departureTime,
           const QDateTime& a_arrivalTime,
           const qint64& a_numberFreeSeatsInCabin);

    qint64 flightNumber() const;
    QString destination() const;
    QDateTime departureTime() const;
    QDateTime arrivalTime() const;
    qint64 numberFreeSeatsInCabin() const;

    QString toQString();
    friend std::ostream& operator<<(std::ostream& out, const Flight& f)
    {
        out << f.m_flightNumber << ' ' << f.m_destination.toStdString()
            << ' ' << f.m_departureTime.toString().toStdString()
            << ' ' << f.m_arrivalTime.toString().toStdString()
            << ' ' << f.m_numberFreeSeatsInCabin;

        return out;
    }
private:
    // номер рейса
    qint64 m_flightNumber;
    // пункт назначения
    QString m_destination;
    // время вылета
    QDateTime m_departureTime;
    // время прибытия
    QDateTime m_arrivalTime;
    // количество свободных мест в салоне
    qint64 m_numberFreeSeatsInCabin;

    friend bool operator==(const Flight& left, const Flight& right);
    friend bool operator!=(const Flight& left, const Flight& right);
};

#endif // FLIGHT_H
