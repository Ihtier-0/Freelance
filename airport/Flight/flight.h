#ifndef FLIGHT_H
#define FLIGHT_H

#include <QDateTime>
#include <QString>

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
};

#endif // FLIGHT_H
