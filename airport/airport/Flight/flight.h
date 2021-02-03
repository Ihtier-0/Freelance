#ifndef FLIGHT_H
#define FLIGHT_H

#include <QDateTime>
#include <string>
#include <iostream>

// класс хранящий информацию о рейсе
class Flight
{
public:
    // конструктор по умолчанию
    Flight();
    // конструктор копирования
    Flight(const Flight& f);
    // конструктор принимающий все поля класса
    Flight(const qint64& a_flightNumber,
           const QString& a_destination,
           const QDateTime& a_departureTime,
           const QDateTime& a_arrivalTime,
           const qint64& a_numberFreeSeatsInCabin);

    // геттер на каждое поле
    qint64 flightNumber() const;
    QString destination() const;
    QDateTime departureTime() const;
    QDateTime arrivalTime() const;
    qint64 numberFreeSeatsInCabin() const;

    // запись рейса в строку
    QString toQString() const;

    // перегрузка оператора ввода/вывода
    friend std::ostream &operator<<(std::ostream& out, const Flight& f);
    friend std::istream &operator>>(std::istream& is, Flight& f);

    // перегрузка оператора присваивания
    Flight& operator=(const Flight& x);

    // перегрузка оператора сравнения
    friend bool operator==(const Flight& left, const Flight& right);
    friend bool operator!=(const Flight& left, Flight& right);
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
